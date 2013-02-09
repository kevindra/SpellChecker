Components:

1. SpellChecker class:
	This class exposes three methods:
	a. train( string ): This method trains the dictionary.
	b. check(string, maxResults): This method gives spellcheck suggestions for the input string.
	c. spellingMistakeGenerator(string) : This method applies the the given error criteria and 
										  returns list of string with spelling mistakes.
									
2. Node class:
	This class implements the BKTree and exposes these methods:
	a. insert(string): inserts the new word in the BKTree
	b. search(string, int maxResults): searches the similar words in the tree.
	