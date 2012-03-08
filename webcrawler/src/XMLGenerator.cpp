/*
 * XMLGenerator.cpp
 *
 *  Created on: March 5, 2012
 *      Author: jared
 */

#include "XMLGenerator.h"

void XMLGenerator::writeFile(){
	createTag("website");
	startPageTag();
	pageTags();
	wordTags();
	createTag("/website");
	ofstream xml_file(output_file.data());
	cout << xml.data();
	xml_file << xml;
	xml_file.close();
}

void XMLGenerator::createTag(string value){
	EncodeToXml(value);
	xml.append("<" + value + ">");
}

void XMLGenerator::addText(string text){
	EncodeToXml(text);
	xml.append(text);
}

void XMLGenerator::startPageTag(){
	createTag("start-url");
	addText(start_url);
	createTag("/start-url");
}

void XMLGenerator::pageTags(){
	Page * page;
	createTag("pages");
	while(!history->isEmpty()){
		page = history->pop();
		createTag("page");
		createTag("url");
		addText(page->getURL());
		createTag("/url");
		createTag("description");
		addText(page->getDescription());
		delete page;
		createTag("/description");
		createTag("/page");
	}
	createTag("/pages");
}

void XMLGenerator::wordTags(){
	string indexed_word;
	OccurrenceSet * occurrences;
	Occurrence occurrence;
	char count_string[MAX_WORD_CHAR];
	createTag("index");
	while(!index->isEmpty()){
		createTag("word");
		occurrences = index->pop(indexed_word);
		createTag("value");
		addText(indexed_word);
		createTag("/value");
		while(!occurrences->isEmpty()){
			createTag("occurrence");
			occurrence = occurrences->pop();
			createTag("url");
			addText(occurrence.getURL());
			createTag("/url");
			createTag("count");
			sprintf(count_string,"%d",occurrence.getCount());
			addText(count_string);
			createTag("/count");
			createTag("/occurrence");
		}
		createTag("/word");
		delete occurrences;
	}
	createTag("/index");
}
