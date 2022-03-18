#ifndef _LEXER_H_
#define _LEXER_H_
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

//all your tokens goes here
enum class TokenType
{
	END_OF_FILE = 0,
	ERROR,
	KEYW_FUNC, KEYW_INT,KEYW_CHAR,KEYW_CALL,KEYW_IF,KEYW_ELIF,KEYW_ELSE,KEYW_FOR,KEYW_PRINT,KEYW_PRINTLN,
    KEYW_RETURN,KEYW_IN,
    EQUALS, GREATER_THAN , GREATER_THAN_EQUALTO , SMALLER_THAN , SMALLER_THAN_EQUALTO , NOT_EQUAL,
    ASSIGN,
    ADD , SUBTRACT , MULTIPLY , DIVIDE , MODULO ,
    IDENTIFIER , NUMERIC_LITERAL , CHARACTER_LITERAL , STRING_LITERAL , COMMENT , BLOCK_START , BLOCK_END,
    COMMA , HASH , COLON , SEMICOLON
};
//structure of a token 
struct token
{
	string lexeme;
	TokenType tokenType;//enum type
	//constructor
	token(string lexeme, TokenType tokenType);
	//constructor default
	token();
	void Print();
};
class lexer
{
	vector<char> stream;  //used for storing file sample_code.cc content
	vector<token> tokens; //vector to store all (tokens,lexeme) pairs
	void Tokenize();//populates tokens vector
	int index;

public:
	lexer();
	lexer(const char filename[]);
	void printRaw();//just print everything as it is present in file
	token getNextToken();//get next token
	void resetPointer();//reset pointer to start getting tokens from start
	int getCurrentPointer();//get where current pointer in tokens vector is
	void setCurrentPointer(int pos);//move current pointer to wherever
	token peek(int);//peek the next token
	int isIdentifier(vector<char>::iterator); 
	int isNumericLiteral(vector<char>::iterator); 
	int isStringLiteral(vector<char>::iterator); 
};

#endif // !_LEXER_H
