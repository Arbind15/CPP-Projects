#include <iostream>
#include <string>
#include<math.h>

using namespace std;

class ListData{
    private:
        int power,base;

    public:
        void setValue(int bas, int pow){
            power=pow;
            base=bas;
        }

        int getBase(){
            return base;
        }
        int getPower(){
            return power;
        }

        bool operator==(ListData d1){
            if(d1.base==base&&d1.power==power){
                return 1;
            }
            else{
                return 0;
            }
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
            data=x;
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
            //cout<<n.getData().getValue();
            data=n.getData();
        }
};


class List{

    private:
        Node node,*head;

    public:
        List(){
            ListData t;
            t.setValue(0,0);
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
        int Length();

        char* operator = (char *);

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

    data->setPreviousNode(temp);
    data->setNextNode(temp->getNextNode());
    temp->getNextNode()->setPreviousNode(data);
    temp->setNextNode(data);
}




bool List::Remove(ListData data){
    Node *temp;
    temp=head;
    while(temp->getNextNode()!=nullptr){

        if(temp->getNextNode()->getData()==data){
            if(temp->getNextNode()->getNextNode()==nullptr){
                //printf("N=%d\n",temp->getNextNode()->getData().getValue());
                temp->setNextNode(nullptr);
            }
            else{
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
        if(temp->getData()==data1){
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
    printf("\n\tIndex\tBase\tPower\n");
    while(temp!=nullptr){
        printf("\t%d\t%d\t%d\n",indx++,temp->getData().getBase(),temp->getData().getPower());
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
        printf("\t%d\t%d\n",indx--,temp->getData().getBase());
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

char* List::operator=(char *c){
    int i=0;
    while(*c!='\0'){
        cout<<*c<<endl;
        c++;
        i++;
    }

}

int List::Length(){
    Node node, *temp;
    temp=head;
    int indx=0;
    while(temp->getNextNode()!=nullptr){
        indx++;
        temp=temp->getNextNode();
    }
    return indx;
}


void ArrayToLinkedList(char *S1, List *L){
    int i=0,j=0,k,Sum1,Sum2;
    ListData data;
    Node  node,*temp;

    while(S1[i]!='\0'){
        if(S1[i]=='+'||S1[i]=='-'){
            j++;
            k=0;
            Sum1=0;
            Sum2=0;

            temp=node.getListNode();

            while(S1[j]!='+'&&S1[j]!='-'&&S1[j]!='x'&S1[j]!='\0'){
                //cout<<int(S1[j]-'0');
                Sum1=Sum1*10+int(S1[j]-'0');
                j++;
                k++;
            }
            if(S1[i]=='-'){
                Sum1=-Sum1;
            }
            //cout<<Sum1;
            data.setValue(Sum1,0);
            //cout<<endl;
            if(S1[j]=='x'){
                //cout<<"d";
                if(S1[j+1]=='^'){
                    //cout<<"d";
                    j=j+2;
                    k=0;
                    Sum2=0;
                    while(S1[j]!='+'&&S1[j]!='-'&&S1[j]!='x'&&S1[j]!='\0'){
                        Sum2=Sum2*10+int(S1[j]-'0');
                        j++;
                    }
                    //cout<<Sum2;
                    data.setValue(Sum1,Sum2);
                    Sum2=0;
                }
                else{
                   data.setValue(Sum1,1);
                }
            }
            temp->SetData(data);
            L->AppendR(temp);
            i=j;
            continue;
        }

        if(S1[i]!='+'&&S1[i]!='-'&&S1[i]!='x'&&S1[i]!='^'){
            k=0;
            Sum1=0;
            Sum2=0;

            temp=node.getListNode();
            while(S1[j]!='+'&&S1[j]!='-'&&S1[j]!='x'&&S1[j]!='\0'){
                Sum1=Sum1*10+int(S1[j]-'0');
                j++;
            }
            //cout<<Sum1;

            data.setValue(Sum1,0);
            //cout<<endl;
            if(S1[j]=='x'){
                //cout<<"c";
                if(S1[j+1]=='^'){
                    //cout<<"c";
                    j=j+2;
                    k=0;
                    Sum2=0;
                    while(S1[j]!='+'&&S1[j]!='-'&&S1[j]!='x'&&S1[j]!='\0'){
                        Sum2=Sum2*10+int(S1[j]-'0');
                        j++;
                    }
                    //cout<<Sum2;
                    data.setValue(Sum1,Sum2);
                    Sum2=0;
                    //cout<<endl;
                }
                else{
                   data.setValue(Sum1,1);
                }
            }

            temp->SetData(data);
            L->AppendR(temp);
            i=j;
            continue;
        }
        i++;
        j++;
    }
}


int main()
{
    Node  node,*temp;
    List Pol1,Pol2,Pol3;
    ListData data;
    int base,power;
    char S1[20],S2[20];
    int indx;


    cout<<"\n\t(Note exponentiation is denoted by '^' and coefficient '1' should be provided explicitly !)\n"<<endl;
    cout<<"\n\tEnter first polynomial F(x):"<<endl;
    cout<<"\t";
    cin>>S1;
    ArrayToLinkedList(S1,&Pol1);

    cout<<"\n\tEnter second polynomial F(x):"<<endl;
    cout<<"\t";
    cin>>S2;
    ArrayToLinkedList(S2,&Pol2);

    cout<<"\n\tLinked list representation of first polynomial:"<<endl;
    Pol1.Display();
    cout<<"\n\tLinked list representation of second polynomial:"<<endl;
    Pol2.Display();


    for(int i=0;i<Pol1.Length();i++){
            for(int j=0;j<Pol2.Length();j++){
                if(Pol1[i].getData().getPower()==Pol2[j].getData().getPower()){
                    data.setValue((Pol1[i].getData().getBase()+Pol2[j].getData().getBase()),Pol1[i].getData().getPower());
                    temp=node.getListNode();
                    temp->SetData(data);
                    Pol3.AppendR(temp);
                }
            }
    }

    int flag=0;
    for(int i=0;i<Pol1.Length();i++){
            for(int j=0;j<Pol3.Length();j++){
                if(Pol1[i].getData().getPower()==Pol3[j].getData().getPower()){
                    flag=1;
                }
            }
            if(flag!=1){
                data.setValue(Pol1[i].getData().getBase(),Pol1[i].getData().getPower());
                temp=node.getListNode();
                temp->SetData(data);
                Pol3.AppendR(temp);
            }
            flag=0;
    }
    flag=0;
    for(int i=0;i<Pol2.Length();i++){
            for(int j=0;j<Pol3.Length();j++){
                if(Pol2[i].getData().getPower()==Pol3[j].getData().getPower()){
                    flag=1;
                }
            }
            if(flag!=1){
                data.setValue(Pol2[i].getData().getBase(),Pol2[i].getData().getPower());
                temp=node.getListNode();
                temp->SetData(data);
                Pol3.AppendR(temp);
            }
            flag=0;
    }
    cout<<"\n\tLinked list representation of sum of above polynomial:"<<endl;
    Pol3.Display();

    cout<<"\n\tSum of above polynomial is F(x) = ";

    for(int i=0;i<Pol3.Length();i++){
        if(Pol3[i].getData().getPower()>=2){
            cout<<" + "<<Pol3[i].getData().getBase()<<"x^"<<Pol3[i].getData().getPower()<<" ";
        }
        else if(Pol3[i].getData().getPower()==1){
            cout<<" + "<<Pol3[i].getData().getBase()<<"x ";
        }
        else if(Pol3[i].getData().getPower()==0){
            cout<<" + "<<Pol3[i].getData().getBase()<<" ";
        }
    }
    cout<<endl<<endl;
    return 0;
}
