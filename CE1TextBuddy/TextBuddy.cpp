// TextBuddy.cpp:
// TextBuddy is used to store, retrieve and delete lines in a textfile. 
// The command format is given by the example interaction below:
//
// Welcome to TextBuddy. <filename>.txt is ready for use
// command: add a quick brown fox
// added to <filename>.txt: "a quick brown fox"
// command: add jumped over a lazy dog
// added to <filename>.txt: "jumped over a lazy dog"
// command: display
// 1. a quick brown fox
// 2. jumped over a lazy dog
// command: delete 1
// deleted from <textfile>.txt: "a quick brown fox"
// command: display
// 1. jumped over a lazy dog
// command: clear
// all content deleted from <textfile>.txt
// command: exit
// 
// author: Yeow Li Teng Cheryl 

#include "stdafx.h"
#include "TextBuddy.h"

using namespace std;

const string MESSAGE_EMPTY = "%s is empty";
const string MESSAGE_ADDED = "added to %s: \"%s\"";
const string MESSAGE_DELETED = "deleted from %s: \"%s\"";
const string MESSAGE_CLEARED = "all content deleted from %s";
const string MESSAGE_INVALID_FORMAT = "invalid command format: %s";
const string MESSAGE_PROGRAM_TERMINATION = "Enter any key to exit: ";
const string WELCOME_MESSAGE = "Welcome to TextBuddy. %s is ready for use";
const string ERROR_UNRECOGNISED_COMMAND_TYPE = "ERROR: Unrecognised command type.\n1. add <text>\n2. delete <line number>\n3. clear all\n4. display all\n";
const string ERROR_USAGE = "ERROR: Usage: textbuddy.exe <filename>.txt";

void TextBuddy::main(int argc, char* argv[]) {
	string filename;

	if (argc != 2) {
		// if the command line input is wrong, generates an error message and terminates the program.
		showToUser(ERROR_USAGE);
		showToUser(MESSAGE_PROGRAM_TERMINATION);

		getchar();
		exit(0);
	}

	filename = argv[1];

	sprintf_s(buffer, WELCOME_MESSAGE.c_str(), filename.c_str());
	showToUser(buffer);

	while (true) {
		cout << "command:";
		string userCommand;
		getline(cin, userCommand);
		string feedback = executeCommand(filename, userCommand);
		showToUser(feedback);
	}

	return;
}

string TextBuddy::executeCommand(string filename, string userCommand) {
	CommandType command;
	string content;

	command = determineCommandType(getFirstWord(userCommand));
	content = removeFirstWord(userCommand);


	switch (command) {
	case ADD_LINE:
		return addLine(filename, content);

	case DISPLAY_ALL:
		return displayAll(filename);

	case DELETE_LINE:
		return deleteLine(filename, content);

	case CLEAR_ALL:
		return clearAll(filename);

	case EXIT:
		exit(0);

	case INVALID:
		sprintf_s(buffer, MESSAGE_INVALID_FORMAT.c_str(), userCommand.c_str());
		return buffer;

	default:
		showToUser(ERROR_UNRECOGNISED_COMMAND_TYPE);
		showToUser(MESSAGE_PROGRAM_TERMINATION);

		getchar();
		exit(EXIT_FAILURE);
	}

}

string TextBuddy::addLine(string filename, string content) {
	ofstream file;

	file.open(filename, ios::app);
	file << content << endl;
	file.close();

	sprintf_s(buffer, MESSAGE_ADDED.c_str(), filename.c_str(), content.c_str());

	return buffer;
}

string TextBuddy::displayAll(string filename) {
	ifstream file;
	string line;
	int i;

	file.open(filename);

	for (i = 1; getline(file, line); i++) {
		cout << i << ". " << line << endl;
	}

	if (i == 1) {
		sprintf_s(buffer, MESSAGE_EMPTY.c_str(), filename.c_str());
		return buffer;
	}

	file.close();

	return "";
}

string TextBuddy::deleteLine(string filename, string content) {
	ofstream newFile;
	ifstream oldFile;
	string tempLine;
	string deletedLine;

	oldFile.open(filename);
	newFile.open("temp.txt");

	for (int i = 1; getline(oldFile, tempLine); i++) {
		if (i == stoi(content)) {
			deletedLine = tempLine;
			continue;
		}
		else {
			newFile << tempLine << endl;
		}
	}

	oldFile.close();
	newFile.close();

	remove(filename.c_str());
	rename("temp.txt", filename.c_str());

	sprintf_s(buffer, MESSAGE_DELETED.c_str(), filename.c_str(), deletedLine.c_str());

	return buffer;
}

string TextBuddy::clearAll(string filename) {
	ifstream file;

	file.open("temp.txt");
	file.close();
	remove(filename.c_str());
	rename("temp.txt", filename.c_str());

	sprintf_s(buffer, MESSAGE_CLEARED.c_str(), filename.c_str());

	return buffer;
}

TextBuddy::CommandType TextBuddy::determineCommandType(string command) {
	transform(command.begin(), command.end(), command.begin(), ::tolower);

	if (command == "add"){
		return CommandType::ADD_LINE;
	}
	else if (command == "display") {
		return CommandType::DISPLAY_ALL;
	}
	else if (command == "delete") {
		return CommandType::DELETE_LINE;
	}
	else if (command == "clear") {
		return CommandType::CLEAR_ALL;
	}
	else if (command == "exit") {
		return CommandType::EXIT;
	}
	else
		return CommandType::INVALID;
}

string TextBuddy::removeFirstWord(string command){
	return command.substr(command.find_first_of(" ") + 1);
}

string TextBuddy::getFirstWord(string command){
	return command.substr(0, command.find(' '));
}

void TextBuddy::showToUser(string text) {
	cout << text << endl;
}


int main(int argc, char* argv[]) {
	TextBuddy::main(argc, argv);
}