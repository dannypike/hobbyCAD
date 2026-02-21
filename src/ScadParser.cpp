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

    // ---- statement ----
    std::any visitStatement(OpenSCADParser::StatementContext* ctx) override {
        return visit(ctx->functionCall());
    }

    // ---- functionCall ----
    std::any visitFunctionCall(OpenSCADParser::FunctionCallContext* ctx) override {
        std::string name = ctx->ID()->getText();

        if (name == "cube") {
            parseCube(ctx);
        } else {
            model.warnings.push_back(
                "Line " + std::to_string(ctx->getStart()->getLine())
                + ": unsupported statement '" + name + "' (skipped)");
        }
        return {};
    }

private:
    // ---- cube() argument handling ----

    // Extract a double from a NumberExpr context
    static double getNumber(OpenSCADParser::ExpressionContext* expr) {
        return std::stod(expr->getText());
    }

    // Extract a bool from a BoolExpr context
    static bool getBool(OpenSCADParser::ExpressionContext* expr) {
        return expr->getText() == "true";
    }

    void parseCube(OpenSCADParser::FunctionCallContext* ctx) {
        ScadCube cube;
        auto* argList = ctx->argumentList();
        if (!argList) {
            model.warnings.push_back(
                "Line " + std::to_string(ctx->getStart()->getLine())
                + ": cube() with no arguments");
            return;
        }

        auto args = argList->argument();

        for (auto* arg : args) {
            // Named argument:  center = true/false
            if (auto* named = dynamic_cast<OpenSCADParser::NamedArgContext*>(arg)) {
                std::string paramName = named->ID()->getText();
                if (paramName == "center") {
                    cube.center = getBool(named->expression());
                }
            }
            // Positional argument: the size
            else if (auto* positional = dynamic_cast<OpenSCADParser::PositionalArgContext*>(arg)) {
                auto* expr = positional->expression();

                // cube([x, y, z])
                if (auto* vecExpr = dynamic_cast<OpenSCADParser::VectorExprContext*>(expr)) {
                    auto* vec = vecExpr->vector();
                    auto components = vec->expression();
                    if (components.size() >= 3) {
                        cube.dx = getNumber(components[0]);
                        cube.dy = getNumber(components[1]);
                        cube.dz = getNumber(components[2]);
                    } else if (components.size() == 1) {
                        double sz = getNumber(components[0]);
                        cube.dx = cube.dy = cube.dz = sz;
                    } else {
                        model.warnings.push_back(
                            "Line " + std::to_string(ctx->getStart()->getLine())
                            + ": cube() vector needs 1 or 3 components");
                        return;
                    }
                }
                // cube(size)
                else if (dynamic_cast<OpenSCADParser::NumberExprContext*>(expr)) {
                    double sz = getNumber(expr);
                    cube.dx = cube.dy = cube.dz = sz;
                }
                else {
                    model.warnings.push_back(
                        "Line " + std::to_string(ctx->getStart()->getLine())
                        + ": unexpected argument type in cube()");
                    return;
                }
            }
        }

        model.cubes.push_back(cube);
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
