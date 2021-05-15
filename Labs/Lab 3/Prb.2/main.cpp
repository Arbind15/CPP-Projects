#include <iostream>
#include <cmath>
using namespace std;



class Polar
{
    float ang,rad;
public:
    void getdata()
    {
        cout<<"Enter radius and angle: "<<endl;
        cin>>rad>>ang;
    }

    void showdata()
    {
        cout<<"Radius is: "<<rad<<endl<<"Angle is: "<<ang<<endl;
    }

    Polar(){}

    float getang(){return ang;}
    float getrad(){return rad;}

};



class Rectangluar
{
    float x,y;
public:
    void getdata()
    {
        cout<<"Enter x and y: "<<endl;
        cin>>x>>y;
    }

    void showdata()
    {
        cout<<"x is: "<<x<<endl<<"y is: "<<y<<endl;
    }

    Rectangluar(){}

    Rectangluar(Polar p)
    {
        x=p.getrad()*cos((p.getang()*3.14)/180);
        y=p.getrad()*sin((p.getang()*3.14)/180);
    }

};





int main()
{
    Polar p;
    Rectangluar r;

    p.getdata();

    r=p;

    r.showdata();

    return 0;
}
