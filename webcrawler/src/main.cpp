#include <iostream>
//#include "WebCrawler.h"
using namespace std;

int main(int argc, char* argv[]){
	if(argc>3){
		//WebCrawler webcrawler((string)argv[1], (string)argv[2], (string)argv[3]);
		//webcrawler.CrawlWeb();
	}
	else{
		cout << "Please enter the correct number of arguments" << endl;
	}
	return 0;
}
