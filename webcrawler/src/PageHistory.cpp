/*
 * PageHistory.cpp
 *
 *  Created on: Feb 10, 2012
 *      Author: jared
 */

#include "PageHistory.h"

//Default Constructor
PageHistory::PageHistory(){
}

//Default Deconstructor
PageHistory::~PageHistory(){
}

//Push the page onto the history BST
//@par page - page to be inserted
void PageHistory::push(Page * page){
	history.Insert(page);
}

//Return the next page in the BST
//@ret page - page pointer popped off
//returns NULL if no pages in history
Page * PageHistory::pop(){
	return history.Pop();
}

//Remove the page that matches the argument
//from the BST
//@par page - page to be removed
void PageHistory::remove(Page * page){
	history.Remove(page);
}

int PageHistory::getSize(){
	return history.GetSize();
}
