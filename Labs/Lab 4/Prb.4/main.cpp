#include <iostream>

using namespace std;

class Date
{
    int day,month,year;
public:
    Date()
    {

    }

    Date(int y,int m, int d)
    {
        year=y;
        month=m;
        day=d;
    }

    ~Date()
    {

    }
    void display()
    {
        cout<<"Date is: "<<year<<"/"<<month<<"/"<<day<<endl;
    }
    Date get()
    {

    }
    void Set()
    {
        cout<<"Enter the Date be set(YYYY MM DD):"<<endl;
        cin>>year>>month>>day;
    }
};

class Time
{
    int hr,mi,sec;
public:
    Time()
    {

    }

    Time(int h,int m, int s)
    {
        hr=h;
        mi=m;
        sec=s;
    }

    ~Time()
    {

    }
    void display()
    {
        cout<<"Time is: "<<hr<<" hrs "<<mi<<" min "<<sec<<" sec "<<endl;
    }
    Time get()
    {

    }

    void Set()
    {
        cout<<"Enter the time be set(hr min sec):"<<endl;
        cin>>hr>>mi>>sec;
    }
};

class DateAndTime: public Date, public Time
{
public:

    DateAndTime()
    {

    }

    DateAndTime(int yr, int mn, int d, int hr, int mi, int s):Date(yr,mn,d),Time(hr,mi,s)
    {

    }

    void display()
    {
        Date::display();
        Time::display();
    }
};



int main()
{
    DateAndTime Watch(2057,10,14,9,35,35);
    Watch.display();
    Watch.Date::Set();
    Watch.Time::Set();
    Watch.display();

    return 0;
}
