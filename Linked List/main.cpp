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
    public:
        Node* getListNode(){
            Node *n_ptr= new Node;
            return n_ptr;
        }

        void setNextNode(Node *n){
            nxt_node=n;
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
};


class List{

    private:
        Node node,*head,*tail;

    public:
        List(){

            /*tail= node.getListNode();
            tail->SetData(-1);
            tail->setNextNode(nullptr);*/
            ListData t;
            t.setValue(0);
            head=node.getListNode();
            head->SetData(t);
            head->setNextNode(nullptr);

        }
        Node* Head();
        ListData AppendR(Node *);
        ListData AppendF(Node *);
        bool Insert(int,Node *);
        bool Remove(ListData);
        bool Replace(ListData,ListData,bool);
        void Display();



};


Node* List::Head(){
    return head;
}



ListData List::AppendR(Node *data){
    if(head->getNextNode()==nullptr){
        head->setNextNode(data);
        data->setNextNode(nullptr);
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
        //printf("X=%d\n",temp->getData().value);
    }
}

ListData List::AppendF(Node *data){
    if(head->getNextNode()==nullptr){
        head->setNextNode(data);
        data->setNextNode(nullptr);
    }
    else{
        data->setNextNode(head->getNextNode());
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
    data->setNextNode(temp->getNextNode());
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
                //printf("N=%d\n",temp->getNextNode()->getNextNode()->getData().getValue());
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



int main()
{
    Node  node,*temp;
    List L;
    ListData data;

    int choice,d,d1,indx,dis=0;

    while(1){
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
    }

    /*data.setValue(11);
    temp=node.getListNode();
    temp->SetData(data);
    L.AppendF(temp);

    data.setValue(15);
    temp=node.getListNode();
    temp->SetData(data);
    L.AppendF(temp);

    data.setValue(18);
    temp=node.getListNode();
    temp->SetData(data);
    L.AppendF(temp);

    L.Display();

    data.setValue(16);
    temp=node.getListNode();
    temp->SetData(data);
    L.Insert(2,temp);

    L.Display();*/

    return 0;
}
