#include <string>
#include<iostream>
#include<fstream>
#include<iomanip>
#include<ctype.h>
#include "lexical.h"
#include "Par.h"
using namespace std;
int main(){
    ifstream input;
    ofstream output("output.txt");
    string line,file;
     int onOff=0;
        //allow user to choose file instead of always being test.txt
        cout<< "Enter the input filename:"<<endl;
        cin>>file;
        input.open(file.c_str());
        //check if file opened
        if(!input.is_open()){
            cout<<"Failed to open file."<<endl;
            return 0;
        }
    cout<<"This file's tokens and lexemes:"<<endl;
    output<<"This file's tokens and lexemes:"<<endl;
    Par p;
    input.clear();
    //set position back
    input.seekg(0);
    cout<< "Press 1 to turn on Syntax Analysis or enter 0 to continue with just a Lexical Analysis."<<endl;
    cin>>onOff;

    //Turns on syntax check
    p.ParserOnOff(onOff);
    p.RAT19F(input,output);
        input.close();
    output.close();
    return 0;

}
