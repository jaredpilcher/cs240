#include <iostream>
#include <string>
using namespace std;

#include "UnitTest.h"
#include "Page.h"
#include "PageQueue.h"
#include "PageHistory.h"

bool pageTest(ostream&, bool);
bool pageQueueTest(ostream & os, bool success);
bool pageHistoryTest(ostream & os, bool success);

int main(int argc, char* argv[]){
	bool success=true;
	//Page Test
	success = pageTest(cout, success);

	//PageQueue Test
	success = pageQueueTest(cout, success);

	//PageHistory Test
	success = pageHistoryTest(cout, success);

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

	//create new page and place in queue
	Page* page = new Page(url);
	queue.push(page);

	//One item on queue
	TEST(1==queue.getSize());

	//Page is retrieved properly
	TEST(page == queue.pop());

	//No items on queue
	TEST(0==queue.getSize());

	delete page;
	return success;
}

bool pageHistoryTest(ostream & os, bool success){
	string url = "http://hello.com";
	string url2 = "http://hello.com";
	string description = "description1";
	string description2 = "description2";
	PageHistory history;

	//create new page and place in history
	Page * page = new Page(url);
	page->setDescription(description);
	history.push(page);

	//One item in history
	TEST(1==history.getSize());

	//Second item in history
	Page * page2 = new Page(url2);
	page2->setDescription(description2);
	history.push(page2);
	TEST(2==history.getSize());


	//Pages are retrieved properly
	Page * testpage = history.pop();
	TEST(page==testpage || page2==testpage);
		//page is same
		TEST(testpage->getURL() == url || testpage->getURL() == url2);
		TEST(testpage->getDescription() == description || testpage->getDescription() == description2);
	testpage = history.pop();
	TEST(page==testpage || page2==testpage);
		//page is same
		TEST(testpage->getURL() == url || testpage->getURL() == url2);
		TEST(testpage->getDescription() == description || testpage->getDescription() == description2);

	//NULL returned if not pages on history
	TEST(NULL==history.pop());

	//No items in history
	TEST(0==history.getSize());

	//Page is removed properly
	history.push(page);
	history.remove(page);
	TEST(NULL==history.pop());
	
	//No items in history
	TEST(0==history.getSize());
	
	delete page;
	return success;

}
