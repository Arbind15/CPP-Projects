#include <iostream>

using namespace std;

class employee
{
    static int eng_count,mng_count;
    char id[20],nam[100],deg;

public:
    void get_info()
    {
        cout << "Enter employee id:" << endl;
        cin>>id;
        cout << "Enter employee name:" << endl;
        cin>>nam;
        cout << "Enter employee Post\nEngineer- e\nManager-m:\nOther-0" << endl;
        cin>>deg;
        if(deg=='e')
        {
            eng_count++;
        }
        else if(deg=='m')
        {
            mng_count++;
        }
    }

    static int num_eng()
    {
        return eng_count;
    }
    static int num_mng()
    {
        return mng_count;
    }


};
int employee::eng_count;
int employee::mng_count;

void show_count(int eng_count, int mng_count, int emp_count)
    {
        cout<<"Total number of Engineer is "<<eng_count<<"\nTotal number of Manager is "<<mng_count<<"\nOther:"<<emp_count-(eng_count+mng_count);
        cout<<"\nTotal number of Employee is: "<<emp_count;
    }

int main()
{
    cout << "Enter number of employee:" << endl;
    int emp_num,coun[2];
    cin>>emp_num;
    employee e[emp_num];

    for (int i=0;i<emp_num;i++)
    {
        e[i].get_info();
        coun[0]=e[i].num_eng();
        coun[1]=e[i].num_mng();
    }
    show_count(coun[0],coun[1],emp_num);
    return 0;
}
