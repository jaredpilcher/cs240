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
#include "WordIndex.h"
#include "StopWords.h"
#include "XMLGenerator.h"
#include "WebCrawler.h"

static const unsigned int npos = -1;

bool pageTest(ostream&, bool);
bool pageQueueTest(ostream & os, bool success);
bool pageHistoryTest(ostream & os, bool success);
bool pageDownloaderTest(ostream & os, bool success);
bool URLTest(ostream & os, bool success);
bool HTMLParserTest(ostream & os, bool success);
bool OccurrenceTest(ostream & os, bool success);
bool OccurrenceSetTest(ostream & os, bool success);
bool WordIndexTest(ostream & os, bool success);
bool StopWordsTest(ostream & os, bool success);
bool XMLGeneratorTest(ostream & os, bool success);
bool WebCrawlerTest(ostream & os, bool success);

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
	success = OccurrenceTest(cout, success);

	//OccurrenceSet Test
	success = OccurrenceSetTest(cout, success);

	//WordIndex Test
	success = WordIndexTest(cout, success);

	//StopWords Test
	success = StopWordsTest(cout, success);

	//XMLGenerator Test
	//success = XMLGeneratorTest(cout, success);

	//WebCrawler Test
	success = WebCrawlerTest(cout, success);

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
	Occurrence occurrence;

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
	occurrence = occurrences.pop();
	if(occurrence.getURL()==url){
		TEST(occurrence.getCount()==1);
	}else{
		TEST(occurrence.getCount()==2);
	}
	TEST(!occurrences.isEmpty());
		
	occurrence = occurrences.pop();
	if(occurrence.getURL()==url){
		TEST(occurrence.getCount()==1);
	}else{
		TEST(occurrence.getCount()==2);
	}
	TEST(occurrences.isEmpty());
	return success;
}

bool WordIndexTest(ostream & os, bool success){
	string word = "hello";
	string word2 = "jared";
	string word3 = "pilcher";
	string url = "http://www.google.com";
	string url2 = "http://www.yahoo.com";
	string url3 = "http://www.amazon.com";
	WordIndex index;
	Occurrence occurrence;
	OccurrenceSet * occurrences;
	string indexed_word;

	//Simple push/pop test
	index.push(word,url);
	occurrences = index.pop(indexed_word);
	occurrence = occurrences->pop();
	TEST(occurrence.getURL()==url);
	TEST(occurrence.getCount()==1);
	TEST(occurrences->isEmpty());
	TEST(index.isEmpty());
	delete occurrences;

	//Count test
	index.push(word,url);
	index.push(word,url);
	TEST(!index.isEmpty());
	occurrences = index.pop(indexed_word);
	TEST(index.isEmpty());
	TEST(!occurrences->isEmpty());
	occurrence = occurrences->pop();
	TEST(occurrence.getCount()==2);
	TEST(occurrence.getURL()==url);
	delete occurrences;

	//Multiple url push test
	index.push(word,url);
	index.push(word,url2);
	index.push(word,url3);
	TEST(!index.isEmpty());
	occurrences=index.pop(indexed_word);
	TEST(index.isEmpty());
	TEST(!occurrences->isEmpty());
		//Test first occurrence
		occurrence = occurrences->pop();
		TEST(!occurrences->isEmpty());
		TEST(occurrence.getCount()==1);
		TEST(occurrence.getURL()==url || occurrence.getURL()==url2 || occurrence.getURL()==url3);

		//Test second occurrence
		occurrence = occurrences->pop();
		TEST(!occurrences->isEmpty());
		TEST(occurrence.getCount()==1);
		TEST(occurrence.getURL()==url || occurrence.getURL()==url2 || occurrence.getURL()==url3);

		//Test third occurrence
		occurrence = occurrences->pop();
		TEST(occurrences->isEmpty());
		TEST(occurrence.getCount()==1);
		TEST(occurrence.getURL()==url || occurrence.getURL()==url2 || occurrence.getURL()==url3);
	delete occurrences;

	//Multiple word push test*/
	index.push(word,url);
	index.push(word2,url);
	index.push(word3,url);
	TEST(!index.isEmpty());
		//Test first word
		occurrences=index.pop(indexed_word);
		TEST(!index.isEmpty());
		TEST(!occurrences->isEmpty());
		occurrence = occurrences->pop();
		TEST(occurrence.getCount()==1);
		TEST(occurrence.getURL()==url);
		TEST(occurrences->isEmpty());
		delete occurrences;

		//Test second word
		occurrences=index.pop(indexed_word);
		TEST(!index.isEmpty());
		TEST(!occurrences->isEmpty());
		occurrence = occurrences->pop();
		TEST(occurrence.getCount()==1);
		TEST(occurrence.getURL()==url);
		TEST(occurrences->isEmpty());
		delete occurrences;

		//Test third word
		occurrences=index.pop(indexed_word);
		TEST(index.isEmpty());
		TEST(!occurrences->isEmpty());
		occurrence = occurrences->pop();
		TEST(occurrence.getCount()==1);
		TEST(occurrence.getURL()==url);
		TEST(occurrences->isEmpty());
		delete occurrences;

	return success;
}

