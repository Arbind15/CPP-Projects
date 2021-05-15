#include <iostream>

using namespace std;
class Area
{
    float len, bre , hei, rad;

public:
    void circle()
    {
        cout<<"Enter radius of circle:\n";
        cin>>rad;
        cout<<"Area of circle is: "<<3.14*rad*rad<<" sq. units."<<endl;
    }

    void triangle()
    {
        cout<<"Enter base and height of triangle:\n";
        cin>>bre>>hei;
        cout<<"Area of triangle is: "<<0.5*bre*hei<<" sq. units."<<endl;
    }

    void square()
    {
        cout<<"Enter length of Square:\n";
        cin>>len;
        cout<<"Area of square is: "<<len*len<<" sq. units."<<endl;
    }

    void rectangle()
    {
        cout<<"Enter length and breadth of rectangle:\n";
        cin>>len>>bre;
        cout<<"Area of rectangle is: "<<len*bre<<" sq. units."<<endl;
    }
};

int main()
{
    char choice;
    Area Shape;
    cout<<"Enter your choice(c, r, t, s):"<<endl;
    cin>>choice;

    switch(choice)
    {
    case 'c':
        Shape.circle();
        break;

    case 't':
        Shape.triangle();
        break;

    case 's':
        Shape.square();
        break;

    case 'r':
        Shape.rectangle();
        break;

    default:
        cout<<"Please enter valid choice!";
        break;
    }





    return 0;
}
