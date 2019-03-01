#include "BookDB.h"

//temp
#include <iostream>

//Pre:  None
//Post: Initializes a BookDB object and its variables
BookDB::BookDB(std::string filename)
{
    DBFilename = filename;
    numBooks = 0;
    totalWholesaleValue = 0;
    totalRetailValue = 0;
    
    books = new Book[MAX_BOOKS];
    // Parse books here? ... yes. parse thems hurr.
    readBooks(DBFilename);
    
}
//Pre:  BookDB Exists
//Post: stuff gets deleted and whatnot
BookDB::~BookDB()
{
    if(books)
        delete[] books;
}



// ============Getters==============
//Pre:  books has been filled with at least 1 book?
//Post: pointer to books array is returned
Book* BookDB::getBooks()
{
    return books;
}

Book BookDB::getBook(int index)
{
    return books[index];
}

//Pre:  books has been initialized
//Post: books array is traversed to find how many book entries there are
//          number of books is returned as an int
int BookDB::getNumBooks()
{
    // figure out how many books via iteratting
    return numBooks;
}

//Pre:  books has been initialized
//Post: returns the wholesale value of all the books combined
double BookDB::getWholesaleValue()
{
    return totalWholesaleValue;
}

double BookDB::getRetailValue()
{
    return totalRetailValue;
}

int BookDB::findBook(unsigned long ISBN)
{
    if( numBooks > 0 )
        for(int idx = 0; idx < numBooks; idx++)
            if(books[idx].ISBN == ISBN)
                return idx;
    return 0;
}


// ============Mutators==============

//Pre:  Filename is valid and bk is initialized to hold at least
//      MAX_BOOKS
//Post: bk is filled with books from the file <filename>.
//      WholesaleValue and retailValue are updated as the books
//      are moved into the books array
void BookDB::readBooks(std::string filename)
{
    //file init
    
    //loop through the input
    //add books as they're found
    //add books' value as they're added
    
    // Thingies I have to set here...
    
    // file format:
    // <isbn> <title>} <author>} <publisher>} <month-added> <day-added> <year-added> <quantity> <retailcost> <wholesalecost>
    /*
     1239428842 Hello Kitty} Krissi Yan} Meow Books Inc} 1 5 2019 200 10.21 12.02
     */
    numBooks = 0;
    totalRetailValue = totalWholesaleValue = 0;
    
    DBFile.open(DBFilename);

  //  std::string db;
  //  DBFile >> db;
  //  std::cout << db;
 //   DBFile << "moew";
    unsigned long temp = 0;
    do
    {
        std::string tstr;
        
        DBFile >> books[numBooks].ISBN;
        
        
        // Search for an existing entry
        temp = findBook(books[numBooks].ISBN);
        
        // increase quantity if a match was found
        if( temp > 0 )
        {
            int junkint;
            double junkdbl;
            std::cout << "\nduplicate entry found";
            std::cout << "\nmerging quantities and info for " << books[temp].title;
            std::getline(DBFile, tstr, '}');
            std::getline(DBFile, tstr, '}' );
            std::getline(DBFile, tstr, '}' );
            DBFile >> junkint; //day
            DBFile >> junkint; //month
            DBFile >> junkint; //year
            DBFile >> junkint;
            books[temp].quantity += junkint;
            DBFile >> junkdbl;
            totalRetailValue += junkdbl * (double)junkint;
            DBFile >> junkdbl;
            totalWholesaleValue += junkdbl * (double)junkint;
            
            temp = 0;
        }
        
        std::getline(DBFile, tstr, '}');
        books[numBooks].title = tstr;
        std::getline(DBFile, tstr, '}' );
        books[numBooks].author = tstr;
        std::getline(DBFile, tstr, '}' );
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
        
        
    } while(!DBFile.eof());//while( DBFile.peek() != '\n' && numBooks < MAX_BOOKS);
    
}

//Pre: filename is valid and not currently being r/w'd to.
//Post: Book array is formatted and outputted to a file. The filename should
//      always be DBFile? as you want to 'edit' the database you've opened,
//      not copy it.
void BookDB::writeBooks(std::string filename)
{
    //clear input buffer: sync()
    //do stuff
    //close the DBFile fstream and reopen it for writing instead of reading
    //write the formatted database to the file
    //close the file
    // /dance
}

//pre: bk is a valid book
//post: bk is added to the end of the array IF the numBooks is less than
//      or equal to the max amt of books. Wholesale and Retail value is updated
//      by adding to the class's member variables. Returns 1 if success, 0 if
//      error such as not enough space or bk not initialized. Also checks the
//      values of bk to make sure they're there (not missing ISBN, etc...)
bool    BookDB::addBook(Book bk)
{
    if(numBooks == MAX_BOOKS)
        return false;
    books[numBooks++] = bk;
    return 1;
}

//Pre:  iunno?
//Post: A book of ISBN is sold from the database IF the ISBN is found AND the
//      quantity is > 0. Retail and wholesale value of the databse is adjusted
//      for the book. Returns the price of the book sold.
double BookDB::sellBook(unsigned long ISBN)
{
    return 0.0;
}

//Pre:  stuff
//Post: Pretty much the same as sellBook, except it's the inventory management version?
bool    BookDB::removeBook(unsigned long ISBN, int quantity)
{
    return 1;
}

//Pre:  sm is a valid sort method. books array should hold > 1 book
//Post: books array is sorted through using the appropriate SORT_METHOD
bool BookDB::sortBooks(SORT_METHOD sm)
{
    //is the array > 1?
    //if no, return 0
    //Book *books = getBooks();
    //int numBooks = getNumBooks();
    if (numBooks <= 1)
    {
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
            
            //test//
            //books[2] = books[1];
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
    return false;
}


std::ostream& operator <<(std::ostream &out, const Book &bk)
{
    std::cout << "\n  Title: " << bk.title << "\n  Author: " << bk.author << "\n  Cost: " << bk.retailCost
    << "\n  Wholesale: " << bk.wholesaleCost << "\n  Publisher: " << bk.publisher
    << "\n  ISBN: " << bk.ISBN << "\n  Quantity: " << bk.quantity;
    return out;
}

