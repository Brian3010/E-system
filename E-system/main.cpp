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
bool isID(vector<int>& vect1, int id);
bool isNumber(string id);

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
				else if (isNumber(id) && isID(voterID, stoi(id)) ) {
					cout << "registered" << endl;
					/*cout << "Enter candidate's name (Please start the name with capital letter): ";
					getline(cin.ignore(), candidateName);*/

					/*if (isName(can_Name, candidateName)) {
						cout << "true";

					}
					else {
						cout << "false";
					}*/
					bool flag = false;
					do {
						int voteNum;
						cout << "\nEnter candidate's name (Please start the name with capital letter): ";
						getline(cin.ignore(), candidateName);
						
						if (isName(can_Name, candidateName)) {
							cout << "true";
							cout << "enter number of votes: ";
							cin >> voteNum;
							addVoteToCandidate(candidateFile, voteNum,candidateName, can_Name, can_Count);
							flag = true;
						}
						else {
							cout << "false";
							flag = false;
							
						}

					} while (flag != false);
				}
				else {
					cout << "not registered" << endl;
				}
				
				

				break;
			case 'S':
				//Display smallest number of votes



				break;
			case 'L':
				//Display largest number of votes



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

bool isID(vector<int>& vect1, int id)
{
	for (int i = 0; i < vect1.size(); i++) {
		if (vect1[i] == id) {
			return true;
		}	
	}
	return false;
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

void addVoteToCandidate(string file, int voteNum, string name, vector<string>& canName, vector<int>& canCount)
{
	string line, symbol, nameofCan, age, suburb, count;

	int newCount = 0;
	int pos =0;
	//bool flag = false;
	for (int i = 0; i < canName.size(); i++) {
		if (canName[i].compare(name) == 0) {
			canCount[i] += voteNum;
			newCount = canCount[i];
			pos = i;
			//flag = true;
		}

	}

	cout << newCount;
	fstream inFile;
	//https://stackoverflow.com/questions/34507989/update-and-delete-data-from-file-in-c
	inFile.open(file, ios::in );
	int j = 0;
	if (inFile.is_open()){
		while (!inFile.eof()) {
			getline(inFile, symbol, ',');
			getline(inFile, nameofCan, ',');
			getline(inFile, age, ',');
			getline(inFile, suburb, ',');
			getline(inFile, count, '\n');
		
			if (nameofCan.compare(canName[pos]) == 0) {
			
				count = to_string(newCount);
				cout << count << endl;
				line = symbol + ",as" + nameofCan + "," + age + "," + suburb + "," + count;
				cout << line << "found" << endl;
			}
			else {
				line = symbol + ",as" + nameofCan + "," + age + "," + suburb + "," + count ;
			}
			ofstream inFile2;
			inFile2.open(file, ios::app | ios::out);
			if (inFile2.is_open()) {
				inFile2 << line<< endl;
				inFile2.close();
			}
			/*cout << j << ": " << line << endl;
			j++;*/
			//cout << nameofCan << " asd " << endl;
			
		}
		inFile.close();
		
		
	}
	
	
	//inFile.close();
	
	
}

