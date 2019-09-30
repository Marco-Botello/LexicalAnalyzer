#include <iostream>
#include<fstream>
#include <iomanip>
#include<string.h>
using namespace std;

//Check if the lexicalUnit is a keyword, returns true or false
bool keywordCheck(char lexicalUnit[]){
  char keywords[32][10] = {"auto","break","case","char","const","continue","default",
              "do","double","else","enum","extern","float","for","goto",
              "if","int","long","register","return","short","signed",
              "sizeof","static","struct","switch","typedef","union",
              "unsigned","void","volatile","while"};
  for(int i=0;i<32;i++){
    if(strcmp(keywords[i],lexicalUnit)==0)
      return true;
  }
  return false;
}

bool separCheck(char lexicalUnit){
  char separaters[] = '(',')',',','{','}','[',']',

bool idenCheck(char lexicalUnit[]){
  if(

     

int main(){


  ifstream input("test.txt");
  char data;
  //Go through the file char by char
  while(!input.eof()){
    input>>data;
    cout<<data<<endl;
  }

ofstream output;
output.open("output.txt");
output<<"Token" << setw(10) << "Lexeme";
output.close();

  input.close();
}
