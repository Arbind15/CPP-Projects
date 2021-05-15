#include <iostream>

using namespace std;


class Student
{
protected:
    int rn;
    char name[20];
public:
    void getdata()
    {
        cout<<"Enter roll number:"<<endl;
        cin>>rn;
        cout<<"Enter name:"<<endl;
        cin>>name;
    }

    void putdata()
    {
        cout<<"Roll number: "<<rn<<endl;
        cout<<"Name: "<<name<<endl;
    }
};

class Internal_Exam : virtual public Student
{
protected:
    int m[7];

public:
    void getdata()
    {
        cout<<"Enter internal marks:"<<endl;
        for(int i=0;i<7;i++)
        {
            cin>>m[i];
        }

    }

    void putdata()
    {
        cout<<"Internal marks are:"<<endl;
        for(int i=0;i<7;i++)
        {
            cout<<m[i]<<endl;
        }
    }


};


class Final_Exam : virtual public Student
{
protected:
    int m[7];

public:
    void getdata()
    {
        cout<<"Enter final marks:"<<endl;
        for(int i=0;i<7;i++)
        {
            cin>>m[i];
        }

    }

    void putdata()
    {
        cout<<"Final marks are:"<<endl;
        for(int i=0;i<7;i++)
        {
            cout<<m[i]<<endl;
        }
    }


};

class Avg_Mark :public Internal_Exam,public Final_Exam
{
    float avgmark=0;
public:
    void getdata()
    {
        Student::getdata();
        Internal_Exam::getdata();
        Final_Exam::getdata();
    }

    void putdata()
    {
        Student::putdata();
        Internal_Exam::putdata();
        Final_Exam::putdata();
    }

    float getavg()
    {
        for(int i=0;i<7;i++)
        {
            avgmark+=Internal_Exam::m[i]+Final_Exam::m[i];
        }
        return avgmark;
    }
};

int main()
{
    Avg_Mark A;
    A.getdata();
    A.putdata();
    cout<<"Total marks is: "<<A.getavg()<<endl;
    return 0;
}
