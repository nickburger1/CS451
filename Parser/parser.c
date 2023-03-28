/*
[x] My program compiles without error on the csis machine.
[x] The lexical analyzer successfully recognizes floating point number.
[x] The lexical analyzer successfully recognizes all the new key words if, while, and else.
[x] The lexical analyzer successfully recognizes the comparison operators as new tokens.
[x] My program prints the proper messages for newly added tokens and keywords
[x] My program implements functions for each non-terminals
[x] I prepared for a typescript file (hw3-lastname.txt) that includes the compilation, source code listing, and the run result for all four input files.
*/

/* parser.c - a lexical analyzer system for simple arithmetic expressions */
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE* in_fp, * fopen();
void addChar();
void getChar();
void getNonBlank();
int lex();
void expr();
void term();
void factor();
void stmts();
void stmt();
void whilestmt();
void asgnstmt();
void booexpr();
void comp();
void ifstmt();
void forstmt();
void err(char*);
/* Character classes */
#define LETTER 0
#define DIGIT 1
#define FLOAT 2
#define UNKNOWN 99
/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define FLOAT_LIT 27
#define SEMI_COLON 28
#define LEFT_CURLY 29
#define RIGHT_CURLY 30
#define IF 31
#define WHILE 32
#define FOR 33
#define LESS 34
#define GREATER 35
#define ELSE 36

/******************************************************/
/* main driver */
int main(int argc, char* argv[])
{
    /* Open the input data files and process its contents */
    char filename[] = "in1.txt";
    int i;
    for (i = 1; i<6; i++) {
        filename[2] = i + '0';
        printf("\nFile Name: %s\n", filename);
        if ((in_fp = fopen(filename, "r"))==NULL)
            printf("ERROR - cannot open %s \n", filename);
        else {
            nextChar = 0;
            stmts();
            fclose(in_fp);
        }
    }
    return 0;
}

/*****************************************************/
/* lookup - a function to lookup operators and parentheses
 * and return the token */
int lookup(char ch)
{
    switch (ch) {
    case '(':
        addChar();
        nextToken = LEFT_PAREN;
        break;
    case ')':
        addChar();
        nextToken = RIGHT_PAREN;
        break;
    case '+':
        addChar();
        nextToken = ADD_OP;
        break;
    case '-':
        addChar();
        nextToken = SUB_OP;
        break;
    case '*':
        addChar();
        nextToken = MULT_OP;
        break;
    case '/':
        addChar();
        nextToken = DIV_OP;
        break;
    case '=':
        addChar();
        nextToken = ASSIGN_OP;
        break;
    case '<':
        addChar();
        nextToken = LESS;
        break;
    case '>':
        addChar();
        nextToken = GREATER;
        break;
    case '{':
        addChar();
        nextToken = LEFT_CURLY;
        break;
    case '}':
        addChar();
        nextToken = RIGHT_CURLY;
        break;
    case ';':
        addChar();
        nextToken = SEMI_COLON;
        break;
    default:
        addChar();
        nextToken = EOF;
        break;
    }
    return nextToken;
}
/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar()
{
    if (lexLen<=98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    }
    else
        printf("Error - lexeme is too long \n");
}
/*****************************************************/
/* getChar - a function to get the next character of
 * input and determine its character class */
void getChar()
{
    if ((nextChar = getc(in_fp))!=EOF) {
        if (isalpha(nextChar)) {
            charClass = LETTER;
        }else if (isdigit(nextChar) && charClass!=FLOAT){
           charClass = DIGIT; 
        }else if (isdigit(nextChar) && charClass==FLOAT){
            charClass = FLOAT;
        }else if (nextChar=='.') {
            if (charClass==DIGIT){
                charClass = FLOAT;
            }else if (charClass!=FLOAT){
                charClass = FLOAT;
            }else if (charClass==FLOAT){
                charClass = UNKNOWN;
            }      
        }else{
            charClass = UNKNOWN;
        }   
    }else{
       charClass = EOF; 
    }       
}

/*****************************************************/
/* getNonBlank - a function to call getChar until it
 * returns a non-whitespace character */
void getNonBlank()
{
    while (isspace(nextChar))
        getChar();
}

