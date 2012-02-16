/*
 * PageQueue.cpp
 *
 *  Created on: Feb 10, 2012
 *      Author: jared
 */
using namespace std;

//Default Constructor
PageQueue::PageQueue(){}

//Default Deconstructor
PageQueue::~PageQueue(){}

//Pushes a page on the the queue
//@par page - the page to be inserted onto the queue
void PageQueue::push(Page page){
	queue.Insert(page, GetLast());
}

//Removes and returns a copy of 
//the next page on the queue
//@ret Page - returns the next node in the queue 
	//or NULL if there isn't any page in the queue
Page PageQueue::pop(){
	return queue.Pop();
}


