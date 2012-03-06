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

void WebCrawler::CrawlWeb(){
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

	stop_words.getWords(stop_file);
	cout << "here" << endl;
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

		//Get links from html, create new page and push on queue and history
		while(parser.hasNextLink()){
			string link = parser.getLink();
			if(!isHTML(link)) continue;
			page=new Page(link);
			if(history.push(page)){
				queue.push(page);
			}
		}

	}

	generator.writeFile();

}


//Determines if the page is HTML
bool WebCrawler::isHTML(string url){
	if(url[url.size()-1]=='/') return true;
	if(hasNoExtension(url)) return true;
	//if(hasCorrectExtension(url)) return true;
	return false;
}

bool WebCrawler::hasNoExtension(string url){
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
}