/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic expressions */
int lex() {
    lexLen = 0;
    getNonBlank();
    switch (charClass) {
        /* Parse identifiers */
    case LETTER:addChar();
        getChar();
        while (charClass==LETTER || charClass==DIGIT) {
            addChar();
            getChar();
        }
        if (!strcmp(lexeme, "if")) {
            nextToken = IF;
            break;
        }
        if (!strcmp(lexeme, "while")) {
            nextToken = WHILE;
            break;
        }
        if (!strcmp(lexeme, "for")) {
            nextToken = FOR;
            break;
        }
        if (!strcmp(lexeme, "else")) {
            nextToken = ELSE;
            break;
        }
        nextToken = IDENT;
        break;

        /* Parse integer literals */
    case FLOAT:
    case DIGIT:addChar();
        bool isFloat = false;
        getChar();
        while (charClass==DIGIT || charClass==FLOAT) {
            isFloat = charClass==FLOAT;
            addChar();
            getChar();
        }
        if (isFloat)
            nextToken = FLOAT_LIT;
        else
            nextToken = INT_LIT;
        break;
        /* Parentheses and operators */
    case UNKNOWN:lookup(nextChar);
        getChar();
        break;
        /* EOF */
    case EOF:nextToken = EOF;
        lexeme[0] = 'E';
        lexeme[1] = 'O';
        lexeme[2] = 'F';
        lexeme[3] = 0;
        break;
    } /* End of switch */

    printf("Next token is: %d, Next lexeme is %s \n",
            nextToken, lexeme);
    return nextToken;
} /* End of function lex */

/* Parses strings in the language generated by the rule:
 *    <expr> -> <term> {(+ | -) <term>} */
void expr()
{
    printf("Enter <expr>\n");
    /* Parse the first term */
    term();
    /* As long as the next token is + or -, get
 *     the next token and parse the next term */
    while (nextToken==ADD_OP || nextToken==SUB_OP) {
        lex();
        term();
    }
    printf("Exit <expr>\n");
}

/* Parses strings in the language generated by the rule:
 *    <term> -> <factor> {(* | /) <factor>) */
void term()
{
    printf("Enter <term>\n");
    /* Parse the first factor */
    factor();
    /* As long as the next token is * or /, get the
 *     next token and parse the next factor */
    while (nextToken==MULT_OP || nextToken==DIV_OP) {
        lex();
        factor();
    }
    printf("Exit <term>\n");
}

/* Parses strings in the language generated by the rule:
 *     <factor> -> id | int_constant | ( <expr> ) */
void factor()
{
    printf("Enter <factor>\n");
    /* Determine which RHS */
    if (nextToken==IDENT || nextToken==INT_LIT || nextToken==FLOAT_LIT) {
        printf("ID or Literal\n");
        /* Get the next token */
        lex();
    }
        /* If the RHS is ( <expr>), call lex to pass over the left parenthesis,
         *        call expr, and check for the right parenthesis */
    else {
        if (nextToken==LEFT_PAREN) {
            lex();
            expr();
            if (nextToken==RIGHT_PAREN)
                lex();
            else
                err("Factor, no right parentesis");
        } /* End of if (nextToken == ... */
            /* It was not an id, an integer literal, or a left parenthesis */
        else
            err("Factor, no id, left or right parenthesis");
    } /* End of else */
    printf("Exit <factor>\n");
}


//new functions
void err(char* error){
    /*
    * Function to display an error message if a criteria is not met
    * After message is displayed program will exit
    */
    printf("Error: %s", error);
    exit(-1);
}

//<stmts> → <stmt> {; <stmt> } 
void stmts(){
    /*
    * Function first calls stmt and check if it is repeating or not
    * An example could be <stmt> or <stmt>;<stmt>;<stmt>;<stmt>;...
    */
    printf("Enter <stmts>\n");
    do {
        stmt();
    }
    while(nextToken == SEMI_COLON);

    if (nextToken!=EOF && nextToken!=RIGHT_CURLY){
        err("Missing ; or }\n");
    }
        
    printf("Exit <stmts>\n");
}

//<stmt> → <ifstmt> | <whilestmt> | <forstmt> | <asgnstmt>
void stmt(){
    /*
    * Function that redirects to one of the following functions:
    * ifstmt, whilestmt, forstmt, asgnstmt
    */
    printf("Enter <stmt>\n");
    if (nextChar==0)
        getChar();   
    lex();   
    if (nextToken==IF) {     
        ifstmt();
    }
    else if (nextToken==WHILE) {
        whilestmt();
    }
    else if (nextToken==FOR) {
        forstmt();
    }
    else if (nextToken==IDENT) {
        asgnstmt();
    }
    printf("Exit <stmt>\n");
}

