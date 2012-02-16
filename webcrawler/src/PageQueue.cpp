/*
 * PageQueue.cpp
 *
 *  Created on: Feb 10, 2012
 *      Author: jared
 */
#include "PageQueue.h"

//Default Constructor
PageQueue::PageQueue(){}

//Default Deconstructor
PageQueue::~PageQueue(){}

//Pushes a page on the the queue
//@par page - the page to be inserted onto the queue
void PageQueue::push(Page * page){
	queue.Insert(page, queue.GetLast());
}

//Removes and returns a pointer to 
//the next page on the queue
//@ret Page - returns a pointer to the next page in the queue 
	//or NULL if there isn't any page in the queue
Page * PageQueue::pop(){
	return queue.Pop();
}


