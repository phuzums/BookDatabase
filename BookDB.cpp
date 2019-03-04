#include <iostream>
#include <iomanip>
#include "BookDB.h"

/////////////////////////////////////////////////////////////////////////
//Pre:  None
//Post: Initializes a BookDB object and its variables
BookDB::BookDB(std::string filename, std::string sFilename)
{
	DBFilename			= filename;
	salesFilename		= sFilename;
	numBooks			= 0;
	totalWholesaleValue = 0;
	totalRetailValue	= 0;
	currentNetProfit	= 0;
	currentSalesAmount	= 0;

	books = new Book[MAX_BOOKS];
	readBooks(DBFilename);
	readSalesData(salesFilename);
}

/////////////////////////////////////////////////////////////////////////
//Pre:  BookDB Exists
//Post: stuff gets deleted and whatnot
BookDB::~BookDB()
{
	std::cout << "\nWritting Database to file " << DBFilename << "... ";
	if (writeBooks(DBFilename))
		std::cout << "Success!\n";
	else
		std::cout << "Error writting to file...\n";

	std::cout << "\nWritting Sales data to file " << salesFilename << "... ";
	if (writeSalesData(salesFilename))
		std::cout << "Success!\n";
	else
		std::cout << "Error writting to file...\n";

	if (books)
		delete[] books;
}



// ============Getters==============

/////////////////////////////////////////////////////////////////////////
//Pre:  books has been filled with at least 1 book?
//Post: pointer to books array is returned
Book* BookDB::getBooks()
{
	return books;
}

/////////////////////////////////////////////////////////////////////////
//Pre:  
//Post: 
Book BookDB::getBook(int index)
{
	if(index >= 0)
		return books[index];
	else
	{
		Book bk = { 0, 0, 0, "err", "err", "err", {0,0,0},0 };
	}
}

/////////////////////////////////////////////////////////////////////////
//Pre:  books has been initialized
//Post: books array is traversed to find how many book entries there are
//          number of books is returned as an int
int BookDB::getNumBooks()
{
	// figure out how many books via iteratting
	return numBooks;
}

/////////////////////////////////////////////////////////////////////////
//Pre:  books has been initialized
//Post: returns the wholesale value of all the books combined
double BookDB::getWholesaleValue()
{
	return totalWholesaleValue;
}

/////////////////////////////////////////////////////////////////////////
//Pre:  books has been initialized
//Post: 
double BookDB::getRetailValue()
{
	return totalRetailValue;
}

/////////////////////////////////////////////////////////////////////////
//Pre:  books has been initialized
//Post: returns the wholesale value of all the books combined
int BookDB::findBook(unsigned long ISBN)
{
	if (numBooks > 0)
		for (int idx = 0; idx < numBooks; idx++)
			if (books[idx].ISBN == ISBN)
				return idx;
	return -1;
}

/////////////////////////////////////////////////////////////////////////
//Pre:  books has been initialized
//Post: 
int BookDB::findBook(std::string title)
{
	if (numBooks > 0)
		for (int idx = 0; idx < numBooks; idx++)
			if (books[idx].title == title)
				return idx;
	return -1;
}

// ============Mutators==============
/////////////////////////////////////////////////////////////////////////
//Pre:  Filename is valid and bk is initialized to hold at least
//      MAX_BOOKS
//Post: bk is filled with books from the file <filename>.
//      WholesaleValue and retailValue are updated as the books
//      are moved into the books array
bool BookDB::readBooks(std::string filename)
{
	numBooks = 0;
	totalRetailValue = totalWholesaleValue = 0;

	DBFile.open(DBFilename);

	if (!DBFile)
		return false;

	int temp = 0;
	do
	{
		std::string tstr;

		DBFile >> books[numBooks].ISBN;
		char tc = ' ';
		DBFile >> tc; //Dummy char to read the seperator between isbn & books (used in case a book title starts with a number)


		// Search for an existing entry
		temp = findBook(books[numBooks].ISBN);

		// increase quantity if a match was found
		if (temp > 0)
		{
			int tempint;
			double tempdbl;
			std::getline(DBFile, tstr, '}');
			std::getline(DBFile, tstr, '}');
			std::getline(DBFile, tstr, '}');
			DBFile >> tempint; //day
			DBFile >> tempint; //month
			DBFile >> tempint; //year
			DBFile >> tempint;
			books[temp].quantity += tempint;
			DBFile >> tempdbl;
			totalRetailValue += tempdbl * (double)tempint;
			DBFile >> tempdbl;
			totalWholesaleValue += tempdbl * (double)tempint;

			continue;
		}

		std::getline(DBFile, tstr, '}');
		books[numBooks].title = tstr;
		std::getline(DBFile, tstr, '}');
		books[numBooks].author = tstr;
		std::getline(DBFile, tstr, '}');
		books[numBooks].publisher = tstr;
		DBFile >> books[numBooks].addedOn.month;
		DBFile >> books[numBooks].addedOn.day;
		DBFile >> books[numBooks].addedOn.year;
		DBFile >> books[numBooks].quantity;
		DBFile >> books[numBooks].retailCost;
		DBFile >> books[numBooks].wholesaleCost;

		totalRetailValue += books[numBooks].retailCost * (double)books[numBooks].quantity;
		totalWholesaleValue += books[numBooks].wholesaleCost * (double)books[numBooks].quantity;

		numBooks++;


	} while (!DBFile.eof());

	DBFile.close();
	return true;
}

