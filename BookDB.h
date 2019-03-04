#pragma once
#include <string>
#include <fstream>

#define MAX_BOOKS 2048


/* REQ
 ISBN This is the International Standard Book Number. It is a unique number assigned to each book by the publisher.
 Title The title of the book.
 Author The book’s author.
 Publisher The company that publishes the book.
 Date Added The date the book was added to the inventory.
 Quantity-On-Hand The number of copies of the book in inventory.
 Wholesale Cost The price paid by Serendipity for each copy of the book.
 Retail Price The price Serendipity is charging for each copy of the book.
 */
struct Date
{
	int day, month, year;
};

class Book
{
public:
	unsigned long ISBN;
	double wholesaleCost, retailCost;
	std::string title, author, publisher;
	Date addedOn;
	int quantity = 1;
	friend std::ostream& operator<<(std::ostream &out, const Book &bk);
};

enum SORT_METHOD
{
	QUANTITY = 0, COST, AGE
};

class BookDB
{
public:
	BookDB(std::string filename, std::string salesFilename = "sales_data.txt");                // 2. Require the filename and parse the text file within the code
	~BookDB();
public:
	// Getters
	Book*    getBooks();
	Book     getBook(int index);
	int      getNumBooks();

	double   getWholesaleValue();
	double  getRetailValue();

	// Mutators
	bool    readBooks(std::string filename);
	bool    writeBooks(std::string filename);
	
	bool	readSalesData(std::string filename);
	bool	writeSalesData(std::string filename);

	double  sellBook(unsigned long ISBN);						// These cannot be combined...
	double	sellBook(int idx);
	bool    removeBook(unsigned long ISBN, int quantity);		// <--probably just use this one
	bool    addBook(Book bk);
	int     findBook(unsigned long ISBN);						// Returns the index in our array of the found entry or -1 if not found
	int		findBook(std::string title);
	void    modifyBook(unsigned long ISBN, Book replacement);	// un-needed?

	bool    sortBooks(SORT_METHOD sm);


private:
	Book*   books;
	int     numBooks;				// number of book objects (entries in DB)
	int     quantityItems;			// number of books including duplicate copies
	double  totalWholesaleValue;
	double  totalRetailValue;
	double  currentNetProfit;		// Total profit (retail - wholesale)
	double	currentSalesAmount;		// Basically how much $$$ should be in the register
	std::string     DBFilename;
	std::string		salesFilename;
	std::fstream    DBFile;
	std::fstream	salesFile;
};
