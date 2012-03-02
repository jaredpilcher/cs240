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
void WordIndex::push(const string word, const string url){
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
//@ret OccurenceSet - A unique occurrence set
OccurrenceSet WordIndex::pop(){
	OccurrenceSet * temp_ptr = word_map.PopValue();
	OccurrenceSet temp(*temp_ptr);
	delete temp_ptr;
	return temp;
}

//Returns whether or not the occurrence set is empty
bool WordIndex::isEmpty(){
	return word_map.IsEmpty();
}
