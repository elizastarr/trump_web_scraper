// -----------------------------------
// CSCI 340 - Operating Systems
// Fall 2018
// web.h header file
// 
// Homework 4
//
// -----------------------------------

#define OK 0
#define FAIL -1
#define UNK -1
#define WEB_DEBUG 1

typedef struct {

	char* url; 	// string that has the url 
	char* webpage; // string that has the html web page
	int link_cnt;	// integer that represents the total number of href link counts
	char** links; 	// array that stores a string for each href that contains the word "trump"
} web_t;




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

size_t write_callback(void *ptr, size_t size, size_t nmemb, char** buffer );

// ------------------------------------
// Function prototype that creates a network 
// socket and then connects to the web address 
// specified in the web_t url field and retrieves
// the html webpage.
// 
//
// Arguments:	web_t pointer
//
// Return:     	OK on success, FAIL on error
//

int get_webpage( web_t* web_struct );


// ------------------------------------
// Function prototype that parses response
// that identifies the html anchor tag links
// that have the word "trump" (not case-sensitive)
// in the href attribute.
// 
// e.g. <a href="http://www.fake.com/trump_and_our_nation.html">
// 
//
// Arguments:	web_t pointer
//
// Return:     	void (nothing)
//

void parse( web_t* web_struct );
