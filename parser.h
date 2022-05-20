#ifndef _PARSER_H_
#define _PARSER_H_
#include "lexer.h"
#include "string.h"
#include "SymbolTable.h"
#include <stack>
//for future assignments leave it as it is

class parser
{
    lexer _lexer;
    token _look_ahead;
    SymbolTable _symbol_table;
    int temp_variable_count = 0;
    int _line_no = 0;
    string TAD_code[100];

    void start();
    void main_fun_start();
    void main_fun();
    void statments();
    void dec_ini_assi(string& value, string& type, string& id_v);
    void declaration();
    void ini_assi_statment(string& value, string& type, string& id_v);
    void initialization();
    void input();
    void output();
    void output_1();
    void loop();
    void selection();
    void elif_selection(string& re_e, string s_next);
    void else_selection(string &re_e,string s_next);
    void return_statment();
    void assignment_expression();
    void relational_expression(string& id_v, string& re_s, string &re_e);
    void equal_to_expression(string& id_v, string& re_s, string &re_e);
    void greater_less_expression(string& id_v, string& re_s, string &re_e);
    void greater_less_expression_1(string& ro_v, string& id_v);
    void arithmatic_expression(string& id_v);
    void add_sub_expression(string &a_s_e_v);
    void mul_div_expression(string &id_v);
    void mul_div_expression_1(string &m_d_e_v);
    void id(string &id_v);

    string temp_variable();
    void emit(string);
    void backpatch(string);
    void print_TAC();


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
