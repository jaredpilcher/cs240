/*
 * HTMLParser.cpp
 *
 *  Created on: Feb 10, 2012
 *      Author: jared
 */

#include "HTMLParser.h"
#include <iostream>
using namespace std;
static const size_t npos = -1;

//Clears the words, and links
//Sets the new value for html_page
//Finds all words and links found in page_text
//@par page_text - the html text of the new page
//@par arg_url - url of the page being crawled
void HTMLParser::setNewPage(const string & arg_page_text, string arg_url){
	words.Clear();
	links.Clear();
	page_text = arg_page_text;
	arg_url = lowerRoot(arg_url);
	base_url = arg_url;
}

void HTMLParser::parsePage(){
	findWords();
	description = findDescription();
	findLinks();
}

void HTMLParser::findLinks(){
	HTMLTokenizer tokenizer(page_text);
	HTMLToken token = tokenizer.GetNextToken();
	bool can_parse = false;
	while(tokenizer.HasNextToken()){
		if((startsWith(token.GetValue(),"TITLE") || startsWith(token.GetValue(),"BODY"))  && 
				token.GetType()!=TEXT ){
			can_parse = !can_parse;
		}
		if(startsWith(token.GetValue(),"a") && token.GetType()!=TAG_END && 
			can_parse && token.GetType()!=COMMENT && !startsWith(token.GetValue(), "<!")){

			URL temp_url = token.GetAttribute("href");
			if(!startsWith(temp_url.getURL(),"http") && !startsWith(temp_url.getURL(),"file")){
				temp_url.addBase(base_url);
			}else if(startsWith(temp_url.getURL(),"http")){
				temp_url.setURL(lowerRoot(temp_url.getURL()));
			}
			if(isInScope(temp_url)){
				links.Insert(temp_url, links.GetLast());
			}
		}
		token = tokenizer.GetNextToken();
	}
}

bool HTMLParser::isInScope(URL url){
	if(url.getURL().find(start_url.getURL())!=npos) return true;
	return false;
}

//makes all of the 
string HTMLParser::lowerRoot(string url){
	int slash_count = 0;
	for(unsigned int i=0;i<url.size();++i){
		if(url[i]=='/'){
			slash_count++;
		}
		if(slash_count==3) break;
		toLowerChar(url[i]);
	}
	return url;
}

void HTMLParser::findWords(){
	HTMLTokenizer tokenizer(page_text);
	HTMLToken token = tokenizer.GetNextToken();
	bool can_parse = false;
	while(tokenizer.HasNextToken()){
		if((startsWith(token.GetValue(),"TITLE") || startsWith(token.GetValue(),"BODY")) && 
				token.GetType()!=TEXT){
			can_parse = !can_parse;
		}
		cout << "Token: " << token.GetValue() << endl;
		cout << "Type Test: " << (token.GetType()==TEXT) << endl;
		cout << "can parse: " << can_parse << endl;
		cout << "starts with test: " << !startsWith(token.GetValue(), "<!") << endl;
		if(token.GetType()==TEXT && can_parse && !startsWith(token.GetValue(), "<!")){
				//cout << "Trying to insert: " << token.GetValue() << endl;
				insertWords(token);
		}
		token = tokenizer.GetNextToken();
	}
}

//Retrieves the description from the html text on the page
//@par page_text - the html string of the current page
//@ret string - the description found on the page
string HTMLParser::findDescription(){
	string description = "";	
	HTMLTokenizer tokenizer(page_text);
	HTMLToken token = tokenizer.GetNextToken();
	bool got_title=false;
	bool got_h1=false;
	bool got_h2=false;
	bool got_h3=false;
	bool got_body=false;
	while(1){
		if(startsWith(token.GetValue(),"TITLE") && !got_title){
			description = tokenizer.GetNextToken().GetValue();
			got_title=true;
		}else if(startsWith(token.GetValue(),"h1") && !got_h1 && !got_title){
			token = tokenizer.GetNextToken();
			if(token.GetType()!=TEXT){
				description = tokenizer.GetNextToken().GetValue();
			}else{
				description = token.GetValue();
			}
			got_h1=true;
		}else if(startsWith(token.GetValue(),"h2") && !got_h2 && !got_h1 && !got_title){
			description = tokenizer.GetNextToken().GetValue();
			got_h2=true;
		}else if(startsWith(token.GetValue(),"h3") && !got_h3 && !got_h2 && !got_h1 && !got_title){
			description = tokenizer.GetNextToken().GetValue();
			got_h3=true;
		}else if(startsWith(token.GetValue(),"body") && !got_body && !got_h3 
					&& !got_h2 && !got_h1 && !got_title){
			//cout << "here" << endl;
			description = firstHundredChar(tokenizer);
			//cout << description << endl;
			got_body=true;
		}
		if(!tokenizer.HasNextToken()) break;
		token = tokenizer.GetNextToken();
	}
	return description;
}

