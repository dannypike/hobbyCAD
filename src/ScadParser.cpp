#include "ScadParser.h"

#include "antlr4-runtime.h"
#include "OpenSCADLexer.h"
#include "OpenSCADParser.h"
#include "OpenSCADBaseVisitor.h"

#include <fstream>
#include <sstream>

// ---------------------------------------------------------------------------
// Custom error listener — collects parse errors into ScadModel::warnings
// ---------------------------------------------------------------------------
class ScadErrorListener : public antlr4::BaseErrorListener {
public:
    std::vector<std::string>* warnings = nullptr;

    void syntaxError(antlr4::Recognizer* /*recognizer*/,
                     antlr4::Token* /*offendingSymbol*/,
                     size_t line, size_t col,
                     const std::string& msg,
                     std::exception_ptr /*e*/) override
    {
        if (warnings) {
            warnings->push_back("Line " + std::to_string(line)
                + ":" + std::to_string(col) + " " + msg);
        }
    }
};

// ---------------------------------------------------------------------------
// Visitor that walks the ANTLR4 parse tree and builds a ScadModel
// ---------------------------------------------------------------------------
class ScadBuildVisitor : public OpenSCADBaseVisitor {
public:
    ScadModel model;

    // ---- file ----
    std::any visitFile(OpenSCADParser::FileContext* ctx) override {
        for (auto* stmt : ctx->statement())
            visit(stmt);
        return {};
    }

    // ---- PrimitiveStatement ----
    std::any visitPrimitiveStatement(OpenSCADParser::PrimitiveStatementContext* ctx) override {
        auto node = parseFunctionCall(ctx->functionCall());
        if (node) model.nodes.push_back(node);
        return {};
    }

    // ---- TransformStatement ----
    std::any visitTransformStatement(OpenSCADParser::TransformStatementContext* ctx) override {
        auto node = parseTransformCall(ctx->transformCall());
        if (node) model.nodes.push_back(node);
        return {};
    }

private:
    // ---- helpers ----

    static double getNumber(OpenSCADParser::ExpressionContext* expr) {
        return std::stod(expr->getText());
    }

    static bool getBool(OpenSCADParser::ExpressionContext* expr) {
        return expr->getText() == "true";
    }

    // Parse a [x, y, z] vector argument; returns false on failure
    bool parseVec3(OpenSCADParser::ArgumentListContext* argList,
                   size_t line, double& x, double& y, double& z)
    {
        if (!argList || argList->argument().empty()) {
            model.warnings.push_back("Line " + std::to_string(line)
                + ": transform requires a vector argument");
            return false;
        }
        auto* arg = argList->argument(0);
        OpenSCADParser::ExpressionContext* expr = nullptr;
        if (auto* pos = dynamic_cast<OpenSCADParser::PositionalArgContext*>(arg))
            expr = pos->expression();
        if (!expr) {
            model.warnings.push_back("Line " + std::to_string(line)
                + ": transform argument must be positional");
            return false;
        }
        if (auto* vecExpr = dynamic_cast<OpenSCADParser::VectorExprContext*>(expr)) {
            auto comps = vecExpr->vector()->expression();
            if (comps.size() >= 3) {
                x = getNumber(comps[0]);
                y = getNumber(comps[1]);
                z = getNumber(comps[2]);
                return true;
            }
        }
        model.warnings.push_back("Line " + std::to_string(line)
            + ": transform needs a 3-element vector");
        return false;
    }

    // Collect child nodes from a block
    std::vector<std::shared_ptr<ScadNode>>
    parseBlock(OpenSCADParser::BlockContext* block)
    {
        std::vector<std::shared_ptr<ScadNode>> children;
        for (auto* stmt : block->statement()) {
            std::shared_ptr<ScadNode> child;
            if (auto* prim = dynamic_cast<OpenSCADParser::PrimitiveStatementContext*>(stmt)) {
                child = parseFunctionCall(prim->functionCall());
            } else if (auto* tr = dynamic_cast<OpenSCADParser::TransformStatementContext*>(stmt)) {
                child = parseTransformCall(tr->transformCall());
            }
            if (child) children.push_back(child);
        }
        return children;
    }

