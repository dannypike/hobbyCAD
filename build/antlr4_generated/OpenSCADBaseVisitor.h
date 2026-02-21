
// Generated from /home/dan/Projects/hobbyCAD/grammar/OpenSCAD.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "OpenSCADVisitor.h"


/**
 * This class provides an empty implementation of OpenSCADVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  OpenSCADBaseVisitor : public OpenSCADVisitor {
public:

  virtual std::any visitFile(OpenSCADParser::FileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(OpenSCADParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionCall(OpenSCADParser::FunctionCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgumentList(OpenSCADParser::ArgumentListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamedArg(OpenSCADParser::NamedArgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPositionalArg(OpenSCADParser::PositionalArgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNumberExpr(OpenSCADParser::NumberExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBoolExpr(OpenSCADParser::BoolExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVectorExpr(OpenSCADParser::VectorExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBoolLiteral(OpenSCADParser::BoolLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVector(OpenSCADParser::VectorContext *ctx) override {
    return visitChildren(ctx);
  }


};

