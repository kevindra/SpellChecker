/*
 * SpellChecker.cpp
 *
 *  Created on: 09-Feb-2013
 *      Author: Kevindra
 */

#include "SpellChecker.h"
#include <iostream>
#include <string>

SpellChecker::SpellChecker() {
	node = new Node;
}

SpellChecker::~SpellChecker() {
	node = NULL;
}

void SpellChecker::train(string s) {
	node->insert(s);
}

vector<string> SpellChecker::check(string s, int maxResults) {
	// lower case the letters
	for (unsigned int i = 0; i < s.size(); i++)
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] = s[i] - 'A' + 'a';

	return node->search(s, maxResults);
}

// Error Type "sheep" -> "sheeeeep"
string applyErrorType1(string s) {
	string errorWord = "";
	int idx = rand() % s.size();
	errorWord += s.substr(0, idx);
	for (int i = 0; i < 3; i++)
		errorWord += s[idx];
	errorWord += s.substr(idx + 1, s.size() - idx);
	return errorWord;
}

// Error Type "people" to "peeple"
string applyErrorType2(string s) {
	string errorWord = s;
	errorWord[rand() % s.size()] = (rand() % 26) + 'a';
	return errorWord;
}

vector<string> SpellChecker::spellingMistakeGenerator(string s) {
	vector<string> res;

	res.push_back(applyErrorType1(s));
	res.push_back(applyErrorType2(s));
	res.push_back(applyErrorType2(applyErrorType1(s)));

	return res;
}
