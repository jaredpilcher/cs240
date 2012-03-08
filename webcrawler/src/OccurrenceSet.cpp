/*
 * OccurrenceSet.cpp
 *
 *  Created on: March 2, 2012
 *      Author: jared
 */

#include "OccurrenceSet.h"
	
//Default Constructor
OccurrenceSet::OccurrenceSet(){
}

//Default Deconstructor
OccurrenceSet::~OccurrenceSet(){
}

//Copy Constructor
OccurrenceSet::OccurrenceSet(OccurrenceSet & other){
	occurrences = other.occurrences;
}

//Creates an occurrence, or increments the
//count of an occurrence on the class BST
//@par url - the url that the occurrence is on
void OccurrenceSet::push(string url){
	BSTNode<string,Occurrence*> * node = occurrences.Find(url);
	if(node==NULL){
		Occurrence * occurrence = new Occurrence(url);
		occurrence->addOccurrence();
		static int count = 0;
        cout << "push count: " << ++count << endl;
		occurrences.Insert(url,occurrence);
	}else{
		node->GetValue()->addOccurrence();
	}
}

//Return a unique Occurrence
//WARNING: Must check to see if the occurrence set is empty before calling this!
Occurrence OccurrenceSet::pop(){
	
	Occurrence * temp_ptr = occurrences.PopValue();
	static int count = 0;
	cout << "pop count: " << ++count << endl;
	Occurrence temp(*temp_ptr);
	delete temp_ptr;
	return temp;
}

//Returns whether or not the occurrence set is empty
bool OccurrenceSet::isEmpty(){
	return occurrences.IsEmpty();
}
