#include <iostream>
#include <iomanip>
#include "BookDB.h"

/////////////////////////////////////////////////////////////////////////
//Pre:  None
//Post: Initializes a BookDB object and its variables
BookDB::BookDB(std::string filename, std::string sFilename) : BookList()
{
	listFilename		= filename;
	salesFilename		= sFilename;

	totalWholesaleValue = 0;
	totalRetailValue	= 0;
	currentNetProfit	= 0;
	currentSalesAmount	= 0;

	books = new Book[MAX_BOOKS];
	readBooks();
	readSalesData(salesFilename);
}

/////////////////////////////////////////////////////////////////////////
//Pre:  BookDB Exists
//Post: stuff gets deleted and whatnot
BookDB::~BookDB()
{
	std::cout << "\nWritting Database to file " << listFilename << "... ";
	if (writeBooks())
		std::cout << "Success!\n";
	else
		std::cout << "Error writting to file...\n";

	std::cout << "\nWritting Sales data to file " << salesFilename << "... ";
	if (writeSalesData(salesFilename))
		std::cout << "Success!\n";
	else
		std::cout << "Error writting to file...\n";
}



// ============Getters==============







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





// ============Mutators==============
/////////////////////////////////////////////////////////////////////////
//Pre:  Filename is valid and bk is initialized to hold at least
//      MAX_BOOKS
//Post: bk is filled with books from the file <filename>.
//      WholesaleValue and retailValue are updated as the books
//      are moved into the books array
bool BookDB::readBooks()
{
	numBooks = 0;
	totalRetailValue = totalWholesaleValue = 0;

	listFile.open(listFilename);

	if (!listFile)
		return false;

	int temp = 0;
	do
	{
		std::string tstr;

		listFile >> books[numBooks].ISBN;
		char tc = ' ';
		listFile >> tc; //Dummy char to read the seperator between isbn & books (used in case a book title starts with a number)


		// Search for an existing entry
		temp = findBook(books[numBooks].ISBN);

		// increase quantity if a match was found
		if (temp > 0)
		{
			int tempint;
			double tempdbl;
			std::getline(listFile, tstr, '}');
			std::getline(listFile, tstr, '}');
			std::getline(listFile, tstr, '}');
			listFile >> tempint; //day
			listFile >> tempint; //month
			listFile >> tempint; //year
			listFile >> tempint;
			books[temp].quantity += tempint;
			listFile >> tempdbl;
			totalRetailValue += tempdbl * (double)tempint;
			listFile >> tempdbl;
			totalWholesaleValue += tempdbl * (double)tempint;

			continue;
		}

		std::getline(listFile, tstr, '}');
		books[numBooks].title = tstr;
		std::getline(listFile, tstr, '}');
		books[numBooks].author = tstr;
		std::getline(listFile, tstr, '}');
		books[numBooks].publisher = tstr;
		listFile >> books[numBooks].addedOn.month;
		listFile >> books[numBooks].addedOn.day;
		listFile >> books[numBooks].addedOn.year;
		listFile >> books[numBooks].quantity;
		listFile >> books[numBooks].retailCost;
		listFile >> books[numBooks].wholesaleCost;

		totalRetailValue += books[numBooks].retailCost * (double)books[numBooks].quantity;
		totalWholesaleValue += books[numBooks].wholesaleCost * (double)books[numBooks].quantity;

		numBooks++;


	} while (!listFile.eof());

	listFile.close();
	return true;
}

/////////////////////////////////////////////////////////////////////////
//Pre:	Filename is valid and not currently being r/w'd to. We're assuming the
//		file will never shrink (as only quantities are set to zero, not removed)
//Post: Book array is formatted and outputted to a file. The filename should
//      always be listFile? as you want to 'edit' the database you've opened,
//      not copy it.
bool BookDB::writeBooks()
{
	if (listFile.is_open())
		return false;

	listFile.open(listFilename);
	
	if (!listFile.is_open())
		return false;

	for (int idx = 0; idx < numBooks; idx++)
	{
		listFile << books[idx].ISBN << '}';
		listFile << books[idx].title << '}';
		listFile << books[idx].author << '}';
		listFile << books[idx].publisher << '}';
		listFile << books[idx].addedOn.month << ' ';
		listFile << books[idx].addedOn.day << ' ';
		listFile << books[idx].addedOn.year << ' ';
		listFile << books[idx].quantity << ' ';
		listFile << std::fixed << std::setprecision(2);
		listFile << books[idx].retailCost << ' ';
		listFile << std::fixed << std::setprecision(2);
		listFile << books[idx].wholesaleCost;
		listFile.unsetf(std::ios_base::fixed);
		if (idx < numBooks - 1)
			listFile << '\n';
	}

	listFile.close();
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
	std::cout << "Book sold. Profit: " << currentNetProfit << std::endl;
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
//Pre:  
//Post: 
std::ostream& operator <<(std::ostream &out, const Book &bk)
{
	std::cout << "\n  Title: " << bk.title << "\n  Author: " << bk.author << "\n  Cost: " << bk.retailCost
		<< "\n  Wholesale: " << bk.wholesaleCost << "\n  Publisher: " << bk.publisher
		<< "\n  ISBN: " << bk.ISBN << "\n  Quantity: " << bk.quantity;
	return out;
}
