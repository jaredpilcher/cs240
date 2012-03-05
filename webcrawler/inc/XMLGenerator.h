/*
 * XMLGenerator.h
 *
 *  Created on: Feb 10, 2012
 *      Author: jared
 */

#ifndef XMLGENERATOR_H_
#define XMLGENERATOR_H_

#include "PageHistory.h"
#include "WordIndex.h"
#include "StringUtil.h"
#include <fstream>
#define MAX_WORD_CHAR 2400
using namespace std;
using namespace StringUtil;

//Creates XML output summary of index, history and start_url
class XMLGenerator{
	//Contains history of pages indexed
	PageHistory * history;
	//Contains the queue of pages
	WordIndex * index;
	//contains the start_url of the web crawler
	string start_url;
	//contains the finalized xml of the output
	string xml;
public:
	//Default constructor
	XMLGenerator(PageHistory * arg_history, WordIndex * arg_index, string arg_start_url): 
			history(arg_history), index(arg_index), start_url(arg_start_url) {
	}

	//Default Deconstructor
	~XMLGenerator(){
	}

	//Creates the finalized output and writes it to the file named "output.xml"
	void writeFile();
private:
	//Creates a tag and places it in the variable xml
	//@par value - the string to place inside of the tag
	void createTag(string value);

	//Adds text to the xml output
	//@par text - text to be added to the xml output
	void addText(string text);
	
	//Creates and formats page text
	void startPageTag();

	//Creates page tags
	void pageTags();

	//Create word tags
	void wordTags();

};

#endif /* XMLGENERATOR_H_ */
