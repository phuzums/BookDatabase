#include "BookDB.h"

//NOTES::
//  - ISBN13's look like dis: 978-1-56931-507-1... i think we should be able to just strip the dashes, right?
//  - ISBN10's look like 164273005X ... the chars would be more work search-wise... let's just use 13's w/o dashes?
int main(int argc, char** argv)
{
    
    int isbn;
    // Test stuff out before we have file I/O working...
    // so... make the structs by hand first.
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
    
    myDB.sortBy(SORT_METHOD::COST);
    
    // cout test stuff
    
    myDB.sellBook(9784063840308);
    
    // cout test stuff
    
    for(int idx = 0; idx < 2000; idx++)
        myDB.addBook(HinaMatsuri);
    
    // more test stuff
    
    myDB.sortBy(SORT_METHOD::QUANTITY);
    
    // meow test stuff...
    
    
    
    
    
    
    cout << "which book to remove?";
    cin >> isbn;
    
    if (myDB.removeBook(isbn))
        cout << "book was removed";
    else
        cout << "err. book not on hand...";
    
    return 0;
    
}
