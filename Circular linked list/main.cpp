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
        ListData Append(Node *);
        bool Insert(int,Node *);
        bool Remove(ListData);
        bool Replace(ListData,ListData,bool);
        void Merge(List *);
        void Display();



};


Node* List::Head(){
    return head;
}

ListData List::Append(Node *data){
    if(head->getNextNode()==nullptr){
        head->setNextNode(data);
        data->setNextNode(head->getNextNode());
    }
    else{

        //printf("\nA%X\n",head->getNextNode());
        Node *temp;
        temp=head->getNextNode();
        while(temp->getNextNode()!=head->getNextNode()){
            //printf("X=%d\n",temp->getData().getValue());
            temp=temp->getNextNode();
        };

        temp->setNextNode(data);
        data->setNextNode(head->getNextNode());
        //printf("\nA%X\n",data->getNextNode());
    }


}

bool List::Insert(int index,Node *data){
    int i=0;
    Node *temp;
    temp=head;
    if(head->getNextNode()==nullptr){
        head->setNextNode(data);
        data->setNextNode(head->getNextNode());
        return 1;
    }
    /*if(index==0){
        data->setNextNode(head->getNextNode());
        head->setNextNode(data);
        //printf("\td");
        return 1;

    }*/
    while(i<index){
        //printf("%d\n",i);

        if(temp->getNextNode()->getNextNode()==head->getNextNode()){
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
    if((head->getNextNode()==head->getNextNode()->getNextNode())&&(head->getNextNode()->getData().getValue()==data.getValue())){
        head->setNextNode(head);
        return 1;
    }
    while(temp->getNextNode()->getNextNode()!=head->getNextNode()){
        if(temp->getNextNode()->getData().getValue()==data.getValue()){
            if(temp->getNextNode()==head->getNextNode()){
                head->setNextNode(temp->getNextNode()->getNextNode());
                Node *t;
                t=temp;
                while(t->getNextNode()->getNextNode()!=head->getNextNode()){
                    t=t->getNextNode();
                }
                t->setNextNode(head->getNextNode());
            }
            else{
                temp->setNextNode(temp->getNextNode()->getNextNode());
            }
            return 1;
        }
        temp=temp->getNextNode();
    }
    //printf("\nN %d",temp->getData().getValue());
    if(temp->getNextNode()->getData().getValue()==data.getValue()){
        temp->setNextNode(head->getNextNode());
        return 1;
    }

    return 0;
}


bool List::Replace(ListData data1,ListData data2,bool all=0){
    Node *temp;
    temp=head->getNextNode();
    while(temp->getNextNode()!=head->getNextNode()){
        if(temp->getData().getValue()==data1.getValue()){
            temp->SetData(data2);
            if(all!=1){
                return 1;
            }
        }
        temp=temp->getNextNode();
    }
    if(temp->getData().getValue()==data1.getValue()){
            temp->SetData(data2);
    }
    return 0;
}

void List::Merge(List *lst){
    Node *temp;
    temp=head->getNextNode()->getNextNode();

    head->getNextNode()->setNextNode(lst->Head()->getNextNode()->getNextNode());
    lst->Head()->getNextNode()->setNextNode(temp);


}

void List::Display(){
    //printf("\nHead= %d",head->getData().value);
    Node node, *temp;
    temp=head->getNextNode();
    int indx=0;
    printf("\n\tIndex\tValue\n");
    while(temp->getNextNode()!=head->getNextNode()){
        printf("\t%d\t%d\n",indx++,temp->getData().getValue());
        temp=temp->getNextNode();
    }
    printf("\t%d\t%d\n",indx++,temp->getData().getValue());

}



int main()
{
    Node  node,*temp;
    List L,L1;
    ListData data;

    int choice,d,d1,indx,dis=0;

    /*while(1){
        cout<<"\n\t\tCircular Linked List\n"<<endl;
        cout<<"\tSelect operation:"<<endl<<endl;
        cout<<"\t1.Append data to List."<<endl;
        cout<<"\t2.Insert data to index."<<endl;
        cout<<"\t3.Remove data from list."<<endl;
        cout<<"\t4.Update data of list."<<endl;
        cout<<"\t5.Update data of list(all)."<<endl;
        cout<<"\t6.Display data of list."<<endl;
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
                L.Append(temp);
                break;
            }

            case 2:{
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

            case 3:{
                cout<<"\tEnter data to be removed:"<<endl;
                cout<<"\t";
                cin>>d;
                data.setValue(d);
                if((L.Remove(data)==0)){
                   cout<<"\n\tSorry, Something went wrong."<<endl;
                }
                break;
            }

            case 4:{
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
                L.Replace(data,data1,1);
                break;
            }

            case 6:{
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

    data.setValue(11);
    temp=node.getListNode();
    temp->SetData(data);
    L.Append(temp);

    data.setValue(15);
    temp=node.getListNode();
    temp->SetData(data);
    L.Append(temp);

    data.setValue(18);
    temp=node.getListNode();
    temp->SetData(data);
    L.Append(temp);

    data.setValue(16);
    temp=node.getListNode();
    temp->SetData(data);
    L.Insert(2,temp);

    printf("\n\tFirst List:\n");
    L.Display();

    data.setValue(5);
    temp=node.getListNode();
    temp->SetData(data);
    L1.Append(temp);

    data.setValue(156);
    temp=node.getListNode();
    temp->SetData(data);
    L1.Append(temp);

    data.setValue(36);
    temp=node.getListNode();
    temp->SetData(data);
    L1.Append(temp);

    data.setValue(17);
    temp=node.getListNode();
    temp->SetData(data);
    L1.Insert(2,temp);

    printf("\n\n\tSecond List:\n");
    L1.Display();
    printf("\n\n\tMerged List:\n");

    L.Merge(&L1);

    int idx=0;
    Node *tmp;
    tmp=L.Head();
    printf("\n\tIndex\tValue\n");
    while(tmp->getNextNode()->getNextNode()!=L.Head()->getNextNode()){
        printf("\t%d\t%d\n",idx++,tmp->getNextNode()->getData().getValue());
        tmp=tmp->getNextNode();
    }
    printf("\t%d\t%d\n",idx++,tmp->getNextNode()->getData().getValue());


    return 0;
}
