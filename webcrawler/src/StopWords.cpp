/*
 * StopWords.cpp
 *
 *  Created on: March 4, 2012
 *      Author: jared
 */

//Default Constructor
StopWords():count(0){

}

//Default Deconstructor
~StopWords(){
}

//Retrieves all of the words from the stop_words file
//Places words into the stop_words array
//@par stop_file - file url of the stop words file
void getWords(string stop_file){
	fstream file(stop_file);
	char temp[MAX_CHAR_IN_LINE];
	while(1){
		file.getline(temp,MAX_CHAR_IN_LINE);
		if(!file) break;
		stop_words[count]=temp;
		count++;
	}
	file.close();
}

//Determines if the given word is a stop word
//@par word - word to be found
bool isStopWord(string word){

}
