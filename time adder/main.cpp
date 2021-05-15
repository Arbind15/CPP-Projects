#include <iostream>

using namespace std;

class time
{
    int hr, mi, sec;
public:
    void get_time()
    {
        cin>>hr>>mi>>sec;
    }

    void show_time()
    {
        cout<<hr<<" hrs  "<<mi<<" min  "<<sec<<" secs";
    }
    void add_time(time t1, time t2)
    {
        sec=t1.sec+t2.sec;
        mi=t1.mi+t2.mi+sec/60;
        hr=t1.hr+t2.hr+mi/60;
        sec=sec%60;
        mi%=60;
    }
};

int main()
{
    time t1,t2,t3;
    cout << "Enter time" << endl;
    t1.get_time();
    cout << "Enter time" << endl;
    t2.get_time();
    t3.add_time(t1,t2);
    cout << "Sum is:" << endl;
    t3.show_time();
    return 0;
}
