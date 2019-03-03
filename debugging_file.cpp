#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){
    int counter  = 0;
    string line = "";
    string finding_number_of_books = "";
    fstream inputFile;
    int start = 0;

    inputFile.open("BookTitles.txt");
    if (inputFile.fail() ){
        cout<<"the file could not be opened properly"<<endl;
    }
    else{//if the file properly opened
        cout<<"the file properly opened"<<endl;
        
        while (inputFile){
            getline(inputFile,line,'\n');
            for(int i = 0; i<7;i++){
                cout<<endl;
                //cout<<start<<endl;
                int finished = line.find("`");
                //cout<<finished<<endl;
                finding_number_of_books = line.substr(start,finished);
                line.erase(start,finished + 1);
                //cout<<line<<" this is line"<<endl;
                //cout<<line[0]<<"this is the first element in line"<<endl;
                cout<<endl;
            }
            string number;
            number = line[0];
            cout<<number<<"this is number"<<endl;
            int incrementer = atoi(number.c_str());
            counter = counter + incrementer;
            cout<<counter<<"this is counter"<<endl;
            cout<<endl;
            cin.get();
            //counter++;

        }
    }
    cout<<counter<<" this is the counter of the number of unique books in the library"<<endl;

}