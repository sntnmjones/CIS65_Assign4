#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "FileIn.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

struct Book
{
	std::string title;
	std::string author;
	std::string subject;
	char* time;
	std::string action;
};

class DB : public FileIn
{
public:
	//////////
	// vars //
	//////////
	int logIter;
	std::ifstream bookDB;
	Book* unsortedList;
	Book* log;
	Book* sortedByTitle;
	Book* sortedByAuthor;
	Book* sortedBySubject;

	unsigned int unsortedArrayLength;
	///////////////
	// functions //
	///////////////
	DB();
	/*******************************************************************************
	* Function Name:isMemFull()
	* Parameters: none
	* Return Value: bool
	* Purpose: checks to see if memory is full
	*******************************************************************************/
	bool isMemFull();

	/*******************************************************************************
	* Function Name: insertBook
	* Parameters: Book*
	* Return Value: void
	* Purpose: inserts user input book into unsortedList array
	*******************************************************************************/
	void insertBook(Book*);

	/*******************************************************************************
	* Function Name: deleteBook()
	* Parameters: Book*, string, int
	* Return Value: void
	* Purpose: deletes book from unsortedList array that user chooses
	*******************************************************************************/
	void deleteBook(Book*, std::string, int);

	/*******************************************************************************
	* Function Name: loadDBs()
	* Parameters: none
	* Return Value: void
	* Purpose: loads books.txt into buffer into unsortedList
	*******************************************************************************/
	void loadDBs();
	~DB();

private:
	///////////////
	// variables //
	///////////////
	int mid;

	///////////////
	// functions //
	///////////////
	/*******************************************************************************
	* Function Name: printToLog()
	* Parameters: Book*
	* Return Value: void
	* Purpose: prints passed in tempBook to be printed to log.txt
	*******************************************************************************/
	void printToLog(Book*);

	/*******************************************************************************
	* Function Name: createNodes()
	* Parameters: char*, int
	* Return Value: void
	* Purpose: fills unsortedList
	*******************************************************************************/
	void createNodes(const char*, int);
};