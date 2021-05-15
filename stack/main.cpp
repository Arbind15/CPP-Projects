#include <iostream>
#define Size 3
using namespace std;

class Stack{
    private:
        int container[Size],cursor=-1;

    public:
        int push();
        int pop();
        void Display();
};

int Stack::pop(){
    if(cursor<=-1){
        cout<<"Sorry, Stack is empty"<<endl;
    }
    else{
        cursor--;
        cout<<"Successfully popped: "<<container[cursor+1]<<endl;
    }
}

int Stack::push(){
    int tmp;
    //cout<<"cursor"<<cursor<<endl;
    if(cursor>=(Size-1)){

        cout<<"Sorry, Stack is full"<<endl;

    }
    else{
        cout<<"Enter number to be pushed:"<<endl;
        cin>>tmp;
        cursor++;
        container[cursor]=tmp;
        cout<<"Successfully pushed: "<<tmp<<endl;
    }
}

void Stack::Display(){

    cout<<"Current Stack is:"<<endl;
    for(int i=cursor;i>=0;i--){
        cout<<"\t"<<container[i]<<endl;
    }

}

int main()
{
    Stack s1;

    int choice;

    while(1){
        cout<<"\t\t\tStack Operation\n"<<endl;
        cout<<"1. Push"<<endl;
        cout<<"2. Pop"<<endl;
        cin>>choice;

        switch(choice){

        case 1:
            s1.push();
            break;
        case 2:
            s1.pop();
            break;
        default:
            cout<<"Enter valid choice"<<endl;
            break;

        }

        s1.Display();
        system("pause");
        system("cls");
    }

    return 0;
}
