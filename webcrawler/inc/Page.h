/*
 * Page.h
 *
 *  Created on: Feb 10, 2012
 *      Author: jared
 */


#ifndef PAGE_H_
#define PAGE_H_
#include <string>
using namespace std; 

//Contains the url and description of a page
class Page{
	//Contains the url of the page
	string url;
	//Contains the description found on the page
	string description;
public:
	//Default Constructor
	Page(string arg_url);

	//Copy Constructor
	Page(Page & arg_page);

	//Default Deconstructor
	~Page();
	
	//Retrieves the url of the page
	string getURL()const;

	//Retrieves the description of the page
	string getDescription()const;

	//Sets the url of the page
	//@par url - the url of the page
	void setURL(string url);

	//Set the description of the page
	//@par description - the description of the page
	void setDescription(string description);

};

#endif /* PAGE_H_ */
