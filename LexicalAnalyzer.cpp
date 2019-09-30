#include <iostream>
#include<fstream>
#include <iomanip>
#include<string.h>
#include<stdio.h>
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
  char separators[8] = {'(',')',',','{','}','[',']','"'};
  for(int i=0;i<8;i++){
    if(separators[i]==lexicalUnit)
      return true;
  }
  else
    return false;
}
bool operatorCheck(
bool idenCheck(char lexicalUnit[]){
  if(

void lexer(const string &fileName){
  while(){
    char data;
  //Go through the file char by char
    getchar(data);
    cout<<data<<endl;
}

  }
}


int main(){
  ifstream input("test.txt");
  while(!input.eof()){
    lexer("test.txt");
    int main(){


  ifstream input("test.txt");
  //Go through the file char by char
  while(!input.eof()){
    input.get(curChar);
    if(curChar=='('){
      cout<<"bracket found";
    }
// putback(curChar);?
    // cout<<data<<endl;

}
    }
}


ofstream output;
output.open("output.txt");
output<<"Token" << setw(10) << "Lexeme";
output.close();

  input.close();
}
