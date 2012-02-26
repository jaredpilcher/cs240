/*
 * URL.cpp
 *
 *  Created on: Feb 26, 2012
 *      Author: jared
 */
#include "URL.h"

//Default Constructor
URL::URL(string arg_url){
	strcpy(stored_url,arg_url);
}

//Default Deconstructor
URL::~URL(){
}

//Adds a base to the stored URL
//@par base - base to be placed on url
void URL::addBase(const string base){
	char temp[URL_SIZE];
	strcpy(temp,stored_url);
	resolveURL(base.data(),temp);
}

//Removes the file name at the end of the url
//@par url - url to manipulate
//@ret string - returns a copy of the manipulated string
string URL::removeFileName(string url){
	
}

void URL::resolveURL(char * base, char * url){
    
    //Set stored url to all zeros
    memset(stored_url,0,2048);

    //Resolve the urls
    switch(url[0]){
        case '/':
			if(base[0]=='f'){
				strcpy(stored_url,"file:///");
				resolveRoot(stored_url,url);
			}
			else{
				//START HERE
				getBaseURL(base, stored_url);
	            resolveRoot(stored_url, url);
			}
            break;
        case '#':
	    	strcpy(stored_url,base);
            strcat(stored_url, url);
            break;
        default:
			if(!strcmp(base,"file:///") || !strcmp(base,"file://")){
				strcpy(stored_url,"file:///");
				resolveRelative(stored_url, url);
			}
			else{
				getBaseURL(base, stored_url);
				resolveRelative(stored_url, url);
			}
            break;
    }
    
}

//Resolve URLs that start with '/' symbols.
void URL::resolveRoot(char * final_url, char * url){
    if(final_url[0] == 'h'){
        getWebBase(final_url);
        joinURL(final_url, url);
    }
    else{
		joinURL(final_url,url);
    }
}

//Sets NULL in final_url after the top portion of the web URL
void URL::getWebBase(char * final_url){
    int slash_count = 0;
    int i = 0;
    for(; final_url[i]!=0; i++){
        if(final_url[i] == '/'){
            slash_count++;
        }
        if(slash_count>2){
            break;
        }
    }
    final_url[i] = 0;
}

//Smartly concatenates two URL c-strings.
void joinURL(char * base, char * url){
	int base_length = strlen(base);
	if(url[0]!='/' && base[base_length-1]!='/'){
		strcat(base, "/");
		strcat(base,url);
	}
	else if(url[0]=='/' && base[base_length-1]=='/'){
		strcat(base,url+1);
	}
	else{
		strcat(base,url);
	}
}