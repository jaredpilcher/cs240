/*
 * WebCrawler.cpp
 *
 *  Created on: Feb 10, 2012
 *      Author: jared
 */
#include "WebCrawler.h"
#include "PageDownloader.h"
#include "WordIndex.h"
#include "HTMLParser.h"
#include "StopWords.h"
#include "PageHistory.h"
#include "PageQueue.h"
#include "XMLGenerator.h"
#include "Page.h"
#include <string>

#define MAX_LINE 32000

void WebCrawler::CrawlWeb(){
	PageDownloader downloader;
	WordIndex index;
	HTMLParser parser(start_url);
	StopWords stop_words;
	PageHistory history;
	PageQueue queue;
	XMLGenerator generator(&history, &index, start_url, output_file);
	string word, link;
	ifstream file;
	string line;
	string page_text;

	//create new page and place in queue and history
	Page* page = new Page(start_url);
	queue.push(page);
	history.push(page);
	history.push(page);

	stop_words.getWords(stop_file);
	while(!queue.isEmpty()){
		//pop page from queue
		page = queue.pop();

		//Download page
		//Parse string returned from downloader
		string page_url = page->getURL();
		if(page_url[0]=='/'){
			page_text = "";
			file.open(page_url.data());
			while (file.good())
			{
			  getline (file,line);
			  page_text.append(line);
			}
			file.close();
		}else{
			page_text = downloader.download(*page);
		}
		parser.setNewPage(page_text, page_url);
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

		//Get links from html, create new page and push on queue and history
		while(parser.hasNextLink()){
			link = parser.getLink();
			if(!isHTML(link)) continue;
			page=new Page(link);
			if(history.push(page)){
				queue.push(page);
				continue;
			}
			delete page;
		}

	}
	cout << "Finished Loop" << endl;
	generator.writeFile();
	cout << "end" << endl;

}


//Determines if the page is HTML
bool WebCrawler::isHTML(string url){
	if(url[url.size()-1]=='/') return true;
	if(!hasExtension(url)) return true;
	if(hasCorrectExtension(url)) return true;
	return true;
}

bool WebCrawler::hasExtension(string url){
	string file_name = getFileName(url);
	if(file_name.size()==0) return true;
	for(int i=file_name.size()-1;i>=0;--i){
		if(file_name[i]=='/') return false;
		if(file_name[i]=='.') return true;
	}
	return false;
}

string WebCrawler::getFileName(string url){
	if(url.size()==0) return url;
	for(int i=url.size()-1;i>=0;--i){
		if(url[i]=='/') return (&url[i]+1);
	}
	return url;
}

bool WebCrawler::hasCorrectExtension(string url){
	string extension = getExtension(url);
	if(extension=="html" || extension=="htm" || extension=="shtml" || 
		extension=="cgi" || extension=="jsp" || extension=="asp"   || 
		extension=="aspx"|| extension=="php" || extension=="pl"    || extension=="cfm"){
		
		return true;
	}
	return false;
}

string WebCrawler::getExtension(string url){
	if(url.size()==0) return url;
	for(int i=url.size()-1;i>=0;--i){
		if(url[i]=='.') return (&url[i]+1);
	}
	return "";
}
