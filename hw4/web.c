// -----------------------------------
// CSCI 340 - Operating Systems
// Fall 2018
// web.c header file
// 
// Homework 4
//
// -----------------------------------

#include <string.h>
#include <stdio.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "web.h"

#define _GNU_SOURCE

// global variable used by the write_callback function
size_t length = 0;


// ------------------------------------
// Function prototype that is used by the curl library to
// retrieve the webpage (in the response message) and 
// store in the web_t webpage field.
// 
//
// Arguments:	web_t pointer
//
// Return:     	OK on success, FAIL on error
//

size_t write_callback(void *ptr, size_t size, size_t nmemb, char** buffer ) {

	// -------------------------------------
	// Please do not modify this code
	// -------------------------------------

	*buffer = (char*)realloc( *buffer, ( length + size*nmemb )*sizeof( char* ) ); 

	strcat( *buffer, (char*) ptr );

	length += (size*nmemb);

	return size * nmemb;

} // end write_callback function

// ------------------------------------
// Function prototype that connects to the web address 
// specified in the web_t url field and retrieves
// the html webpage (using the curl c-library)
// 
//
// Arguments:	web_t pointer
//
// Return:     	OK on success, FAIL on error
//

int get_webpage( web_t* web_struct ) {

	// -------------------------------------
	// Please do not modify this code
	// -------------------------------------

	CURL *curl;
  	CURLcode error_code = FAIL;

	length = 0;

  	curl = curl_easy_init();

  	if ( curl ) {

	    	web_struct->webpage = malloc( sizeof( char ) * length );

	    	curl_easy_setopt(curl, CURLOPT_URL, web_struct->url );
	    	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	    	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
	    	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &web_struct->webpage );
	 
	    	error_code = curl_easy_perform( curl );

		curl_easy_cleanup( curl );

	}
    
	return ( error_code == OK ) ? OK : FAIL;

} // end get_response function



// ------------------------------------
// Function prototype that parses webpage/URL 
// pointed at by client socket
// 
//
// Arguments:	web_t pointer
//
// Return:     	OK on success, FAIL on error
//
void parse( web_t* web_struct ) {

	
	// -----------------------------------------
	// TODO:
	// -----------------------------------------
	//
	// Parse the webpage field in the web_t stuct
	// looking for each href attribute value that
	// has the word "trump" (not case-sensitive)
	// in the string.
	//
	// An example (from the usatoday website)
	// href="/story/news/politics/2018/10/23/donald-trump-looks-ahead-life-after-midterms/1732675002/"
	// 
	// If the word "trump" is in the href string, then
	// the entire href string value is added to the links 
	// array and the link_cnt field (also in the web_t struct)
	// is incremented by one.
	// 
	// Pseudocode example,
	// links[ link_cnt++ ]="/story/news/politics/2018/10/23/donald-trump-looks-ahead-life-after-midterms/1732675002/"
	//
	// Note: you will need to malloc the links array

	
	char* p_href = web_struct[0].webpage; // pointer to webpage to search for hrefs
	char temp_href[7];
	char* p_trump; // pointer to link to search for trump
	char temp_trump[6];

	char hrefStr[] = "href=\""; 
    char trumpStr[] = "trump";

	

	pthread_mutex_t lock;

	web_struct[0].links = malloc(sizeof(char*)*1024);
	for ( int i=0; i<1024; i++ ) web_struct[0].links[i] = malloc(sizeof(char)*4000);
	
    while( *(p_href + 7) != '\0') { // SEARCH "href"
		
		strncpy(temp_href, p_href, 6);  
		
		if(strstr(temp_href, hrefStr) != NULL){ // FOUND href
			//char link_content[4000];
			char* link_content = malloc(2000);
			char* link_start;
			char* link_end;
			int link_len;

			link_start = p_href + 6; //offset by 6 for href="
			link_end = strstr( link_start, "\"" );
			link_len = link_end - link_start;

			strncpy(link_content, link_start, link_len);
			
			if(strcasestr(link_content, trumpStr) != NULL){ // SEARCH "trump"
				//printf("%s\n\n", link_content);
				web_struct->links[web_struct->link_cnt] = link_content;
				web_struct->link_cnt = 1 + web_struct->link_cnt;
			}

		}		

		p_href++;
    }

	if ( WEB_DEBUG ) {
		//printf("WeeURL=%s\n", web_struct->url ); 
		//printf("CNT=%d\n", web_struct->link_cnt );
		//printf("WEBPAGE=%s\n", web_struct->webpage );
	}

} // end parse function
