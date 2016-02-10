#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include "LexemeData.h"
using namespace std;

/*Character classes*/
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/*Token Codes, we don't want these printed out ultimately*/
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26

class LexicalAnalyzer
{
public:

	//constructor/destructor
	LexicalAnalyzer();
	LexicalAnalyzer(string filename);
	~LexicalAnalyzer();

	//methods
	vector<LexemeData> analyze(); //when analyze gets called, return a list of the lexemeData, then the syntaxAnalyzer can go through that (this will probably be the only public method)
	LexemeData getNextLexemeData(); //return a lexemeData object, this will record the lineNumber, then get the next lexeme, then get the token code
	string getNextLexeme();
	int getTokenCode(string lexeme);
	bool isSpecialCharacter(char c);


	//properties
	ifstream sourceCode;
	int lineNumber;	
	vector<LexemeData> lexemeDataList;
};

