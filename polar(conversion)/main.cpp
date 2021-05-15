#include <iostream>
#include<math.h>

using namespace std;

class polar;
class rectangular; //class declaration

class polar
{
    float rad,ang;
public:
    polar()
    {
        rad=0;
        ang=0;
    }
    polar(float a, float b)
    {
        rad=a;
        ang=b;
    }
    float getrad()
    {
        return rad;
    }
    float getang()
    {
        return ang;
    }
    void display()
    {
        cout<<"("<<rad<<", "<<ang<<")\n";
    }
    polar operator+(polar);
    //yaha function define garda -fpermessive error phalxa!!!



};


polar polar::operator+(polar p) //for direct addition which is invalid for polar
    {
        polar temp;
        temp.rad=rad+p.rad;
        temp.ang=ang+p.ang;

        return (temp);
    }



class rectangular //for converting polar into rectangular coordinates to perform addition
{
    float x,y;
public:
    rectangular()
    {
        x=0;
        y=0;
    }
    rectangular(float a, float b)//constructor
    {
        x=a;
        y=b;
    }
    float gertx(){return x;}
    float gety(){return y;}
    rectangular(polar p)//class conversion
    {
        x=p.getrad()*(cos(p.getang()));
        y=p.getrad()*(sin(p.getang()));

    }
    rectangular operator+(rectangular);

    polar(rectangular R) //defining constructor for type(polar to rectangular) conversion
    {
        ang=atan(R.gety()/R.gertx());
        rad=sqrt((R.gertx()*R.gertx())+(R.gety()*R.gety()));
    }

};
 rectangular rectangular::operator+(rectangular R) //overloading +
    {
        rectangular temp;
        temp.x=x+R.x;
        temp.y=y+R.y;

        return (temp);
    }






int main()
{
    polar p3;
    float a,b;

    cout<<"Enter first polar coordinates:";
    cin>>a>>b;
    polar p1(a,b);
    cout<<"Enter second polar coordinates:";
    cin>>a>>b;
    polar p2(a,b);
    cout<<"You have entered:\n";
    p1.display();
    p2.display();
    //p3=p1+p2;//overloaded + operator since p1 and p2 are not built in data-types
    rectangular R1=rectangular(p1);
    rectangular R2=rectangular(p2);
    rectangular R3=R1+R2;// or p3=R2+R2
    p3=R3;
    cout<<"And sum is:\n";
    p3.display();
    return 0;
}
