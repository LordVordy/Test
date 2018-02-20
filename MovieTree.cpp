//Daniel Scott
//Assignment 5
//TA: Jason Zietz


#include <iostream>
#include "MovieTree.hpp"
using namespace std;


MovieTree::MovieTree() {
	root = NULL;//new MovieNode;
	// root->parent = NULL;
	// root->leftChild = NULL;
	// root->rightChild = NULL;
	// root->ranking = 0;
	// root->title = "";
	// root->year = 0;
	// root->quantity = 0;
}

void delTree(MovieNode* node)
{
	if (node != NULL) {
		delTree(node->leftChild);
		delTree(node->rightChild);
		delete node;
	}
}

MovieTree::~MovieTree() {
	delTree(root);
}

void print(MovieNode* node) {
	if(node == NULL) {
		return;
	}

	print(node->leftChild);
	cout << "Movie: " << node->title << " " << node->quantity << endl; 
	print(node->rightChild);
}

void MovieTree::printMovieInventory() {
	print(root);
}

MovieNode* newNode(int ranking, std::string title, int year, int quantity) {

	MovieNode* newNode = new MovieNode;
	newNode->title = title;
	newNode->year = year;
	newNode->quantity = quantity;
	newNode->ranking = ranking;	
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;
	return newNode;
}

MovieNode* addNode(MovieNode* node, int ranking, std::string title, int year, int quantity) {
	
	if(node->title == "") {
		node->ranking = ranking;
		node->title = title;
		node->year = year;
		node->quantity = quantity;
	}
	else if(title < node->title) {
		if(node->leftChild != NULL) {
			addNode(node->leftChild, ranking, title, year, quantity);
		}
		else {
			node->leftChild = newNode(ranking, title, year, quantity);
			node->leftChild->parent = node->leftChild;
		}
	}
	else if(title > node->title) {
		if(node->rightChild != NULL) {
			addNode(node->rightChild, ranking, title, year, quantity);
		}
		else {
			node->rightChild = newNode(ranking, title, year, quantity);
			node->rightChild->parent = node->rightChild;
		}
	}
	else {
		cout << "node with title " << title << " already in tree" << endl;
	}

	return node;
}

void MovieTree::addMovieNode(int ranking, std::string title, int year, int quantity) {
	if(root == NULL) {
		root = newNode(ranking, title, year, quantity);
	}
	else {
		addNode(root, ranking, title, year, quantity);
	}
}

void MovieTree::findMovie(std::string title) {
	MovieNode* foundMovie;
	foundMovie = search(root, title);

	//If found
	if(foundMovie != NULL) {
		cout << "Movie Info:" << endl;
		cout << "===========" << endl;
		cout << "Ranking:" << foundMovie->ranking << endl;
		cout << "Title:" << foundMovie->title << endl;
		cout << "Year:" << foundMovie->year << endl;
		cout << "Quantity:" << foundMovie->quantity << endl;
	}
	//Not found
	else {
		cout << "Movie not found." << endl;
	}

	//delete foundMovie;
}

void MovieTree::rentMovie(std::string title) {
	MovieNode* foundMovie;
	foundMovie = search(root, title);

	//If found
	if(foundMovie == NULL) {
		//If movie not found in tree
		cout << "Movie not found." << endl;
	}
	//Not found
	else if(foundMovie->quantity == 0){
		//If movie is out of stock
		cout << "Movie out of stock." << endl;
	}
	else {
		//If movie is in stock
		foundMovie->quantity--;
		cout << "Movie has been rented." << endl;
		cout << "Movie Info:" << endl;
		cout << "===========" << endl;
		cout << "Ranking:" << foundMovie->ranking << endl;
		cout << "Title:" << foundMovie->title << endl;
		cout << "Year:" << foundMovie->year << endl;
		cout << "Quantity:" << foundMovie->quantity << endl;

		if(foundMovie->quantity == 0) {
			deleteMovie(title);
		}
	}

	//delete foundMovie;
}

MovieNode *MovieTree::search(MovieNode *node, std::string title) {
	MovieNode *current;
    current = node;
    while(current !=NULL){
        if(current->title == title){
            return current ;
        }
        else if(current->title < title){
            current = current->rightChild;
        }
        else{
            current = current->leftChild;
        }
    }
    return current;
}

string getMinValue(MovieNode* node) {
	if(node->leftChild != NULL) {
		return getMinValue(node->leftChild);
	}
	else {
		return node->title;
	}
}

MovieNode* delNode(MovieNode* node, string title) {

	//Gets root val

	//Check if the node is NULL
	if(node == NULL) {
		cout << endl << "Movie not found." << endl << endl;
		return NULL;
	}
	// cout << "delnode called!!!" << endl;
	//Check if on the left
	if(node->title > title) {
		// cout << " -:- Node is to the left" << endl;
		node->leftChild = delNode(node->leftChild, title);
	}

	//Check if on the right
	else if(node->title < title) {
		// cout << " -:- Node is to the right" << endl;
		node->rightChild = delNode(node->rightChild, title);
	}

	//Title matches the one to be deleted
	else {

		// cout << " -:- Node matches searched node" << endl;
		//Check if at most one child
		if(node->leftChild == NULL) {
			// cout << " -:- Left node is NULL" << endl;
			MovieNode* tNode = node->rightChild;
			delete node;
			return tNode;
		}

		else if(node->rightChild == NULL) {
			// cout << " -:- Right node is NULL" << endl;
			MovieNode* tNode = node->leftChild;
			delete node;
			return tNode;
		}

		//The node has two children
		// cout << " -:- Node has two children" << endl;
		string minVal = getMinValue(node->rightChild);
		// cout << " -:- Searching for " << minVal << endl;

		//SEARCH
		MovieNode *current;
	    current = node->rightChild;
	    while(current !=NULL){
	        if(current->title == minVal){
	            break;
	        }
	        else if(current->title < minVal){
	            current = current->rightChild;
	        }
	        else{
	            current = current->leftChild;
	        }
	    }
	    MovieNode* tNode = current;
		//END SEARCH

		node->title = tNode->title;
		// node->parent = tNode->parent;
		// node->leftChild = tNode->leftChild;
		// node->rightChild = tNode->rightChild;
		node->ranking = tNode->ranking;
		node->year = tNode->year;
		node->quantity = tNode->quantity;
		
		node->rightChild = delNode(node->rightChild, tNode->title);
	}
	return node;
}

void MovieTree::deleteMovie(string title) {
	root = delNode(root, title);
}

int counter(MovieNode* node) {
	int size = 0;
	if(node != NULL) {
		size++;
		size+=counter(node->leftChild);
		size+=counter(node->rightChild);
	}
	return size;
}

void MovieTree::countMovies() {
	cout << "Count = " << counter(root) << endl;
}