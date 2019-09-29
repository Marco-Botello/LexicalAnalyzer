#include <iostream>
#include<fstream>
#include <iomanip>
using namespace std;
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
