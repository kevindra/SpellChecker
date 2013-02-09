/*
 * main.cpp
 *
 *  Created on: 09-Feb-2013
 *      Author: Kevindra
 */
#include <iostream>
#include "SpellChecker.h"
#include <fstream>

using namespace std;

int main() {
	ifstream ifile;
	ifile.open("dictionary.in");
	SpellChecker *spellChecker = new SpellChecker;
	string s;

	cout << "Training the dictionary: \n";
	while (getline(ifile, s) && s != "\0") {
		spellChecker->train(s);
	}
	ifile.close();
	cout << "Finished" << endl;

	cout << "Type your word: ['0' to exit] ";
	while (cin >> s && s != "0") {
		vector<string> e = spellChecker->spellingMistakeGenerator(s);
		for (unsigned int i = 0; i < e.size(); i++) {
			cout << "Input Word: [" << e[i] << "] " << endl;
			vector<string> suggestions = spellChecker->check(e[i], 5);

			if (suggestions.size() == 0)
				cout << "NO SUGGESTION" << endl;
			else {
				for (unsigned int i = 0; i < suggestions.size(); i++) {
					cout << suggestions[i] << " ";
				}
				cout << endl;
			}
		}
		cout << "Type your word: ['0' to exit] ";
	}

	return 0;
}

