#include <iostream>

using namespace std;

class Time
{
    int hr,mi,sec;

public:
    Time(int H, int M, int S)
    {
        hr=H;
        mi=M;
        sec=S;
    }
    Time()
    {
        hr=0;
        mi=0;
        sec=0;
    }

    void show()
    {
        cout<<hr<<" : "<<mi<<" : "<<sec<<endl;
    }

    friend Time operator +(Time,Time);
    friend Time operator -(Time,Time);
    friend bool operator >(Time,Time);
};

Time operator +(Time t1, Time t2)
{
    Time t;
    t.sec=t1.sec+t2.sec;
    t.mi=t1.mi+t2.mi+(t.sec/60);
    t.hr=t1.hr+t2.hr+(t.mi/60);
    t.sec=t.sec%60;
    t.mi=t.mi%60;

    return t;
}

Time operator -(Time t1, Time t2)
{

    Time t;
    int T, T1, T2;
    /*if(t1.sec<t2.sec)
    {
        t1.sec=t1.sec+60;
        t1.mi=t1.mi-1;
        t.sec=t1.sec-t2.sec;
    }
    if(t1.sec>=t2.sec)
    {
        t.sec=t1.sec-t2.sec;
    }

    if(t1.mi<t2.mi)
    {
        t1.mi=t1.mi+60;
        t1.hr=t1.hr-1;
        t.mi=t1.mi-t2.mi;
    }
    if(t1.mi>=t2.mi)
    {
        t.mi=t1.mi-t2.mi;
    }

    if(t1.hr<t2.hr)
    {
        t.hr=t1.hr-t2.hr;
    }
    if(t1.mi>=t2.mi)
    {
        t.hr=t1.hr-t2.hr;
    }
*/
    T1=t1.hr*3600+t1.mi*60+t1.sec;
    T2=t2.hr*3600+t2.mi*60+t2.sec;
    T=T1-T2;

    if(T1<T2)
        T=-T;

    if((T/60.0)>1)
    {
        t.mi=int(T/60.0);
        t.sec=float(((T/60.0)-int(T/60.0))*60.0);
        //cout<<float(((T/60.0)-int(T/60.0))*60.0)<<endl;
    }
    else
    {
        t.sec=T;
    }

    if((t.mi/60.0)>1)
    {
        t.hr=float(t.mi/60.0);
        t.mi=float(((t.mi/60.0)-int(t.mi/60.0))*60);
    }
    else
    {
        t.hr=0;
    }
    return t;
}

bool operator >(Time t1,Time t2)
{
   float ts1,ts2;
   ts1=(t1.hr*60*60)+(t1.mi*60)+t1.sec;
   ts2=(t2.hr*60*60)+(t2.mi*60)+t2.sec;

   if(ts1>ts2)
   {
       return true;
   }
   else
   {
       return false;
   }
}

int main()
{
    Time t1(10,10,4),t2(9,15,3),t3;
    bool result;

    t3=t1-t2;
    t3.show();

    result=t1>t2;
    cout<<result<<endl;



    return 0;
}
