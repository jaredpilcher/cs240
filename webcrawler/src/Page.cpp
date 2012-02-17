/*
 * Page.cpp
 *
 *  Created on: Feb 10, 2012
 *      Author: jared
 */
#include "Page.h"

//Default Constructor
Page::Page(string arg_url=""):url(arg_url), description(""){
}

//Default Deconstructor
Page::~Page(){
}

//Retrieves the url of the page
string Page::getURL(){
	return url;
}

//Retrieves the description of the page
string Page::getDescription(){
	return description;
}

//Sets the url of the page
//@par url - the url of the page
void Page::setURL(string arg_url){
	url=arg_url;
}

//Set the description of the page
//@par description - the description of the page
void Page::setDescription(string arg_description){
	description=arg_description;
}

