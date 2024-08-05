#include <iostream>
#include <fstream>
#include <algorithm>
#include "BST.h"
#include <string>

using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;

	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode *cur, int &count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode *cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)){

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode *cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode			*cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode	*cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode *cur, BTNode *newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)){
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode *pre, BTNode *cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)){
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode *pre, BTNode *cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode *cur) {
	BTNode		*is, *isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}


bool BST::deepestNodes() {
	int count = 0, lvl;    // initialize the variable

	if (empty())
	{
		cout << endl << "Binary Search Tree is currently.";
		cout << endl <<"Please try again." << endl << endl;
		return false;            //special case
	}
	deepestNodes2(root, count, lvl);

	return true;
}

void BST::deepestNodes2(BTNode* cur, int& count1, int& lvl) {
	int count = count1;
	if (cur == NULL)
		return;             //special case

	count++;

	if (lvl < count)  
		lvl = count;
	deepestNodes2(cur->left, count, lvl);
	deepestNodes2(cur->right, count, lvl);
	if (count == lvl) {
		cout << "=====================================================" << endl;
		cout << "Student id(s) located in the deepest nodes: ";
		cout << cur->item.id << endl;       //Display the nodes within the maximum level which is the deepest in BST
		cout << "=====================================================" << endl;
	}
}

bool BST::display(int order, int source) {

	if (root == NULL)                           //handle special case
		return false;

	return display2(root, order, source);       //handle normal case 

}

bool BST::display2(BTNode* cur, int order, int source) {

	ofstream outFile("student-info.txt", ios::app);

	if (cur == NULL)
		return false;

	if (order == 1 && source == 1)              //Display content of node on screen in ascending order     
	{
		displayAsc(cur, cout);
	}
	if (order == 1 && source == 2)              //Display content of node on text file in ascending order 
	{
		displayAsc(cur, outFile);
		cout << "\n\nAll records have been written into \"student-info.txt\".\n\n";
	}

	if (order == 2 && source == 1)              //Display content of node on screen in descending order 
		displayDesc(cur, cout);

	if (order == 2 && source == 2)              //Display content of node on text file in descending order 
	{
		displayDesc(cur, outFile);
		cout << "\n\nAll records have been written into \"student-info.txt\".\n\n";
	}
	outFile.close();
	return true;
}

void BST::displayAsc(BTNode* cur, ostream& write) {      //To display the output in ascending order

	if (cur == NULL)
		return;

	displayAsc(cur->left, write);
	cur->item.print(write);
	displayAsc(cur->right, write);

}

void BST::displayDesc(BTNode* cur, ostream& write) {     //To display the output in descending order

	if (cur == NULL)
		return;

	displayDesc(cur->right, write);
	cur->item.print(write);
	displayDesc(cur->left, write);
}

bool BST::CloneSubtree(BST t1, type item) {

	BTNode* cur = t1.root;
	if (t1.empty())
	{
		cout << "Binary Seach Tree is currently empty.\nCannot clone subtree.\nPlease try again.\n\n";
		return false;		//special case
	}
	CloneSubtree2(cur, item);
	cout << "Subtree t2 in pre-order display: " << endl;
	preOrderPrint();

	return true;

}

bool BST::CloneSubtree2(BTNode* cur, type item) {

	if (cur == NULL)
		return false;		//special case


	if (item.id == cur->item.id) {	//clone the particular subtree t2 if user input is found in BST t1
		CloneSubtree3(cur, item);
		return true;
	}

	else {
		CloneSubtree2(cur->left, item);
		CloneSubtree2(cur->right, item);
	}

	return true;
}

bool BST::CloneSubtree3(BTNode* cur, type item) {

	if (cur == NULL)
		return false;		//special case
	insert(cur->item);			//insert the node into subtree t2
	CloneSubtree3(cur->left, item);
	CloneSubtree3(cur->right, item);

	return true;
}

// Implement the printLevelNodes function
bool BST::printLevelNodes() {
	if (root == NULL) 
	{
		cout << endl <<  "Binary Search Tree is currently empty." << endl;
		cout << "Please try again." << endl;
		return false;
	}// Special case

	Queue q;
	q.enqueue(root);

	int level = 1;
	while (!q.empty()) {
		cout << "Level " << level << " nodes: ";
		int levelSize = q.size();

		for (int i = 0; i < levelSize; ++i) {
			BTNode* cur;
			q.dequeue(cur);

			cout << cur->item.id << " ";

			if (cur->left != NULL)
				q.enqueue(cur->left);
			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
		cout << endl;
		++level;
	}
	return true;
}

// Inside the printPath2 function
void printPath2(BTNode* cur, string path);

// Implement the printPath function
bool BST::printPath() {
	if (root == NULL)
	{
		cout << endl << "Binary Search Tree is currently empty." << endl;
		cout << "Please try again" << endl;
		return false; // Special case
	}
	printPath2(root, "");

	return true;
}

void printPath2(BTNode* cur, string path) {
	if (cur == NULL) return;

	path += to_string(cur->item.id) + " "; // Convert int to string using to_string()

	if (cur->left == NULL && cur->right == NULL) {
		cout << path << endl;
		return;
	}

	printPath2(cur->left, path);
	printPath2(cur->right, path);
}

