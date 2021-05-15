#include <iostream>
#include <string>

using namespace std;

class ListData{
    private:
        int value;

        //char flag[10];
    public:
        void setValue(int Val1){
            value=Val1;
        }

        int getValue(){
            return value;
        }

};

class Node{
    private:
        ListData data;
        Node *nxt_node;
        Node *prev_node;
    public:
        Node* getListNode(){
            Node *n_ptr= new Node;
            return n_ptr;
        }

        void setNextNode(Node *n){
            nxt_node=n;
        }
        void setPreviousNode(Node *n){
            prev_node=n;
        }

        void SetData(ListData x){
            data.setValue(x.getValue());
        }
        ListData getData(){
            return data;
        }

        Node* getNextNode(){
            return nxt_node;
        }

        Node* getPreviousNode(){
            return prev_node;
        }

        void operator = (Node n){
            cout<<n.getData().getValue();
            data=n.getData();
        }
};


class List{

    private:
        Node node,*head;

    public:
        List(){
            ListData t;
            t.setValue(0);
            head=node.getListNode();
            head->SetData(t);
            head->setNextNode(nullptr);
            head->setPreviousNode(nullptr);
        }
        Node* Head();
        ListData AppendR(Node *);
        ListData AppendF(Node *);
        bool Insert(int,Node *);
        bool Remove(ListData);
        bool Replace(ListData,ListData,bool);
        Node operator[](int);
        void Display();
        void DisplayR();



};


Node* List::Head(){
    return head;
}



ListData List::AppendR(Node *data){
    if(head->getNextNode()==nullptr){
        head->setNextNode(data);
        data->setNextNode(nullptr);
        data->setPreviousNode(head);
    }
    else{
        Node *temp;
        temp=head;
        while(temp->getNextNode()!=nullptr){
            //printf("X=%d\n",temp->getData().value);
            temp=temp->getNextNode();
        }

        temp->setNextNode(data);
        data->setNextNode(nullptr);
        data->setPreviousNode(temp);
        //printf("X=%d\n",temp->getData().value);
    }
}

ListData List::AppendF(Node *data){
    Node *tmp;
    if(head->getNextNode()==nullptr){
        head->setNextNode(data);
        data->setNextNode(nullptr);
        data->setPreviousNode(head);
    }
    else{
        data->setNextNode(head->getNextNode());
        data->setPreviousNode(head);
        head->getNextNode()->setPreviousNode(data);
        head->setNextNode(data);
    }
}

bool List::Insert(int index,Node *data){
    int i=0;
    Node *temp;
    temp=head;
    while(i<index){
        //printf("%d\n",i);

        if(temp->getNextNode()->getNextNode()==nullptr){
        //if(temp->getNextNode()==nullptr){         //it will work as AppendR
            printf("\n\tList index out of range!\n");
            return 0;
        }
        temp=temp->getNextNode();
        i++;
    }

    /*printf("P %d\n",temp->getData().getValue());
    printf("V %d\n",temp->getNextNode()->getData().getValue());
    printf("N %d\n",temp->getNextNode()->getNextNode()->getData().getValue());*/


    data->setPreviousNode(temp);
    data->setNextNode(temp->getNextNode());
    temp->getNextNode()->setPreviousNode(data);
    temp->setNextNode(data);
}




bool List::Remove(ListData data){
    Node *temp;
    temp=head;
    while(temp->getNextNode()!=nullptr){

        if(temp->getNextNode()->getData().getValue()==data.getValue()){
            if(temp->getNextNode()->getNextNode()==nullptr){
                //printf("N=%d\n",temp->getNextNode()->getData().getValue());
                temp->setNextNode(nullptr);
            }
            else{
                /*printf("P=%d\n",temp->getData().getValue());
                printf("V=%d\n",temp->getNextNode()->getData().getValue());
                printf("N=%d\n",temp->getNextNode()->getNextNode()->getData().getValue());*/
                temp->getNextNode()->getNextNode()->setPreviousNode(temp);
                temp->setNextNode(temp->getNextNode()->getNextNode());


            }
            return 1;
        }
        temp=temp->getNextNode();
    }
    return 0;
}


bool List::Replace(ListData data1,ListData data2,bool all=0){
    Node *temp;
    temp=head;
    while(temp!=nullptr){
        if(temp->getData().getValue()==data1.getValue()){
            temp->SetData(data2);
            if(all!=1){
                return 1;
            }
        }
        temp=temp->getNextNode();
    }
    return 0;
}

void List::Display(){
    //printf("\nHead= %d",head->getData().value);
    Node node, *temp;
    temp=head->getNextNode();
    int indx=0;
    printf("\n\tIndex\tValue\n");
    while(temp!=nullptr){
        printf("\t%d\t%d\n",indx++,temp->getData().getValue());
        temp=temp->getNextNode();
    }
}