/////////////////////////////////////////////////////////////////////////
//Pre:	Filename is valid and not currently being r/w'd to. We're assuming the
//		file will never shrink (as only quantities are set to zero, not removed)
//Post: Book array is formatted and outputted to a file. The filename should
//      always be DBFile? as you want to 'edit' the database you've opened,
//      not copy it.
bool BookDB::writeBooks(std::string filename)
{
	if (DBFile.is_open())
		return false;

	DBFile.open(DBFilename);
	
	if (!DBFile.is_open())
		return false;

	for (int idx = 0; idx < numBooks; idx++)
	{
		DBFile << books[idx].ISBN << '}';
		DBFile << books[idx].title << '}';
		DBFile << books[idx].author << '}';
		DBFile << books[idx].publisher << '}';
		DBFile << books[idx].addedOn.month << ' ';
		DBFile << books[idx].addedOn.day << ' ';
		DBFile << books[idx].addedOn.year << ' ';
		DBFile << books[idx].quantity << ' ';
		DBFile << std::fixed << std::setprecision(2);
		DBFile << books[idx].retailCost << ' ';
		DBFile << std::fixed << std::setprecision(2);
		DBFile << books[idx].wholesaleCost;
		DBFile.unsetf(std::ios_base::fixed);
		if (idx < numBooks - 1)
			DBFile << '\n';
	}

	DBFile.close();
	return true;
}

/////////////////////////////////////////////////////////////////////////
//Pre:  
//Post: 
bool	BookDB::readSalesData(std::string filename)
{

	// Attempt to create or open the file
	salesFile.open(filename,std::fstream::out | std::fstream::app);
	if (!salesFile.is_open())
		return false;

	// Reopen for input after creating
	salesFile.close();
	salesFile.open(filename, std::fstream::in);
	if (salesFile.eof())
	{
		currentNetProfit = 0.0;
		salesFile.close();
		return true;
	}

	salesFile >> currentNetProfit >> currentSalesAmount;
	salesFile.close();
	return true;
}

/////////////////////////////////////////////////////////////////////////
//Pre:  
//Post: 
bool	BookDB::writeSalesData(std::string filename)
{
	salesFile.open(filename, std::fstream::out);
	if (!salesFile.is_open())
		return false;
	std::cout << "currentnetprofit = " << currentNetProfit;
	salesFile << std::setprecision(2) << std::fixed << currentNetProfit;
	salesFile << std::endl << currentSalesAmount;

	salesFile.close();
	return true;
}

/////////////////////////////////////////////////////////////////////////
//Pre: bk is a valid book
//Post: bk is added to the end of the array IF the numBooks is less than
//      or equal to the max amt of books. Wholesale and Retail value is updated
//      by adding to the class's member variables. Returns 1 if success, 0 if
//      error such as not enough space or bk not initialized. Also checks the
//      values of bk to make sure they're there (not missing ISBN, etc...)
bool BookDB::addBook(Book bk)
{
	if (numBooks == MAX_BOOKS)
		return false;
	books[numBooks++] = bk;
	return 1;
}

/////////////////////////////////////////////////////////////////////////
//Pre:  iunno?
//Post: A book of ISBN is sold from the database IF the ISBN is found AND the
//      quantity is > 0. Retail and wholesale value of the databse is adjusted
//      for the book. Returns the price of the book sold and 0 if there was an error (assuming nothing is free).
double BookDB::sellBook(unsigned long ISBN)
{
	int idx = findBook(ISBN);
	
	// Error checking
	if (idx < 0)
		return 0.0;
	if (books[idx].quantity <= 0)
		return 0.0;

	quantityItems--;
	books[idx].quantity--;
	totalRetailValue	-= books[idx].retailCost;
	totalWholesaleValue -= books[idx].wholesaleCost;

	currentNetProfit += (books[idx].retailCost - books[idx].wholesaleCost);
	std::cout << "currentnetprof = " << currentNetProfit;
	currentSalesAmount += books[idx].retailCost;

	return books[idx].retailCost;
}

