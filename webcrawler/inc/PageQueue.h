/*
 * PageQueue.h
 *
 *  Created on: Feb 10, 2012
 *      Author: jared
 */

#ifndef PAGEQUEUE_H_
#define PAGEQUEUE_H_

#include "LinkedList.h"
#include "Page.h"
using namespace std;

//Holds the list of pages that need to be indexed
class PageQueue{
public:
	//Default Constructor
	PageQueue();

	//Default Deconstructor
	~PageQueue();

	//Pushes a page on the the queue
	//@par page - the page to be inserted onto the queue
	void push(Page * page);

	//Removes and returns a pointer of 
	//the next page on the queue
	Page * pop();

	//Retrieves the number of items on queue
	//@ret int - number of items on quue
	int getSize();

private:
	//The linked list that holds the list
	//of pages that need to be indexed
	LinkedList<Page*> queue;
};

#endif /* PAGEQUEUE_H_ */
