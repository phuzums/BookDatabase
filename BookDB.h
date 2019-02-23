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

struct Book
{
    unsigned long ISBN;
    double wholesaleCost, retailCost;
    std::string title, author, publisher;
    Date addedOn;
    int quantity = 1;
};

/* REQ  List by Quantity. A list of all books in the inventory sorted by quantity on hand. The books with the greatest quantity on hand will be listed first.
 List by Cost. A list of all books in the inventory, sorted by wholesale cost. The
 books with the greatest wholesale cost will be listed first.
 List by Age. A list of all books in the inventory, sorted by purchase date. The
 books that have been in the inventory longest will be listed first.
 */
enum SORT_METHOD
{
    QUANTITY = 0, COST, AGE
};

class BookDB
{
    // Update : We should do option 2, otherwise the code in main will be huge and less organized...
    // Ideally we should just make a function outside of this class in the .cpp / .h so that the class
    // doesn't hold a function that doesn't need to be carried with instances of the DB... but i don't think
    // he'll care...
public:                                        // We can do any of these
    BookDB();                                    // 1. Create the database then initialize it later using some funciton like myBookDB.init("filename.txt");
    BookDB(std::string filename);                // 2. Require the filename and parse the text file within the code
    BookDB(Book* bookdatabase, int numBooks);    // 3. Parse the textfile elsewhere and just take an array of books and len of that array
    ~BookDB();
public:
    // Getters
    //!! REQ Inventory List. A list of information on all books in the inventory.
    Book*    getBooks();
    Book     getBook(int index);
    int      getNumBooks();
    
    //!! REQ Inventory Wholesale Value A list of the wholesale value of all books in the inventory and the total wholesale value of the inventory.
    double   getWholesaleValue();
    
    //!! REQ Inventory Retail Value. A list of the retail value of all books in the inventory and the total retail value of the inventory.
    double  getRetailValue();
    
    // Mutators
    void    readBooks(std::string filename);    // Needed if we go with option 1 or 2
    void    writeBooks(std::string filename);
    //!! REQ When a book is purchased, subtract it from the inventory file !!//
    
    // ** Book Modifiers ** //
    double  sellBook(unsigned long ISBN);                 // These cannot be combined...
    //!! REQ Add, change, delete, and look up books in the inventory file !!//
    bool    removeBook(unsigned long ISBN, int quantity);               // <--probably just use this one
    bool    addBook(Book bk);
    int     findBook(unsigned long ISBN);                     // Returns the index in our array of the found entry or -1 if not found
    void    modifyBook(unsigned long ISBN, Book replacement);
    int     findBook(std::string author);
    
    // Sorting
    bool    sortBooks(SORT_METHOD sm);
    
private:
    Book*   books;
    int     numBooks;
    double  totalWholesaleValue;
    double  totalRetailValue;
    double  currentNetProfit;
    std::string     DBFilename;
    std::fstream    DBFile;
};


