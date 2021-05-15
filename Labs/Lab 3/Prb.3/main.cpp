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
    Polar(float ra, float an)
    {
        rad=ra;
        ang=an;
    }

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

    operator Polar()        //cast operator in destinantion
    {
        float ra=sqrt((x*x)+(y*y));
        float an=atan(y/x); //returns in radian
        //ang=ang*(3.14/180);
        return Polar(ra,an);
    }
};





int main()
{
    Polar p;
    Rectangluar r;

    r.getdata();

    p=r;

    p.showdata();

    return 0;
}
