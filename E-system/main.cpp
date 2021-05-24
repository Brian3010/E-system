/*
Group members:	102257701 - Lam Duong
				102932516 - Rohan Ford
				101778599 - Gia Phuc Nguyen (Brian)

File name: main.cpp

Purpose of the program: The program is designed to help users in Melbourne to vote for
their prefered candidate and provide voters with information about the candidates.
*/

#include <iostream>
#include <fstream>	// library to work with file
#include <string>
#include <vector>

using namespace std;

/* Function Declaration */
bool fexist(string file);
void importCandidateToVector(string file, vector<string>& symbol, vector<string>& name, vector<int>& age, vector<string>& suburb, vector<int>& count);
void importVoterToVector(string file, vector<int>& id, vector<string>& name, vector<int>& age, vector<string>& suburb, vector<string>& status);
void numberOfVote(string nameInput, vector<string>& cName, vector<int>& cCount);
int compareId(vector<int>& vId, int idInput);
int compareName(vector<string>& cName, string nameInput);
bool isNumber(string id);
void addVoteToCandidate(string file, int voteInput, string nameInput, vector<string>& canName, vector<int>& canCount);
void displaySmallestNumber(vector<string>& cName, vector<int>& cCount);
void displayLargestNumber(vector<string>& cName, vector<int>& cCount);

/* MAIN */
int main() 
{
	char option, input;		// variables to work with user's input

	string canNameInput;
	string voterIdInput;

	const string voterFile = "voters.txt";
	const string candidateFile = "candidates.txt";

	// vector declaration for storing data from candidate database
	vector <string> can_Symbol, can_Name, can_Suburb;
	vector <int> can_Age, can_Count;

	// vector declaration for storing data from candidate database
	vector <string> voterName,voterSuburb,voterStatus;
	vector <int> voterID,voterAge;

	// check if files exist
	if (!fexist(voterFile) || !fexist(candidateFile)) {
		cout << "ERROR openning file" << endl;
	}
	else {
		// loop until 'Q' option is selected
		do {
			// convert text file to vector
			importCandidateToVector(candidateFile, can_Symbol, can_Name, can_Age, can_Suburb, can_Count);
			importVoterToVector(voterFile, voterID, voterName, voterAge, voterSuburb, voterStatus);

			// display menu to the user
			cout << "\n------------------------------------------------------------------------------------------" << endl;
			cout << "P - Print numbers for a particular candidate" << endl;
			cout << "A - Add number of votes to a candidate (with an existing voter ID)" << endl;
			cout << "S - Display the smallest number of votes candidate" << endl;
			cout << "L - Display the largest number of votes candidate" << endl;
			cout << "Q - Quit" << endl;
			cout << "Enter your choice: " << endl;
			cin >> input;				// take input from user
			option = toupper(input);	// convert to uppercase

			/* Corresponding Option */
			switch (option) {
			// Print number of votes
			case 'P':
				cout << "Enter candidate's name - Please capitalize the first letter of each word: " << endl;
				getline(cin.ignore(), canNameInput);	// get name from user

				// call function to get vote amount
				numberOfVote(canNameInput, can_Name, can_Count);

				break;

			// Add number of votes to candidate 
			case 'A':
				cout << "Enter your ID: " << endl;
				cin >> voterIdInput;		// get id from user

				// loop until input is in number format
				while (!isNumber(voterIdInput)) {
					cout << "Id has to be a number. Enter again: " << endl;
					cin >> voterIdInput;	// get id from user
				}

				if (voterID.empty()) {
					cout << "The list is empty" << endl;
				}
				else {
					// check if id exists in database
					if (compareId(voterID, stoi(voterIdInput)) != -1) {
						cout << "\nWelcome " << voterName[compareId(voterID, stoi(voterIdInput))] << endl;

						string voteNum;
						bool flag = true;

						cout << "Enter candidate's name - Please capitalize the first letter of each word: " << endl;
						getline(cin.ignore(), canNameInput);	// get name from user

						if (can_Name.empty()) {
							cout << "Unable to calculate the mean - no data" << endl;
						}
						else {
							// check if name exists in database
							if (compareName(can_Name, canNameInput) != -1) {
								cout << "Enter number of votes: ";
								cin >> voteNum;

								// loop until input is a number
								while (!isNumber(voteNum)) {
									cout << "Invalid number. Enter again: " << endl;
									cin >> voteNum;
								}

								addVoteToCandidate(candidateFile, stoi(voteNum), canNameInput, can_Name, can_Count);
							}
							else {
								cout << canNameInput << " does not exist in the database" << endl;
							}
						}
					}
					else {
						cout << "The ID does not exist in the database" << endl;
					}
				}

				break;

			// Smallest number of votes
			case 'S':
				displaySmallestNumber(can_Name, can_Count);
				break;

			// Largest number of votes
			case 'L':
				displayLargestNumber(can_Name, can_Count);
				break;

			// Quit
			case 'Q':
				cout << "Goodbye!!" << endl;
				break;

			default:
				cout << "Unknown selection, please try again" << endl;
			}
		} while (option != 'Q');
	}

	return 0;
}


