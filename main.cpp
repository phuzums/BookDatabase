#include <iostream>
#include "BookDB.h"


//NOTES::
//  - ISBN13's look like dis: 978-1-56931-507-1... i think we should be able to just strip the dashes, right?
//  - ISBN10's look like 164273005X ... the chars would be more work search-wise... let's just use 13's w/o dashes?
int main(int argc, char** argv)
{
    
    Date today;
    today.day   = 21;
    today.month = 2;
    today.year  = 2019;
    
    Book PokemonAdventures;
    
    PokemonAdventures.ISBN          = 9781569315071;
    PokemonAdventures.wholesaleCost = 474.00;
    PokemonAdventures.retailCost    = 512.99;
    PokemonAdventures.title         = "Pokemon Adventures";
    PokemonAdventures.author        = "Hidenori Kusaka";
    PokemonAdventures.publisher     = "Shogakukan";
    PokemonAdventures.addedOn       = today;
    
    Book HinaMatsuri;
    HinaMatsuri.ISBN                = 9781642730050;
    HinaMatsuri.wholesaleCost       = 9.01;
    HinaMatsuri.retailCost          = 9.53;
    HinaMatsuri.title               = "Hinamatsuri Volume 1";
    HinaMatsuri.author              = "Masao Ohtake";
    HinaMatsuri.publisher           = "One Peace Books";
    HinaMatsuri.addedOn             = today;
    
    Book LewdAnimeh;
    LewdAnimeh.ISBN                 = 9784063840308;
    LewdAnimeh.wholesaleCost        = 7.89;
    LewdAnimeh.retailCost           = 99999999999.99; //#worthit
    LewdAnimeh.title                = "Seitokai Yakuindomo 1";
    LewdAnimeh.author               = "Tozen Ujiie";
    LewdAnimeh.publisher            = "Kodansha";
    LewdAnimeh.addedOn              = today;
    
    BookDB myDB("not_implemented_yet.nyan");
    myDB.addBook(PokemonAdventures);
    myDB.addBook(HinaMatsuri);
    myDB.addBook(LewdAnimeh);
    
    // cout test stuff
    std::cout << "\n\n  ~ Outputting Info On Books ~";
    std::cout << "\nBook 1: " << myDB.getBook(0).title << "\n  Author: " << myDB.getBook(0).author << "\n  Cost: " << myDB.getBook(0).retailCost;
    std::cout << "\nBook 2: " << myDB.getBook(1).title << "\n  Author: " << myDB.getBook(1).author << "\n  Cost: " << myDB.getBook(1).retailCost;
    std::cout << "\nBook 3: " << myDB.getBook(2).title << "\n  Author: " << myDB.getBook(2).author << "\n  Cost: " << myDB.getBook(2).retailCost;
    std::cout << "\n====================================";
    
    myDB.sortBooks(SORT_METHOD::COST);
    
    std::cout << "\n\n  ~ Sorting Books By Cost ~";
    std::cout << "\nBook 1: " << myDB.getBook(0).title;
    std::cout << "\nBook 2: " << myDB.getBook(1).title;
    std::cout << "\nBook 3: " << myDB.getBook(2).title;
    std::cout << "\n====================================";
    
    myDB.sellBook(9784063840308L);
    
    std::cout << "\n\n  ~ Selling LewdAnimeh By ISBN ~";
    std::cout << "\nBook 1: " << myDB.getBook(0).title;
    std::cout << "\nBook 2: " << myDB.getBook(1).title;
    std::cout << "\nBook 3: " << myDB.getBook(2).title;
    std::cout << "\n====================================";
    
    for(int idx = 0; idx < 2000; idx++)
        myDB.addBook(HinaMatsuri);
    // NOTE: Adding duplicate copies of books shouldn't increase numBooks, it should update the quantity of the existing book entry...
    //       Point being, there should only be 3 books here still and myDB.getBook(4) should fail and return either a null ptr or failfish Book
    std::cout << "\n\n  ~ Adding 2000 copies of Hina Matsuri ~";
    std::cout << "\nBook 1: " << myDB.getBook(0).title;
    std::cout << "\nBook 2: " << myDB.getBook(1).title;
    std::cout << "\nBook 3: " << myDB.getBook(2).title;
    std::cout << "\nBook 5: " << myDB.getBook(4).title;
    std::cout << "\nBook 401: " << myDB.getBook(400).title;
    std::cout << "\nBook 2001: " << myDB.getBook(2000).title;
    std::cout << "\nNumber of books in database: " << myDB.getNumBooks();
    std::cout << "\n====================================";
    
    myDB.sortBooks(SORT_METHOD::QUANTITY);
    
    std::cout << "\n\n  ~ Sorting Books By Quantity ~ ";
    std::cout << "\nBook 1: " << myDB.getBook(0).title;
    std::cout << "\nBook 1002: " << myDB.getBook(1001).title;
    std::cout << "\nBook 2000: " << myDB.getBook(1999).title;
    std::cout << "\n====================================";
    
    
    
    std::cout << "\n\n";
    return 0;
    
}
