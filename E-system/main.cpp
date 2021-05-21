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

bool fexist(string file);

//void storeDataintoVector()
void numberOfVote(string name, string file);



int main() {

	char option, input; // variable to work with user's input
	string candidateName;

	const string voterFile = "voters.txt";
	const string candidateFile = "candidates.txt";

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


			/*the switch-case then is used to idenfify choices from the user. depending on user's choice,
			each case calls coresponding function to execute.
			Invalid choice is prompted to try again*/
			switch (option) {
			case 'P':
				//Display number of votes
				//cout << "Enter candidate's name: " << endl;
				//cin >> candidateName;
				numberOfVote(candidateName, candidateFile);


				break;
			case 'A':
				//Add vote (integer) to the candidate 



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
// another fucntion to get the count in candidate database 


void numberOfVote(string name, string file) {


	string symbol, canName, age, suburb, count;
	vector <string> sym_bol;
	vector <string> can_Name;
	vector <int> can_Age;
	vector <string> sub_burb;
	vector <int> can_Count;

	
	string line;
	getline (inFile,line);  //ignore the first line (heading)
	//cout << line;
	
	if (inFile.is_open()) {
		
		while (!inFile.eof()) {
			getline(inFile,symbol , ',');
			sym_bol.push_back(symbol);

			getline(inFile,canName, ',');
			can_Name.push_back(canName);

			getline(inFile,age, ',');
			can_Age.push_back(stoi(age));

			getline(inFile,suburb, ',');
			sub_burb.push_back(suburb);

			getline(inFile,count, '\n');
			can_Count.push_back(stoi(count));
			
		}
		
		for (int i = 0; i < can_Age.size(); i++){
			cout <<can_Age[i] << endl;
		}
		

	}
	else {
		cout << "unable to open the database" << endl;
	}


}