/* Function Definition */

// Function to check if file exists
bool fexist(string file) 
{
	ifstream isFile;
	isFile.open(file);
	return !isFile.fail();
}

// Function to convert candidate data in file to vector
void importCandidateToVector(string file, vector<string>& symbol, vector<string>& name, vector<int>& age, vector<string>& suburb, vector<int>& count)
{
	string lSymbol, lName, lAge, lSuburb, lCount;
	string line;

	ifstream inFile(file);
	if (inFile.is_open()) {

		/*	Candidate file format:
			Symbol,Name,Age,Suburb,Count
			Eureka,Stephen Cummings,51,Kensington,50
		*/

		getline(inFile, line);  // ignore the first line (heading)

		// loop until end of file
		while (!inFile.eof()) {
			getline(inFile, lSymbol, ',');	// get first data: Symbol (e.g. Eureka) 
			symbol.push_back(lSymbol);		// push into vector 

			getline(inFile, lName, ',');	// get next data: Name (e.g. Stephen Cummings)
			name.push_back(lName);			// push into vector

			getline(inFile, lAge, ',');		// get next data: Age (e.g. 51)
			age.push_back(stoi(lAge));		// push into vector

			getline(inFile, lSuburb, ',');	// get next data: Suburb (e.g.Kensington)
			suburb.push_back(lSuburb);		// push into vector

			getline(inFile, lCount, '\n');  // get next data: Count (e.g. 50)
			count.push_back(stoi(lCount));	// push into vector
		}

		inFile.close();
	}
	else {
		cout << "Unable to open Candidate file" << endl;
	}
}

// Function to convert voter data in file to vector
void importVoterToVector(string file, vector<int>& id, vector<string>& name, vector<int>& age, vector<string>& suburb, vector<string>& status)
{
	string lId, lName, lAge, lSuburb, lStatus;
	string line;

	ifstream inFile(file);
	if (inFile.is_open()) {

		/*	Voter file format:
			Voter ID,Name,Age,Suburb,Status
			100,Lunea Yang,31,Fleminton,Active
		*/

		getline(inFile, line); // ignore the first line (heading)

		// loop until end of file
		while (!inFile.eof()) {
			getline(inFile, lId, ',');		// get first data: Voter ID (e.g. 100) 
			id.push_back(stoi(lId));		// push into vector

			getline(inFile, lName, ',');	// get next data: Name (e.g. Lunea Yang)
			name.push_back(lName);			// push into vector

			getline(inFile, lAge, ',');		// get next data: Age (e.g. 31)
			age.push_back(stoi(lAge));		// push into vector

			getline(inFile, lSuburb, ',');	// get next data: Suburb (e.g. Fleminton)
			suburb.push_back(lSuburb);		// push into vector

			getline(inFile, lStatus, '\n');	// get next data: Status (e.g. Active)
			status.push_back(lStatus);		// push into vector
		}

		inFile.close();
	}
	else {
		cout << "Unable to open Voter file" << endl;
	}
}

