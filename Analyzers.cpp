

#include "stdafx.h"
#include "LexicalAnalyzer.h"
#include "SyntacticalAnalyzer.h"
#include <iostream>
#include <ctype.h>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <fstream>
#include <ctype.h>

using namespace std;

int main()
{

	LexicalAnalyzer * lexicalAnalyzer = new LexicalAnalyzer("program.dat");
	vector<LexemeData> lexicalData = lexicalAnalyzer->analyze();


	SyntacticalAnalyzer * syntacticalAnalyzer = new SyntacticalAnalyzer(lexicalData);
	syntacticalAnalyzer->analyze();

	cout << syntacticalAnalyzer->message << endl << endl;
	

	system("pause");
	return 0;

}