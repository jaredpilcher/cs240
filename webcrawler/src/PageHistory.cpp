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
bool PageHistory::push(Page * page){
	return history.Insert(page->getURL(),page) != NULL;
}

//Return the next page in the BST
//@ret page - page pointer popped off
//must verify that is empty before using this function
Page * PageHistory::pop(){
	Page * page = history.PopValue();
	return page;
}

//Remove the page that matches the argument
//from the BST
//@par page - page to be removed
void PageHistory::remove(Page * page){
	history.Remove(page->getURL());
}

int PageHistory::getSize(){
	return history.GetSize();
}

bool PageHistory::isEmpty(){
	return history.IsEmpty();
}