// Function to get vote amount of a candidate
void numberOfVote(string nameInput, vector<string>& cName, vector<int>& cCount) 
{
	// check if list is empty
	if (cName.empty()) {
		cout << "The list is empty" << endl;
	}
	else {
		// call function to compare name
		int index = compareName(cName, nameInput);

		// print to the screen
		if (index == -1) {
			cout << nameInput << " does not exist in the database" << endl;
		}
		else {
			cout << nameInput << " has " << cCount[index] << " vote(s)." << endl;
		}
	}
}

// Function to compare each voter id with id input
int compareId(vector<int>& vId, int idInput)
{
	for (int i = 0; i < vId.size(); i++) {
		if (vId[i] == idInput) {	// if equal
			return i;				// return index
		}
	}
	return -1;
}

// Function to compare each candidate name with name input
int compareName(vector<string>& cName, string nameInput) 
{
	for (int i = 0; i < cName.size(); i++) {
		if (cName[i].compare(nameInput) == 0) {	// if equal
			return i;							// return index
		}
	}
	return -1;
}

// Function to check if input is a number
bool isNumber(string id)
{
	for (int i = 0; i < id.length(); i++) {
		if (!isdigit(id[i])) {
			return false;
		}
	}
	return true;
}

// Function to add vote to the candidate
void addVoteToCandidate(string file, int voteInput, string nameInput, vector<string>& canName, vector<int>& canCount) 
{
	string line, lSymbol, lName, lAge, lSuburb, lCount;

	string newLine;

	int index = compareName(canName, nameInput);	// get index where candidate's name equals name input
	canCount[index] += voteInput;					// update count

	// open file for reading
	ifstream inFile;
	inFile.open(file);

	// open new file for writing
	ofstream tempFile;
	tempFile.open("temp.txt");

	bool firstline = true;

	if (inFile.is_open() && tempFile.is_open()) {
		// loop until end of file
		while (!inFile.eof()) {
			//extracting "," and "\n" and store data 
			getline(inFile, lSymbol, ','); 
			getline(inFile, lName, ',');
			getline(inFile, lAge, ',');
			getline(inFile, lSuburb, ',');
			getline(inFile, lCount, '\n');

			if (!firstline) {		// delete a new line from the end of the text file
				tempFile << endl;
			}

			firstline = false;

			// compare the current candidate's name with the updated cadidate's count, and update the line in file
			if (lName.compare(canName[index]) == 0) {	
				newLine = lSymbol + "," + lName + "," + lAge + "," + lSuburb + "," + to_string(canCount[index]);
			}
			else {
				newLine = lSymbol + "," + lName + "," + lAge + "," + lSuburb + "," + lCount;
			}

			tempFile << newLine;	// save to the new file
		}

		inFile.close();
		tempFile.close();

		remove("candidates.txt");	// delete the old file 

		// rename file
		if (rename("temp.txt", "candidates.txt") != 0) {
			cout << "ERROR renaming file" << endl;
		}
		else {
			cout << "Number of votes added successfully" << endl
				<< canName[index] << " now has " << canCount[index] << " vote(s)" << endl;
		}

	} else {
		cout << "ERROR! Cannot access the file" << endl;
	}
}

// Function to display smallest number of votes
void displaySmallestNumber(vector<string>& cName, vector<int>& cCount)
{
	if (cName.empty()) {
		cout << "Unable to determine the smallest number - list is empty" << endl;
	}
	else {
		string name;
		int min = 0xfffffff;

		for (int i = 0; i < cCount.size(); i++) {
			if (cCount[i] < min) {	// if vote count less then min
				name = cName[i];	// assign new name
				min = cCount[i];	// assign new min
			}
		}

		// display
		cout << "The candidate with the smallest number of votes is " << name << " with " << min << " vote(s)" << endl;
	}
}

// Function to display largest number of votes
void displayLargestNumber(vector<string>& cName, vector<int>& cCount)
{
	if (cName.empty()) {
		cout << "Unable to determine the largest number - list is empty" << endl;
	}
	else {
		string name;
		int max = 0;

		for (int i = 0; i < cCount.size(); i++) {
			if (cCount[i] > max) {	// if vote count more then max
				name = cName[i];	// assign new name
				max = cCount[i];	// assign new max
			}
		}

		// display
		cout << "The candidate with the smallest number of votes is " << name << " with " << max << " vote(s)" << endl;
	}
}