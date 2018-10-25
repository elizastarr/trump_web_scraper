
#include <stdio.h>	// IO functions
#include <stdlib.h> 	// std lib function
#include <unistd.h>	// close function
#include <pthread.h>	// creating, running, joining threads
#include <string.h>	// string processing 
#include "web.h"	// our code :)

#define DEBUG 1 



// -----------------------------------
// CSCI 340 - Operating Systems
// Fall 2018
// hw4.c file
// 
// Homework 4
//
// -----------------------------------

// ---------------------------------------------
// Global variable shared by all threads
// This is not thread safe.
web_t* web_array;


// ---------------------------------------------
// Function prototypes to read and write url files
int read_url_file( char* file_path, web_t* web_array );
int write_url_file( char* file_path, web_t* web_array, int num_urls );

// ---------------------------------------------
// Function prototypes that is ran by a thread
void th_run( int* i );

int main( int argc, char *argv[] ) {

	int i = 0;
	int write_error = 0;

	// malloc web_t array with 100 elements
	web_array = malloc( sizeof( web_t )*100 );

	// -------------------------------------------------
	// Verify the correct number of arguments are provided
	// when the application is executed.

	if ( argc == 2 ) { 

		int num_urls = read_url_file( argv[1], web_array );

		if ( DEBUG ) printf("Number of urls in text file = %d\n", num_urls);

		// -----------------------------------------
		// TODO:
		// ------------------------------------------
		// You complete steps 1 to 3 below.
		//
		// If either the thread create or join fails, you may exit the entire
		// program.
		// 
		// Hint: you will loop through an array of threads

		pthread_t thread_array[num_urls];
		int index[num_urls];

		for ( i=0; i<num_urls; i++ ) {

			if ( DEBUG ) {
				printf("URL=%s\n", web_array[i].url ); 
				printf("CNT=%d\n", web_array[i].link_cnt );
				printf("WEBPAGE=%s\n", web_array[i].webpage );
			}
	
			index[i] = i;

			// -------------------------------------------------------------
			// STEP 1: Create and run threads
			// Hint: Each thread will execute the th_run function
			// 	 The array index value is a shared variable
			//
			// If one thread cannot be created (i.e. an error occurs) you may exit
			// the entire program.

			



			
		}

		// -------------------------------------------------------------
		// STEP 2: Join all threads
		//
		// If one thread cannot be joined (i.e. an error occurs) you may exit
		// the entire program.

		

		// -------------------------------------------------------------
		// STEP 3: write results to output file 
		// Note: please do not change this file name (used for testing purposes)
		// output file name = "make_merica_great_again.txt"
		
		
		

	} else {

		printf( "URL file is not specified!\n" );
		printf( "Example usage: %s %s\n", argv[0], "url.txt" );

	}

	return OK;
     
} // end main function

// ------------------------------------
// Function ran by an individual thread
// 
//
// Arguments:	i = an index value (to access individual web_t structs in the web_array)
//
// Return:     	nothing (void)
//
void th_run( int* i ) {

	// -------------------------------------
	// Please do not modify this code
	// -------------------------------------

	if ( web_array[ (*i) ].link_cnt == OK ) {

		parse( &web_array[ (*i) ] );

	} else printf( "[%s] failed to retrieve webpage\n", web_array[ (*i) ].url );

	pthread_exit( NULL );

} // end th_run function

// ------------------------------------
// Function that writes the identified links 
// stored in the web_t links field to formated
// text file.
// 
// 
//
// Arguments:	file_path = fully qualified path to output text file
//		web_array = pointer to array of web_t structs
//		num_urls = the total number of websites in the url.txt file
//
// Return:     	OK on success, FAIL on error
//
int write_url_file( char* file_path, web_t* web_array, int num_urls ) {

	// -----------------------------------------
	// TODO:
	// -----------------------------------------
	// The format of this file is provided below. 
	// 
	// <url>, <link>\n
	//
	//
	// For example,
	//
	//	usatoday.com, /story/news/politics/2018/10/23/donald-trump-looks-ahead-life-after-midterms/1732675002/
	//	wsj.com, /articles/trump-not-satisfied-with-saudi-arabias-explanation-for-khashoggi-death-1540237930?mod=hp_major_pos8
	//      .
	//	.
	//      .
	//

	

	return OK;

} // end write_url_file function



// ------------------------------------
// Function that reads the url in the input
// url text file.
// 
// 
// Arguments:	file_path = fully qualified path to output text file
//		web_array = pointer to array of web_t structs
//
// Return:     	Total number of urls defined in the url text file
//
int read_url_file( char* file_path, web_t* web_array ) {

	// -------------------------------------
	// Please do not modify this code
	// -------------------------------------

	int url_cnt = 0;

	FILE* fhnd;

    	fhnd = fopen( file_path, "r" );

    	char line[50];

    	if ( fhnd != NULL ) {

        	while ( fgets( line, sizeof( line ), fhnd ) != NULL ) {

			line[strlen(line)-1] = '\0';
			web_array[url_cnt].url = malloc(sizeof(char)*100);
			sprintf( web_array[url_cnt].url, "www.%s", line );

			web_array[url_cnt].link_cnt = OK;

			if ( FAIL == get_webpage( &web_array[url_cnt++] ) ) {

				printf("Failed to load webpage for URL( %s )\n", web_array[url_cnt--].url );
				web_array[url_cnt].link_cnt = FAIL;				

			}

        	}

    	} else url_cnt = FAIL;

    	fclose( fhnd );

	return url_cnt;

} // end read_url_file function

