/*
 * WebPage.h
 *
 *  Created on: Feb 10, 2012
 *      Author: jared
 */


#ifndef PAGE_H_
#define PAGE_H_
#include <string>
using namespace std; 

//Contains the url and description of a page
class WebPage{
	//Contains the url of the webpage
	string url;
	//Contains the description found on the webpage
	string description;
public:
	//Default Constructor
	WebPage(string arg_url);

	//Default Deconstructor
	~WebPage();
	
	//Retrieves the url of the page
	string GetURl();

	//Retrieves the description of the page
	string getDescription();

	//Sets the url of the page
	//@par url - the url of the page
	void setURL(string url);

	//Set the description of the page
	//@par description - the description of the page
	void setDescription(string description);

};

#endif /* PAGE_H_ */
