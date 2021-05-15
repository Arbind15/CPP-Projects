#include <iostream>

using namespace std;

class Publication
{
protected:
    char title[100];
    float price;
public:
    void getdata()
    {
        cout<<"Enter the title: "<<endl;
        cin>>title;
        cout<<"Enter Price: "<<endl;
        cin>>price;
    }
    void putdata()
    {
        cout<<"Title: "<<title<<endl;
        cout<<"Price: "<<price<<endl;
    }

};


class Sales
{
protected:
    float sales[3];
public:
    void getdata()
    {
        cout<<"Enter three sales amount: "<<endl;
        for(int i=0;i<3;i++)
        {
            cin>>sales[i];
        }
    }
    void putdata()
    {
        cout<<"The sales amount are: "<<endl;
        for(int i=0;i<3;i++)
        {
            cout<<sales[i]<<endl;
        }

    }

};


class Book :public Publication,public Sales
{
protected:
    int pg_count;
public:
    void getdata()
    {
        Publication::getdata();
        Sales::getdata();
        cout<<"Enter the page of the book: "<<endl;
        cin>>pg_count;
    }
    void putdata()
    {
        Publication::putdata();
        cout<<"Page count of the book is: "<<pg_count<<endl;
        Sales::putdata();
    }

};


class Tape :public Publication,public Sales
{
protected:
    float ply_time;
public:
    void getdata()
    {
        Publication::getdata();
        Sales::getdata();
        cout<<"Enter the playing time of tape: "<<endl;
        cin>>ply_time;
    }
    void putdata()
    {
        Publication::putdata();
        Sales::putdata();
        cout<<"Playing time of tape is: "<<ply_time<<endl;
    }

};

int main()
{
    Book B;
    Tape T;
    B.getdata();
    B.putdata();
    T.getdata();
    T.putdata();
    return 0;
}
