#include <iostream>
#include<math.h>
#include<stdlib.h>
#define Size 50
using namespace std;

class Stack{
    private:
        float container[Size];
        int cursor=-1;

    public:
        void push(char);
        float pop();
        void Display();
        bool isEmpty();
        float Top();
};

float Stack::pop(){
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
        //printf("%0.2f, ",container[i]);
        cout<<container[i]<<",";
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
float Stack::Top(){
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

float Eval(float v1,float v2, char op){
    switch(op){
        case '+':return (v1+v2);
        case '-':return (v1-v2);
        case '*':return (v1*v2);
        case '/':return (v1/v2);
        case '^':return pow(v1,v2);
        default:return 0;
    }
}


int main()
{
    int exp_len=15;
    //char infix[exp_len]={'2','3','9','*','8','1','4','^','/','2','*','-','7','*','+'};
    char infix[exp_len]={'6','2','3','+','-','3','8','2','/','+','*','2','^','3','+'};
    //char infix[exp_len]={'2','3','+','1','*','5','2','-','4','6','+','*','-'};
    Stack s1;
    int i=0,j=0,k=0;
    float val1,val2,rslt;
    //printf("h%df",j);
    cout<<"\tSymbol\t"<<"\tValue1\t"<<"\tValue2\t"<<"\tValue\t"<<"\tStack"<<endl;
    while(i<exp_len){
        cout<<"\t"<<infix[i];
        if(infix[i]=='+'||infix[i]=='-'||infix[i]=='*'||infix[i]=='/'||infix[i]=='^'){
            val1=(s1.pop());
            val2=(s1.pop());
            rslt=Eval(val2,val1,infix[i]);
            s1.push(rslt);
            cout<<"\t\t"<<val2<<"\t\t"<<val1<<"\t\t"<<rslt;

        }
        else{
            s1.push((infix[i]-'0'));
            cout<<"\t\t"<<""<<"\t\t"<<""<<"\t\t"<<"";
        }
        cout<<"\t\t";
        s1.Display();
        cout<<endl;
        i++;

    }


    return 0;
}
