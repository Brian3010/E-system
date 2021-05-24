/*Group members: Lam Duong - 102257701
				 Rohan Ford - 102932516
				 Gia Phuc Nguyen (Brian) - 101778599
  File name:

  Purpose of the program: the program is designed to help users in Melbourne to vote for their
  prefered candidate and provide voters with information about the candidates.
*/

#include <iostream>
#include <fstream> //library to work with file
#include <string>
#include <vector>

using namespace std;



/*function declaration*/

int main();

bool fexist(string file);

void numberOfVote(string name, vector<string>& vect1, vector<int>& vect2);

void importCandidateToArray(string file, vector<string>& vect1, vector<string>& vect2, vector<int>& vect3, vector<string>& vect4, vector<int>& vect5);
void importVoterToArray(string file, vector<int> &vect1, vector<string> &vect2, vector<int> &vect3, vector<string> &vect4, vector<string> &vect5);

bool isName(vector<string>& vect1, string name);
int isID(vector<int>& vect1, int id);
bool isNumber(string id);

void displaySmallestNumber(string file);
void displaylargestNumber(string file);

void addVoteToCandidate(string file, int voteNum, string name,vector<string>& canName, vector<int> & canCount);
int main() {

	char option, input; // variable to work with user's input
	string candidateName;
	string id;


	const string voterFile = "voters.txt";
	const string candidateFile = "candidates.txt";

	/*vector declaration for storing data from candidate database*/
	vector <string> sym_bol, can_Name, can_Suburb;
	vector <int> can_Age, can_Count;

	/*vector declaration for storing data from candidate database*/
	vector <string> voterName,voterSuburb,voterStatus;
	vector <int> voterID,voterAge;
	


	if (!fexist(voterFile) || !fexist(candidateFile)) {
		cout << "Error!! openning the database" << endl;


	}
	else {
		/*using do-while loop to keep the program running until 'Q' option is selected*/
		do {
			/*display menu to the user*/
			cout << "\n------------------------------------------------------------------------------------------" << endl;
			cout << "P - Print numbers for a particular candidate (for example candidate 1 or candidate 2)" << endl;
			cout << "A - Add number of votes to a candidate (with an existing voter ID)" << endl;
			cout << "S - Display the smallest number of votes candidate" << endl;
			cout << "L - Display the largest number of votes candidate" << endl;
			cout << "Q - Quit" << endl;
			cout << "Enter your choice: " << endl;

			/*take the input from the user and convert it to uppercase for easier verification*/
			cin >> input;
			option = toupper(input);

			/*convert text file to vector for easier data modification*/
			importCandidateToArray(candidateFile, sym_bol, can_Name, can_Age, can_Suburb, can_Count);
			importVoterToArray(voterFile,voterID, voterName, voterAge, voterSuburb, voterStatus);

			/*the switch-case then is used to idenfify choices from the user. depending on user's choice,
			each case calls coresponding function to execute.
			Invalid choice is prompted to try again*/
			switch (option) {
			case 'P':
				//Display number of votes
				cout << "Enter candidate's name (Please start the name with capital letter): " << endl;
				getline(cin.ignore(), candidateName);

				numberOfVote(candidateName,can_Name,can_Count);
				break;
			case 'A':
				//Add vote (integer) to the candidate 
				cout << "Enter your ID: ";
				cin >> id;

				/* the isNumber checks if the input is in number format or not, once it satisfies
				* the required format, it checks if id is registered or not (isID (vector, id)),
				* and process the data.
				*/
				if (!isNumber(id)) {
					cout << "Please enter your id in number format" << endl;
				}
				else if (isNumber(id) && isID(voterID, stoi(id)) != -1 ) {
					cout << "Welcome back, " << voterName[isID(voterID, stoi(id))] << endl;
						
						string voteNum;
						bool flag = true;
						cout << "\nEnter candidate's name (Please start the name with capital letter): ";
						getline(cin.ignore(), candidateName);

						if (isName(can_Name, candidateName)) {

							cout << "\nEnter number of votes: ";
							cin >> voteNum;
							if(!isNumber(voteNum)){
								cout << "Not a valid number, Please try again \n";
							}
							else {
								
								addVoteToCandidate(candidateFile, stoi(voteNum), candidateName, can_Name, can_Count);
							}

						}
						else {
							cout << candidateName << " does not exists, Please try again" << endl;
	
						}

				}
				else {
					cout << "You are not registered" << endl;
				}

				break;
			case 'S':
				//Display smallest number of votes
				displaySmallestNumber(candidateFile);

				break;
			case 'L':
				//Display largest number of votes
				displaylargestNumber(candidateFile);

				break;
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


/*function definition*/

//check if the database exists
bool fexist(string file) {
	ifstream isFile;
	isFile.open(file);
	return !isFile.fail();
}



void importCandidateToArray(string file,vector<string> &vect1, vector<string> &vect2, vector<int> &vect3, vector<string> &vect4, vector<int> &vect5) {
	string symbol, canName, age, suburb, count;

	ifstream inFile(file);
	string line;
	getline(inFile, line);  //ignore the first line (heading)

	if (inFile.is_open()) {

		while (!inFile.eof()) {  

			/*dataset in candidate file: Eureka,Stephen Cummings,51,Kensington,50 
			*							Nationals,Burke Lambert,61,Parkville,59
			*/
			getline(inFile, symbol, ','); //get first data e.g. Eureka
			vect1.push_back(symbol);	//push into vector 

			getline(inFile, canName, ','); // move to next data e.g. Stephen Cummings
			vect2.push_back(canName);	//push into vector

			getline(inFile, age, ','); //move to next e.g. 51
			vect3.push_back(stoi(age));//push into vector

			getline(inFile, suburb, ','); //move to next e.g.Kensington
			vect4.push_back(suburb);//push into vector

			getline(inFile, count, '\n');  //move to next e.g. 50
			vect5.push_back(stoi(count));//push into vector

		}

		/*for (int i = 0; i < vect1.size(); i++) {
			cout << vect1[i] << endl;
		}*/
		inFile.close();
	}
	else {
		cout << "unable to open the database" << endl;
	}
	
}

void importVoterToArray(string file, vector<int>& vect1, vector<string>& vect2, vector<int>& vect3, vector<string>& vect4, vector<string>& vect5)
{
	string id, name, age, suburb,status;

	ifstream inFile(file);
	string line;
	getline(inFile, line); //ignore the first line (heading)

	if (inFile.is_open()) {
		while (!inFile.eof()) {
			getline(inFile, id, ',');
			vect1.push_back(stoi(id));

			getline(inFile, name, ',');
			vect2.push_back(name);

			getline(inFile, age, ',');
			vect3.push_back(stoi(age));

			getline(inFile, suburb, ',');
			vect4.push_back(suburb);

			getline(inFile, status, '\n');
			vect5.push_back(status);

		}

		/*for (int i = 0; i < vect1.size(); i++) {
			cout << vect1[i] << endl;
		}*/
		inFile.close();
	}
	else {
		cout << "unable to open the Voter database" << endl;
	}

	
}

void numberOfVote(string name, vector<string>& vect1, vector<int>& vect2) {
	int vote = -1;
	for ( int i = 0; i < vect1.size(); i++) {

		if (vect1[i].compare(name) == 0) {
			vote = vect2[i];
		}
		if (vect1[i].compare(name) == 0 &&  vect2[i] ==0) {
			vote = 0;
		}
	}

	if (vote > 0){
		cout << name << " has " << vote << " votes." << endl;
	}
	if (vote == 0) {
		cout << "the list is empty" << endl;
	}
	if (vote == -1) {
		cout << name << " is not listed in the database" << endl;
	}
}

bool isName(vector<string>& vect1, string name) {
	for (int i = 0; i < vect1.size(); i++) {
		if (vect1[i].compare(name) == 0) {
			return true;
		}
	
	}
	return false;
	
}

int isID(vector<int>& vect1, int id)
{
	for (int i = 0; i < vect1.size(); i++) {
		if (vect1[i] == id) {
			return i;
		}	
	}
	return -1;
}

bool isNumber(string id)
{
	for (int i = 0; i < id.length(); i++) {
		if (isdigit(id[i])) {
			return true;
		}
	}
	return false;
}



/*this function update the count in candidate file, then open the candidate.txt for reading,
open a new file temp.txt to copy data from candidates.txt with updated count. Finally, delete the candidates.txt
and rename temp.txt to candidates.txt*/
void addVoteToCandidate(string file, int voteNum, string name, vector<string>& canName, vector<int>& canCount) {

	string line, symbol, nameofCan, age, suburb, count;
	string newLine;
	int pos = 0;

	for (int i = 0; i < canName.size(); i++) {
		if (canName[i].compare(name) == 0) { // search for name
			canCount[i] += voteNum; // update count
			pos = i; // get position in the array
		}
	}

	// open file for reading
	ifstream inFile;
	inFile.open(file);

	// open new file for writing
	ofstream tempFile;
	tempFile.open("temp.txt");

	bool firstline = true;

	if (inFile.is_open() && tempFile.is_open()){

		while (!inFile.eof()) {
			//extracting "," and "\n" and store data 
			getline(inFile, symbol, ','); 
			getline(inFile, nameofCan, ',');
			getline(inFile, age, ',');
			getline(inFile, suburb, ',');
			getline(inFile, count, '\n');


			if (!firstline) { //delete a new line from the end of the text file
				tempFile << endl;
			}
			firstline = false;

			//compare the current candidate's name with the updated cadidate's count, and update the line in file
			if (nameofCan.compare(canName[pos]) == 0) {	

				newLine = symbol + "," + nameofCan + "," + age + "," + suburb + "," + to_string(canCount[pos]);
				tempFile << newLine; // save to the new file
			}
			else {
				newLine = symbol + "," + nameofCan + "," + age + "," + suburb + "," + count;
				tempFile << newLine;// save to the new file
			}


		}

		inFile.close();
		tempFile.close();
		remove("candidates.txt"); // delete the old file 

		if (rename("temp.txt", "candidates.txt") != 0) {
			cout << "ERROR renaming file" << endl;
		}
		else {
			cout << "Number of votes added successfully" << endl
				<< canName[pos] << " now has " << canCount[pos] << " votes" << endl;
		}

	}else {
		cout << "ERROR! Cannot access the database" << endl;
	}

}

void displaySmallestNumber(string file)
{
	string nameCurrentLine;
	string name;
	int votes = 0xfffffff;
	ifstream inFile(file);
	string line;
	int index = 0;
	getline(inFile, line); //skip the first line
	while (!inFile.eof()) {
		for (int index = 0; index < 5; index++) {
			if (index < 4) {
				getline(inFile, line, ',');
			}
			else {
				getline(inFile, line);
			}
			if (index == 1) {
				nameCurrentLine = line;
			}
			if (index == 4) {
				if (stoi(line) < votes) {
					name = nameCurrentLine;
					votes = stoi(line);
				}
			}
		}
	}

	inFile.close();
	cout << "The candidate with the smallest number of votes is " << name << " with " << votes << endl;

}

void displaylargestNumber(string file)
{

	string nameCurrentLine;
	string name;
	int votes = 0;
	ifstream inFile(file);
	string line;
	int index = 0;
	getline(inFile, line); //skip the first line
	while (!inFile.eof()) {
		for (int index = 0; index < 5; index++) {
			if (index < 4) {
				getline(inFile, line, ',');
			}
			else {
				getline(inFile, line);
			}
			if (index == 1) {
				nameCurrentLine = line;
			}
			if (index == 4) {
				if (stoi(line) > votes) {
					name = nameCurrentLine;
					votes = stoi(line);
				}
			}
		}
	}

	inFile.close();
	cout << "The candidate with the smallest number of votes is " << name << " with " << votes << endl;
}