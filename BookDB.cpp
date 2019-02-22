#include "BookDB.h"


//Pre:  None
//Post: Initializes a BookDB object and its variables
BookDB::BookDB(std::string filename)
{
    DBFilename = filename;
    numBooks = 0;
    wholesaleValue = 0;
    retailValue = 0;
    
    books = new Book[MAX_BOOKS];
    // Parse books here? ... yes. parse thems hurr.
    parseBooks(DBFilename);
    
    numBooks = getNumBooks();
    
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

//Pre:  books has been initialized
//Post: books array is traversed to find how many book entries there are
//          number of books is returned as an int
int BookDB::getNumBooks()
{
    // figure out how many books via iteratting
    return 0;
}

//Pre:  books has been initialized
//Post: returns the wholesale value of all the books combined
double BookDB::getWholesaleValue()
{
    return wholesaleValue;
}

double BookDB::getRetailValue()
{
    return retailValue;
}


// ============Mutators==============

//Pre:  Filename is valid and bk is initialized to hold at least
//      MAX_BOOKS
//Post: bk is filled with books from the file <filename>.
//      WholesaleValue and retailValue are updated as the books
//      are moved into the books array
void parseBooks(std::string filename)
{
    //file init
    
    //loop through the input
        //add books as they're found
            //add books' value as they're added
    
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
    //re-sort the array?
    return SUCCESS;
}

//Pre:  iunno?
//Post: A book of ISBN is sold from the database IF the ISBN is found AND the
//      quantity is > 0. Retail and wholesale value of the databse is adjusted
//      for the book. Returns the price of the book sold.
double sellBook(int ISBN)
{
    
}

//Pre:  stuff
//Post: Pretty much the same as sellBook, except it's the inventory management version?
bool    BookDB::removeBook(int ISBN, int quantity)
{
    
}

//Pre:  sm is a valid sort method. books array should hold > 1 book
//Post: books array is sorted through using the appropriate SORT_METHOD
bool    BookDB::sortBooks(SORT_METHOD sm)
{
    //is the array > 1?
        //if no, return 0
    
    //loop through books using books array and numBooks
        //compare values determined by the sm (case switch?)
            //move and sort the books
}
