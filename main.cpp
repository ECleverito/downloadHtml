#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <limits>
#include <fstream>
#include <string>
#include <curl/curl.h>

using namespace std;

//size_t writeCbk(char *ptr, size_t size, size_t nmemb, void *userdata);
size_t writeCbk(char *ptr, size_t size, size_t nmemb, void *userdata){
	
	//Initialize html chunk number statically then iterate
	static int fileCount = 0;
	
	//Create output file object and its name
	ofstream htmlFile();
	string fileNameComplete = "part"+ to_string(++fileCount) + ".txt";
		
	//Open each chunk of file for writing
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
	
	//String for holding URL
	string URL;
	
	//Initialize properly
	curl_global_init(CURL_GLOBAL_ALL);
	myCUrl = curl_easy_init();

	//User greeting and URL query
	cout << "Enter the URL of the website you would like the .html file from: ";
	
	getline(cin,URL);
	
	cout << "URL you entered:" << URL << " (URL)\n";

	//Below is custom function for performing .html file generating directly from a URL string
	//url2html(myCUrl, URL);
	
	//Trying directly with c-string here
	curl_easy_setopt(myCUrl,CURLOPT_URL,URL.c_str());
	curl_easy_setopt(myCUrl,CURLOPT_WRITEFUNCTION,writeCbk);
	
	curl_easy_perform(myCUrl);
	
	curl_easy_cleanup(myCUrl);
	
	return 0;
}
