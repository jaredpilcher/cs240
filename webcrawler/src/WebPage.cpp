/*
 * Page.cpp
 *
 *  Created on: Feb 10, 2012
 *      Author: jared
 */
#include "WebPage.h"

//Default Constructor
WebPage::WebPage(string arg_url=""):url(arg_url), description(""){
}

//Default Deconstructor
WebPage::~WebPage(){
}

//Retrieves the url of the page
string WebPage::GetURl(){
	return url;
}

//Retrieves the description of the page
string WebPage::getDescription(){
	return description;
}

//Sets the url of the page
//@par url - the url of the page
void WebPage::setURL(string arg_url){
	url=arg_url;
}

//Set the description of the page
//@par description - the description of the page
void WebPage::setDescription(string arg_description){
	description=arg_description;
}

