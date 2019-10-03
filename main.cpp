#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <stdio.h>

using namespace std;

int keywordCheck(char lexicalUnit[]){
	char keywords[32][10] = {"auto","break","case","char","const","continue","default",
							"do","double","else","enum","extern","float","for","goto",
							"if","int","long","register","return","short","signed",
							"sizeof","static","struct","switch","typedef","union",
							"unsigned","void","volatile","while"};
  int mark = 0;

	for(int i = 0; i < 32; i++){
		if(strcmp(keywords[i], lexicalUnit) == 0){
			mark = 1;
			break;
		}
	}
	return mark;
}

int main(){
	char curChar, lexicalUnit[20], lexicalUnit2[20], separators[] = ",;''[]{}()", operators[] = "-+*/<=>%";
	ifstream input("test.txt");
	int i,j = 0,k = 0, flag = 0;

  cout << "Output:" << endl;
  cout << "Token\t\t" << "Lexeme" << endl;
  cout << "------------------------------" << endl;

	if(!input.is_open()){
		cout << "error while opening the file\n";
		exit(0);
	}

	while(!input.eof()){

   		curChar = input.get();

      for(i = 0; i < 10; i++){
        if(curChar == separators[i])
          cout << "Separator\t" << curChar << endl;
      }

		for(i = 0; i < 8; i++){
   			if(curChar == operators[i])
   				cout << "Operator\t" << curChar << endl;
   		}

   		if(isalpha(curChar)){
   			lexicalUnit[j++] = curChar;
   		}
   		else if((curChar == ' ' || curChar == '\n') && (j != 0)){
   				lexicalUnit[j] = '\0';
   				j = 0;

   				if(keywordCheck(lexicalUnit) == 1)
   					cout << "Keyword\t\t" << lexicalUnit << endl;
   				else
   					cout << "Identifier\t" << lexicalUnit << endl;
   		}

      if(isdigit(curChar) || curChar == '.'){
   			lexicalUnit2[k++] = curChar;
      }

   		else if((curChar == ' ' || curChar == '\n') && (k != 0)){
   				lexicalUnit2[k] = '\0';
   				k = 0;

          for (i = 0; i < 10; i++){
            if(lexicalUnit2[i] == '.'){
              flag = 1;
              break;
            }
            else flag = 0;
          }

   				if(flag == 1)
   					cout << "Real\t\t" << lexicalUnit2 << endl;
   				else
   					cout << "Integer\t\t" << lexicalUnit2 << endl;

   		}
	}
	input.close();
	return 0;
}
