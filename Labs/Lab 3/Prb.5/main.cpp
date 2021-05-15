#include <iostream>

using namespace std;



class Time12
{
    float hr,mi,sec;
    char ampm;
public:
    void getdata()
    {
        cout<<"Enter hr, min, sec (12) (ampm):"<<endl;
        cin>>hr>>mi>>sec>>ampm;
    }
    void show()
    {
        cout<<"12 hr format: "<<hr<<" hrs "<<mi<<" min "<<sec<<" secs "<<ampm<<endl;
    }

     Time12(){}



     float gethr(){return hr;}
    float getmi(){return mi;}
    float getsec(){return sec;}
};

class Time24
{
    float hr,mi,sec;
public:
    void getdata()
    {
        cout<<"Enter hr, min, sec (24):"<<endl;
        cin>>hr>>mi>>sec;
    }
    void show()
    {
        cout<<"24 hr format: "<<hr<<" hrs "<<mi<<" min "<<sec<<" secs "<<endl;
    }

    Time24(){}
         Time24(Time12 t12)
     {
         if(t12.gethr()<12)
            hr=t12.gethr()+12;
         else
            hr=t12.gethr();
         mi=t12.getmi();
         sec=t12.getsec();

     }

};



int main()
{
    Time12 t12;
    Time24 t24;
    t12.getdata();

    t24=t12;

    t24.show();

    return 0;
}
