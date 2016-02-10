#pragma once

#include <iostream>
#include <string>
#include "LexemeData.h"
#include "LexicalAnalyzer.h"

using namespace std;

class SyntacticalAnalyzer
{
public:
	SyntacticalAnalyzer(vector<LexemeData> lexemeDataList);
	~SyntacticalAnalyzer();
	void analyze();
	string message;
	bool foundError;
	vector<LexemeData> lexemeDataList;
	LexemeData current;
	int counter;
	string getTokenName(int tokenCode);

private:
	void expr();
	void factor();
	void term();
	void error(string message);
};

