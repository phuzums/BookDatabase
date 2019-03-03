# BookDatabase
Project for CIS 22B
Change log:
 - Added Sales Data Functionality, including another i/o fstream object, salesFile
 - Filled in functionality for cashier module -> sell by ISBN
    [] This should work when tested for most all cases!
 - sales_data.txt is created or opened when running the program
    [] This filename can be changed when initializing, but the parameter defaults to "sales_data.txt"
 - Several variables for sales data has been added to the BookDB class
 - #include <iomanip> has been added to several files for output formatting
 - Several error checking screens have been added
 - Output regarding the DB/SalesData write functions added when exiting the program
 - Default constructor changed
 - Read/WriteSalesData() added
 - getBook(int idx) now returns an 'error' book if it can't find the book, rather than crashing the program
 - findBook(unsigned long ISBN) now returns an int instead of unsigned int, -1 is returned as an error code (since 0 is a valid index)
  
