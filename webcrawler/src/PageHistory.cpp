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

//Remove the page that matches the argument
//from the BST
//@par page - page to be removed
void PageHistory::pop(Page * page){
	
}
