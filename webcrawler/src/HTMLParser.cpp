/*
 * HTMLParser.cpp
 *
 *  Created on: Feb 10, 2012
 *      Author: jared
 */

#include "HTMLParser.h"

void HTMLParser::HTMLParser(string arg_start_url): start_url(arg_start_url){
}

void HTMLParser::setNewPageString(const string arg_page_text){
	words.Clear();
	links.Clear();
	page_text = arg_page_text;
	html_page= determineIfHTML(arg_page_text);
}

void HTMLParser::parsePage(){
	findWords();
	description = findDescription(page_text);
}

//START HERE. MAKE SURE TO ADD IGNORING COMMENTS
void HTMLParser::findWords(){
	HTMLTokenizer tokenizer(page_text);
	HTMLToken token;
	bool can_parse = false;
	while(tokenizer.HasNextToken()){
		token = tokenizer.GetNextToken();
		if(startsWith(token.GetValue(),"<TITLE") || startsWith(token.GetValue(),"<BODY")){
			can_parse = true;
		}else if(startsWith(token.GetValue(),"</TITLE") || startsWith(token.GetValue(),"</BODY")){
			can_parse = false;
		}

		if(token.GetType()==TEXT){
			insertWords(token);
		}
	}
}

void HTMLParser::insertWords(HTMLToken token){
	string value = token.GetValue();
	while(value != ""){
		word = getNextWord(value);
		words.Insert(word);
	}
}