bool StopWordsTest(ostream & os, bool success){
	StopWords stop_words;
	stop_words.getWords("StopWordsTestFiles/stopwords.txt");
	TEST(stop_words.getCount()==35);
	TEST(stop_words.isStopWord("a"));
	TEST(stop_words.isStopWord("an"));
	TEST(stop_words.isStopWord("and"));
	TEST(stop_words.isStopWord("are"));
	TEST(stop_words.isStopWord("with"));
	TEST(stop_words.isStopWord("such"));
	TEST(stop_words.isStopWord("but"));
	TEST(stop_words.isStopWord("will"));

	//Testing multiple times to make sure not deleting array objects
	TEST(stop_words.isStopWord("but"));
	TEST(stop_words.isStopWord("but"));
	TEST(stop_words.getCount()==35);

	return success;
}

bool XMLGeneratorTest(ostream & os, bool success){
	string start_url = "http://students.cs.byu.edu/~cs240ta/crawler_tests/crawlindex.html";
	string stop_file = "StopWordsTestFiles/stopwords.txt";
	PageDownloader downloader;
	WordIndex index;
	HTMLParser parser;
	StopWords stop_words;
	PageHistory history;
	PageQueue queue;
	XMLGenerator generator(&history, &index, start_url);
	string word;

	//create new page and place in queue and history
	Page* page = new Page(start_url);
	queue.push(page);
	history.push(page);

	page = new Page("http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/TestOne.html");
	queue.push(page);
	history.push(page);

	page = new Page("http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/testFour.htm");
	queue.push(page);
	history.push(page);

	stop_words.getWords(stop_file);
	while(!queue.isEmpty()){
		//pop page from queue
		page = queue.pop();

		//Download page
		//Parse string returned from downloader
		parser.setNewPage(downloader.download(*page), page->getURL());

		parser.parsePage();

		//Grab the description and set to page
		page->setDescription(parser.getDescription());

		//Go through the html document and index words
		while(!parser.isEmpty()){
			word =parser.getWord();
			if(!stop_words.isStopWord(word)){
				index.push(word, page->getURL());
			}
		}
	}


	generator.writeFile();

	return success;
}

bool WebCrawlerTest(ostream & os, bool success){
	string start_url = "http://students.cs.byu.edu/~cs240ta/crawler_tests/crawlindex.html";
	string output_file = "/home/jared/cs240/webcrawler/output.xml";
	string stop_words_file = "StopWordsTestFiles/stopwords.txt";
	WebCrawler crawler(start_url, output_file, stop_words_file);
	crawler.CrawlWeb();
	return success;
}