/////////////////////////////////////////////////////////////////////////
//Pre:  
//Post: 
double BookDB::sellBook(int idx)
{
	// Error checking
	if (idx < 0)
		return 0.0;
	if (books[idx].quantity <= 0)
		return 0.0;

	quantityItems--;
	books[idx].quantity--;
	totalRetailValue -= books[idx].retailCost;
	totalWholesaleValue -= books[idx].wholesaleCost;

	currentNetProfit += (books[idx].retailCost - books[idx].wholesaleCost);
	std::cout << "currentnetprof = " << currentNetProfit;
	currentSalesAmount += books[idx].retailCost;


	return books[idx].retailCost;
}

/////////////////////////////////////////////////////////////////////////
//Pre:  stuff
//Post: Pretty much the same as sellBook, except it can remove multiple books at
//		one and returns true if successful and false if there was an error
bool    BookDB::removeBook(unsigned long ISBN, int quantity)
{
	int idx = findBook(ISBN);
	if (idx < 0)
		return false;
	if (books[idx].quantity < 1 + quantity)
		return false;

	quantityItems -= quantity;
	books[idx].quantity -= quantity;
	totalRetailValue -= books[idx].retailCost * quantity;
	totalWholesaleValue -= books[idx].wholesaleCost * quantity;
	return 1;
}

/////////////////////////////////////////////////////////////////////////
//Pre:  sm is a valid sort method. books array should hold > 1 book
//Post: books array is sorted through using the appropriate SORT_METHOD
bool BookDB::sortBooks(SORT_METHOD sm)
{
	//is the array > 1?
	//if no, return 0
	Book *books = getBooks();
	int numBooks = getNumBooks();
	if (numBooks <= 1) {
		return false;
	}

	//loop through books using books array and numBooks
	//compare values determined by the sm (case switch?)
	//move and sort the books
	if (sm == QUANTITY) {
		int i, j, min_idx;

		// One by one move boundary of unsorted subarray
		for (i = 0; i < numBooks - 1; i++)
		{
			min_idx = i;
			for (j = i + 1; j < numBooks; j++)
				if (books[j].quantity < books[min_idx].quantity)
					min_idx = j;
			// Swap
			Book temp = books[min_idx];
			books[min_idx] = books[j];
			books[j] = temp;
		}
		return true;
	}
	else if (sm == COST) {
		int i, j, min_idx;

		// One by one move boundary of unsorted subarray
		for (i = 0; i < numBooks - 1; i++)
		{
			min_idx = i;
			for (j = i + 1; j < numBooks; j++)
				if (books[j].retailCost < books[min_idx].retailCost)
					min_idx = j;
			// Swap
			Book temp = books[min_idx];
			books[min_idx] = books[j];
			books[j] = temp;
		}
		return true;
	}
	else if (sm == AGE) {
		int i, j, min_idx;

		// One by one move boundary of unsorted subarray
		for (i = 0; i < numBooks - 1; i++)
		{
			min_idx = i;
			for (j = i + 1; j < numBooks; j++)
				if (books[j].addedOn.year < books[min_idx].addedOn.year && books[j].addedOn.year != books[min_idx].addedOn.year)
					min_idx = j;
				else if (books[j].addedOn.month < books[min_idx].addedOn.month && books[j].addedOn.month != books[min_idx].addedOn.month)
					min_idx = j;
				else if (books[j].addedOn.day < books[min_idx].addedOn.day && books[j].addedOn.day != books[min_idx].addedOn.day)
					min_idx = j;

			// Swap
			if (min_idx == j) {
				Book temp = books[min_idx];
				books[min_idx] = books[j];
				books[j] = temp;
			}
		}
		return true;
	}
	return false; // end-of-function return val needed incase it gets reached somehow
}

/////////////////////////////////////////////////////////////////////////
//Pre:  
//Post: 
std::ostream& operator <<(std::ostream &out, const Book &bk)
{
	std::cout << "\n  Title: " << bk.title << "\n  Author: " << bk.author << "\n  Cost: " << bk.retailCost
		<< "\n  Wholesale: " << bk.wholesaleCost << "\n  Publisher: " << bk.publisher
		<< "\n  ISBN: " << bk.ISBN << "\n  Quantity: " << bk.quantity;
	return out;
}
