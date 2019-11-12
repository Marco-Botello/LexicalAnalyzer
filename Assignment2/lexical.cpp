#include "lexical.h"
int Lexical::lineNum=1;
Lexical::Lexical(){
    input = 'a';
}
int Lexical::column(const char c)const{
    if(isdigit(c))
        return 1;
    else if(c=='.')
        return 2;
    else if(isalpha(c))
        return 3;
    else return 5;
}

int Lexical::intFSM(const string s){
    int state =1;
    int arr[3][2]={0,'d',1,2,2,2};
    int acc[1]={2};
    int stringSize=s.size();
    for (int i=0; i<stringSize; i++){
        int co=column(s[i]);
        state=arr[state][co];
    
    }
    if (state==acc[0]){
        return 1;
    }
    else return 0;
}

int Lexical::realFSM(string s){
    int state=1;
    int arr[5][3]={0,'d','.',1,2,0,2,2,3,3,4,0,4,4,0};
    int acc[1]={4};
    int stringSize=s.size();
    //get column number
    for(int i=0;i<stringSize;i++){
        int co=column(s[i]);
        state=arr[state][co];
        if (state==0) return 0;
    }
    if (state==acc[0])
        return 1;
    else return 0;
}

int Lexical::identifierFSM(string s){
    int state = 1;
    int arr[6][5]= {0,'d','.','l','#',1,0,0,2,0,2,0,0,3,4,3,0,3,4,4,0,0,5,0,5,0,0,3,4};
    int acc[4]={2,3,4,5};
    int stringSize= s.size();
    for (int i=0; i<stringSize; i++) {
        int co=column(s[i]);
        state=arr[state][col];
        if(state==0){
            return 0;
        }
    }
for (int i=0; i<4; i++) {
    if(state==acc[i]){
        return 1;
    }
    return 0;
    }
}



//check Operator
bool Lexical::Operator(const char o) const{
    int i;
    int operators[8]={'-','+','*','/','<','=','>',':'};
    for(i=0;i<8;i++){
        if(operators[i]==o){
        return 1;
    }
    }
    return 0;
}

//seperator
bool Lexical::Separator(const char s) const{
    int separators[9]={',',';','[',']','{','}','(',')','%'};
    for(int i=0; i<9;i++){
        if(separators[i]==s){
            return 1;
        }
    }
    return 0;
}

// Keyword
bool Lexical::checkKeyword(string K)const{
    
    
//    char keywords[36][10] = {"auto","break","case","char","const","continue","default",
//                            "do","double","else","enum","extern","float","for","goto",
//                            "if","int","long","register","return","short","signed",
//                            "sizeof","static","struct","switch","typedef","union",
//                            "unsigned","void","volatile","while","true","false","cin","cout"};

    string keywords[17]={"if","else","return","read","write","int","true","false","bool","float","while","break","const","switch","struct","cin","cout"};
    for (int i=0;i<17;i++){
        if(keywords[i]==K){
            return 1;
        }
    }
    return 0;
}

int Lexical::identifyLexeme(string L){
    int length=L.length();
    char ch=L[0];
    int i=0;
    //seperator
    for(int i=0;i<length;i++){
        if (Separator(L[i])){
            return 2;
        }
    }
    
    //operator
    for(int i=0;i<length;i++){
          if (Operator(L[i])){
              return 1;
          }
      }
    
    
    //if identifier
    if(isalpha(ch)){
        for(i=0;i<length;i++){
            if(isalpha(L[i]));
            else{
                return 6;
            }
        }
        return 3;
    }
    //real number
    else if(isdigit(ch)){
        for(int j=0;j<length;j++){
            if(L[j]=='.'||isdigit(L[j]));
            else return 6;
        }
           for (int i = 0; i < length; i++)
                {
                    if (L[i] == '.')
                      return 4;
            }

//Otherwise integer
        return 5;
        
    }
    else
        return 6;
    
}



