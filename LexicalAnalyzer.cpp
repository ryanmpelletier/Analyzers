#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <string>
#include "LexicalAnalyzer.h"


LexicalAnalyzer::LexicalAnalyzer()
{
	this->lineNumber = 1;
	cout << "LexicalAnalyzer has been created" << endl << endl;
}

LexicalAnalyzer::LexicalAnalyzer(string filename){
	this->lineNumber = 1;
	this->sourceCode.open(filename);
	if (!this->sourceCode.is_open()){
		cout << "Error: File was not opened.";
	}
	else{
		cout << "LexicalAnalyzer has been created with a file" << endl << endl;
	}
}

LexicalAnalyzer::~LexicalAnalyzer(){
	cout << "Lexical Analyzer DESTROYED.";
}

vector<LexemeData> LexicalAnalyzer::analyze(){
	vector<LexemeData> lexemeDataList;
	int i = 0;
	lexemeDataList.push_back(this->getNextLexemeData());
	while (lexemeDataList[i].lexeme.at(0) != -1){
		lexemeDataList.push_back(this->getNextLexemeData());
		i++;
	}
	return lexemeDataList;
}

LexemeData LexicalAnalyzer::getNextLexemeData(){
	LexemeData lexemeData;
	lexemeData.lexeme = this->getNextLexeme();
	lexemeData.lineNumber = this->lineNumber; //record the line number lexemeAnalyzer is currently on (this will be incremented in getNextLexeme
	lexemeData.tokenCode = this->getTokenCode(lexemeData.lexeme);
	return lexemeData;
}

//this is a recursive function, the base cases are that which let us identify a lexeme, otherwise we call recursively (this has the potential to be aweful if there is alot of white space)
string LexicalAnalyzer::getNextLexeme(){
	string returnedLexeme = "";
	char c;
	c = this->sourceCode.peek();	//we may not have to peek here if in all our cases we call get()
	if (c == '\n'){
		this->lineNumber++;
		this->sourceCode.get(c);
		return this->getNextLexeme();
	}
	else if (c == ' '){
		this->sourceCode.get(c);	//move the file pointer over once (our way of skipping white space)
		return this->getNextLexeme(); 
	}
	else if (this->isSpecialCharacter(c)){//if it is a special character, then it is the next lexeme, because we don't have special characters that are longer than one char.
		this->sourceCode.get(c); //stores character we were peeking at in c, and also moves the file pointer to the next char
		returnedLexeme += c;
		return returnedLexeme;
	}
	else if (isdigit(c)){
		this->sourceCode.get(c);
		int i = 0;
		returnedLexeme += c;
		while (isdigit(this->sourceCode.peek())){
			i++;
			this->sourceCode.get(c);
			returnedLexeme += c;
		}
		return returnedLexeme;
	}
	else if (isalpha(c)){
		this->sourceCode.get(c);
		int i = 0;
		returnedLexeme += c;
		while (isdigit(this->sourceCode.peek()) || isalpha(this->sourceCode.peek())){
			i++;
			this->sourceCode.get(c);
			returnedLexeme += c;
		}
		return returnedLexeme;
	}
	return NULL;
}

bool LexicalAnalyzer::isSpecialCharacter(char c){
	if (c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/' || c == '=' | c == -1){
		return true;
	}
	return false;
}

int LexicalAnalyzer::getTokenCode(string lexeme){
	if (isdigit(lexeme.at(0))){
		return INT_LIT;
	}
	else if (isalpha(lexeme.at(0))){
		return IDENT;
	}
	else if ((lexeme.at(0)) == '('){
		return LEFT_PAREN;
	}
	else if ((lexeme.at(0)) == ')'){
		return RIGHT_PAREN;
	}
	else if ((lexeme.at(0)) == '+'){
		return ADD_OP;
	}
	else if ((lexeme.at(0)) == '-'){
		return SUB_OP;
	}
	else if ((lexeme.at(0)) == '*'){
		return MULT_OP;
	}
	else if ((lexeme.at(0)) == '/'){
		return DIV_OP;
	}
	else if ((lexeme.at(0)) == '='){
		return ASSIGN_OP;
	}
	return NULL;
}


