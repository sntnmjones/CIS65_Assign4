#pragma once
#include <iostream>
#include <fstream>

class FileIn
{
public:
	///////////////
	// Variables //
	///////////////
	char* buffer; // stores chars from file
	int inFileBufferLength; // number of chars in *buffer
	int bookCount; // number of books stored in books.txt

	///////////////
	// Functions //
	///////////////
	FileIn();
	/*******************************************************************************
	* Function Name: fileInStuff
	* Parameters: none
	* Return Value: void
	* Purpose: A public variable for the object created in main() to access private
				functions.
	*******************************************************************************/
	void fileInStuff();

	/*******************************************************************************
	* Function Name: getBookCount()
	* Parameters: char*, int
	* Return Value: void
	* Purpose: fills variable bookCount with amount of books in unsortedList
	*******************************************************************************/
	void getBookCount(const char*, const int);
	~FileIn();

private:
	///////////////
	// Variables //
	///////////////
	std::ifstream inFile;

	///////////////
	// Functions //
	///////////////
	/*******************************************************************************
	* Function Name: fileOpen
	* Parameters: none
	* Return Value: void
	* Purpose: Opens file "books.txt"
	*******************************************************************************/
	void fileOpen();


	/*******************************************************************************
	* Function Name: fillBuffer
	* Parameters: std::ifstream&
	* Return Value: void
	* Purpose: Reads the input file and fills an char array
	*******************************************************************************/
	void fillBuffer(std::ifstream&);

	/*******************************************************************************
	* Function Name: getBufferLength
	* Parameters: std::ifstream&
	* Return Value: int
	* Purpose: Returns the number of chars in input file array
	*******************************************************************************/
	int getBufferLength(std::ifstream&);
};