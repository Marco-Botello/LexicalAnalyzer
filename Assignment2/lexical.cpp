#include "lexical.h"
int Lexical::line=1;
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
    //accepting states
    int acc[1]={2};
    int stringSize=s.size();
    //get column number
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
        state=arr[state][co];
        if(state==0){
            return 0;
        }
    }
for (int i=0; i<4; i++) {
    if(state==acc[i]){
        return 1;
    }
    }
    return 0;

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

void Lexical::Lexer(ifstream& f){
    bool flag=false;
    string s;
    char currChar='a';
    char previousChar='a';
    int state=0;
    int identify=identifyLexeme(s);
    
    while (!flag){
        if(previousChar == '\n') line++;
        currChar=f.get();
        previousChar=currChar;
        //check if seperator, operator, space
        if(this->Separator(currChar)||currChar==-1||this->Operator(currChar)||currChar==' ') {
            flag=true;
        }
        if((!s.empty()&&this->Separator(currChar))||(this->Operator(currChar))){
            f.unget();
        }
        else if (currChar!=' ' && !(currChar==-1)){
            s+=currChar;
        }
        if(!(currChar==-1)&&s.empty()){
            flag=false;
        }
        
    }
    if(s.empty() && currChar==-1){
        this->setToken("EOF");
        this->setLexeme("EOF");
        
        return;
    }
    
    if(identify==3){
        state=identifierFSM(s);
        this->setLexeme(s);
        if(state==1){
            //if it isnt an identifier it must be an identifier
            if(checkKeyword(s))
                this->setToken("Keyword");
            else
            this->setToken("Identifier");
        }
        else
            this->setToken("Unknown");
    }
    else if(identify==1){
        s=currChar;
        currChar=f.peek();
        //check for >=, <=,:= etc
        if((s[0]=='>' && currChar=='=')|| (s[0]=='<' && currChar=='=')||(s[0]==':'&&currChar =='=')||(s[0]=='/'&&currChar=='=')){
            s+=currChar;
            f.get();
        }
        if(s==":="||s=="/="||s=="<="||s==">="||Operator(s[0])){
            this->setLexeme(s);
            this->setToken("Operator");
        }
        else{
            this->setLexeme(s);
            this->setToken("Unknown");
        }
    }
    else if(identify==2){
        s=currChar;
        currChar=f.peek();
        if(currChar=='%' && s[0]=='%'){
            s=currChar;
            f.get();
        }
        if(!(s[0]=='%')||s=="%%"){
            this->setToken("Separator");
            this->setLexeme(s);
        }
        else{
            this->setToken("Unknown");
            this->setLexeme(s);
            
        }
    }
    else if (identify==4){
        state=realFSM(s);
        this->setLexeme(s);
        if(state==1){
            this->setToken("Real");
        }
        else{
            this->setToken("Unknown");
        }
    }
    else if(identify==5){
        state=intFSM(s);
        this->setLexeme(s);
        if(state==1){
            this->setToken("Integer");
        }
        else
            this->setToken("Unknown");
    }
    else{
        this->setToken("Unknown");
        this->setLexeme(s);
        
    }
}



void Lexical::setToken(const string newT){
    token = newT;
}
void Lexical::setLexeme(const string newL){
    lexeme=newL;
}

string Lexical::getLexeme() const{
    return lexeme;
}
string Lexical::getToken() const{
    return token;
}
void Lexical::print() const
{
    cout << "Token: "<<left<<"\t\t"<<this->token<<"Lexeme: "<<"\t\t"<<this->lexeme<<endl;
}


