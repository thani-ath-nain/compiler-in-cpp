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
    //_symbol_table.print();
    print_TAC();
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
        string id, value, type, id_v;
        bool flag = 0;
        id = _look_ahead.lexeme;
        get_next_token();
        dec_ini_assi(value, type, id_v, flag);
        if (flag)
            emit(id + " = " + id_v + ";");
        _symbol_table.insert(id, value, type);
        statments();
    }
    else if (_look_ahead.tokenType == TokenType::KEYW_IN)
    {
        string id_v;
        input(id_v);
        emit("in " + id_v + ";");
        statments();
    }
    else if (_look_ahead.tokenType == TokenType::KEYW_PRINT|| _look_ahead.tokenType == TokenType::KEYW_PRINTLN)
    {
        string id_v;
        bool flag = 1;
        output(id_v, flag);
        if(flag)
            emit("out " + id_v + ";");
        else
            emit("out \"" + id_v + "\";");
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
        string id_v;
        return_statment(id_v);
        emit("ret " + id_v + ";");
        statments();
    }
    else
    {
        
    }
}

void parser::dec_ini_assi(string& value, string& type, string& id_v,bool& flag)
{
    if (_look_ahead.tokenType == TokenType::ASSIGN)
    {
        get_next_token();
        ini_assi_statment(value, type, id_v);
        flag = 1;
    }
    else if (_look_ahead.tokenType == TokenType::KEYW_INT || _look_ahead.tokenType == TokenType::KEYW_CHAR)
    {
        if (_look_ahead.tokenType == TokenType::KEYW_INT)
        {
            type = "int";
        }
        else if (_look_ahead.tokenType == TokenType::KEYW_CHAR)
        {
            type = "char";
        }
        value = "";
        declaration();
        flag = 0;
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

void parser::ini_assi_statment(string& value, string& type, string& id_v)
{
    if (_look_ahead.tokenType == TokenType::CHARACTER_LITERAL)
    {
        value = _look_ahead.lexeme;
        get_next_token();
        if (_look_ahead.tokenType == TokenType::KEYW_CHAR)
        {
            type = "char";
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
        value = _look_ahead.lexeme;
        type = "int";
        arithmatic_expression(id_v);
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

void parser::input(string& id_v)
{
    if (_look_ahead.tokenType == TokenType::KEYW_IN)
    {
        get_next_token();
        if (_look_ahead.tokenType == TokenType::IDENTIFIER)
        {
            id_v = _look_ahead.lexeme;
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

void parser::output(string& id_v, bool& flag)
{
    if (_look_ahead.tokenType == TokenType::KEYW_PRINT || _look_ahead.tokenType == TokenType::KEYW_PRINTLN)
    {
        get_next_token();
        output_1(id_v, flag);
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

void parser::output_1(string& id_v, bool& flag)
{
    if (_look_ahead.tokenType == TokenType::IDENTIFIER || _look_ahead.tokenType == TokenType::STRING_LITERAL || _look_ahead.tokenType == TokenType::CHARACTER_LITERAL)
    {
        if (_look_ahead.tokenType == TokenType::IDENTIFIER)
            flag = 1;
        else
            flag = 0;
        id_v = _look_ahead.lexeme;
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
            string id_v, id, s_next;
            id = _look_ahead.lexeme;
            assignment_expression(id_v);
            emit(id + " = " + id_v + ";");
            s_next = to_string(_line_no);
            if (_look_ahead.tokenType == TokenType::COMMA)
            {
                get_next_token();
                if (_look_ahead.tokenType == TokenType::IDENTIFIER || _look_ahead.tokenType == TokenType::NUMERIC_LITERAL)
                {
                    string id_v, re_s, re_e;
                    relational_expression(id_v, re_s, re_e);
                    backpatch(re_s + ";");
                    if (_look_ahead.tokenType == TokenType::COMMA)
                    {
                        get_next_token();
                        if (_look_ahead.tokenType == TokenType::IDENTIFIER || _look_ahead.tokenType == TokenType::NUMERIC_LITERAL)
                        {
                            string id_v, id;
                            id = _look_ahead.lexeme;
                            assignment_expression(id_v);
                            emit(id + " = " + id_v + ";");
                            if (_look_ahead.tokenType == TokenType::COLON)
                            {
                                get_next_token();
                                if (_look_ahead.tokenType == TokenType::BLOCK_START)
                                {
                                    get_next_token();
                                    statments();
                                    emit("goto " + s_next + ";");
                                    backpatch(re_e + ";");
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
            string id_v, re_s, re_e;
            relational_expression(id_v, re_s, re_e);
            backpatch(re_s + ";");
            if (_look_ahead.tokenType == TokenType::COLON)
            {
                get_next_token();
                if (_look_ahead.tokenType == TokenType::BLOCK_START)
                {
                    get_next_token();
                    statments();
                    string statments_next = to_string(_line_no);
                    if (_look_ahead.tokenType == TokenType::BLOCK_END)
                    {
                        get_next_token();
                        if (_look_ahead.tokenType == TokenType::KEYW_ELIF)
                        {
                            elif_selection(re_e, statments_next);
                        }
                        else if (_look_ahead.tokenType == TokenType::KEYW_ELSE)
                        {
                           
                            else_selection(re_e, statments_next);
                        }
                        else
                        {
                            backpatch(re_e + ";");
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

void parser::elif_selection(string& re_e, string s_next)
{
    if (_look_ahead.tokenType == TokenType::KEYW_ELIF)
    {
        emit("goto");
        backpatch(re_e + ";");
        get_next_token();
        if (_look_ahead.tokenType == TokenType::IDENTIFIER || _look_ahead.tokenType == TokenType::NUMERIC_LITERAL)
        {
            string id_v, re_s, re_e;
            relational_expression(id_v, re_s, re_e);
            backpatch(re_s + ";");
            if (_look_ahead.tokenType == TokenType::COLON)
            {
                get_next_token();
                if (_look_ahead.tokenType == TokenType::BLOCK_START)
                {
                    get_next_token();
                    statments();
                    backpatch(s_next + ";");
                    s_next = to_string(_line_no);
                    if (_look_ahead.tokenType == TokenType::BLOCK_END)
                    {
                        get_next_token();
                        if (_look_ahead.tokenType == TokenType::KEYW_ELIF)
                        {
                            elif_selection(re_e, s_next);
                        }
                        else if (_look_ahead.tokenType == TokenType::KEYW_ELSE)
                        {
                            else_selection(re_e, s_next);
                        }
                        else
                        {
                            backpatch(re_e + ";");
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

void parser::else_selection(string& re_e, string s_next)
{
    if (_look_ahead.tokenType == TokenType::KEYW_ELSE)
    {
        emit("goto");
        get_next_token();
        if (_look_ahead.tokenType == TokenType::COLON)
        {
            get_next_token();
            if (_look_ahead.tokenType == TokenType::BLOCK_START)
            {
                get_next_token();
                backpatch(re_e + ";");
                statments();
                backpatch(s_next + ";");
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

void parser::return_statment(string &id_v)
{
    if (_look_ahead.tokenType == TokenType::KEYW_RETURN)
    {
        get_next_token();
        arithmatic_expression(id_v);
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

void parser::assignment_expression(string& id_v)
{
    if (_look_ahead.tokenType == TokenType::IDENTIFIER)
    {
        get_next_token();
        if (_look_ahead.tokenType == TokenType::ASSIGN)
        {
            get_next_token();
            arithmatic_expression(id_v);
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

void parser::relational_expression(string& id_v, string& re_s, string &re_e)
{
    greater_less_expression(id_v, re_s, re_e);
    equal_to_expression(id_v, re_s, re_e);
}

void parser::equal_to_expression(string& id_v, string& re_s, string &re_e)
{
    if (_look_ahead.tokenType == TokenType::EQUALS)
    {
        get_next_token();
        greater_less_expression(id_v, re_s, re_e);
        equal_to_expression(id_v, re_s, re_e);
    }
    else if (_look_ahead.tokenType == TokenType::NOT_EQUAL)
    {
        get_next_token();
        greater_less_expression(id_v, re_s, re_e);
        equal_to_expression(id_v, re_s, re_e);
    }
    else
    {

    }
}

void parser::greater_less_expression(string& id_v, string& re_s, string &re_e)
{
    arithmatic_expression(id_v);
    string ro_v, id_v_1;
    greater_less_expression_1(ro_v, id_v_1);
    re_s = to_string(_line_no);
    emit("if " + id_v + " " + ro_v + " " + id_v_1 + " goto");
    re_e = to_string(_line_no);
    emit("goto");

}

void parser::greater_less_expression_1(string& ro_v,string& id_v)
{
    if (_look_ahead.tokenType == TokenType::GREATER_THAN)
    {
        ro_v = ">";
        get_next_token();
        arithmatic_expression(id_v);
        greater_less_expression_1(ro_v,id_v);
    }
    else if (_look_ahead.tokenType == TokenType::SMALLER_THAN)
    {
        ro_v = "<";
        get_next_token();
        arithmatic_expression(id_v);
        greater_less_expression_1(ro_v,id_v);
    }
    else if (_look_ahead.tokenType == TokenType::GREATER_THAN_EQUALTO)
    {
        ro_v = ">=";
        get_next_token();
        arithmatic_expression(id_v);
        greater_less_expression_1(ro_v,id_v);
    }
    else if (_look_ahead.tokenType == TokenType::SMALLER_THAN_EQUALTO)
    {
        ro_v = "<=";
        get_next_token();
        arithmatic_expression(id_v);
        greater_less_expression_1(ro_v, id_v);
    }
    else
    {

    }
}

void parser::arithmatic_expression(string &id_v)
{
    mul_div_expression(id_v);
    string a_s_e_v = id_v;
    add_sub_expression(a_s_e_v);
    id_v = a_s_e_v;
}

void parser::add_sub_expression(string &a_s_e_v)
{
    if (_look_ahead.tokenType == TokenType::ADD)
    {
        get_next_token();
        string id_v;
        mul_div_expression(id_v);
        string temp = temp_variable();
        emit(temp + " = " + a_s_e_v + " + " + id_v + ";");
        string a_s_e_v_1 = temp;
        add_sub_expression(a_s_e_v_1);
        a_s_e_v = a_s_e_v_1;
    }
    else if (_look_ahead.tokenType == TokenType::SUBTRACT)
    {
        get_next_token();
        string id_v;
        mul_div_expression(id_v);
        string temp = temp_variable();
        emit(temp + " = " + a_s_e_v + " - " + id_v + ";");
        string a_s_e_v_1 = temp;
        add_sub_expression(a_s_e_v_1);
        a_s_e_v = a_s_e_v_1;
    }
    else
    {

    }
}

void parser::mul_div_expression(string &id_v)
{
    id(id_v);
    string m_d_e_v = id_v;
    mul_div_expression_1(m_d_e_v);
    id_v = m_d_e_v;
}

void parser::mul_div_expression_1(string &m_d_e_v)
{
    if (_look_ahead.tokenType == TokenType::MULTIPLY)
    {
        get_next_token();
        string id_v;
        id(id_v);
        string temp = temp_variable();
        emit(temp + " = " + m_d_e_v + " * " + id_v + ";");
        string m_d_e_v_1 = temp;
        mul_div_expression_1(m_d_e_v_1);
        m_d_e_v = m_d_e_v_1;

    }
    else if (_look_ahead.tokenType == TokenType::DIVIDE)
    {
        get_next_token();
        string id_v;
        id(id_v);
        string temp = temp_variable();
        emit(temp + " = " + m_d_e_v + " / " + id_v + ";");
        string m_d_e_v_1 = temp;
        mul_div_expression_1(m_d_e_v_1);
        m_d_e_v = m_d_e_v_1;

    }
    else if (_look_ahead.tokenType == TokenType::MODULO)
    {
        get_next_token();
        string id_v;
        id(id_v);
        string temp = temp_variable();
        emit(temp + " = " + m_d_e_v + " % " + id_v + ";");
        string m_d_e_v_1 = temp;
        mul_div_expression_1(m_d_e_v_1);
        m_d_e_v = m_d_e_v_1;
    }
    else
    {

    }
}

void parser::id(string &id_v)
{
    if (_look_ahead.tokenType == TokenType::IDENTIFIER)
    {
        id_v = _look_ahead.lexeme;
        get_next_token();
    }
    else if (_look_ahead.tokenType == TokenType::NUMERIC_LITERAL)
    {
        id_v = _look_ahead.lexeme;
        get_next_token();
    }
    else
    {
        syntax_error();
    }
}

string parser::temp_variable()
{
    string temp = "t" + to_string(temp_variable_count);
    temp_variable_count++;
    return temp;   
}

void parser::emit(string line)
{
    TAD_code[_line_no] = line;
    //cout << _line_no << " " << line << endl;
    _line_no++;
}

void parser::backpatch(string line_no)
{
    TAD_code[stoi(line_no)] = TAD_code[stoi(line_no)] + " " + to_string(_line_no);
}

void parser::print_TAC()
{
    for (int i = 1; i < _line_no; i++)
    {
        cout << i<<" "<<TAD_code[i] << endl;
    }
}





