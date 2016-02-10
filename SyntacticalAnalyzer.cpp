#include "stdafx.h"
#include "SyntacticalAnalyzer.h"
#include <iostream>

using namespace std;

SyntacticalAnalyzer::SyntacticalAnalyzer(vector<LexemeData> lexemeDataList)
{
	this->lexemeDataList = lexemeDataList;
	this->counter = 0;
	this->foundError = false;
	this->current = this->lexemeDataList.at(this->counter);
	this->message = "The program is syntactically correct.";
	cout << "Syntactical Analyzer was created with lexemeDataList" << endl << endl;
}


SyntacticalAnalyzer::~SyntacticalAnalyzer()
{
	cout << "Syntactical Analyzer was destroyed";
}

void SyntacticalAnalyzer::analyze(){
	while (this->current.tokenCode != 0 && this->foundError == false){
		this->expr();
	}
}
void SyntacticalAnalyzer::expr(){
	term();
	while (this->current.tokenCode == ADD_OP || this->current.tokenCode == SUB_OP){
		this->counter++;
		this->current = this->lexemeDataList.at(this->counter);
		term();
	}
}


void SyntacticalAnalyzer::term(){
	factor();
	while (this->current.tokenCode == MULT_OP || this->current.tokenCode == DIV_OP){
		this->counter++;
		this->current = this->lexemeDataList.at(this->counter);
		factor();
	}
}

void SyntacticalAnalyzer::factor() {
	if (this->current.tokenCode == IDENT || this->current.tokenCode == INT_LIT){
		this->counter++;
		this->current = this->lexemeDataList.at(this->counter);
	}
	else {
		if (this->current.tokenCode == LEFT_PAREN) {
			this->counter++;
			this->current = this->lexemeDataList.at(this->counter);
			expr();
			if (this->current.tokenCode == RIGHT_PAREN){
				this->counter++;
				this->current = this->lexemeDataList.at(this->counter);
			}
			else{
				error("Line " + to_string(this->current.lineNumber) + ": ERROR, expected a right parenthesis, found " + this->getTokenName(this->current.tokenCode) + ".");
			}
		}
		else{
			error("Line " + to_string(this->current.lineNumber) + ": ERROR, expected an id, integer literal, or a left parenthesis, found " + this->getTokenName(this->current.tokenCode) + ".");
		}
	}
}

void SyntacticalAnalyzer::error(string message){
	this->foundError = true;
	this->message = message;
}

string SyntacticalAnalyzer::getTokenName(int tokenCode){
	string tokenName;
	switch (tokenCode){
	case 10:
		tokenName = "INT_LIT";
		break;
	case 11:
		tokenName = "IDENT";
		break;
	case 20:
		tokenName = "ASSIGN_OP";
		break;
	case 21:
		tokenName = "ADD_OP";
		break;
	case 22:
		tokenName = "SUB_OP";
		break;
	case 23:
		tokenName = "MULT_OP";
		break;
	case 24:
		tokenName = "DIV_OP";
		break;
	case 25:
		tokenName = "LEFT_PAREN";
		break;
	case 26:
		tokenName = "RIGHT_PAREN";
		break;
	case -1:
		tokenName = "EOF";
		break;
	default:
		tokenName = "UNDEFINED";
		break;
	}
	return tokenName;
}