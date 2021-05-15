#include <iostream>

using namespace std;

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

    float gethr(){return hr;}
    float getmi(){return mi;}
    float getsec(){return sec;}
};


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

     Time12(Time24 t24)
     {

         if(t24.gethr()>12)
         {

             hr=(t24.gethr()-12);


             if(hr<12)
             {
                 ampm='P';
             }
             if(hr>12)
             {
                 ampm='A';
             }
         }
         else
         {
             hr=t24.gethr();
             ampm='A';
         }

         if(t24.gethr()==0)
             {
                 ampm='A';
                 hr=12;
             }

         mi=t24.getmi();
         sec=t24.getsec();

     }
};


int main()
{
    Time12 t12;
    Time24 t24;
    t24.getdata();

    t12=t24;

    t12.show();

    return 0;
}
