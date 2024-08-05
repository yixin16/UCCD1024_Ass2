#include	<iostream>
#include <iomanip>
#include <string>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include	"BST.h"
#include    "Student.h"

using namespace std;

bool readFile(const char *, BST *);
int menu();

int main() {

	//variable declaration
	BST t1;
	Student stu1;

	int choice, order, source;
	char filename[30] = "student.txt";

	do {

		BST t2;
		choice = menu();

		if (choice == 1) {                       //option 1: Read data to BST

			if (readFile(filename, &t1)) {
				cout << endl;
				cout << t1.count << " records have been successfully read into the Binary Search Tree from \"student.txt\"." << endl;
			}
			else
				cout << "\nUnable to open " << filename << endl;

		}

		else if (choice == 2) {                  //option 2: Print deepest nodes

			//readFile(filename, &t1);
			t1.deepestNodes();
			cout << endl;
		}

		else if (choice == 3) {                  //option 3: Display student

			//readFile(filename, &t1);
			cout << "In what order you want to display the student's information? (1 - Ascending / 2 - Descending): ";
			cin >> order;

			cout << "Where do you want to display the output? (1 - Screen / 2 - File): ";
			cin >> source;

			if (!t1.display(order, source)) {
				cout << endl << "The Binary Search Tree is currenty empty." << endl;
				cout << "Please try again." << endl;
			}
		}

		else if (choice == 4) {                  //option 4: Clone Subtree

			//readFile(filename, &t1);
			cout << "Please enter the node you wish to clone: ";
			cin >> stu1.id;
			cout << "\n=====================================================" << endl;
			cout << "t1 in pre-order display:" << endl;
			t1.preOrderPrint();
			cout << "=====================================================" << endl;
			cout << endl;

			if (t2.CloneSubtree(t1, stu1)) {
				if (!t2.empty()) {
					cout << "=====================================================" << endl;
					cout << endl;
				}

				else
					cout << "\nThe subtree for " << stu1.id << " cannot be found in BST t1." << endl;
			}

		}

		else if (choice == 5) {                   //option 5: Print Level Nodes
			//readFile(filename, &t1);
			t1.printLevelNodes();
			cout << endl;
		}

		else if (choice == 6) {                   //option 6: Print Path
			//readFile(filename, &t1);
			cout << "Below are all the external paths for the tree:" << endl;
			t1.printPath();
			cout << endl;
		}

		else {
			cout << "\n\n\nExiting the program..." << endl;
			break;                               //Exit the do while loop if user selects 'Exit' option
		}

		cout << endl;

	} while (choice >= 1 && choice <= 6);

	system("pause");
	return 0;
}


bool readFile(const char* filename, BST* t1) {         //read from the text file and store the information into a BST

	string temp;
	ifstream readFile;

	if (t1->empty()) {                           //ensure there will be no duplicate content of BST if user continue to
		readFile.open(filename);                 //read the file again

		if (readFile.is_open()) {                //check if the text file is successfully opened or not
			while (!readFile.eof()) {

				Student student;

				//Read the text file
				//store the information into student struct
				getline(readFile, temp, '=');
				readFile >> student.id;

				getline(readFile, temp, '=');
				readFile.getline(student.name, 30);

				getline(readFile, temp, '=');
				readFile.getline(student.address, 100);

				getline(readFile, temp, '=');
				readFile >> student.DOB;

				getline(readFile, temp, '=');
				readFile >> student.phone_no;

				getline(readFile, temp, '=');
				readFile >> student.course;

				getline(readFile, temp, '=');
				readFile >> student.cgpa;

				t1->insert(student);	         //insert the content of student struct into BST
			}                                    //the BST.cpp
		}

		else {
			return false;
		}

		readFile.close();
	}
	return true;
}

int menu() {                                     //main menu

	int choice;

	cout << "Menu:\n" << endl;
	cout << "(1) Read data to BST" << endl;
	cout << "(2) Print deepest nodes" << endl;
	cout << "(3) Display student" << endl;
	cout << "(4) Clone Subtree" << endl;
	cout << "(5) Print Level Nodes" << endl;
	cout << "(6) Print Path" << endl;
	cout << "(7) Exit" << endl;

	cout << "Enter your choice: ";               //prompt user to enter their choice
	cin >> choice;

	return choice;
}