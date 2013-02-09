/*
 * Node.h
 *
 *  Created on: 09-Feb-2013
 *      Author: Kevindra
 */

#ifndef NODE_H_
#define NODE_H_

#include <string>
#include <vector>

using namespace std;

#define MAX_DISTANCE 50

// BKTree node
struct node {
	string s;
	node *link[MAX_DISTANCE];
};

class Node {
private:
	node *root;

	node *createNewNode(string s);
	void insertPrivate(node *&root, string s);
	int editDistance(string s1, string s2);
	void display(node *root);
	vector<string> searchInner(node *root, string toSearch, int threshold);
	vector<string> filterResults(vector<string> words, string s, int maxResults);
public:
	Node();
	virtual ~Node();

	void insert(string s);
	vector<string> search(string s, int maxResults);
};

#endif /* NODE_H_ */