void List::DisplayR(){
    //printf("\nHead= %d",head->getData().value);
    Node node, *temp;
    temp=head;
    int indx=0;
    printf("\n\tIndex\tValue\n");
    while(temp->getNextNode()!=nullptr){
        indx++;
        temp=temp->getNextNode();
    }

    indx--;
    //printf("\t%d\tL%d\n",indx++,temp->getData().getValue());
    while(temp->getPreviousNode()!=nullptr){
        printf("\t%d\t%d\n",indx--,temp->getData().getValue());
        temp=temp->getPreviousNode();
    }
}

Node List::operator[](int index){
    int i=0;
    Node *temp;
    temp=head;
    while(i<index){
        if(temp->getNextNode()->getNextNode()==nullptr){
        //if(temp->getNextNode()==nullptr){         //it will work as AppendR
            printf("\n\tList index out of range!\n");
            return Node();
        }
        temp=temp->getNextNode();
        i++;
    }
    return *temp->getNextNode();
}



int main()
{
    Node  node,*temp;
    List L;
    ListData data;

    int choice,d,d1,indx,dis=0;

    /*while(1){
        cout<<"\n\t\tLinked List\n"<<endl;
        cout<<"\tSelect operation:"<<endl<<endl;
        cout<<"\t1.Append data to front."<<endl;
        cout<<"\t2.Append data to rare."<<endl;
        cout<<"\t3.Insert data to index."<<endl;
        cout<<"\t4.Remove data from list."<<endl;
        cout<<"\t5.Update data of list."<<endl;
        cout<<"\t6.Update data of list(all)."<<endl;
        cout<<"\t7.Display data of list."<<endl;
        cout<<endl;
        cout<<"\t";
        cin>>choice;
        switch(choice){
            case 1:{
                cout<<"\tEnter data:"<<endl;
                cout<<"\t";
                cin>>d;
                data.setValue(d);
                temp=node.getListNode();
                temp->SetData(data);
                L.AppendF(temp);
                break;
            }

            case 2:{
                cout<<"\tEnter data:"<<endl;
                cout<<"\t";
                cin>>d;
                data.setValue(d);
                temp=node.getListNode();
                temp->SetData(data);
                L.AppendR(temp);
                break;
            }

            case 3:{
                cout<<"\tEnter Index:"<<endl;
                cout<<"\t";
                cin>>indx;
                cout<<"\tEnter Data:"<<endl;
                cout<<"\t";
                cin>>d;
                data.setValue(d);
                temp=node.getListNode();
                temp->SetData(data);
                L.Insert(indx,temp);
                break;
            }

            case 4:{
                cout<<"\tEnter data to be removed:"<<endl;
                cout<<"\t";
                cin>>d;
                data.setValue(d);
                if((L.Remove(data)==0)){
                   cout<<"\n\tSorry, Something went wrong."<<endl;
                }
                break;
            }

            case 5:{
                cout<<"\tEnter data to be replaced:"<<endl;
                cout<<"\t";
                cin>>d;
                data.setValue(d);
                cout<<endl;
                cout<<"\tEnter data to be replaced:"<<endl;
                cout<<"\t";
                cin>>d1;

                ListData data1;
                data1.setValue(d1);
                L.Replace(data,data1);
                break;
            }

            case 6:{
                cout<<"\tEnter data to be replaced:"<<endl;
                cout<<"\t";
                cin>>d;
                data.setValue(d);
                cout<<endl;
                cout<<"\tEnter data to be replaced:"<<endl;
                cout<<"\t";
                cin>>d1;
                ListData data1;
                data1.setValue(d1);
                L.Replace(data,data1,1);
                break;
            }

            case 7:{
                 dis=1;
                 cout<<"\n\tCurrent List is:"<<endl;
                 L.Display();
                 break;
            }

            default:{
                cout<<"\n\tInvalid input."<<endl;
                break;
            }

        }
        cout<<endl;
        if(dis==0){
            cout<<"\n\tCurrent List is:"<<endl;
            L.Display();
        }
        dis=0;

        cout<<endl;
        cout<<"\t";
        system("pause");

        system("cls");
    }*/


    data.setValue(89);
    temp=node.getListNode();
    temp->SetData(data);
    L.AppendR(temp);

    data.setValue(81);
    temp=node.getListNode();
    temp->SetData(data);
    L.AppendR(temp);

    data.setValue(899);
    temp=node.getListNode();
    temp->SetData(data);
    L.AppendF(temp);



    data.setValue(15);
    temp=node.getListNode();
    temp->SetData(data);
    L.AppendR(temp);

    data.setValue(88);
    temp=node.getListNode();
    temp->SetData(data);
    L.AppendR(temp);

    data.setValue(809);
    temp=node.getListNode();
    temp->SetData(data);
    L.Insert(2,temp);


    data.setValue(899);
    L.Remove(data);
    //cout<<L.Head()->getData().getValue();

    L.Display();

    //L.DisplayR();
    L[3]=L[1];

    L.Display();



    return 0;
}
