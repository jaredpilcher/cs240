/*
 * HTMLParser.cpp
 *
 *  Created on: Feb 10, 2012
 *      Author: jared
 */

#include "HTMLParser.h"
static const size_t npos = -1;

//Clears the words, and links
//Sets the new value for html_page
//Finds all words and links found in page_text
//@par page_text - the html text of the new page
//@par arg_url - url of the page being crawled
void HTMLParser::setNewPage(const string & arg_page_text, const string arg_url){
	words.Clear();
	links.Clear();
	page_text = arg_page_text;
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
		if(startsWith(token.GetValue(),"TITLE") || startsWith(token.GetValue(),"BODY")){
			can_parse = !can_parse;
		}
		if(startsWith(token.GetValue(),"a ") && token.GetType()!=TAG_END && can_parse && token.GetType()!=COMMENT && !startsWith(token.GetValue(), "<!")){
			URL temp_url = token.GetAttribute("href");
			if(isInScope(temp_url)){
				temp_url.addBase(base_url);
				links.Insert(temp_url, links.GetLast());
			}
		}
		token = tokenizer.GetNextToken();
	}
}

bool HTMLParser::isInScope(URL url){
	if(startsWith(url.getURL(),"http")) return false;
	url.addBase(base_url);
	if(url.getURL().find(start_url.getURL())!=npos) return true;
	return false;
}

void HTMLParser::findWords(){
	HTMLTokenizer tokenizer(page_text);
	HTMLToken token = tokenizer.GetNextToken();
	bool can_parse = false;
	while(tokenizer.HasNextToken()){
		if(startsWith(token.GetValue(),"TITLE") || startsWith(token.GetValue(),"BODY")){
			can_parse = !can_parse;
		}
		if(token.GetType()==TEXT && can_parse && token.GetType()!=COMMENT && !startsWith(token.GetValue(), "<!")){
			insertWords(token);
		}
		token = tokenizer.GetNextToken();
	}
}

//Retrieves the description from the html text on the page
//@par page_text - the html string of the current page
//@ret string - the description found on the page
string HTMLParser::findDescription(){
	HTMLTokenizer tokenizer(page_text);
	HTMLToken token = tokenizer.GetNextToken();
	string title,h1,h2,h3,body;
	bool got_title=false;
	bool got_h1=false;
	bool got_h2=false;
	bool got_h3=false;
	bool got_body=false;
	while(1){
		if(startsWith(token.GetValue(),"TITLE") && got_title==false){
			title = tokenizer.GetNextToken().GetValue();
			got_title=true;
		}else if(startsWith(token.GetValue(),"h1") && got_h1==false){
			h1 = tokenizer.GetNextToken().GetValue();
			got_h1=true;
		}else if(startsWith(token.GetValue(),"h2") && got_h2==false){
			h2 = tokenizer.GetNextToken().GetValue();
			got_h2=true;
		}else if(startsWith(token.GetValue(),"h3") && got_h3==false){
			h3 = tokenizer.GetNextToken().GetValue();
			got_h3=true;
		}else if(startsWith(token.GetValue(),"body") && got_body==false){
			body = firstHundredChar(tokenizer);
			got_body=true;
		}
		if(!tokenizer.HasNextToken()) break;
		token = tokenizer.GetNextToken();
	}
	if(title.size()!=0) return title;
	if(h1.size()!=0) return h1;
	if(h2.size()!=0) return h2;
	if(h3.size()!=0) return h3;
	if(body.size()!=0) return body;
	return "";
}

string HTMLParser::firstHundredChar(HTMLTokenizer tokenizer){
	string value;
	string hundred_char;
	int char_count = 0;
	while(tokenizer.HasNextToken()){
		HTMLToken token = tokenizer.GetNextToken();
		if(token.GetType()!=TEXT || token.GetType()==COMMENT) continue;
		if(startsWith(token.GetValue(),"Body")) return hundred_char;
	
		value = token.GetValue();
		for(unsigned int i=0;i<value.size();++i){
			hundred_char.append(1,value[i]);
			if(value[i]!=' ' && value[i]!='\t' && value[i]!='\n' && value[i]!='\r'){
				++char_count;
			}
			if(char_count==100) return hundred_char;
		}
		
	}
	return "";
}

bool HTMLParser::startsWith(string line,string substring){
	toCapital(line);
	toCapital(substring);
	for(unsigned int i=0;i<substring.size() && i<line.size();++i){
		if(line[i]==substring[i]){
			continue;
		}
		return false;
	}
	return true;
}

void HTMLParser::toCapital(string & line){
	for(unsigned int i=0; i<line.size();++i){
		if(line[i] >= 'a' && line[i] <= 'z'){
			line[i]=line[i]-' ';
		}
	}
}

//Print all words (for testing)
void HTMLParser::printWords(){
	words.printValues();
}


void HTMLParser::insertWords(HTMLToken token){
	//TO DO LATER: Change this to a malloc
	char value[MAX_CHAR_IN_LINE];
	strcpy(value, token.GetValue().data());
	//END TO DO LATER
	string word;
	while(strlen(value)!=0){
		word = getNextWord(value);
		if(!isWhiteSpace(word)){
			words.Insert(word,words.GetLast());
		}
	}
}

bool HTMLParser::isWhiteSpace(string word){
	return word.find(" ")!=npos || word.find("\n")!=npos || word.find("\t")!=npos || word.find("\r")!=npos;
}

//Grab the next word in the sentence
string HTMLParser::getNextWord(char * sentence){
	int start = 0;
	int end = 0;
	bool started = false;
	unsigned int i;
	for(i=strlen(sentence);i>0;i--){
		if(((sentence[i]>='a' && sentence[i]<='z') || (sentence[i]>='0' && sentence[i]<='9') || (sentence[i]>='A' && sentence[i]<='Z') || sentence[i]=='-' || sentence[i]=='_') && !started){
			end=i;
			started=true;
		}
		if(!((sentence[i]>='a' && sentence[i]<='z') || (sentence[i]>='0' && sentence[i]<='9') || (sentence[i]>='A' && sentence[i]<='Z') || sentence[i]=='-' || sentence[i]=='_') && started){
			start=i;
			break;
		}
	}
	char * return_string;
	if(i!=0){
		return_string = &sentence[start+1];
		sentence[i]=0;
	}else if(sentence[0]==' '){
		return_string = &sentence[start+1];
		sentence[i]=0;
	}else{
		//TO DO LATER: change this to a malloc
		char return_string_end[MAX_CHAR_IN_LINE];
		strcpy(return_string_end,sentence);
		//END TO DO LATER
		return_string = return_string_end;
		sentence[0]=0;
	}
	sentence[end+1]=0;
	return string(return_string);
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
