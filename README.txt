Description: C application that curls weather data from a NOAA station and prints it to standart output.

Author: Chris Livingston

This file explains special notes and assumptions made about relevant files and inputs.


To run: 

	weather [NOAA code]

Ex:

	weather KLEB



Compilation and Execution: 

weather.c must be compiled with the file "mycurl.c" and the -lcurl option.

This program needs a valid 4 letter station code to retrieve information from the NOAA website. 

The arguments should be given like so: weather [CODE]

There must be one and only one code and it must be a valid 4 capital letter station code. 


Assumptions:
n/a
