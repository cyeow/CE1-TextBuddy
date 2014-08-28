// CE1TextBuddy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include "FileManip.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void readCmd();

int main(int argc, char* argv[]) {
	string filename, line;
	ifstream myfile;
	ofstream outfile;

	filename = argv[1];

	outfile.open(filename);
    outfile << "helloo o\n";
	outfile.close();
	
	cout << argc << " " << filename << endl;
	myfile.open(filename);
	getline(myfile, line);
	

	cout << line << endl;

	myfile.close();

//	FileManip myFile(filename);


	return 0;
}