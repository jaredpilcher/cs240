/*
 * Occurrence.h
 *
 *  Created on: Feb 10, 2012
 *      Author: jared
 */

#ifndef OCCURRENCE_H_
#define OCCURRENCE_H_

#include "Page.h"

//An occurrence of a word that is noted on a website
class Occurrence{
public:
	//Default Constructor
	Occurrence();

	//Constructor
	Occurrence(string arg_url);

	//Default Deconstructor
	~Occurrence();

	//Copy Constructor
	Occurrence(Occurrence & other);

	//Increments the number of occurrences on the page
	void addOccurrence();

	string getURL();
	int getCount();
	void setURL(string arg_url);

private:
	//The number of times the occurrence happens
	int count;

	//The url that the occurrence occurs on
	string url;
};

#endif /* OCCURRENCE_H_ */
