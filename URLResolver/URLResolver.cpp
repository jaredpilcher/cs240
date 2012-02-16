#include <iostream>
#include <string.h>
using namespace std;

//Removes the file name from the base string that is passed in through the shell.
char * getBaseString(char * base_url){
    int slash_location = 0;
    for(int i = 0; base_url[i] != 0; i++){
        if(base_url[i]=='/'){
            slash_location = i;
        }
    }
	int base_length = strlen(base_url);
	if(base_url[base_length-4] != '.'){
	    base_url[slash_location + 1] = 0; 
	}
    return base_url;
}

//Smartly concatenates two URL c-strings.
//If the base does not end in a slash, a slash is appended.
//If the url starts with a slash, it is removed
//Both the base and url pointers and values are changed
char * joinURL(char * base, char * url){
	int base_length = strlen(base);
	if(base[base_length-1]!='/' && url[0]!='/' && &base[base_length+1] == url){
		base[base_length] = '/';
		return base;
	} 
	if((base[base_length-1]!='/' && url[0]=='/') || (base[base_length-1]=='/' && url[0]!='/')){
		strncat(base,url,strlen(url));
		return base;
	}
	if(url[0]=='/'){
		strncat(base,url+1,strlen(url));
	}
	else{
			strcat(base, "/");
			strncat(base,url,strlen(url));
	}
	return base;
}

//Collects only the top portion of the URL for resolveRoot function
//Changes the base pointer and value
char * getWebBase(char * base){
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
    return base;
}

//Resolve URLs that start with '/' symbols.
//Both the base and url pointers and values are changed
char * resolveRoot(char * base, char * url){
    if(base[0] == 'h'){
        base = getWebBase(base);
        url = joinURL(base, url);
    }
    else{
		url = joinURL(base,url);
    }
	
    return url;
}

//Resolve URLs that include internal links with # symbols
//Both the base and url pointers and values are changed
char * resolveInternal(char * base, char * url){
	strncat(base, url, strlen(url));
    return base;
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
char * cleanRelative(char * url){
	for(int i = 0; url[i+1] != 0; i++){
		if(url[i] >= 'A'){
			url = &url[i];
			break;
		}
	}
	return url;
}

//Go through the base and remove the number of parents specified by relative_count
//Return the base c-string
char * removeParents(char * base, int relative_count){
	for(int i = strlen(base) - 2; i >= 0; i--){
		if(relative_count == 0) break;
		if(base[i] == '/'){
			base[i + 1] = 0;
			relative_count--;
		}
	}
	return base;
}

//Count the number of parents that the base url contains. Return result
int countParents(char * base){
	int parent_count = 0;
	for(int i = strlen(base) - 3; i> 0; i--){
		if(base[i] == '/'){
			if(base[0]=='h'){
				if(base[i-1] == '/' || base[i+1] == '/') break;
			}
			parent_count++;
			if(base[0]=='f'){
				if(base[i-1] == '/' || base[i+1] == '/') break;
			}
			
		}
	}	
	return parent_count;
}

char * resolveFileBase(char * base){
	
}

//Resolve URL that include relative file symbols.
//These are symbols that include './' and '../'
//Both the base and url pointers and values are changed
char * resolveRelative(char * base, char * url){
	int relative_count = countRelative(url);
	int parent_count = countParents(base);
	if(parent_count < relative_count){
		relative_count = parent_count;
	}
	url = cleanRelative(url);
	base = removeParents(base, relative_count);
	base = joinURL(base,url);
    return base;
}

//Resolve URL concatenation
int main(int argc, char * argv[]){
    if(argc != 3){
        cout << "USAGE: ./URLResolver <base-url> <relative-url>" << endl;
        return 0;
    }
    
    //Set up original url variables
	char * base_url = 0;
	char base_url_file[9] = "file:///";
	char * url = argv[2];
	if(url[0] != '#'){
		base_url = getBaseString(argv[1]);
	}
	else{
		base_url = argv[1];
	}
    //Perform actions on url variables
    switch(url[0]){
        case '/':
			if(base_url[0]=='f'){
				url = resolveRoot(base_url_file, url);
			}
			else{
	            url = resolveRoot(base_url, url);
			}
            break;
        case '#':
            url = resolveInternal(base_url, url);
            break;
        default:
			if(countParents(base_url)==0 && base_url[0]=='f'){
				url = resolveRelative(base_url_file, url);
			}
			else{
				url = resolveRelative(base_url, url);
			}
            break;
    }
    
    //Print out result
	cout << url << endl;
    return 0;

}