string HTMLParser::firstHundredChar(HTMLTokenizer tokenizer){
	string value;
	string hundred_char;
	int char_count = 0;
	bool got_space;
	while(tokenizer.HasNextToken()){
		HTMLToken token = tokenizer.GetNextToken();
		if(token.GetType()!=TEXT || token.GetType()==COMMENT) continue;
		if(startsWith(token.GetValue(),"Body")) return hundred_char;
		value = token.GetValue();
		for(unsigned int i=0;i<value.size();++i){
			if(value[i]!='\t' && value[i]!='\n' && value[i]!='\r') hundred_char.append(1,value[i]);
			if(value[i]!=' ' && value[i]!='\t' && value[i]!='\n' && value[i]!='\r'){
				++char_count;
			}
			if(char_count==100) return hundred_char;
		}
		if(hundred_char[hundred_char.size()-1]!=' ')hundred_char.append(" ");
		
	}
	return hundred_char;
}

bool HTMLParser::startsWith(string line,string substring){
	toCapital(line);
	toCapital(substring);
	unsigned int i=0;
	for(;i<substring.size() && i<line.size();++i){
		if(line[i]==substring[i]){
			continue;
		}
		return false;
	}
	if(i<substring.size()) return false;
	return true;
}

void HTMLParser::toCapital(string & line){
	for(unsigned int i=0; i<line.size();++i){
		if(line[i] >= 'a' && line[i] <= 'z'){
			line[i]=line[i]-' ';
		}
	}
}

void HTMLParser::toLowerChar(char & character){
	if(character >= 'A' && character <= 'Z'){
		character=character+' ';
	}
}

//Print all words (for testing)
void HTMLParser::printWords(){
	words.printValues();
}


void HTMLParser::insertWords(HTMLToken token){
	string word;
	string sentence = token.GetValue();
	while(sentence.size()>0){
		//cout << "sentence: " << sentence << endl;
		sentence = getNextWord(word, sentence);
		if(word.size()>0){
			//cout << "actually inserting: " << word << endl;
			words.Insert(word,words.GetLast());
		}
	}
}

bool HTMLParser::isWhiteSpace(string word){
	return word.find(" ")!=npos || word.find("\n")!=npos || 
				word.find("\t")!=npos || word.find("\r")!=npos;
}

//Grab the next word in the sentence
string HTMLParser::getNextWord(string& word, string sentence){
	int start = 0;
	int end = 0;
	bool started = false;
	bool finished = false;
	string return_string;
	unsigned int i=0;
	for(;i<sentence.size();++i){
		if(isWordChar(sentence[i]) && !started){
			start=i;
			started=true;
		}
		if(!isWordChar(sentence[i]) && started){
			//cout << "here6" << endl;
			end=i;
			finished=true;
			break;
		}
	}
	//cout << "finished: " << finished << endl;
	//cout << "start: " << start << endl;
	
	if(!started){
		//cout << "here1" << endl;
		word = "";
		return "";
	}else if(!finished && !startsWithNumber(sentence.substr(start))){
		//cout << "here2" << endl;
		word = sentence.substr(start);
		return "";
	}else if(!startsWithNumber(sentence.substr(start,end-start))){
		//cout << "here3" << endl;
		word = sentence.substr(start,end-start);
		//cout << "end: " << end << endl;
		return sentence.substr(end+1);
	}else if(i!=sentence.size()){
		//cout << "here4" << endl;
		word = "";
		return sentence.substr(end+1);
	}
		//cout << "here5" << endl;
	word = "";
	return "";
}

bool HTMLParser::startsWithNumber(string word){
	if((word[0]>='a' && word[0]<='z') || (word[0]>='A' && word[0]<='Z')){
		return false;
	}
	return true;
}

bool HTMLParser::isWordChar(char character){
	if((character>='a' && character<='z') || (character>='0' && character<='9') || 
			(character>='A' && character<='Z') || character=='-' || character=='_'){
		return true;
	}
	return false;
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
//WARNING: Does not check that the link list is not empty. Must check first!
string HTMLParser::getLink(){
	return links.Pop().getURL();
}
