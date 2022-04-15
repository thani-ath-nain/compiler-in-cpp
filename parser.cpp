#include "parser.h"

void parser::syntax_error()
{
    cout << "SYNTAX ERROR\n";
    exit(1);
}
token parser::expect(TokenType expected_type)
{
    token t = _lexer.getNextToken();
    if (t.tokenType != expected_type)
        syntax_error();
    return t;
}
parser::parser(const char filename[])
{
    _lexer = lexer(filename);
    _look_ahead = _lexer.getNextToken();
    start();
}
void parser::readAndPrintAllInput() //read and print allinputs (provided)
{
    token t;
    t = _lexer.getNextToken();
    while (t.tokenType != TokenType::END_OF_FILE)
    {
        t.Print();
        t = _lexer.getNextToken();
    }
}
void parser::resetPointer()
{
    _lexer.resetPointer();
}
void parser::parse()
{

}
void parser::get_next_token()
{
    _look_ahead = _lexer.getNextToken();
    if (_look_ahead.tokenType == TokenType::COMMENT)
        get_next_token();
}

void parser::start()
{
    if (_look_ahead.tokenType == TokenType::COMMENT)
    {
        get_next_token();
        start();
    }
    else if (_look_ahead.tokenType==TokenType::KEYW_FUNC)
    {
        main_fun_start();
        if (_look_ahead.tokenType == TokenType::END_OF_FILE)
        {
            cout << "No Syntax error found" << endl;
        }
        else
        {
            syntax_error();
        }
    }
    else
    {
        syntax_error();
    }
}

void parser::main_fun_start()
{
    if (_look_ahead.tokenType == TokenType::KEYW_FUNC)
    {
        get_next_token();
        if (_look_ahead.tokenType == TokenType::KEYW_INT)
        {
            get_next_token();
            if (_look_ahead.tokenType == TokenType::IDENTIFIER && _look_ahead.lexeme == "main")
            {
                get_next_token();
                if (_look_ahead.tokenType == TokenType::COLON)
                {
                    get_next_token();
                    if (_look_ahead.tokenType == TokenType::BLOCK_START)
                    {
                        get_next_token();
                        main_fun();
                        if (_look_ahead.tokenType == TokenType::BLOCK_END)
                        {
                            get_next_token();
                        }
                        else
                        {
                            syntax_error();
                        }
                    }
                    else
                    {
                        syntax_error();
                    }
                }
                else
                {
                    syntax_error();
                }
            }
            else
            {
                syntax_error();
            }
        }
        else
        {
            syntax_error();
        }
    }
    else
    {
        syntax_error();
    }
}

void parser::main_fun()
{
    statments();
}

void parser::statments()
{
    if (_look_ahead.tokenType == TokenType::COMMENT)
    {
        get_next_token();
        statments();
    }
    else if (_look_ahead.tokenType==TokenType::IDENTIFIER)
    {
        get_next_token();
        dec_ini_assi();
        statments();
    }
    else if (_look_ahead.tokenType == TokenType::KEYW_IN)
    {
        input();
        statments();
    }
    else if (_look_ahead.tokenType == TokenType::KEYW_PRINT|| _look_ahead.tokenType == TokenType::KEYW_PRINTLN)
    {
        output();
        statments();
    }
    else if (_look_ahead.tokenType == TokenType::KEYW_FOR)
    {
        loop();
        statments();
    }
    else if (_look_ahead.tokenType == TokenType::KEYW_IF)
    {
        selection();
        statments();
    }
    else if (_look_ahead.tokenType == TokenType::KEYW_RETURN)
    {
        return_statment();
        statments();
    }
    else
    {
        
    }
}

void parser::dec_ini_assi()
{
    if (_look_ahead.tokenType == TokenType::ASSIGN)
    {
        get_next_token();
        ini_assi_statment();
    }
    else if (_look_ahead.tokenType == TokenType::KEYW_INT || _look_ahead.tokenType == TokenType::KEYW_CHAR)
    {
        declaration();
    }
}

void parser::declaration()
{
    if (_look_ahead.tokenType == TokenType::KEYW_INT || _look_ahead.tokenType == TokenType::KEYW_CHAR)
    {
        get_next_token();
    }
    else
    {
        syntax_error();
    }

    if (_look_ahead.tokenType == TokenType::SEMICOLON)
    {
        get_next_token();
    }
    else
    {
        syntax_error();
    }

}

void parser::ini_assi_statment()
{
    if (_look_ahead.tokenType == TokenType::CHARACTER_LITERAL)
    {
        get_next_token();
        if (_look_ahead.tokenType == TokenType::KEYW_CHAR)
        {
            get_next_token();
            if (_look_ahead.tokenType == TokenType::SEMICOLON)
            {
                get_next_token();
            }
            else
            {
                syntax_error();
            }
        }
        else
        {
            syntax_error();
        }
    }
    else if (_look_ahead.tokenType == TokenType::NUMERIC_LITERAL || _look_ahead.tokenType == TokenType::IDENTIFIER)
    {
        arithmatic_expression();
        initialization();

        if (_look_ahead.tokenType == TokenType::SEMICOLON)
        {
            get_next_token();
        }
        else
        {
            syntax_error();
        }
    }
    else
    {
        syntax_error();
    }

    
}

