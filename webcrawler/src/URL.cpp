/*
 * URL.cpp
 *
 *  Created on: Feb 26, 2012
 *      Author: jared
 */
#include "URL.h"

//Default Constructor
URL::URL(string arg_url){
	strcpy(stored_url,arg_url.data());
}

//Default Deconstructor
URL::~URL(){
}

string URL::getURL(){
	return string(stored_url);
}

//Adds a base to the stored URL
//@par base - base to be placed on url
void URL::addBase(string base){
	char temp[URL_SIZE];
	char temp_base[URL_SIZE];
	strcpy(temp,stored_url);
	strcpy(temp_base,base.data());
	resolveURL(temp_base,temp);
}



void URL::setURL(string url){
	strcpy(stored_url,url.data());
}

void URL::resolveURL(char * base, char * url){
    
    //Set stored url to all zeros
    memset(stored_url,0,2048);

    //Resolve the urls
    switch(url[0]){
        case '/':
			if(base[0]=='f' || base[0]=='F'){
				strcpy(stored_url,"file:///");
				resolveRoot(stored_url,url);
			}
			else{
				getBaseURL(stored_url, base);
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
				getBaseURL(stored_url, base);
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
void URL::joinURL(char * base, char * url){
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

//Removes the file name from the base string that is passed in through the shell.
//Stores it into final_url
void URL::getBaseURL(char * final_url, char * base){
    int slash_location = 0;
    for(int i = 0; base[i] != 0; i++){
        if(base[i]=='/'){
            slash_location = i;
        }
    }
	int base_length = strlen(base);
	//if ends in '.com' or '.net', etc then don't remove file name
	if(base[base_length-4] != '.'){
	    strncpy(final_url,base,slash_location+1);
	}
	else{
		strcpy(final_url,base);
	}
}

//Resolves URLs that include relative file symbols.
//These are symbols that include './' and '../'
void URL::resolveRelative(char * base, char * url){
	int relative_count = countRelative(url);
	cleanRelative(url);
	removeParents(base, relative_count);
	joinURL(base,url);
}

//Count the number of parent directories we are moving up
//Return this value
int URL::countRelative(char * url){
	int relative_count = 0;
	for(int i = 0; url[i] != 0 && url[i+1] != 0; i++){
		if(url[i] == '.' && url[i+1] == '.'){
			relative_count++;
		}
	}
	return relative_count;
}

//Remove all of the './' and '../' items in url
void URL::cleanRelative(char * url){
	char * temp_ptr;
	char temp_url[URL_SIZE];
	for(int i = 0; url[i] != 0; i++){
		if(url[i] >= 'A'){
			temp_ptr = &url[i];
			break;
		}
	}
	strcpy(temp_url, temp_ptr);
	strcpy(url, temp_url);
}

//Go through the base and remove the number of parents specified by relative_count
void URL::removeParents(char * base, int relative_count){
	for(int i = strlen(base) - 2; i >= 0; i--){
		if(relative_count == 0) break;
		if(base[i] == '/'){
			base[i + 1] = 0;
			relative_count--;
		}
	}
}
