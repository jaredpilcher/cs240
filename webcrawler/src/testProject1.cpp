#include <iostream>
#include <string>
using namespace std;

#include "UnitTest.h"
#include "Page.h"
#include "PageQueue.h"

bool pageTest(ostream&, bool);
bool pageQueueTest(ostream & os, bool success);

int main(int argc, char* argv[]){
	bool success=true;
	//Page Test
	success = pageTest(cout, success);

	//PageQueue Test
	success = pageQueueTest(cout, success);

	if(success){
		cout << "Success!" << endl;
	}
	return 0;
}

bool pageTest(ostream & os, bool success){
	string url = "http://hello.com";
	string description = "This is a description";
	Page page(url);
	page.getURL();
	//Test that url is set properly
	TEST(url==page.getURL());

	//Description is set properly
	page.setDescription(description);
	TEST(description==page.getDescription());

	//URL is set properly
	url = "file:///hello";
	page.setURL(url);
	TEST(url==page.getURL());
	
	return success;
	
	
}

bool pageQueueTest(ostream & os, bool success){
	string url = "http://hello.com";
	PageQueue queue;

	//create new page and place in queue and history
	Page* page = new Page(url);
	queue.push(page);

	//One item on queue
	TEST(1==queue.getSize());

	//Page is retrieved properly
	TEST(page == queue.pop());

	//No items on queue
	TEST(0==queue.getSize());


	return success;
}
