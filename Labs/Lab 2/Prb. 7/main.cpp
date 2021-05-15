#include <iostream>

using namespace std;

class Time
{
    int hr,mi,sec;

public:
        friend istream & operator >>(istream &,Time &);
        friend ostream & operator <<(ostream &,Time);
};

istream & operator >> (istream &in ,Time &t1)
{
    cout<<"Enter time to be displayed:"<<endl;
    in>>t1.hr>>t1.mi>>t1.sec;

    return in;
}

ostream & operator << (ostream &out ,Time t1)
{
    cout<<"The time is:"<<endl;
    out<<t1.hr<<" hrs "<<t1.mi<<" min "<<t1.sec<<" secs";

    return out;
}

int main()
{
    Time t;
    cin>>t;
    cout<<t;
    return 0;
}
