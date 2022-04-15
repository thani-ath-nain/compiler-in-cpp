#include "lexer.h"
#include <cstring>
using namespace std;
//for printing tokens names, Same as the enum defined in lexer.h
string reserved[] = {
    "END_OF_FILE",
    "ERROR",
    "KEYW_FUNC", "KEYW_INT", "KEYW_CHAR", "KEYW_CALL", "KEYW_IF", "KEYW_ELIF", "KEYW_ELSE", "KEYW_FOR", "KEYW_PRINT", "KEYW_PRINTLN",
    "KEYW_RETURN", "KEYW_IN",
    "EQUALS", "GREATER_THAN", "GREATER_THAN_EQUALTO", "SMALLER_THAN", "SMALLER_THAN_EQUALTO", "NOT_EQUAL",
    "ASSIGN",
    "ADD", "SUBTRACT", "MULTIPLY", "DIVIDE", "MODULO",
    "IDENTIFIER", "NUMERIC_LITERAL", "CHARACTER_LITERAL", "STRING_LITERAL", "COMMENT", " BLOCK_START", "BLOCK_END",
    "COMMA", "HASH", "COLON", "SEMICOLON"};
token::token()
{
    this->lexeme = "";
    this->tokenType = TokenType::ERROR;
}
token::token(string lexeme, TokenType tokenType)
{
    this->lexeme = lexeme;
    this->tokenType = tokenType;
}
void token::Print()
{
    cout << "{" << lexeme << " , "
         << reserved[(int)tokenType] << "}\n";
}
int lexer::getCurrentPointer()
{
    return index;
}
void lexer::setCurrentPointer(int pos)
{
    if (pos >= 0 && pos < tokens.size())
        index = pos;
    else
        index = 0;
}
void lexer::Tokenize() //function that tokenizes your input stream
{
    vector<char>::iterator it = stream.begin();
    string tokenName = "";
    //your implementation goes here
    for (it = stream.begin(); it != stream.end(); it++)
    {
        // for comments
        string s = "";
        if (*it == '#' && ((isalnum(*(it + 1)))||isspace(*(it+1))))
        {
            for (it; *it != '\n'; it++)
            {
                if (isdigit((int)*it) || isalpha((int)*it) || isspace((int)*it))
                {
                    s += *it;
                }
            }
            cout << *it ;
            tokens.push_back(token(string(s), TokenType::COMMENT));
        }
        // for keywords
        else if ((*it == 'f') && (*(it + 1) == 'u') && (*(it + 2) == 'n') && (*(it + 3) == 'c'))
        {
            tokenName = "func";
            tokens.push_back(token(string(tokenName), TokenType::KEYW_FUNC));
            it = it + 3;
        }
        else if (*it == 'i' && *(it + 1) == 'n' && *(it + 2) == 't')
        {
            tokenName = "int";
            tokens.push_back(token(string(tokenName), TokenType::KEYW_INT));
            it = it + 2;
        }
        else if (*it == 'c' && *(it + 1) == 'h' && *(it + 2) == 'a' && *(it + 3) == 'r')
        {
            tokenName = "char";
            tokens.push_back(token(string(tokenName), TokenType::KEYW_CHAR));
            it = it + 3;
        }
        else if (*it == 'c' && *(it + 2) == 'a' && *(it + 3) == 'l' && *(it + 4) == 'l')
        {
            tokenName = "call";
            tokens.push_back(token(string(tokenName), TokenType::KEYW_CALL));
            it = it + 3;
        }
        else if (*it == 'i' && *(it + 1) == 'f')
        {
            tokenName = "if";
            tokens.push_back(token(string(tokenName), TokenType::KEYW_IF));
            it = it + 1;
        }
        else if (*it == 'e' && *(it + 1) == 'l' && *(it + 2) == 'i' && *(it + 3) == 'f')
        {
            tokenName = "elif";
            tokens.push_back(token(string(tokenName), TokenType::KEYW_ELIF));
            it = it + 3;
        }
        else if (*it == 'e' && *(it + 1) == 'l' && *(it + 2) == 's' && *(it + 3) == 'e')
        {
            tokenName = "else";
            tokens.push_back(token(string(tokenName), TokenType::KEYW_ELSE));
            it = it + 3;
        }
        else if (*it == 'f' && *(it + 1) == 'o' && *(it + 2) == 'r')
        {
            tokenName = "for";
            tokens.push_back(token(string(tokenName), TokenType::KEYW_FOR));
            it = it + 2;
        }
        else if (*it == 'p' && *(it + 1) == 'r' && *(it + 2) == 'i' && *(it + 3) == 'n' && *(it + 4) == 't')
        {
            tokenName = "print";
            tokens.push_back(token(string(tokenName), TokenType::KEYW_PRINT));
            it = it + 4;
        }
        else if (*it == 'p' && *(it + 1) == 'r' && *(it + 2) == 'i' && *(it + 3) == 'n' && *(it + 4) == 't' && *(it + 5) == 'l' && *(it + 6) == 'n')
        {
            tokenName = "println";
            tokens.push_back(token(string(tokenName), TokenType::KEYW_PRINTLN));
            it = it + 6;
        }
        else if (*it == 'r' && *(it + 1) == 'e' && *(it + 2) == 't' && *(it + 3) == 'u' && *(it + 4) == 'r' && *(it + 5) == 'n')
        {
            tokenName = "return";
            tokens.push_back(token(string(tokenName), TokenType::KEYW_RETURN));
            it = it + 5;
        }
        else if (*it == 'i' && *(it + 1) == 'n')
        {
            tokenName = "in";
            tokens.push_back(token(string(tokenName), TokenType::KEYW_IN));
            it = it + 1;
        }
        // for block start and end
        else if (*it == 'b' && *(it + 1) == 'e' && *(it + 2) == 'g' && *(it + 3) == 'i' && *(it + 4) == 'n')
        {
            tokenName = "begin";
            tokens.push_back(token(string(tokenName), TokenType::BLOCK_START));
            it = it + 4;
        }
        else if (*it == 'e' && *(it + 1) == 'n' && *(it + 2) == 'd')
        {
            tokenName = "end";
            tokens.push_back(token(string(tokenName), TokenType::BLOCK_END));
            it = it + 2;
        }
        // for assignment operator
        else if (*it == '<' && *(it + 1) == '-')
        {
            tokenName = "assign";
            tokens.push_back(token(string(tokenName), TokenType::ASSIGN));
            it = it + 1;
        }
        // for arithematic operators
        else if (*it == '+')
        {
            tokenName = "add";
            tokens.push_back(token(string(tokenName), TokenType::ADD));
        }
        else if (*it == '-')
        {
            tokenName = "subtract";
            tokens.push_back(token(string(tokenName), TokenType::SUBTRACT));
        }
        else if (*it == '*')
        {
            tokenName = "multiply";
            tokens.push_back(token(string(tokenName), TokenType::MULTIPLY));
        }
        else if (*it == '/')
        {
            tokenName = "divide";
            tokens.push_back(token(string(tokenName), TokenType::DIVIDE));
        }
        else if (*it == '%')
        {
            tokenName = "modulo";
            tokens.push_back(token(string(tokenName), TokenType::MODULO));
        }
        // for relational operators
        else if (*it == '=')
        {
            tokenName = "equals";
            tokens.push_back(token(string(tokenName), TokenType::EQUALS));
        }
        else if (*it == '>')
        {
            tokenName = "greater than";
            tokens.push_back(token(string(tokenName), TokenType::GREATER_THAN));
        }
        else if (*it == '>' && *(it + 1) == '=')
        {
            tokenName = "greater than equal to";
            tokens.push_back(token(string(tokenName), TokenType::GREATER_THAN_EQUALTO));
            it = it + 1;
        }
        else if (*it == '<')
        {
            tokenName = "smaller than";
            tokens.push_back(token(string(tokenName), TokenType::SMALLER_THAN));
        }
        else if (*it == '<' && *(it + 1) == '=')
        {
            tokenName = "smaller than equal to";
            tokens.push_back(token(string(tokenName), TokenType::SMALLER_THAN_EQUALTO));
            it = it + 1;
        }
        else if (*it == '~' && *(it + 1) == '=')
        {
            tokenName = "not equal";
            tokens.push_back(token(string(tokenName), TokenType::NOT_EQUAL));
            it = it + 1;
        }
        // for special characters
        else if (*it == ',')
        {
            tokenName = "comma";
            tokens.push_back(token(string(tokenName), TokenType::COMMA));
        }
        else if (*it == '#')
        {
            tokenName = "hash";
            tokens.push_back(token(string(tokenName), TokenType::HASH));
        }
        else if (*it == ':')
        {
            tokenName = "colon";
            tokens.push_back(token(string(tokenName), TokenType::COLON));
        }
        else if (*it == ';')
        {
            tokenName = "semicolon";
            tokens.push_back(token(string(tokenName), TokenType::SEMICOLON));
        }
        //for identifier
        else if (isalpha((int)*it))
        {
             it=it+isIdentifier(it)-1;
        }
        // for character literal
        else if (*it == ' \' ' && isalpha((int)*(it + 1)) && *(it + 2) == ' \' ')
        {
            tokenName = "character literal";
            tokens.push_back(token(string(tokenName), TokenType::CHARACTER_LITERAL));
            it = it + 2;
        }
        // for string literal
        else if (*it == 34)
        {
            it=it+isStringLiteral(it)+1;
        }
        // for numeric literal
        else if (isdigit((int)*it))
        {
            it=it+isNumericLiteral(it)-1;
        }
    }
    //push_back EOF token at end to identify End of File
    tokens.push_back(token(string(""), TokenType::END_OF_FILE));
}
lexer::lexer(const char filename[])
{
    index = 0;
    //constructors: takes file name as an argument and store all
    //the contents of file into the class varible stream
    ifstream fin(filename);
    if (!fin) //if file not found
    {
        cout << "file not found" << endl;
    }
    else
    {
        char byte = 0;
        while (fin.get(byte))
        { //store file contents into stream
            if (byte != '\r')
                stream.push_back(byte);
        }
        stream.push_back(' '); //dummy spaces appended at the end
        stream.push_back(' ');
        //Tokenize function to get all the (token,lexeme) pairs
        Tokenize();
        //assigning tokens to iterator::pointer
        index = 0;
    }
}
lexer::lexer()
{
    index = -1;
}
void lexer::printRaw()
{
    //helper function to print the content of file
    vector<char>::iterator it = stream.begin();
    for (it = stream.begin(); it != stream.end(); it++)
    {
        cout << *it;
    }
    cout << endl;
}
token lexer::getNextToken()
{
    //this function will return single (token,lexeme) pair on each call
    //this is an iterator which is pointing to the beginning of vector of tokens
    token _token;
    if (index == tokens.size())
    {                       // return end of file if
        _token.lexeme = ""; // index is too large
        _token.tokenType = TokenType::END_OF_FILE;
    }
    else
    {
        _token = tokens[index];
        index = index + 1;
    }
    return _token;
}
void lexer::resetPointer()
{
    index = 0;
}
token lexer::peek(int howFar)
{
    if (howFar <= 0)
    { // peeking backward or in place is not allowed
        cout << "LexicalAnalyzer:peek:Error: non positive argument\n";
        exit(-1);
    }

    int peekIndex = index + howFar - 1;
    if (peekIndex > (tokens.size() - 1))
    {                                             // if peeking too far
        return token("", TokenType::END_OF_FILE); // return END_OF_FILE
    }
    else
        return tokens[peekIndex];
}

int lexer::isIdentifier(vector<char>::iterator it)
{
    string s = "";
    for (it; isalnum(*(it)); it++)
    {
        if (isalpha((int)*it))
        {
            s += *it;
        }
    }
    string tokenName = "identifier";
    tokens.push_back(token(string(s), TokenType::IDENTIFIER));
    return s.length();
}

int lexer::isStringLiteral(vector<char>::iterator it)
{
    string s = "";
    it = it + 1;
    
    for (it; *it != 34; it++)
    {
            s += *it;  
    }

    string tokenName = "string literal";
    tokens.push_back(token(string(s), TokenType::STRING_LITERAL));
    return s.length();
}
int lexer::isNumericLiteral(vector<char>::iterator it)
{
    string s = "";
    for (it; *it != 32; it++)
    {
        if (isdigit((int)*it))
        {
            s += *it;
        }
    }

    string tokenName = "numeric literal";
    tokens.push_back(token(string(s), TokenType::NUMERIC_LITERAL));
    return s.length();
}
