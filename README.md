# BookDatabase
Project for CIS 22B
Updated 3/18/19 :D
 - Inserted Reports Module to main.cpp
 - Filled out implementation side of Reports module
 - Added SORT_METHOD::WHOLESALE, mostly for the printByMethod function used by the reports module
 - Changed to printByMethod function to print out prettier stuff for the reports module
 - Added a submenu to reports root -- "Sorting" menu
 - Added implementation side to Sorting menu
 - Any numerical menu selection is now tabbed out for clarity 
 - Added Sales Data selection to reports menu
 - Added a getter function for CurrentNetProfit
 - Removed debug menu from root (though it can still be accessed by entering '88'
 
 TODO : 
 - x Maybe have sort by wholesale cost too?
 - x A whole lot of psuedocode

Updated Change log 3/14/19!
 - Implemented new sort methods
 - Added a debug option to the main menu for us to try out sorting / report methods
 - printByMethod(int verbosity = 0, SORT_METHOD sm) added to facilitate the reports module
 - Splash screen updated to the correct version
 - Some minor debug output was removed
 - void printDebugList(BookDB *myDB) was added temporarily for sort method debugging
 - void operator=(const Book &right); was added to the Book class
 - - - - TODO : 
 - !!! Inputing weird stuff to the menus cause them to go whacko!
 - x NEED MENUS SO BAD. SO SO BAD. 
 - x Book class should not be 100% public, this was intended to make the transfer from a struct easier but has kind of grown into the  mainstay
 - x Sort Methods AGE and QUANTITY do not work... Cost does though! 
 - x Should we implement the ability to sort via ascending / descending?
 - x Make a presentation-friendly version of the books.txt database file, preferably with about 50-100 books (can someone make a script to do this? i.e. rando word generator for title / author / publisher)
 - x Final check-down to make an over-the-weekend TODO list
 - x Polymorhping PowerFunctions
 - x Powerpoint assets
 
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
 - Lots of formatting has been done and debug code moved / deleted...
 - books.txt and database file formatting has changed to have less spaces and less complicated output formatting
    [] Values also normalized to be less hillarious and thus less confusing during debugging :(
