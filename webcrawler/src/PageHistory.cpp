/*
 * PageHistory.cpp
 *
 *  Created on: Feb 10, 2012
 *      Author: jared
 */

#include "PageHistory.h"

//static int count =0;

//Default Constructor
PageHistory::PageHistory(){
}

//Default Deconstructor
PageHistory::~PageHistory(){
}

//Push the page onto the history BST
//@par page - page to be inserted
bool PageHistory::push(Page * page){
       // cout << ++count << endl;
	return history.Insert(page->getURL(),page) != NULL;
}

//Return the next page in the BST
//@ret page - page pointer popped off
//must verify that is empty before using this function
Page * PageHistory::pop(){
	//cout << --count << endl;
	Page * page = history.PopValue();
	//cout << "in pagehistory pop" << endl;
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
