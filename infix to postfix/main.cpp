#include <iostream>
#include<math.h>
#define Size 50
using namespace std;

class Stack{
    private:
        char container[Size],cursor=-1;

    public:
        void push(char);
        char pop();
        void Display();
        bool isEmpty();
        char Top();
};

char Stack::pop(){
    if(cursor<=-1){
    }
    else{
        cursor--;
        return container[cursor+1];
    }
}

void Stack::push(char tmp){
    //cout<<"cursor"<<cursor<<endl;
    if(cursor>=(Size-1)){
    }
    else{
        cursor++;
        container[cursor]=tmp;
    }
}

void Stack::Display(){
    for(int i=0;i<(cursor+1);i++){
        cout<<container[i];
    }
}

bool Stack::isEmpty(){
    if(cursor<=-1){
        return true;
    }
    else{
        return false;
    }
}
char Stack::Top(){
    return container[cursor];
}

int Precedance(char c){
    switch(c){
        case '+':return 1;
        case '-':return 1;
        case '*':return 2;
        case '/':return 2;
        case '^':return 3;
        case '(':return 10;
        case ')':return 10;
        default:return 0;
    }
}

int CharMap(char c){
    if(c<=57&&c>=48){
        return 1;//number
    }
    else if(c<=90&&c>=65){
        return 2; //char
    }
}

int main()
{
    int exp_len=17;
    //char infix[exp_len]="A+(B*C-(D/E^F)*G)*H";
    //char infix[exp_len]="((A-(B+C))*D)^(E+F)";
    char infix[exp_len]="A+B-C*(D-E+F/G)/H";
    char postfix[exp_len];
    Stack s1;
    int i=0,j=0,k=0;
    //printf("h%df",j);
    cout<<"\tSymbol\t"<<"\tPostfix\t"<<"\t\tStack"<<endl;
    while(i<exp_len){
        if(infix[i]=='+'||infix[i]=='-'||infix[i]=='*'||infix[i]=='/'||infix[i]=='^'){

                if(s1.isEmpty()||s1.Top()=='('||(Precedance(infix[i])>Precedance(s1.Top()))){
                        s1.push(infix[i]);
                }
                else{
                    while((s1.Top()=='+'||s1.Top()=='-'||s1.Top()=='*'||s1.Top()=='/'||s1.Top()=='^')&&(Precedance(s1.Top())>=Precedance(infix[i]))){
                            postfix[j]=s1.pop();
                            j++;
                    }
                    s1.push(infix[i]);
                }

        }
        else if(infix[i]=='('){
            s1.push(infix[i]);
        }
        else if(infix[i]==')'){
            char tmp;
            while(tmp=s1.pop(),tmp!='('){
                postfix[j]=tmp;
                j++;
            }
        }
        else{
            postfix[j]=infix[i];
            j++;
        }

        cout<<"\t"<<infix[i]<<"\t\t";
        for(k=0;k<j;k++){
            cout<<postfix[k];
        }
        cout<<"\t\t\t";
        s1.Display();
        cout<<endl;

        i++;

    }

    while(!(s1.isEmpty())){
        postfix[j]=s1.pop();
        j++;
    }

    cout<<"\t"<<""<<"\t\t";
        for(k=0;k<j;k++){
            cout<<postfix[k];
        }
        cout<<"\t\t\t";
        s1.Display();
        cout<<endl;
    return 0;
}
