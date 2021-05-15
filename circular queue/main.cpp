#include <iostream>
#define Size 5
using namespace std;

class Queue{
    private:
        int container[Size],Front=0,Rear=0;

    public:
        int enqueue();
        int dequeue();
        void Display();
};

int Queue::enqueue(){
    int tmp;
    if(((Rear+1)%Size)==Front){
        cout<<"\nSorry, Queue is Full"<<endl;
    }
    else{
        cout<<"\nEnter number to be Enqueued:"<<endl;
        cin>>tmp;
        Rear=(Rear+1)%Size;
        container[Rear]=tmp;
        cout<<"\nSuccessfully Enqueued: "<<container[Rear]<<endl;
    }
}

int Queue::dequeue(){

    //cout<<"cursor"<<cursor<<endl;
    if(Rear==Front){
        cout<<"\nSorry, queue is empty."<<endl;
    }
    else{
        Front=(Front+1)%Size;
        cout<<"\nSuccessfully Dequeued: "<<container[Front]<<endl;
    }
}

void Queue::Display(){
    //cout<<"\nCurrent Queue is:\n"<<Rear<<"\t"<<Front<<endl;
    cout<<"\nCurrent Queue is:\n"<<endl;
    if(Rear==Front){
        cout<<"\t\tEmpty!"<<endl;
        return;
    }
    //cout<<Rear<<endl;
    //cout<<Front<<endl;
    if(Rear==0){
        cout<<"\t\t"<<container[0];
        for(int i=(Size-1);i>Front;i--){
            cout<<"\t\t"<<container[i];
        }
        cout<<endl;
        return;
    }

    if(Rear<Front){
        for(int i=Rear;i>=0;i--){
            cout<<"\t\t"<<container[i];
        }
        for(int i=(Size-1);i>Front;i--){
            cout<<"\t\t"<<container[i];
        }
        cout<<endl;
        return;
    }

    for(int i=Rear;i>Front;i--){
        cout<<"\t\t"<<container[i];
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
        cout<<"3. Display"<<endl;
        cin>>choice;

        switch(choice){

        case 1:
            q1.enqueue();
            q1.Display();
            break;
        case 2:
            q1.dequeue();
            q1.Display();
            break;
        case 3:
            q1.Display();
            break;
        default:
            cout<<"\nEnter valid choice"<<endl;
            break;

        }
        printf("\n");
        system("pause");
        system("cls");
    }

    return 0;
}