//<ifstmt> → if (<boolexpr>) ‘{‘ <stmts> ‘}’ [ else ‘{‘ <stmts> ‘}’ ]
void ifstmt(){
    /*
    * Function to check if the if statement has the correct syntax
    * utilizing the booexpr and stmts functions
    */
    printf("Enter <ifstmt>\n");
    lex();

    if (nextToken==LEFT_PAREN) {
        booexpr();
        lex();
        if (nextToken!=RIGHT_PAREN)
            err("Missing )\n");
    }
    lex();
    if (nextToken==LEFT_CURLY) {
        stmts();
        if (nextToken==RIGHT_CURLY) {
            lex();
            if (nextToken==ELSE) {
                lex();
                if (nextToken==LEFT_CURLY) {
                    stmts();
                    if (nextToken!=RIGHT_CURLY){
                        err("Missing }\n");
                    }else {
                        lex();
                        printf("Exit <ifstmnt>\n");
                        return;
                    }
                }else {
                    err("Missing {\n");
                }
            }else {
                printf("Exit <ifstmnt>\n");
                return;
            }
        }else{
           err("Missing }\n"); 
        }      
    }else {
        err("Missing {\n");
    }
}

//<whilestmt> → while (<boolexpr>) ‘{‘ <stmts> ‘}’
void whilestmt(){
    /*
    * Function to check if the while statement has the correct syntax
    * utilizing the booexpr and stmts functions
    */
    printf("Enter <whilestmt>\n");
    lex();
    if (nextToken==LEFT_PAREN) {
        booexpr();
        lex();
        if (nextToken!=RIGHT_PAREN)
            err("While statement, no valid boolean expression\n");
    }
    else {
        err("While statement, no valid boolean expression\n");
    }
    lex();
    if (nextToken==LEFT_CURLY) {
        stmts();
        if (nextToken==RIGHT_CURLY) {
            lex();
        }
        else
            err("While statement not closed by right curly braces\n");
        printf("Exit <whilestmnt>\n");
        return;
    }
    else {
        err("While statement not started with left curly braces\n");
    }
    printf("Exit <whilestmt>\n");
}

//<forstmt> → for (<asgnstmt>; <boolexpr>; <asgnstmt>) ‘{‘ <stmts> ‘}’
void forstmt(){
    /*
    * Function to check if the for statement has the correct syntax
    * utilizing the asgnstmt, booexpr and stmts functions
    */
    printf("Enter <forstmnt>\n");
    lex();
    if (nextToken==LEFT_PAREN) {
        lex();
        if (nextToken==IDENT) {
            asgnstmt();
        }else {
            err("Missing ID\n");
        }
        if (nextToken==SEMI_COLON) {
            booexpr();
            lex();
            if (nextToken==SEMI_COLON) {
                lex();
                if (nextToken==IDENT) {
                    asgnstmt();
                }else {
                    err("Missing ID\n");
                }
                if (nextToken==RIGHT_PAREN) {
                    lex();
                    if (nextToken==LEFT_CURLY) {
                        stmts();
                        if (nextToken==RIGHT_CURLY) {
                            lex();
                        }else{
                           err("Missing }\n"); 
                        }   
                        printf("Exit <forstmnt>\n");
                        return;
                    }else {
                        err("Missing {\n");
                    }
                }else {
                    err("Missing )\n");
                }
            }else {
                err("Missing ;\n");
            }
        }else {
            err("Missing ;\n");
        }
    }else {
        err("Missing (\n");
    }
}

//<asgnstmt> → id = <expr>
void asgnstmt(){
    /*
    * Function to check if the assign statement has the correct syntax
    * utilizing the expr function
    */
    printf("Enter <asgnstmnt>\n");
    getChar();
    lex();
    if (nextToken==ASSIGN_OP) {
        lex();
        expr();
    }else {
        err("Missing =\n");
    }
    printf("Exit <asgnstmnt>\n");
}

//<booexpr> → id <comp> int_constant
void booexpr(){
    /*
    * Function to check if the boolean expression has the correct syntax
    * utilizing the comp function
    */
    printf("Enter <booexpr>\n");
    lex();
    if (nextToken==IDENT) {
        comp();
        lex();
        if (nextToken==INT_LIT) {
            printf("Exit <booexpr>\n");
            return;
        }else{
            err("Missing literal\n");
        }     
    }else{
        err("Missing ID\n");
    }     
}

//<comp> → < | >
void comp(){
    /*
    * Function to check if the comp statement has the correct syntax
    * check for either < or >
    */
    printf("Enter <comp>\n");
    lex();
    if (nextToken==LESS || nextToken==GREATER) {
        printf("Exit <comp>\n");
        return;
    }else {
        err("Missing < or >\n");
    }     
}