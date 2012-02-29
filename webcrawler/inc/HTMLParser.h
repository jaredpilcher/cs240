/*
 * HTMLParser.h
 *
 *  Created on: Feb 10, 2012
 *      Author: jared
 */

#ifndef HTMLPARSER_H_
#define HTMLPARSER_H_
#include "LinkedList.h"
#include "HTMLTokenizer.h"
#include "HTMLToken.h"
#include "URL.h"
#include <string.h>

//Provides tools to parse HTML text strings
class HTMLPARSER{
	//The list of words on the current page
	LinkedList<string> words;

	//The list of links on the current page
	LinkedList<URL> links;

	//The start_url passed in from the user.
	//The description of the current
	string start_url, description;

	//page
	string page_text;
public:
	//Default Constructor
	HTMLParser(){
	}

	//Default Deconstructor
	~HTMLParser(){
	}

	//Clears the words, and links
	//Sets the new value for html_page
	//Finds all words and links found in page_text
	//@par page_text - the html text of the new page
	void setNewPageString(const string & page_text);

	//Retrieves the description of the page
	string getDescription();

	//Determines if there are any more words in the list
	bool isEmpty();

	//Retrieves the next word
	string getWord();

	//Determines if another link exists in the link list
	bool hasNextLink();

	//Retrieves the next link
	string getLink();

	//Begin parsing the page string
	void parsePage();


private:
	
	//Finds all the necessary words in the string
	//@par page_text - the html text of the page to be searched
	void findWords(string page_text);

	//Places all words in the token into the list of words
	//@par token - token containing the words to be places in the words list
	void insertWords(HTMLToken token);

	//Retrieves the description from the html text on the page
	//@par page_text - the html string of the current page
	//@ret string - the description found on the page
	string findDescription(const string page_text);

	//Grabs the next word in the sentence
	string HTMLParser::getNextWord(char * sentence);
	
	//Grab the first 100 characters (excluding whitespace) of the tokenizer
	string firstHundredChar(HTMLTokenizer tokenizer);
};

#endif /* HTMLPARSER_H_ */
