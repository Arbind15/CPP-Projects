#include <iostream>

using namespace std;
class Person
{
protected:
    char name[100];
    float age;
    int id;
public:
    void readper()
    {
        cout<<"Enter name: "<<endl;
        cin>>name;
        cout<<"Enter age: "<<endl;
        cin>>age;
        cout<<"Enter id: "<<endl;
        cin>>id;
    }
    void showper()
    {
        cout<<"Name: "<<name<<endl;
        cout<<"Age: "<<age<<endl;
        cout<<"ID: "<<id<<endl;
    }
};

class Employee: public Person
{
protected:
    char deg;
    float bs,overtim,hr_rate;

public:
      void reademp()
    {
        readper();
        cout<<"Enter Deg: "<<endl;
        cin>>deg;
        cout<<"Enter Basic Salary: "<<endl;
        cin>>bs;
        cout<<"Enter overtime: "<<endl;
        cin>>overtim;
        cout<<"Hourly Rate: "<<endl;
        cin>>hr_rate;
    }
    void showemp()
    {
        showper();
        cout<<"Deg: "<<deg<<endl;
        cout<<"Basic Salary: "<<bs<<endl;
        cout<<"Overtime: "<<overtim<<endl;
        cout<<"Hourly Rate: "<<hr_rate<<endl;
    }
};

class ComputedSalary: public Employee
{


public:

    void showsal()
    {
        showemp();
        cout<<"Net Salary: "<<bs+(overtim*hr_rate)<<endl;
    }
};
int main()
{
    ComputedSalary e1;
    e1.reademp();
    e1.showsal();
    return 0;
}
