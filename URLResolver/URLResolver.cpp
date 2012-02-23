#include <iostream>
#include <string.h>
using namespace std;

//Removes the file name from the base string that is passed in through the shell.
void getBaseURL(char * base_url, char * final_url){
    int slash_location = 0;
    for(int i = 0; base_url[i] != 0; i++){
        if(base_url[i]=='/'){
            slash_location = i;
        }
    }
	int base_length = strlen(base_url);
	if(base_url[base_length-4] != '.'){
	    strncpy(final_url,base_url,slash_location+1);
	}
	else{
		strcpy(final_url,base_url);
	}
}

//Smartly concatenates two URL c-strings.
//If the base does not end in a slash, a slash is appended.
//If the url starts with a slash, it is removed
//Both the base and url pointers and values are changed
void joinURL(char * final_url, char * url){
	int base_length = strlen(final_url);
	if(url[0]!='/' && final_url[base_length-1]!='/'){
		strcat(final_url, "/");
		strcat(final_url,url);
	}
	else if(url[0]=='/' && final_url[base_length-1]=='/'){
		strcat(final_url,url+1);
	}
	else{
		strcat(final_url,url);
	}
}

//Collects only the top portion of the URL for resolveRoot function
//Changes the base pointer and value
void getWebBase(char * base){
    int slash_count = 0;
    int i = 0;
    for(; base[i]!=0; i++){
        if(base[i] == '/'){
            slash_count++;
        }
        if(slash_count>2){
            break;
        }
    }
    base[i] = 0;
}

//Resolve URLs that start with '/' symbols.
//Both the base and url pointers and values are changed
void resolveRoot(char * final_url, char * url){
    if(final_url[0] == 'h'){
        getWebBase(final_url);
        joinURL(final_url, url);
    }
    else{
		joinURL(final_url,url);
    }
}

//Count the number of parent directories we are moving up
//Return this value
int countRelative(char * url){
	int relative_count = 0;
	for(int i = 0; url[i] != 0 && url[i+1] != 0; i++){
		if(url[i] == '.' && url[i+1] == '.'){
			relative_count++;
		}
	}
	return relative_count;
}

//Remove all of the './' and '../' items in the relative URL
//Return the url pointer
void cleanRelative(char * &url){
	for(int i = 0; url[i+1] != 0; i++){
		if(url[i] >= 'A'){
			url = &url[i];
			break;
		}
	}
}

//Go through the base and remove the number of parents specified by relative_count
//Return the base c-string
void removeParents(char * base, int relative_count){
	for(int i = strlen(base) - 2; i >= 0; i--){
		if(relative_count == 0) break;
		if(base[i] == '/'){
			base[i + 1] = 0;
			relative_count--;
		}
	}
}


//Resolve URL that include relative file symbols.
//These are symbols that include './' and '../'
//Both the base and url pointers and values are changed
void resolveRelative(char * final_url, char * url){
	int relative_count = countRelative(url);
	cleanRelative(url);
	removeParents(final_url, relative_count);
	joinURL(final_url,url);
}

//Resolve URL concatenation
int main(int argc, char * argv[]){
    if(argc != 3){
        cout << "USAGE: ./URLResolver <base-url> <relative-url>" << endl;
        return 0;
    }
    
    //Set up original url variables
	char * url = argv[2];
	char * base_url = argv[1];
	char final_url[2048];
	memset(final_url,0,2048);

    //Perform actions on url variables
    switch(url[0]){
        case '/':
			if(base_url[0]=='f'){
				strcpy(final_url,"file:///");
				resolveRoot(final_url, url);
			}
			else{
				getBaseURL(base_url, final_url);
	            resolveRoot(final_url, url);
			}
            break;
        case '#':
			strcpy(final_url,base_url);
            strcat(final_url, url);
            break;
        default:
			if(!strcmp(base_url,"file:///") || !strcmp(base_url,"file://")){
				strcpy(final_url,"file:///");
				resolveRelative(final_url, url);
			}
			else{
				getBaseURL(base_url, final_url);
				resolveRelative(final_url, url);
			}
            break;
    }
    
    //Print out result
	cout << final_url << endl;
    return 0;

}
