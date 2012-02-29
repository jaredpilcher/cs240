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
	HTMLParser parser(start_url);
	StopWords stop_words;
	PageHistory history;
	PageQueue queue;
	XMLGenerator generator(history, index, start_url);
	string word;

	//create new page and place in queue and history
	Page* page = new Page(start_url);
	queue.push(page);
	history.push(page);

	stop_words.getWords(stop_file);

	while(!queue.empty()){
		//pop page from queue
		page = queue.pop();

		//Download page
		//Parse string returned from downloader
		parser.setNewPageString(downloader.download(page));

		//Determine if this is a valid page
		if(!parser.isHTML()){
			history.remove(page);
			delete page;
			continue;
		}

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
			page=new Page(parser.getLink());
			if(history.push(page)){
				queue.push(page);
			}
		}

	}

	generator.writeFile();

}
