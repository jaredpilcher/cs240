/*
 * Occurrence.cpp
 *
 *  Created on: March 2, 2012
 *      Author: jared
 */
#include "Occurrence.h"

Occurrence::Occurrence(string arg_url):count(0), url(arg_url){
}

//Default Deconstructor
Occurrence::~Occurrence(){
}

//Increments the number of occurrences on the page
void Occurrence::addOccurrence(){
	++count;
}

string Occurrence::getURL(){
	return url;
}

int Occurrence::getCount(){
	return count;
}
