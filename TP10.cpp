// To compile on Linux use g++ -std=c+11 name_of_file.cpp
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAXLEN 256

void save();

class Student {
	string fname, lname, unum, email;
	int pres, paper, proj;
public:
	Student(string, string, string, string, int, int, int);
	void set_fname(string);
	void set_lname(string);
	void set_unum(string);
	void set_email(string);
	void set_pres(int);
	void set_paper(int);
	void set_proj(int);
	string get_lname() { return lname; };
	string get_fname() { return fname; };
	string get_unum() { return unum; };
	string get_email() { return email; };
	int get_pres() { return pres; };
	int get_paper() { return paper; };
	int get_proj() { return proj; };
};

Student::Student(string x, string v, string y, string z, int a = 0, int b = 0, int c = 0) {
	fname = x;
	lname = v;
	unum = y;
	email = z;
	pres = a;
	paper = b;
	proj = c;
}

void Student::set_fname(string x)
{
	fname = x;
}

void Student::set_lname(string x){
	lname = x;
}

void Student::set_unum(string x)
{
	unum = x;
}

void Student::set_email(string x)
{
	email = x;
}

void Student::set_pres(int x)
{
	pres = x;
}

void Student::set_paper(int x)
{
	paper = x;
}

void Student::set_proj(int x)
{
	proj = x;
}

vector<Student> database;

// Displays student data, all of the class or just one student. READ ONLY. INDEPENDENT FUNCTION
void DISPLAY() {
	cout << "--------------Student Information--------------" << endl << endl;

	for (int i = 0; i < database.size(); i++) {
		cout << i+1 << ". " << database[i].get_fname() << "\t" << database[i].get_lname() << "\t" << database[i].get_unum() << "\t" << database[i].get_email() << "\tPresentaion:";
		cout << database[i].get_pres() << "\tPaper:" << database[i].get_paper() << "\tProject:" << database[i].get_proj() << endl;
	}
}

// Write student data or change it
void WRITE() {
	int input = 0;
	int nxtinput = 0;
	int grade = 0;

	bool check = false;
	while(!check){
		DISPLAY();
		cout << "Enter the Number of the student whose grade you wish to alter: ";
		cin >> input;
		if((input > 0) && (input < database.size()+1)) check = true;
		else cout << "\nInvalid entry, try a valid number(i.e. 1-" << database.size() << ").\n";
	}
	check = false;
	while(!check){
		cout << "1. Presentation " << database[input-1].get_pres() << "\n2. Paper " << database[input-1].get_paper() << "\n3. Project " << database[input-1].get_proj() << "\nWhich grade? ";
		cin >> nxtinput;
		if((nxtinput > 0) && (nxtinput < 4)) check = true;
		else cout << "\nPlease use a valid number.\n";
	}
	check = false;
	while(!check){
		cout << "\nNew grade?(0-4)";
		cin >> grade;
		if((grade >= 0) && (grade < 5)) check = true;
		else cout << "\nStop making me repeat myself.\n";
	}
	switch(nxtinput){
		case 1:
			database[input-1].set_pres(grade);
			break;
		case 2:
			database[input-1].set_paper(grade);
			break;
		case 3:
			database[input-1].set_proj(grade);
			break;
	}
	DISPLAY();
}

// Adds student to the database
void ADD() {
	string nfName, nlName, nUnum, nEmail;
	cout << "Student First Name:";
	cin >> nfName;
	cout << endl << "Student's Last Name:";
	cin >> nlName;
	cout << endl << "Student's UNumber:";
	cin >> nUnum;
	cout << endl << "Student's Email:";
	cin >> nEmail;
	Student nStu = Student(nfName, nlName, nUnum, nEmail, 0, 0, 0);
	database.push_back(nStu);
	DISPLAY();
	save();
}

// Delete student from database
void DELETE() {
	int input = 0;
	char confirm;
	bool check = false;
	while(!check){
		DISPLAY();
		cout << "Enter the Number of the student that you want to delete: ";
		cin >> input;
		if((input > 0) && (input < database.size()+1)) check = true;
		else cout << "Invalid entry, try a valid number(i.e. 1-" << database.size()+1 << ").\n";
	}
	cout << "\nName: " << database[input-1].get_fname() << " " << database[input-1].get_lname() << "\nU Number: " << database[input-1].get_unum();
	check = false;
	while(!check){
		cout << "\nDelete this Student?(y/n):";
		cin >> confirm;
		if(confirm == 'y'){
			database.erase(database.begin() + input - 1);
			check = true;
		}
		else if(confirm == 'n') {
			check = true;
		}
		else cout << "This is a simple choice between y or n, try again.\n";
	}
	DISPLAY();
	save();
}

// Saerch for a student
void SEARCH() {
	int found[20];
	bool check = false;
	string name;
	char sel;
	DISPLAY();
	int j = 0;
	for(int i = 0; i < 20; i++){
		found[i] = -1;
	}
	while(!check){
		cout << "SEARCH for a Student by\n\t1. Last Name\n\t2. First Name\n\t3. U Number\n\t4. Email Address\nPlease Chose(1-4):";
		cin >> sel;
		if((sel > '0') && (sel < '5')) check = true;
		else cout << "You chose poorly, try again.\n";
	}
	cout << "Enter search criteria: ";
	cin >> name;
	switch(sel){
		case '1':
			for(int i = 0; i < database.size(); i++){
				if(name.compare(database[i].get_lname()) ==0){
					found[j] = i;
					j++;
				}
			}
			break;
		case '2':
			for(int i = 0; i < database.size(); i++){
				if(name.compare(database[i].get_fname()) ==0){
					found[j] = i;
					j++;
				}
			}
			break;
		case '3':
			for(int i = 0; i < database.size(); i++){
				if(name.compare(database[i].get_unum()) ==0){
					found[j] = i;
					j++;
				}
			}
			break;
		case '4':
			for(int i = 0; i < database.size(); i++){
				if(name.compare(database[i].get_email()) ==0){
					found[j] = i;
					j++;
				}
			}
			break;
	}
	cout << "Found " << j << " matching accounts listed below.\n";

	for(int j = 0; j < 20; j++){
		if(found[j] >= 0) {
			int i = found[j];
			cout << j+1 << ". " << database[i].get_fname() << "," << database[i].get_lname() << "," << database[i].get_unum() << "," << database[i].get_email() << "," << database[i].get_pres() << "," << database[i].get_paper() << "," << database[i].get_proj() << endl;
		}
	}

	cout << endl;

}

