#include <iostream>
using namespace std;

int main(int argc, char* argv[]){
	if(argc>3){
		WebCrawler webcrawler(argv[1], argv[2], argv[3]);
		webcrawler.CrawlWeb();
	}
	else{
		cout << "Please enter the correct number of arguments"
	}
	return 0;
}
