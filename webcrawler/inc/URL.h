/*
 * URL.h
 *
 *  Created on: Feb 10, 2012
 *      Author: jared
 */

#ifndef URL_H_
#define URL_H_
#include <string>
#include <string.h>
#include <iostream>
#define URL_SIZE 2048
using namespace std;

//Tools to handle url specific functions
class URL{
public:
	//Default Constructor
	URL(string url);

	//Default Deconstructor
	~URL();

	//Adds a base to the stored URL
	//@par base - base to be placed on url
	void addBase(string base);

	string getURL();
	void setURL(string url);

private:
	char stored_url[URL_SIZE];

	//Resolve the joining of the two urls
	void resolveURL(char * base, char * url);

	//Resolve URLs that start with '/' symbols.
	void resolveRoot(char * final_url, char * url);

	//Sets NULL in final_url after the top portion of the web URL
	void getWebBase(char * final_url);
	
	//Smartly concatenates two URL c-strings.
	void joinURL(char * base, char * url);

	//Removes the file name from the base string that is passed in through the shell.
	//Stores it into final_url
	void getBaseURL(char * final_url, char * base);

	//Resolves URLs that include relative file symbols.
	//These are symbols that include './' and '../'
	void resolveRelative(char * base, char * url);

	//Count the number of parent directories we are moving up
	//Return this value
	int countRelative(char * url);

	//Remove all of the './' and '../' items in url
	void cleanRelative(char * url);

	//Go through the base and remove the number of parents specified by relative_count
	void removeParents(char * base, int relative_count);	
};

#endif /* URL_H_ */