// Search for a student
void UPDATE() {
	char input[256];
	char nxtinput = 0;
	char grade = 0;
	int i;
	string nwAtt;
	bool check = false;
	while(!check){
		DISPLAY();
		cout << "Enter the Number of the student to be modified: ";
		cin.getline(input, 256, '\n');
		if(input[0] > 48 && input[0] < 58){
			i = atoi(input);
			if((i > 0) && (i < database.size()+1)) check = true;
			else cout << "\nInvalid entry, try a valid number(i.e. 1-" << database.size()+1 << ").\n";
		}
		else cout << "\nInvalid entry, try a valid number(i.e. 1-" << database.size()+1 <<").\n";
	}

	check = false;
	while(!check){
		cout << "1. First Name " << database[i-1].get_fname() << "\n2. Last Name " << database[i-1].get_lname() << "\n3. Email " << database[i-1].get_email() << "\n4. U Number " << database[i-1].get_unum() << "\nWhich attribute? ";
		cin >> nxtinput;
		if((nxtinput > 48) && (nxtinput < 53)) check = true;
		else cout << "\nPlease use a valid number.\n";
	}

	check = false;
	while(!check){
		cout << "\nNew attribute:";
		cin >> nwAtt;
		check = true;
	}

	switch(nxtinput){
		case '1':
			database[i-1].set_fname(nwAtt);
			break;
		case '2':
			database[i-1].set_lname(nwAtt);
			break;
		case '3':
			database[i-1].set_email(nwAtt);
			break;
		case '4':
			database[i-1].set_unum(nwAtt);
			break;
	}
	DISPLAY();
	save();
}

void save(){
	ofstream outfile;
	outfile.open("database.txt");
	for(int i = 0; i < database.size(); i++){
		outfile << database[i].get_fname() << "," << database[i].get_lname() << "," << database[i].get_unum() << "," << database[i].get_email() << "," << database[i].get_pres() << "," << database[i].get_paper() << "," << database[i].get_proj() << endl;
	}
	outfile.close();
}

int main() {
	FILE *fp;
	char str[MAXLEN];
	char *fn;
	char *ln;
	char *em;
	char *un;
	char *pres;
	char *pap;
	char *project;

	string line;

	//ifstream db("database.txt");

	//if (db.is_open()) {//checks if it is open
	if((fp = fopen("database.txt", "r")) != NULL){

		while(fgets(str, MAXLEN, fp) != NULL){
			fn = strtok(str, ",");
			ln = strtok(NULL, ",");
			un = strtok(NULL, ",");
			em = strtok(NULL, ",");
			pres = strtok(NULL, ",");
			pap = strtok(NULL, ",");
			project = strtok(NULL, ",");
			Student tmp = Student(fn, ln, un, em, atoi(pres), atoi(pap), atoi(project));
			database.push_back(tmp);

		}
	}
	else {

		// file decleration
		ofstream outfile;

		// Creat file
		outfile.open("database.txt");

		// Populating the file
		outfile << "Rick,Sanchaz,u01234567,regularrick@gmail.com,0,0,0" << endl;
		outfile << "Morty,Smith,u76543210,morty@gmail.com,3,3,2" << endl;
		outfile << "Summer,Smith,u88965238,summer@gmail.com,4,4,3" << endl;
		outfile << "Walter,White,u96571368,hizenburg@gmail.com,2,2,2" << endl;
		outfile << "Jesse,Pinkman,u79269858,pinkman@gmail.com,1,2,1" << endl;

		outfile.close();
		fp = fopen("database.txt", "r");

		while(fgets(str, MAXLEN, fp) != NULL){
			fn = strtok(str, ",");
			ln = strtok(NULL, ",");
			un = strtok(NULL, ",");
			em = strtok(NULL, ",");
			pres = strtok(NULL, ",");
			pap = strtok(NULL, ",");
			project = strtok(NULL, ",");
			Student tmp = Student(fn, ln, un, em, atoi(pres), atoi(pap), atoi(project));
			database.push_back(tmp);

		}
	}

	char choice;

	while (true) {
		cout << "\nWelcome to USF Class-Roll System\n";
		cout << "1: READ Student Data\n";
		cout << "2: WRITE Student Data\n";
		cout << "3: ADD Student\n";
		cout << "4: DELETE Student\n";
		cout << "5: SEARCH Student\n";
		cout << "6: UPDATE Student\n";
		cout << "7: EXIT\n";
		cout << "Enter in a number (1-7): ";

		cin >> choice;
		
		switch (choice)
		{
			case('1'):
				DISPLAY();
				break;
			case('2'):
				WRITE();
				break;
			case('3'):
				ADD();
				break;
			case('4'):
				DELETE();
				break;
			case('5'):
				SEARCH();
				break;
			case('6'):
				UPDATE();
				break;
			case('7'):
				return 0;
				break;
			default:
				cout << "\nYou have entered an incorrect selection\nPlease try again!\n\n";
				break;
		}
	}

	return 0;
}