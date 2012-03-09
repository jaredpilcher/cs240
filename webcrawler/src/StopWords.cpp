/*
 * StopWords.cpp
 *
 *  Created on: March 4, 2012
 *      Author: jared
 */
#include "StopWords.h"

//Default Constructor
StopWords::StopWords():count(0){

}

//Default Deconstructor
StopWords::~StopWords(){
}

//Retrieves all of the words from the stop_words file
//Places words into the stop_words array
//@par stop_file - file url of the stop words file
void StopWords::getWords(string stop_file){
	fstream file(stop_file.data());
	char temp[MAX_CHAR_IN_LINE];
	while(1){
		file.getline(temp,MAX_CHAR_IN_LINE);
		if(!file) break;
		stop_words[count]=temp;
		++count;
	}
	file.close();
}

int comparator(const void * key,const void * other){
	return (*(string*)key).compare((*(string*)other));
}

//Determines if the given word is a stop word
//@par word - word to be found
bool StopWords::isStopWord(string word){
	ToLower(word);
	return bsearch(&word, stop_words, count+1, sizeof(stop_words[0]), comparator) != NULL;
}

unsigned int StopWords::getCount(){
	return count;
}

