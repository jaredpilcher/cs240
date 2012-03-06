/*
 * WebCrawler.h
 *
 *  Created on: Feb 10, 2012
 *      Author: jared
 */
#ifndef WEBCRAWLER_H_
#define WEBCRAWLER_H_

#include <string>
using namespace std;

//The main driver class for the web crawler
class WebCrawler{
		//The start_url that was passed in by the user
		string start_url;
		//The output_file that was passed in by the user
		string output_file;
		//The stop_file that was passed in by the user
		string stop_file;
	public:
		//Default Constructor
		WebCrawler(string arg_url, string arg_output, string arg_stop): start_url(arg_url), output_file(arg_output), stop_file(arg_stop){
		}

		//Default Deconstructor
		~WebCrawler(){
		}

		//Crawls the website specified by 
		//the start_url class variable
		void CrawlWeb();



	private:
		//Determines if the page is HTML
		bool isHTML(string url);
		
		//Determines if url doesn't have an extension
		bool hasNoExtension(string url);

		//Gets the file name of the url
		string getFileName(string url);
};

#endif /* WEBCRAWLER_H_ */
