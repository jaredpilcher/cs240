/*
 * URL.cpp
 *
 *  Created on: Feb 26, 2012
 *      Author: jared
 */
#include "URL.h"

//Default Constructor
URL::URL(string arg_url){
	arg_url = stripInternalRelative(arg_url);
	strcpy(stored_url,arg_url.data());
}

string URL::stripInternalRelative(string url){
	for(unsigned int i=0; i<url.size(); ++i){
		if(url[i]=='#') url[i] = 0;
	}
	return url;
}

void URL::stripQuery(string & url){
	for(unsigned int i=0; i<url.size(); ++i){
		if(url[i]=='?') url[i] = 0;
	}
}

//Blank Constructor
URL::URL(){
	stored_url[0] = 0;
}

//Default Deconstructor
URL::~URL(){
}

string URL::getURL(){
	string return_string = stored_url;
	return return_string;
}

URL& URL::operator=(const URL& other){
	strcpy(stored_url,other.stored_url);
	return *this;
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
	url = stripInternalRelative(url);
	strcpy(stored_url,url.data());
}

void URL::setURLBase(string url){
	url = stripInternalRelative(url);
	stripQuery(url);
	char temp_url[URL_SIZE];
	strcpy(temp_url,url.data());
	getBaseURL(stored_url,temp_url);
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
        default:
			if(strlen(url)==0){
				strcpy(stored_url,base);
			}
			else if(!strcmp(base,"file:///") || !strcmp(base,"file://")){
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
	//if ends in '.com' or '.net' or '.org' or '.edu', then don't remove file name
	if(!endsWith(base,".com") && !endsWith(base,".net") && 
			!endsWith(base,".org") && !endsWith(base,".edu")){
	    strncpy(final_url,base,slash_location+1);
		final_url[slash_location+1]=0;
	}
	else{
		strcpy(final_url,base);
	}
}

bool URL::endsWith(const char * base, const char * substring){
	string string_sub = substring;
	return (strcmp(&base[strlen(base)-4],substring)==0) || 
				(strcmp(&base[strlen(base)-5],(string_sub + "/").data())==0);
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

