#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "UnitTest.h"
#include "Page.h"
#include "PageQueue.h"
#include "PageHistory.h"
#include "PageDownloader.h"
#include "URL.h"
#include "HTMLParser.h"
#include "Occurrence.h"
#include "OccurrenceSet.h"

static const unsigned int npos = -1;

bool pageTest(ostream&, bool);
bool pageQueueTest(ostream & os, bool success);
bool pageHistoryTest(ostream & os, bool success);
bool pageDownloaderTest(ostream & os, bool success);
bool URLTest(ostream & os, bool success);
bool HTMLParserTest(ostream & os, bool success);
bool OccurrenceTest(ostream & os, bool success);
bool OccurrenceSetTest(ostream & os, bool success);

int main(int argc, char* argv[]){
	bool success=true;
	//Page Test
	success = pageTest(cout, success);

	//PageQueue Test
	success = pageQueueTest(cout, success);

	//PageHistory Test
	success = pageHistoryTest(cout, success);

	//PageDownloader Test
	success = pageDownloaderTest(cout, success);

	//URL Test
	success = URLTest(cout, success);

	//HTMLParser Test
	success = HTMLParserTest(cout, success);

	//Occurrence Test
	OccurrenceTest(cout, success);

	//OccurrenceSet Test
	OccurrenceSetTest(cout, success);

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

bool pageDownloaderTest(ostream & os, bool success){
	PageDownloader downloader;
	string url = "http://www.google.com";
	TEST(downloader.download(url).find("<title>Google</title>") != npos);
	return success;
}

bool URLTest(ostream & os, bool success){
	//File Root URL Tests
	URL url("/jared.txt");
	url.addBase("file://");
	TEST(url.getURL()=="file:///jared.txt");

	url.setURL("/jared.txt");
	url.addBase("file:///query?test=something");
	TEST(url.getURL()=="file:///jared.txt");

	url.setURL("/jared.txt");
	url.addBase("file:///jared/pilcher");
	TEST(url.getURL()=="file:///jared.txt");

	url.setURL("/jared.txt");
	url.addBase("file:///jared/pilcher/");
	TEST(url.getURL()=="file:///jared.txt");

	//Web Root URL Test
	url.setURL("/jared.txt");
	url.addBase("http://www.google.com");
	TEST(url.getURL()=="http://www.google.com/jared.txt");

	url.setURL("/jared.txt");
	url.addBase("http://www.google.com/");
	TEST(url.getURL()=="http://www.google.com/jared.txt");

	url.setURL("/jared.txt");
	url.addBase("http://www.google.com/jared");
	TEST(url.getURL()=="http://www.google.com/jared.txt");

	url.setURL("/jared.txt");
	url.addBase("http://www.google.com/jared/");
	TEST(url.getURL()=="http://www.google.com/jared.txt");

	//File Relative Tests
	url.setURL("./jared");
	url.addBase("file://");
	TEST(url.getURL()=="file:///jared");

	url.setURL("./jared");
	url.addBase("file:///query?test=something");
	TEST(url.getURL()=="file:///jared");

	url.setURL("./jared");
	url.addBase("file:///jared/pilcher");
	TEST(url.getURL()=="file:///jared/jared");

	url.setURL("./jared");
	url.addBase("file:///jared/pilcher/");
	TEST(url.getURL()=="file:///jared/pilcher/jared");

	url.setURL("../jared");
	url.addBase("file:///jared/pilcher");
	TEST(url.getURL()=="file:///jared");

	url.setURL("../jared");
	url.addBase("file:///jared/pilcher/");
	TEST(url.getURL()=="file:///jared/jared");

	url.setURL("./.././jared");
	url.addBase("file:///jared/pilcher");
	TEST(url.getURL()=="file:///jared");

	url.setURL("./.././jared");
	url.addBase("file:///jared/pilcher/");
	TEST(url.getURL()=="file:///jared/jared");

	url.setURL("jared");
	url.addBase("file://");
	TEST(url.getURL()=="file:///jared");

	url.setURL("jared");
	url.addBase("file:///query?test=something");
	TEST(url.getURL()=="file:///jared");

	url.setURL("jared");
	url.addBase("file:///jared/pilcher");
	TEST(url.getURL()=="file:///jared/jared");

	url.setURL("jared");
	url.addBase("file:///jared/pilcher/");
	TEST(url.getURL()=="file:///jared/pilcher/jared");

	//Web Relative Tests
	url.setURL("./jared");
	url.addBase("http://www.website.com");
	TEST(url.getURL()=="http://www.website.com/jared");

	url.setURL("./jared");
	url.addBase("http://www.website.com/");
	TEST(url.getURL()=="http://www.website.com/jared");

	url.setURL("./jared");
	url.addBase("http://www.website.com/jared");
	TEST(url.getURL()=="http://www.website.com/jared");

	url.setURL("./jared");
	url.addBase("http://www.website.com/jared/");
	TEST(url.getURL()=="http://www.website.com/jared/jared");

	url.setURL("../jared");
	url.addBase("http://www.website.com/jared/");
	TEST(url.getURL()=="http://www.website.com/jared");

	url.setURL("../jared");
	url.addBase("http://www.website.com/jared/pilcher/");
	TEST(url.getURL()=="http://www.website.com/jared/jared");

	url.setURL("../jared");
	url.addBase("http://www.website.com/jared/pilcher");
	TEST(url.getURL()=="http://www.website.com/jared");

	url.setURL("./.././jared");
	url.addBase("http://www.website.com/jared/");
	TEST(url.getURL()=="http://www.website.com/jared");

	url.setURL("./.././jared");
	url.addBase("http://www.website.com/jared/pilcher/");
	TEST(url.getURL()=="http://www.website.com/jared/jared");

	url.setURL("./.././jared");
	url.addBase("http://www.website.com/jared/pilcher");
	TEST(url.getURL()=="http://www.website.com/jared");

	url.setURL("jared");
	url.addBase("http://www.website.com");
	TEST(url.getURL()=="http://www.website.com/jared");

	url.setURL("jared");
	url.addBase("http://www.website.com/");
	TEST(url.getURL()=="http://www.website.com/jared");

	url.setURL("jared");
	url.addBase("http://www.website.com/jared");
	TEST(url.getURL()=="http://www.website.com/jared");

	url.setURL("jared");
	url.addBase("http://www.website.com/jared/");
	TEST(url.getURL()=="http://www.website.com/jared/jared");

	//File Internal Relative Tests
	url.setURL("#something");
	url.addBase("file:///query?test=something");
	TEST(url.getURL()=="file:///query?test=something");

	url.setURL("#something");
	url.addBase("file:///jared/pilcher");
	TEST(url.getURL()=="file:///jared/pilcher");


	//Web Internal Relative Tests
	url.setURL("#something");
	url.addBase("http://www.website.com/jared");
	TEST(url.getURL()=="http://www.website.com/jared");


	return success;
}

bool HTMLParserTest(ostream & os, bool success){

	//Test 1
		//Download page and parse it
		PageDownloader downloader;
		string url = "http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/scale.php?sec=";
		string page_text = downloader.download(url);
		HTMLParser parser;
		parser.setNewPage(page_text, url);
		parser.parsePage();

		//Test if words are correct
			//Get words
			fstream file("ParseTestFiles/test1.txt");
			char temp[MAX_CHAR_IN_LINE];
			LinkedList<string> words;
			while(1){
				file.getline(temp,MAX_CHAR_IN_LINE);
				if(!file) break;
				words.Insert(temp, words.GetLast());
			}
			file.close();

			//Determine if word lists are equivalent
			while(!words.IsEmpty()){
				//If parser runs out of words before words in file, then fails
				TEST(!parser.isEmpty());
				if(parser.isEmpty()) break;
				//Test if words are equivalent
				TEST(parser.getWord() == words.Pop());
			}

			//Determine if description is correct
			TEST(parser.getDescription()=="Scale test description");

		//Test if links are correct
			//Get links
				file.open("ParseTestFiles/test1Links.txt");
				LinkedList<string> links;
				while(1){
					file.getline(temp,MAX_CHAR_IN_LINE);
					if(!file) break;
					links.Insert(temp, links.GetLast());
				}
				file.close();

			//Determine if link lists are equivalent
			while(!links.IsEmpty()){
				//If parser runs out of links before links in file, then fails
				TEST(parser.hasNextLink());
				if(!parser.hasNextLink()) break;
				//Test if words are equivalent
				TEST(parser.getLink() == links.Pop());
			}

	//Test 2
		//Download page and parse it
		url = "http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/testFour.htm";
		page_text = downloader.download(url);
		parser.setNewPage(page_text, url);
		parser.parsePage();

		//Test if words are correct
			//Get words
			file.open("ParseTestFiles/test2.txt");
			words.Clear();
			while(1){
				file.getline(temp,MAX_CHAR_IN_LINE);
				if(!file) break;
				words.Insert(temp, words.GetLast());
			}
			file.close();
			//Determine if word lists are equivalent
			while(!words.IsEmpty()){
				//If parser runs out of words before words in file, then fails
				TEST(!parser.isEmpty());
				if(parser.isEmpty()) break;
				//Test if words are equivalent
				TEST(parser.getWord() == words.Pop());
			}

			//Determine if description is correct
			TEST(parser.getDescription()=="Description Test");

		//Test if links are correct
			//Get links
				file.open("ParseTestFiles/test2Links.txt");
				links.Clear();
				while(1){
					file.getline(temp,MAX_CHAR_IN_LINE);
					if(!file) break;
					links.Insert(temp, links.GetLast());
				}
				file.close();

			//Determine if link lists are equivalent
			while(!links.IsEmpty()){
				//If parser runs out of links before links in file, then fails
				TEST(parser.hasNextLink());
				if(!parser.hasNextLink()) break;
				//Test if words are equivalent
				TEST(parser.getLink() == links.Pop());
			}
	
	return success;
}


bool OccurrenceTest(ostream & os, bool success){
	string url = "http://www.google.com";
	Occurrence occurrence(url);
	TEST(occurrence.getCount()==0);
	occurrence.addOccurrence();
	TEST(occurrence.getCount()==1);
	TEST(occurrence.getURL()=="http://www.google.com");
	return success;
}


bool OccurrenceSetTest(ostream & os, bool success){
	string url = "http://www.google.com";
	string url2 = "http://www.yahoo.com";
	string url3 = "http://www.amazon.com";
	OccurrenceSet occurrences;

	//Simple push/pop test
	occurrences.push(url);
	TEST(occurrences.pop().getCount()==1);
	TEST(occurrences.isEmpty());

	//Count test
	occurrences.push(url);
	occurrences.push(url);
	TEST(occurrences.pop().getCount()==2);
	TEST(occurrences.isEmpty());

	//Multiple push test
	occurrences.push(url);
	occurrences.push(url2);
	occurrences.push(url2);
	int count;
	string test_url;
	occurrences.pop().getContents(count,test_url);
	if(test_url==url){
		TEST(count==1);
	}else{
		TEST(count==2);
	}
	TEST(!occurrences.isEmpty());
		
	occurrences.pop().getContents(count,test_url);
	if(test_url==url){
		TEST(count==1);
	}else{
		TEST(count==2);
	}
	TEST(occurrences.isEmpty());
	return success;
}
