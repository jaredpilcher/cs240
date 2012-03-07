/*
 * PageDownloader.cpp
 *
 *  Created on: Feb 10, 2012
 *      Author: jared
 */
#include "PageDownloader.h"
#include "URLInputStream.h"
#include <iostream>
using namespace std;

string PageDownloader::download(const Page & page){
	string page_text;
	getText(page.getURL(), page_text);
	return page_text;
}

void PageDownloader::getText(const string url, string & page_text){
	try{
		URLInputStream input_stream(url);
		while(!input_stream.IsDone()){
			page_text.append(1,input_stream.Read());
		}
	}
	catch(...){
		page_text="";
	}

}
