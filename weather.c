/*
* File: weather.c
* 
* Description: A program that will request a weather report from NOAA's weather.gov site 
* or a specified location and print some portions of the response.
* 
* Input: a 4 letter (minimum) weather station location code to use to request from the NOAA.
* 
* Output: Weather report of corresponding location
*
* Note: Compile with -lcurl
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "mycurl.h"

int main(int argc, char **argv) {

  int totalUrlLength; // length of URL with the 4 letter station code
  char stationCode[4]; // location code
 
  /* curl stuff */
  CURL *curl;
  CURLcode res;
  struct string page;

  /* Here is the format string for the URL we will request */
  char *baseURL  = "http://w1.weather.gov/xml/current_obs/%s.xml";

  // Get length of URL + 4 characters for the station code                                              
  totalUrlLength = strlen(baseURL) + 4;

  // Create a new string to store the total url                                                                
  char totalUrl[totalUrlLength];

  if ( argc < 2 )
  {
    fprintf(stderr,"Error: Need a NOAA 4 capital letter code.");
    exit(EXIT_FAILURE);
  }
  /* check if exactly one argument inputed */
  else if ( argc == 2) 
  {
    //Check to see if argument length equals 4, the required code length
    if( ! (strlen(argv[1]) == 4) )
		{
	     fprintf(stderr,"Error: Input format should be a NOAA 4 capital letter code.");
	     exit(EXIT_FAILURE);
	  }
    else
    {
	       strcpy(stationCode, argv[1]);
		}	
  } 
  else
  {
    fprintf(stderr,"Error: Please enter only one argument.\n");
    exit(EXIT_FAILURE);
  }

  /* allocate and intiialize the output area */
  init_string(&page);

  /* create the URL from the format string */
  sprintf(totalUrl, baseURL, stationCode);

  /* initialize curl */
  curl = curl_easy_init();
 
  if ( curl ) {
     
     /* set the URL we want to visit */
     curl_easy_setopt(curl, CURLOPT_URL, totalUrl );
    
     /* set the function curl should call with the result */
     curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
    
     /* set the buffer into which curl should place the data */
     curl_easy_setopt(curl, CURLOPT_WRITEDATA, &page);

     /* Perform the request, res will get the return code */
     res = curl_easy_perform(curl);

    // check if curl was successful
    if ( ! (res == CURLE_OK) )
    {
	    fprintf(stderr, "Error: Unable to find URL with corresponding station code");
	    exit(EXIT_FAILURE);
    }
    
    /* check: if the weather station code wasn't found, we get back HTML instead of XML  */
    if ( ! (strncmp(page.ptr, "<?xml", 5) == 0) ) 
    {
	     fprintf(stderr, "ERROR: Reporting station unavailable at this time");
	     exit(EXIT_FAILURE);
    }

     /* otherwise, select the desired output from the results */
    
    else
    {

      char* end; // char pointer to remember location of end of a section 

      printf(" \n");

      // Place pointer at beginning of desired section
	    page.ptr = strstr(page.ptr, "<credit>");
	    // Store pointer to last character in this section
	    end = strstr(page.ptr, "</credit>");
	    // Move pointer back to the beginning of the section
	    page.ptr = page.ptr + strlen("<credit>");
	    // Print Label
	    printf("Credit: ");
	    // Print the string char by char
	    while ( page.ptr < end ) 
	    {
	      printf("%c", *page.ptr);
	      page.ptr++; // next char
	    }
	    printf("\n");

	    // Place pointer at beginning of desired section                                  
      page.ptr = strstr(page.ptr, "<location>");
	    // Store pointer to last character in this section                              
	    end = strstr(page.ptr, "</location>");
	    // Move pointer back to the beginning of the section                                         
      page.ptr = page.ptr + strlen("<location>");
      // Print Label                                                                                    
      printf("Location: ");
	    // Print the string char by char                            
      while ( page.ptr < end )
      {
        printf("%c", *page.ptr);
        page.ptr++;
	    }
	    printf("\n");

      // Place pointer at beginning of desired section                                  
      page.ptr = strstr(page.ptr, "<station_id>");
      // Store pointer to last character in this section                             
      end = strstr(page.ptr, "</station_id>");
      // Move pointer back to the beginning of the section                                      
      page.ptr = page.ptr + strlen("<station_id>");
      // Print Label                                                                                    
      printf("Station ID: ");
      // Print the string char by char                            
      while ( page.ptr < end )
      {
        printf("%c", *page.ptr);
        page.ptr++;
      }
      printf("\n");

      // Place pointer at beginning of desired section                                  
      page.ptr = strstr(page.ptr, "<observation_time>");
      // Store pointer to last character in this section                             
      end = strstr(page.ptr, "</observation_time>");
      // Move pointer back to the beginning of the section                                         
      page.ptr = page.ptr + strlen("<observation_time>");
      // Print Label                                                                                    
      printf("Last Observation: ");
      // Print the string char by char                             
      while ( page.ptr < end )
      {
        printf("%c", *page.ptr);
        page.ptr++;
      }
      printf("\n");

	    // Place pointer at beginning of desired section                                   
      page.ptr = strstr(page.ptr, "<weather>");
      // Store pointer to last character in this sectionr                              
      end = strstr(page.ptr, "</weather>");
      // Move pointer back to the beginning of the section                                         
      page.ptr = page.ptr + strlen("<weather>");
      // Print Label                                                                                    
      printf("Weather: ");
      // Print the string char by char                             
      while ( page.ptr < end )
      {
        printf("%c", *page.ptr);
        page.ptr++;
      }
      printf("\n");

      // Place pointer at beginning of desired section                                  
      page.ptr = strstr(page.ptr, "<temperature_string>");
      // Store pointer to last character in this section                              
      end = strstr(page.ptr, "</temperature_string>");
      // Move pointer back to the beginning of the section                                        
      page.ptr = page.ptr + strlen("<temperature_string>");
      // Print Label                                                                                    
      printf("Temperature: ");
      // Print the string char by char                             
      while ( page.ptr < end )
      {
        printf("%c", *page.ptr);
        page.ptr++;
      }
      printf("\n");
      
      // Place pointer at beginning of desired section                                   
      page.ptr = strstr(page.ptr, "<relative_humidity>");
      // Store pointer to last character in this section                            
      end = strstr(page.ptr, "</relative_humidity>");
      // Move pointer back to the beginning of the sectionr                                         
      page.ptr = page.ptr + strlen("<relative_humidity>");
      // Print Label                                                                                    
      printf("Relative Humidity: ");
      // Print the string char by char                             
      while ( page.ptr < end )
      {
        printf("%c", *page.ptr);
        page.ptr++;
      }
      printf("\n");

      // Place pointer at beginning of desired section                                   
      page.ptr = strstr(page.ptr, "<wind_string>");
      // Store pointer to last character in this section                            
      end = strstr(page.ptr, "</wind_string>");
      // Move pointer back to the beginning of the section                                        
      page.ptr = page.ptr + strlen("<wind_string>");
      // Print Label                                                                                    
      printf("Weather: ");
      // Print the string char by char                             
      while ( page.ptr < end )
      {
        printf("%c", *page.ptr);
        page.ptr++;
      }
      printf("\n");

      // Place pointer at beginning of desired section                                  
      page.ptr = strstr(page.ptr, "<visibility_mi>");
      // Store pointer to last character in this section                              
      end = strstr(page.ptr, "</visibility_mi>");
      // Move pointer back to the beginning of the section                                      
      page.ptr = page.ptr + strlen("<visibility_mi>");
      // Print Label                                                                                    
      printf("Miles of Visibility: ");
      // Print the string char by char                            
      while ( page.ptr < end )
      {
        printf("%c", *page.ptr);
        page.ptr++;
      }
      printf("\n");

    }
  /* always cleanup */
  curl_easy_cleanup(curl);
  
  }

  return(0);

}