void parser::initialization()
{
    if (_look_ahead.tokenType == TokenType::KEYW_INT)
    {
        get_next_token();
    }
    else
    {
        
    }
}

void parser::input()
{
    if (_look_ahead.tokenType == TokenType::KEYW_IN)
    {
        get_next_token();
        if (_look_ahead.tokenType == TokenType::IDENTIFIER)
        {
            get_next_token();
            if (_look_ahead.tokenType == TokenType::SEMICOLON)
            {
                get_next_token();
            }
            else
            {
                syntax_error();
            }
        }
        else
        {
            syntax_error();
        }
    }
    else
    {
        syntax_error();
    }
}

void parser::output()
{
    if (_look_ahead.tokenType == TokenType::KEYW_PRINT || _look_ahead.tokenType == TokenType::KEYW_PRINTLN)
    {
        get_next_token();
        output_1();
        if (_look_ahead.tokenType == TokenType::SEMICOLON)
        {
            get_next_token();
        }
        else
        {
            syntax_error();
        }
    }
    else
    {
        syntax_error();
    }

}

void parser::output_1()
{
    if (_look_ahead.tokenType == TokenType::IDENTIFIER || _look_ahead.tokenType == TokenType::STRING_LITERAL || _look_ahead.tokenType == TokenType::CHARACTER_LITERAL)
    {
        get_next_token();
    }
    else
    {
        syntax_error();
    }
}

void parser::loop()
{
    if (_look_ahead.tokenType == TokenType::KEYW_FOR)
    {
        get_next_token();
        if (_look_ahead.tokenType == TokenType::IDENTIFIER || _look_ahead.tokenType == TokenType::NUMERIC_LITERAL)
        {
            assignment_expression();
            if (_look_ahead.tokenType == TokenType::COMMA)
            {
                get_next_token();
                if (_look_ahead.tokenType == TokenType::IDENTIFIER || _look_ahead.tokenType == TokenType::NUMERIC_LITERAL)
                {
                    relational_expression();
                    if (_look_ahead.tokenType == TokenType::COMMA)
                    {
                        get_next_token();
                        if (_look_ahead.tokenType == TokenType::IDENTIFIER || _look_ahead.tokenType == TokenType::NUMERIC_LITERAL)
                        {
                            assignment_expression();
                            if (_look_ahead.tokenType == TokenType::COLON)
                            {
                                get_next_token();
                                if (_look_ahead.tokenType == TokenType::BLOCK_START)
                                {
                                    get_next_token();
                                    statments();
                                    if (_look_ahead.tokenType == TokenType::BLOCK_END)
                                    {
                                        get_next_token();
                                    }
                                    else
                                    {
                                        syntax_error();
                                    }
                                }
                                else
                                {
                                    syntax_error();
                                }
                            }
                            else
                            {
                                syntax_error();
                            }
                        }
                        else
                        {
                            syntax_error();
                        }
                    }
                    else
                    {
                        syntax_error();
                    }
                }
                else
                {
                    syntax_error();
                }
            }
            else
            {
                syntax_error();
            }
        }
        else
        {
            syntax_error();
        }
    }
    else
    {
        syntax_error();
    }
}

void parser::selection()
{
    if (_look_ahead.tokenType == TokenType::KEYW_IF)
    {
        get_next_token();
        if (_look_ahead.tokenType == TokenType::IDENTIFIER || _look_ahead.tokenType == TokenType::NUMERIC_LITERAL)
        {
            relational_expression();
            if (_look_ahead.tokenType == TokenType::COLON)
            {
                get_next_token();
                if (_look_ahead.tokenType == TokenType::BLOCK_START)
                {
                    get_next_token();
                    statments();
                    if (_look_ahead.tokenType == TokenType::BLOCK_END)
                    {
                        get_next_token();
                        if (_look_ahead.tokenType == TokenType::KEYW_ELIF)
                        {
                            elif_selection();
                        }
                        else if (_look_ahead.tokenType == TokenType::KEYW_ELSE)
                        {
                            else_selection();
                        }
                        else
                        {

                        }
                    }
                    else
                    {
                        syntax_error();
                    }
                }
                else
                {
                    syntax_error();
                }
            }
            else
            {
                syntax_error();
            }
        }
        else
        {
            syntax_error();
        }
    }
    else
    {
        syntax_error();
    }
}

