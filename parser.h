#ifndef _PARSER_H_
#define _PARSER_H_
#include "lexer.h"
#include "string.h"
//for future assignments leave it as it is

class parser
{
    lexer _lexer;
    token _look_ahead;

    void start();
    void main_fun_start();
    void main_fun();
    void statments();
    void dec_ini_assi();
    void declaration();
    void ini_assi_statment();
    void initialization();
    void input();
    void output();
    void output_1();
    void loop();
    void selection();
    void elif_selection();
    void else_selection();
    void return_statment();
    void assignment_expression();
    void relational_expression();
    void equal_to_expression();
    void greater_less_expression();
    void greater_less_expression_1();
    void arithmatic_expression();
    void add_sub_expression();
    void mul_div_expression();
    void mul_div_expression_1();
    void id();


public:
    void syntax_error();
    token expect(TokenType expected_type);
    parser(const char filename[]);
    void readAndPrintAllInput();
    void resetPointer();
    void parse();
    void get_next_token();
    /*Terminal functions goes here use peek and expect*/
    /*use TokenType:: for token names for example
        expect(TokenType::ASSIGN);   //example function call
      */
	//all your parser function goes here
};
#endif
