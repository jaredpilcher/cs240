#include <iostream>
#include <string>
using namespace std;

#include "UnitTest.h"
#include "WebPage.h"

bool pageTest(ostream&, bool);

int main(int argc, char* argv[]){
	bool success;
	success = pageTest(cout, success);
	
}

bool pageTest(ostream & os, bool success){
	string url = "http://hello.com";
	string description = "This is a description";
	WebPage page(url);
	page.GetURL();
	//Test that url is set properly
	TEST(url==page.GetURL());

	//Description is set properly
	page.setDescription(description);
	TEST(description==page.getDescription());

	//URL is set properly
	url = "file:///hello";
	page.setURL(url);
	TEST(url==page.GetURL());
	
	return success;
	
	
}
