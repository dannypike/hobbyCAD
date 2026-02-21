
// Generated from /home/dan/Projects/hobbyCAD/grammar/OpenSCAD.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "OpenSCADParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by OpenSCADParser.
 */
class  OpenSCADVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by OpenSCADParser.
   */
    virtual std::any visitFile(OpenSCADParser::FileContext *context) = 0;

    virtual std::any visitStatement(OpenSCADParser::StatementContext *context) = 0;

    virtual std::any visitFunctionCall(OpenSCADParser::FunctionCallContext *context) = 0;

    virtual std::any visitArgumentList(OpenSCADParser::ArgumentListContext *context) = 0;

    virtual std::any visitNamedArg(OpenSCADParser::NamedArgContext *context) = 0;

    virtual std::any visitPositionalArg(OpenSCADParser::PositionalArgContext *context) = 0;

    virtual std::any visitNumberExpr(OpenSCADParser::NumberExprContext *context) = 0;

    virtual std::any visitBoolExpr(OpenSCADParser::BoolExprContext *context) = 0;

    virtual std::any visitVectorExpr(OpenSCADParser::VectorExprContext *context) = 0;

    virtual std::any visitBoolLiteral(OpenSCADParser::BoolLiteralContext *context) = 0;

    virtual std::any visitVector(OpenSCADParser::VectorContext *context) = 0;


};