void parser::elif_selection()
{
    if (_look_ahead.tokenType == TokenType::KEYW_ELIF)
    {
        get_next_token();
        if (_look_ahead.tokenType == TokenType::IDENTIFIER || _look_ahead.tokenType == TokenType::NUMERIC_LITERAL)
        {
            relational_expression();
            if (_look_ahead.tokenType == TokenType::COLON)
            {
                get_next_token();
                if (_look_ahead.tokenType == TokenType::BLOCK_START)
                {
                    get_next_token();
                    statments();
                    if (_look_ahead.tokenType == TokenType::BLOCK_END)
                    {
                        get_next_token();
                        if (_look_ahead.tokenType == TokenType::KEYW_ELIF)
                        {
                            elif_selection();
                        }
                        else if (_look_ahead.tokenType == TokenType::KEYW_ELSE)
                        {
                            else_selection();
                        }
                        else
                        {

                        }
                    }
                    else
                    {
                        syntax_error();
                    }
                }
                else
                {
                    syntax_error();
                }
            }
            else
            {
                syntax_error();
            }
        }
        else
        {
            syntax_error();
        }
    }
    else
    {
        syntax_error();
    }
}

void parser::else_selection()
{
    if (_look_ahead.tokenType == TokenType::KEYW_ELSE)
    {
        get_next_token();
        if (_look_ahead.tokenType == TokenType::COLON)
        {
            get_next_token();
            if (_look_ahead.tokenType == TokenType::BLOCK_START)
            {
                get_next_token();
                statments();
                if (_look_ahead.tokenType == TokenType::BLOCK_END)
                {
                    get_next_token();
                }
                else
                {
                    syntax_error();
                }
            }
            else
            {
                syntax_error();
            }
        }
        else
        {
            syntax_error();
        }
    }
    else
    {
        syntax_error();
    }
}

void parser::return_statment()
{
    if (_look_ahead.tokenType == TokenType::KEYW_RETURN)
    {
        get_next_token();
        arithmatic_expression();
        if (_look_ahead.tokenType == TokenType::SEMICOLON)
        {
            get_next_token();
        }
        else
        {
            syntax_error();
        }
    }
    else
    {
        syntax_error();
    }
}

void parser::assignment_expression()
{
    if (_look_ahead.tokenType == TokenType::IDENTIFIER)
    {
        get_next_token();
        if (_look_ahead.tokenType == TokenType::ASSIGN)
        {
            get_next_token();
            arithmatic_expression();
        }
        else
        {
            syntax_error();
        }
    }
    else
    {
        syntax_error();
    }
}

void parser::relational_expression()
{
    greater_less_expression();
    equal_to_expression();
}

void parser::equal_to_expression()
{
    if (_look_ahead.tokenType == TokenType::EQUALS)
    {
        get_next_token();
        greater_less_expression();
        equal_to_expression();
    }
    else if (_look_ahead.tokenType == TokenType::NOT_EQUAL)
    {
        get_next_token();
        greater_less_expression();
        equal_to_expression();
    }
    else
    {

    }
}

void parser::greater_less_expression()
{
    arithmatic_expression();
    greater_less_expression_1();
}

void parser::greater_less_expression_1()
{
    if (_look_ahead.tokenType == TokenType::GREATER_THAN)
    {
        get_next_token();
        arithmatic_expression();
        greater_less_expression_1();
    }
    else if (_look_ahead.tokenType == TokenType::SMALLER_THAN)
    {
        get_next_token();
        arithmatic_expression();
        greater_less_expression_1();
    }
    else if (_look_ahead.tokenType == TokenType::GREATER_THAN_EQUALTO)
    {
        get_next_token();
        arithmatic_expression();
        greater_less_expression_1();
    }
    else if (_look_ahead.tokenType == TokenType::SMALLER_THAN_EQUALTO)
    {
        get_next_token();
        arithmatic_expression();
        greater_less_expression_1();
    }
    else
    {

    }
}

void parser::arithmatic_expression()
{
    mul_div_expression();
    add_sub_expression();
}

void parser::add_sub_expression()
{
    if (_look_ahead.tokenType == TokenType::ADD)
    {
        get_next_token();
        mul_div_expression();
        add_sub_expression();
    }
    else if (_look_ahead.tokenType == TokenType::SUBTRACT)
    {
        get_next_token();
        mul_div_expression();
        add_sub_expression();
    }
    else
    {

    }
}

void parser::mul_div_expression()
{
    id();
    mul_div_expression_1();
}

void parser::mul_div_expression_1()
{
    if (_look_ahead.tokenType == TokenType::MULTIPLY)
    {
        get_next_token();
        id();
        mul_div_expression_1();

    }
    else if (_look_ahead.tokenType == TokenType::DIVIDE)
    {
        get_next_token();
        id();
        mul_div_expression_1();
    }
    else if (_look_ahead.tokenType == TokenType::MODULO)
    {
        get_next_token();
        id();
        mul_div_expression_1();
    }
    else
    {

    }
}

void parser::id()
{
    if (_look_ahead.tokenType == TokenType::IDENTIFIER)
    {
        get_next_token();
    }
    else if (_look_ahead.tokenType == TokenType::NUMERIC_LITERAL)
    {
        get_next_token();
    }
    else
    {
        syntax_error();
    }
}





