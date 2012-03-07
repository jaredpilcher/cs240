/*
 * Page.cpp
 *
 *  Created on: Feb 10, 2012
 *      Author: jared
 */
#include "Page.h"
#include <iostream>
using namespace std;

//Default Constructor
Page::Page(string arg_url=""):url(arg_url), description(""){
}

//Default Constructor
Page::Page():url(""), description(""){
}

//Copy Constructor
Page::Page(Page & arg_page):url(arg_page.url), description(arg_page.description){
}

//Default Deconstructor
Page::~Page(){
}

//Retrieves the url of the page
string Page::getURL()const{
	return url;
}

//Retrieves the description of the page
string Page::getDescription()const{
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

bool Page::operator>(Page other){
	return (url.compare(other.url)>0);
}


bool Page::operator<(Page other){
	return (url.compare(other.url)<0);
}
