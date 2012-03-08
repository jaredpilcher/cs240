/*
 * WordIndex.h
 *
 *  Created on: March 02, 2012
 *      Author: jared
 */

#include "WordIndex.h"

//Default Constructor
WordIndex::WordIndex(){
}

//Default Deconstructor
WordIndex::~WordIndex(){
}

//Index a word in the given url
//@par word - the word to be indexed
//@par url - the url that the word was found on
void WordIndex::push(string word, const string url){
	ToLower(word);
	BSTNode<string,OccurrenceSet*> * node = word_map.Find(word);

	if(node==NULL){
		OccurrenceSet * set = new OccurrenceSet();
		set->push(url);
		word_map.Insert(word,set);
	}else{
		node->GetValue()->push(url);
	}
}

//Get a unique OccurrenceSet.
//WARNING: Must delete the object pointed to by return statement
//@ret OccurenceSet - A unique occurrence set
OccurrenceSet * WordIndex::pop(string & word){
	return word_map.PopVandK(word);
}

//Returns whether or not the occurrence set is empty
bool WordIndex::isEmpty(){
	return word_map.IsEmpty();
}


