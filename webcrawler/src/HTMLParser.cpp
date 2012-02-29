/*
 * HTMLParser.cpp
 *
 *  Created on: Feb 10, 2012
 *      Author: jared
 */

#include "HTMLParser.h"

void HTMLParser::setNewPageString(const string & arg_page_text){
	words.Clear();
	links.Clear();
	page_text = arg_page_text;
}

void HTMLParser::parsePage(){
	findWords();
	description = findDescription();
}

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

		if(token.GetType()==TEXT && can_parse && token.GetType()!=COMMENT){
			insertWords(token);
		}
	}
}

//Retrieves the description from the html text on the page
//@par page_text - the html string of the current page
//@ret string - the description found on the page
string findDescription(){
	HTMLTokenizer tokenizer(page_text);
	HTMLToken token;
	bool found_header = false;
	bool found_body = false;
	while(tokenizer.HasNextToken()){
		token = tokenizer.GetNextToken();
		if(startsWith(token.GetValue(),"<TITLE")){
			return tokenizer.GetNextToken().getValue();
		}else if(startsWith(token.GetValue(),"<H1")){
			return tokenizer.GetNextToken().getValue();
		}else if(startsWith(token.GetValue(),"<H2")){
			return tokenizer.GetNextToken().getValue();
		}else if(startsWith(token.GetValue(),"<H3")){
			return tokenizer.GetNextToken().getValue();
		}else if(startsWith(token.GetValue(),"<Body")){
			return firstHundredChar(tokenizer);
		}

		if(token.GetType()==TEXT && can_parse && token.GetType()!=COMMENT){
			insertWords(token);
		}
	}
}

string firstHundredChar(HTMLTokenizer tokenizer){
	HTMLToken token;
	string value;
	string hundred_char;
	int char_count = 0;
	while(1){
		token = tokenizer.getNextToken();
		if(token.GetType()!=TEXT || token.GetType()==COMMENT) continue;
		if(startsWith(token.GetValue(),"</Body")) return hundred_char;
	
		value = token.GetValue();
		for(int i=0;i<value.size();++i){
			hundred_char.append(1,value[i]);
			if(value[i]!=' ' || value[i]!='\t' || value[i]!='\n' || value[i]!='\r'){
				++char_count;
			}
			if(char_count==99) return hundred_char;
		}
	}
}

void HTMLParser::insertWords(HTMLToken token){
	char * value = token.GetValue().data();
	while(value != ""){
		word = getNextWord(value);
		words.Insert(word);
	}
}

//Grab the next word in the sentence
string HTMLParser::getNextWord(char * sentence){
	int start = 0;
	int end = 0;
	bool started = false;
	for(int i=0;i<sentence.size();++i){
		if(((sentence[i]>47 && sentence[i]<58) || (sentence[i]>64 && sentence[i]<91) || sentence[i]=='-' || sentence[i]=='_') && !started){
			start=i;
			started=true;
		}
		if(!((sentence[i]>47 && sentence[i]<58) || (sentence[i]>64 && sentence[i]<91) || sentence[i]=='-' || sentence[i]=='_') && started){
			end=i;
			break;
		}
	}
	char * temp = &sentence[start];
	sentence[end+1]=0;
	sentence = &sentence[end+1];
	return string(temp);
}

//Retrieves the description of the page
string HTMLParser::getDescription(){
	return description;
}

//Determines if there are any more words in the list
bool HTMLParser::isEmpty(){
	return words.IsEmpty();
}

//Retrieves the next word
string HTMLParser::getWord(){
	return words.Pop();
}

//Determines if another link exists in the link list
bool HTMLParser::hasNextLink(){
	return !links.IsEmpty();
}

//Retrieves the next link
string HTMLParser::getLink(){
	return links.Pop();
}
