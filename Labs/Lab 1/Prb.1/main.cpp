#include <iostream>

using namespace std;
class Distance
{
    float feet,inch;
public:
    void getdata()
    {
        cout<<"Enter Distance(feet inch):"<<endl;
        cin>>feet>>inch;
    }

    void view_data()
    {
        cout<<"Distance is:"<<endl;
        cout<<feet<<"feet(s)\n"<<inch<<"inch(s)"<<endl;
    }
    void add_distance(Distance d1,Distance d2)
    {
        inch=d1.inch+d2.inch;
        if(inch>=12.0)
        {
            feet=d1.feet+d2.feet+(int)(inch/12.0);
            inch=(inch-((int)(inch/12.0)*12));
        }
        else
        {
            feet=d1.feet+d2.feet;
        }

    }
};

int main()
{
    Distance d1,d2,d3;

    d1.getdata();
    d2.getdata();
    d3.add_distance(d1,d2);
    d3.view_data();

    return 0;
}
