/*
 * Node.cpp
 *
 *  Created on: 09-Feb-2013
 *      Author: Kevindra
 */

#include "Node.h"
#include <queue>
#include <iostream>

Node::Node() {
	root = NULL;
}

Node::~Node() {
	root = NULL;
}

node *Node::createNewNode(string s) {
	node *np = new node;
	np->s = s;

	for (int i = 0; i < MAX_DISTANCE; i++)
		np->link[i] = NULL;
	return np;
}

// inserts in the BK tree
void Node::insertPrivate(node *&r, string s) {
	// if the node is null
	// create a node there
	if (r == NULL) {
		r = createNewNode(s);
		return;
	}

	// if not
	// then calculate the distance of new string with the node string
	int d = editDistance(s, r->s);

	// insert in the distance 'd' branch
	insertPrivate(r->link[d], s);
}

// normal edit distance method
// returns edit distance between two string s1 and s2
int Node::editDistance(string s1, string s2) {
	int sz1 = s1.size(), sz2 = s2.size();

	if (sz1 == 0)
		return sz2;
	if (sz2 == 0)
		return sz1;

	// initialize the matrix
	int **m = (int**) malloc((sz1 + 1) * sizeof(int));
	for (int i = 0; i <= sz1; i++)
		m[i] = (int*) malloc((sz2 + 1) * sizeof(int));

	for (int i = 0; i <= sz1; i++)
		m[i][0] = i;
	for (int i = 0; i <= sz2; i++)
		m[0][i] = i;

	for (int i = 1; i <= sz1; i++) {
		for (int j = 1; j <= sz2; j++) {
			m[i][j] = min(m[i - 1][j] + 1,
					min(m[i][j - 1] + 1,
							m[i - 1][j - 1] + (s1[i - 1] != s2[j - 1])));
		}
	}
	return m[sz1][sz2];
}

// for simplicity
// BSF to print the tree level wise
void Node::display(node *r) {
	if (r == NULL)
		return;

	queue<node *> q;
	q.push(r);
	while (!q.empty()) {
		node *n = q.front();
		q.pop();

		if (n == NULL) {
			cout << endl;
			continue;
		} else
			cout << n->s << " ";

		q.push(NULL);
		for (int i = 0; i < MAX_DISTANCE; i++)
			if (n->link[i])
				q.push(n->link[i]);
	}
	cout << endl;
}

// search method
vector<string> Node::searchInner(node *r, string toSearch, int threshold) {
	int d = editDistance(r->s, toSearch);

	vector<string> v;
	if (d <= threshold)
		v.push_back(r->s);

	int dmin = abs(d - threshold);
	int dmax = d + threshold;

	//cout << r->s << " " << toSearch << ": " << d << " [" << dmin << "," << dmax
	//		<< "] \n";

	for (int i = dmin; i <= dmax; i++) {
		if (r->link[i]) {
			vector<string> subv = searchInner(r->link[i], toSearch, threshold);
			v.insert(v.end(), subv.begin(), subv.end());
		}
	}
	return v;
}

void Node::insert(string s) {
	insertPrivate(root, s);
}

bool sorter(pair<string, int> p1, pair<string, int> p2) {
	return p1.second < p2.second;
}

vector<string> Node::search(string s, int results) {
	vector<string> words = searchInner(root, s, (s.size() + 1) / 2);
	vector<pair<string, int> > suggestions;
	for (int i = 0; i < words.size(); i++) {
		pair<string, int> p;
		p.first = words[i];
		p.second = editDistance(words[i], s);
		suggestions.push_back(p);
	}
	sort(suggestions.begin(), suggestions.end(), sorter);

	words.clear();
	for (int i = 0; i < suggestions.size(); i++) {
		words.push_back(suggestions[i].first);
	}
	return (results > words.size()) ?
			words : vector<string>(words.begin(), words.begin() + results);
}
