#pragma once

#include <iostream>
#include <string>
using namespace std;

class LexemeData
{
public:
	LexemeData();
	~LexemeData();
	string lexeme;
	int tokenCode;
	int lineNumber;
};

