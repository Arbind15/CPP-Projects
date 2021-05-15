#include <iostream>

using namespace std;

class Number2;

class Number1
{
    int num;
public:
    void get_num()
    {
        cout<<"Enter number:"<<endl;
        cin>> num;
    }
    void show_num()
    {
        cout<<"Numbers is: "<<num<<endl;
    }

    friend void swap_num(Number1 &,Number2 &);
};

class Number2
{
    int num;
public:
    void get_num()
    {
        cout<<"Enter number:"<<endl;
        cin>> num;
    }
    void show_num()
    {
        cout<<"Numbers is: "<<num<<endl;
    }

    friend void swap_num(Number1 &,Number2 &);
};

void swap_num(Number1 &n1, Number2 &n2)
{
    int temp;
    temp=n2.num;
    n2.num=n1.num;
    n1.num=temp;

}

int main()
{
    Number1 n1;
    Number2 n2;
    n1.get_num();
    n2.get_num();
    swap_num(n1,n2);
    n1.show_num();
    n2.show_num();

    return 0;
}
