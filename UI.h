#pragma once
#include "DB.h"

class UI : public DB
{
public:
	///////////////
	// Variables //
	///////////////
	int userCommands();

	///////////////
	// Functions //
	///////////////
	UI();

	/*******************************************************************************
	* Function Name: saveDB()
	* Parameters: None
	* Return Value: void
	* Purpose: To let Driver.cpp interface with child classes
	*******************************************************************************/
	void saveDB();

	/*******************************************************************************
	* Function Name: deleteMagic();
	* Parameters: string, string, string
	* Return Value: void
	* Purpose: a container function for functions pertaining to deletion of books
	*******************************************************************************/
	void deleteMagic(const std::string, const std::string, const std::string);

	/*******************************************************************************
	* Function Name: insertMagic()
	* Parameters: string, string, string
	* Return Value: void
	* Purpose: a container function for functions pertaining to the insertion of books
	*******************************************************************************/
	void insertMagic(const std::string, const std::string, const std::string);

	/*******************************************************************************
	* Function Name: sortMagic()
	* Parameters: string
	* Return Value: void
	* Purpose: a container function for functions that deal with the sorting of lists
	*******************************************************************************/
	void sortMagic(const std::string);

private:
	///////////////
	// Variables //
	///////////////
	int midPoint;
	std::ofstream outFile;
	bool bookAdded;
	bool inInventory;
	bool memoryFull;

	///////////////
	// Functions //
	///////////////
	/*******************************************************************************
	* Function Name: BinarySearch()
	* Parameters: Book*, string, int, int
	* Return Value: bool
	* Purpose: searches through Book* until string is found.
	*******************************************************************************/
	bool BinarySearch(Book*, std::string, int, int);

	/*******************************************************************************
	* Function Name: printToFile()
	* Parameters: string, int
	* Return Value: void
	* Purpose: prints to txt file name passed as string
	*******************************************************************************/
	void printToFile(std::string, int);

	/*******************************************************************************
	* Function Name: printToLog()
	* Parameters: string, Book*, int
	* Return Value: void
	* Purpose: prints log to txt file passed in as string
	*******************************************************************************/
	void printToLog(std::string, Book*, int);

	/*******************************************************************************
	* Function Name: findStuff()
	* Parameters: string
	* Return Value: int
	* Purpose: searches through array linear until string matches, then returns index
	*******************************************************************************/
	int findStuff(std::string);
};