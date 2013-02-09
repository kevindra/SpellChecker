/*
 * SpellChecker.h
 *
 *  Created on: 09-Feb-2013
 *      Author: Kevindra
 */

#ifndef SPELLCHECKER_H_
#define SPELLCHECKER_H_

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include "Node.h"

using namespace std;

class SpellChecker {
private:
	Node *node;

public:
	SpellChecker();
	virtual ~SpellChecker();

	void train(string s);
	vector<string> check(string s, int maxResults);
	vector<string> spellingMistakeGenerator(string s);
};

#endif /* SPELLCHECKER_H_ */
