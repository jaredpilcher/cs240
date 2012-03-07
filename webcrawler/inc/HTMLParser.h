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
#define MAX_CHAR_IN_LINE 32000

//Provides tools to parse HTML text strings
class HTMLParser{
	//The list of words on the current page
	LinkedList<string> words;

	//The list of links on the current page
	LinkedList<URL> links;

	//The current base_url of the web page
	//The description of the current
	string base_url, description;

	//The start_url passed in from the user.
	URL start_url;

	//page
	string page_text;
public:
	//Default Constructor
	HTMLParser(string arg_start){
		start_url.setURLBase(arg_start);
	}

	//Default Deconstructor
	~HTMLParser(){
	}

	//Clears the words, and links
	//Sets the new value for html_page
	//Finds all words and links found in page_text
	//@par page_text - the html text of the new page
	//@par arg_url - url of the page being crawled
	void setNewPage(const string & arg_page_text, const string arg_url);

	//Retrieves the description of the page
	string getDescription();

	//Determines if there are any more words in the list
	bool isEmpty();

	//Retrieves the next word
	string getWord();

	//Determines if another link exists in the link list
	bool hasNextLink();

	//Retrieves the next link
	//WARNING: Does not check that the link list is not empty. Must check first!
	string getLink();

	//Begin parsing the page string
	void parsePage();

	//Print all words (for testing)
	void printWords();

private:
	
	//Finds all the necessary words in the string
	//@par page_text - the html text of the page to be searched
	void findWords();

	//Places all words in the token into the list of words
	//@par token - token containing the words to be places in the words list
	void insertWords(HTMLToken token);

	//Retrieves the description from the html text on the page
	//@par page_text - the html string of the current page
	//@ret string - the description found on the page
	string findDescription();

	//Grabs the next word in the sentence
	string getNextWord(char * sentence);
	
	//Grab the first 100 characters (excluding whitespace) of the tokenizer
	string firstHundredChar(HTMLTokenizer tokenizer);

	//Determines if substring is in line
	bool startsWith(string line,string substring);

	//Convert all lower case values to uppercase in string
	//WARNING: modifies string
	void toCapital(string & line);

	//Determines if the string contains whitespace
	bool isWhiteSpace(string word);

	//Find all links between <html> tags on page and store in links (class variable)
	void findLinks();

	//Determines if the given url is in scope
	bool isInScope(URL url);
};

#endif /* HTMLPARSER_H_ */
