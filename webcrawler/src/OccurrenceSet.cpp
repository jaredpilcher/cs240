/*
 * OccurrenceSet.cpp
 *
 *  Created on: March 2, 2012
 *      Author: jared
 */

#include "OccurrenceSet.h"
	
//Default Constructor
OccurrenceSet(){
}

//Default Deconstructor
~OccurrenceSet(){
}

//Creates an occurrence, or increments the
//count of an occurrence on the class BST
//@par url - the url that the occurrence is on
void push(string url){
	Occurrence * occurrence = new Occurrence(url);
	occurrence->addOccurrence();
	occurrences.Insert(occurrence);
}

//Return a unique Occurrence
//WARNING: Must check to see if the occurrence set is empty before calling this!
Occurrence pop();

//Returns whether or not the occurrence set is empty
bool isEmpty();
