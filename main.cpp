#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <limits>
#include <fstream>
#include <curl/curl.h>

using namespace std;

void incrementingString(char*);

//size_t writeCbk(char *ptr, size_t size, size_t nmemb, void *userdata);
size_t writeCbk(char *ptr, size_t size, size_t nmemb, void *userdata){
	
	ofstream htmlFile;
	string fileNameComplete = "part";
	
	char fileName[2];
	incrementingString(fileName);
	
	fileNameComplete+=fileName;
	fileNameComplete+=".txt";
		
	htmlFile.open(fileNameComplete);
	
	for(long long c = 0;c<(nmemb*size);c++){
		htmlFile << ptr[c];
			
	}
	
	htmlFile.close(); 
	
	return nmemb*size;
}


//Takes a url and creates a corresponding .html file in the same directory
void url2html(CURL* myCUrl, string url){
	
	curl_easy_setopt(myCUrl,CURLOPT_URL,url.c_str());
	curl_easy_setopt(myCUrl,CURLOPT_WRITEFUNCTION,writeCbk);
	
	curl_easy_perform(myCUrl);
	
	curl_easy_cleanup(myCUrl);
	
}

int main(){

	//Create a curl object
	CURL* myCUrl;
	
	char urlAdd[256];
	string URL; //Holds actual URL from user and is always equal to getline target
	
	//Initialize properly
	curl_global_init(CURL_GLOBAL_ALL);
	myCUrl = curl_easy_init();

	//User greeting and URL query
	cout << "Enter the URL of the website you would like the .html file from: ";
	
	cin.getline(urlAdd,numeric_limits<streamsize>::max());
	
	cout << "URL you entered:" << urlAdd << " (urlAdd)\n";
	URL = urlAdd;

	//Below is custom function for performing .html file generating directly from a URL string
	//url2html(myCUrl, URL);
	
	//Trying directly with c-string here
	curl_easy_setopt(myCUrl,CURLOPT_URL,urlAdd);
	curl_easy_setopt(myCUrl,CURLOPT_WRITEFUNCTION,writeCbk);
	
	curl_easy_perform(myCUrl);
	
	curl_easy_cleanup(myCUrl);
	
	return 0;
}

void incrementingString(char* string){
	
	//Must start at 48. Performs conversion of value, not of character
	static int fileCount = 48;
	
	char fileCountChar;
	fileCountChar = static_cast<char>(fileCount);
	
	string[0] = fileCountChar;
	string[1] = '\0';
	
	fileCount++;
}