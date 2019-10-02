#include <iostream>
#include<fstream>
#include <iomanip>
#include<string.h>
#include<stdio.h>
#include<vector>
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

bool separCheck(char lexicalUnit[]){
  char separators[8] = {'(',')',',','{','}','[',']','"'};
  for(int i=0;i<8;i++){
    if(separators[i]==lexicalUnit[0])
      return true;
  }
    return false;
}

void lexer(const string &fileName){
  ifstream input(fileName);
  vector<char> lexicalUnit;

  char curChar;

  while(!input.eof()){
    while(input.peek()!='e'){
      input.get(curChar);
      lexicalUnit.push_back(curChar);
      cout<<"safe."<<endl;
    }
    // if(curChar=='('){
    //   cout<<"bracket found"<<endl;
    // }
  }

  input.close();

}
int main(){
    lexer("test.txt");
ofstream output;
output.open("output.txt");
output<<"Token" << setw(10) << "Lexeme";
output.close();
}
