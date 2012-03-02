/*
 * OccurrenceSet.h
 *
 *  Created on: Feb 10, 2012
 *      Author: jared
 */

#ifndef OCCURRENCESET_H_
#define OCCURRENCESET_H_
#include "BST.h"
#include "Occurrence.h"

//A set of occurrences of words on pages
class OccurrenceSet{
public:
	
	//Default Constructor
	OccurrenceSet();
	
	//Default Deconstructor
	~OccurrenceSet();

	//Copy Constructor
	OccurrenceSet(OccurrenceSet & other);

	//Creates an occurrence, or increments the
	//count of an occurrence on the class BST
	//@par url - the url that the occurrence is on
	void push(string url);

	//Return a unique Occurrence
	//WARNING: Must check to see if the occurrence set is empty before calling this!
	Occurrence pop();

	//Returns whether or not the occurrence set is empty
	bool isEmpty();

private:
	//The BST that holds the set of occurrences
	BST<string,Occurrence*> occurrences;

	//The BST that holds the map between urls and the Occurrence
};

#endif /* OCCURRENCESET_H_ */
