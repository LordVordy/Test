//Daniel Scott
//Assignment 5
//TA: Jason Zietz


#include <iostream>
#include <fstream>
#include <sstream>
#include "MovieTree.cpp"
using namespace std;


int main(int argc, char* argv[]) {
	MovieTree tree;

	string line, rank, title, year, quantity, fTitle, c;

	bool replay = true;

	int menuChoice = 0;

	ifstream infile(argv[1]);

	if(infile.good()) {
		while(getline(infile, line)) {
			stringstream ss(line);
			getline(ss, rank, ',');
			getline(ss, title, ',');
			getline(ss, year, ',');
			getline(ss, quantity);
			tree.addMovieNode(stoi(rank), title, stoi(year), stoi(quantity));
		}
	}
	else {
		cout << "Error opening file " << argv[1] << endl;
	}


	while(replay) {
		cout << "======Main Menu======" << endl;
		cout << "1. Find a movie" << endl;
		cout << "2. Rent a movie" << endl;
		cout << "3. Print the inventory" << endl;
		cout << "4. Delete a movie" << endl;
		cout << "5. Count movies" << endl;
		cout << "6. Quit" << endl;

		cin >> menuChoice;

		if(menuChoice == 3) {
			tree.printMovieInventory();
		}

		if(menuChoice == 6) {
			replay = false;
		}

		if(menuChoice == 5) {
			tree.countMovies();
		}

		if(menuChoice == 1 || menuChoice == 2 || menuChoice == 4) {
			cout << "Enter title:" << endl;
			
			cin.ignore(256,'\n');
			getline(cin, fTitle);

			if(menuChoice == 1) {
				tree.findMovie(fTitle);
			}
			else if(menuChoice == 4) {
				tree.deleteMovie(fTitle);
			}
			else {
				tree.rentMovie(fTitle);
			}


		}
	} cout << "Goodbye!";


}