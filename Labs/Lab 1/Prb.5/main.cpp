#include <iostream>

using namespace std;

class employee
{

    char nam[100],emp_number[20];
    float basic,net_sal,income_tax=30,da=52;

public:
    void get_info()
    {
        cout << "Enter employee id:" << endl;
        cin>>emp_number;
        cout << "Enter employee name:" << endl;
        cin>>nam;
        cout << "Enter employee Basic Salary:" << endl;
        cin>>basic;

    }

    void com_net_sal()
    {

        net_sal=basic+((da/100)*basic)-((income_tax/100)*(basic+(da/100)*basic));
        cout << "Net salary of "<<nam<<" is "<< net_sal<< endl;
    }
};

int main()
{
    cout << "Enter number of employee:" << endl;
    int emp_num;
    cin>>emp_num;
    employee emp[emp_num];

    for(int i=0; i<emp_num;i++)
    {

        emp[i].get_info();
    }

    for(int i=0; i<emp_num;i++)
    {

        emp[i].com_net_sal();
    }

    return 0;
}
