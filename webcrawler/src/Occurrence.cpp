/*
 * Occurrence.cpp
 *
 *  Created on: March 2, 2012
 *      Author: jared
 */
#include "Occurrence.h"

Occurrence::Occurrence(string arg_url):count(0), url(arg_url){
}

Occurrence::Occurrence():count(0), url(""){
}

//Default Deconstructor
Occurrence::~Occurrence(){
}

//Copy Constructor
Occurrence::Occurrence(Occurrence & other){
	url = other.url;
	count = other.count;
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
