/*
 * PageHistory.h
 *
 *  Created on: Feb 10, 2012
 *      Author: jared
 */

#ifndef PAGEHISTORY_H_
#define PAGEHISTORY_H_
#include "BST.h"
#include <iostream>
#include "Page.h"
using namespace std;

//Contains the history of pages that have been indexed
class PageHistory{
public:
	//Default Constructor
	PageHistory();

	//Default Deconstructor
	~PageHistory();
	
	//Push the page onto the history BST
	//@par page - page to be inserted
	//@ret bool - True if successfully inserted in tree
	bool push(Page * page);
	
	//Remove the page that matches the argument
		//from the BST
	//Each time you pop from history, you must 
		//delete the page afterward
	//@par page - page to be removed
	void remove(Page * page);
	
	//Pop the next lowest Page (pointer value) from the tree
	//@ret Page * - next page with lowest address
	Page * pop();

	int getSize();
	
	//Determines if the history is empty
	bool isEmpty();

private:
	//The BST to hold the history of pages
	BST<string,Page*> history;
};

#endif /* PAGEHISTORY_H_ */
