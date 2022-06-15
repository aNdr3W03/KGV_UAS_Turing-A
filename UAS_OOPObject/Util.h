#pragma once

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

string readFile(string fileName)
{
	cout << "Reading file " << fileName << "\n";
	string fileText;

	ifstream myFile(fileName);

	string tempText;

	while (getline(myFile, tempText))
	{
		fileText += tempText + "\n";
	}

	cout << fileText << "\n";

	return fileText;
}
