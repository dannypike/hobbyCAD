grammar OpenSCAD;

// ---------- Parser rules ----------

file
    : statement* EOF
    ;

statement
    : functionCall SEMI
    ;

functionCall
    : ID LPAREN argumentList? RPAREN
    ;

argumentList
    : argument ( COMMA argument )*
    ;

argument
    : ID EQUALS expression      # NamedArg
    | expression                # PositionalArg
    ;

expression
    : NUMBER                    # NumberExpr
    | boolLiteral               # BoolExpr
    | vector                    # VectorExpr
    ;

boolLiteral
    : TRUE
    | FALSE
    ;

vector
    : LBRACKET expression ( COMMA expression )* RBRACKET
    ;

// ---------- Lexer rules ----------

TRUE     : 'true'  ;
FALSE    : 'false' ;

ID       : [a-zA-Z_] [a-zA-Z0-9_]* ;
NUMBER   : '-'? [0-9]+ ( '.' [0-9]* )? ( [eE] [+-]? [0-9]+ )? ;

SEMI     : ';' ;
COMMA    : ',' ;
LPAREN   : '(' ;
RPAREN   : ')' ;
LBRACKET : '[' ;
RBRACKET : ']' ;
EQUALS   : '=' ;

LINE_COMMENT  : '//' ~[\r\n]* -> skip ;
BLOCK_COMMENT : '/*' .*? '*/'  -> skip ;
WS            : [ \t\r\n]+     -> skip ;
