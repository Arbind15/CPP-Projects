#include <iostream>
#define Size 3
using namespace std;

class Queue{
    private:
        int container[Size],Front=0,Rear=-1;

    public:
        int enqueue();
        int dequeue();
        void Display();
};

int Queue::enqueue(){
    int tmp;
    if(Rear>=(Size-1)){
        cout<<"Sorry, Queue is Full"<<endl;
    }
    else{
        cout<<"Enter number to be Enqueued:"<<endl;
        cin>>tmp;
        Rear++;
        container[Rear]=tmp;
        cout<<"Successfully Enqueued: "<<container[Rear]<<endl;
    }
}

int Queue::dequeue(){

    //cout<<"cursor"<<cursor<<endl;
    if(Rear<Front){
        cout<<"Sorry, queue is empty."<<endl;
    }
    else{
        cout<<"Successfully Dequeued: "<<container[Front++]<<endl;
    }
}

void Queue::Display(){

    cout<<"Current Queue is:"<<endl;
    //cout<<Rear<<endl;
    //cout<<Front<<endl;
    for(int i=Rear;i>=Front;i--){
        cout<<"\t"<<container[i];
    }
    cout<<endl;
}

int main()
{
    Queue q1;

    int choice;

    while(1){
        cout<<"\t\t\ Queue Operation\n"<<endl;
        cout<<"1. Enqueue"<<endl;
        cout<<"2. Dequeue"<<endl;
        cin>>choice;

        switch(choice){

        case 1:
            q1.enqueue();
            break;
        case 2:
            q1.dequeue();
            break;
        default:
            cout<<"Enter valid choice"<<endl;
            break;

        }

        q1.Display();
        system("pause");
        system("cls");
    }

    return 0;
}