    // ---- functionCall → primitive node ----
    std::shared_ptr<ScadNode>
    parseFunctionCall(OpenSCADParser::FunctionCallContext* ctx)
    {
        std::string name = ctx->ID()->getText();
        size_t line = ctx->getStart()->getLine();

        if (name == "cube") {
            return parseCube(ctx);
        }
        model.warnings.push_back("Line " + std::to_string(line)
            + ": unsupported primitive '" + name + "' (skipped)");
        return nullptr;
    }

    // ---- transformCall → transform node ----
    std::shared_ptr<ScadNode>
    parseTransformCall(OpenSCADParser::TransformCallContext* ctx)
    {
        std::string name = ctx->ID()->getText();
        size_t line = ctx->getStart()->getLine();

        if (name == "translate" || name == "rotate") {
            double x = 0, y = 0, z = 0;
            if (!parseVec3(ctx->argumentList(), line, x, y, z))
                return nullptr;

            auto node = std::make_shared<ScadNode>();
            node->type = (name == "translate") ? ScadNodeType::Translate
                                                : ScadNodeType::Rotate;
            node->tx = x; node->ty = y; node->tz = z;
            node->children = parseBlock(ctx->block());
            return node;
        }

        model.warnings.push_back("Line " + std::to_string(line)
            + ": unsupported transform '" + name + "' (skipped)");
        return nullptr;
    }

    // ---- cube() ----
    std::shared_ptr<ScadNode>
    parseCube(OpenSCADParser::FunctionCallContext* ctx)
    {
        ScadCube cube;
        size_t line = ctx->getStart()->getLine();
        auto* argList = ctx->argumentList();
        if (!argList) {
            model.warnings.push_back("Line " + std::to_string(line)
                + ": cube() with no arguments");
            return nullptr;
        }

        for (auto* arg : argList->argument()) {
            if (auto* named = dynamic_cast<OpenSCADParser::NamedArgContext*>(arg)) {
                if (named->ID()->getText() == "center")
                    cube.center = getBool(named->expression());
            } else if (auto* pos = dynamic_cast<OpenSCADParser::PositionalArgContext*>(arg)) {
                auto* expr = pos->expression();
                if (auto* vecExpr = dynamic_cast<OpenSCADParser::VectorExprContext*>(expr)) {
                    auto comps = vecExpr->vector()->expression();
                    if (comps.size() >= 3) {
                        cube.dx = getNumber(comps[0]);
                        cube.dy = getNumber(comps[1]);
                        cube.dz = getNumber(comps[2]);
                    } else if (comps.size() == 1) {
                        double sz = getNumber(comps[0]);
                        cube.dx = cube.dy = cube.dz = sz;
                    } else {
                        model.warnings.push_back("Line " + std::to_string(line)
                            + ": cube() vector needs 1 or 3 components");
                        return nullptr;
                    }
                } else if (dynamic_cast<OpenSCADParser::NumberExprContext*>(expr)) {
                    double sz = getNumber(expr);
                    cube.dx = cube.dy = cube.dz = sz;
                } else {
                    model.warnings.push_back("Line " + std::to_string(line)
                        + ": unexpected argument type in cube()");
                    return nullptr;
                }
            }
        }

        auto node = std::make_shared<ScadNode>();
        node->type = ScadNodeType::Cube;
        node->cube = cube;
        return node;
    }
};

// ---------------------------------------------------------------------------
// Public API
// ---------------------------------------------------------------------------

ScadModel parseScadSource(const std::string& source) {
    antlr4::ANTLRInputStream input(source);
    OpenSCADLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    OpenSCADParser parser(&tokens);

    // Redirect syntax errors into warnings
    ScadErrorListener errorListener;
    ScadModel resultModel;
    errorListener.warnings = &resultModel.warnings;

    lexer.removeErrorListeners();
    lexer.addErrorListener(&errorListener);
    parser.removeErrorListeners();
    parser.addErrorListener(&errorListener);

    // Parse
    auto* tree = parser.file();

    // Visit
    ScadBuildVisitor visitor;
    visitor.model.warnings = std::move(resultModel.warnings);
    visitor.visit(tree);

    return std::move(visitor.model);
}

ScadModel parseScadFile(const std::string& path) {
    std::ifstream ifs(path);
    if (!ifs.is_open()) {
        ScadModel m;
        m.warnings.push_back("Could not open file: " + path);
        return m;
    }
    std::ostringstream ss;
    ss << ifs.rdbuf();
    return parseScadSource(ss.str());
}
