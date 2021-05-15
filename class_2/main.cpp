#include <iostream>
#include <stdio.h>

using namespace std;
class _class
{
private:
    char rem;
    float mar;
public:
    char name[50], add[60];
    int rol;
    float sci, math, eng;

    void display()
    {
       printf("Name: %s, Roll: %d",name,rol);
    }
    float per()
    {
        mar=sci+math+eng;
        return (mar/300)*100;
    }
    char remak()
    {
        if(per()<40.0)
        {
            return 'F';
        }
        else
        {
            return 'P';
        }
    }

};

int main()
{
    int size1,i=0;
    cout <<"Enter the number of Student:";
    cin>>size1;
    _class stu[size1];
    while(i<size1)
    {
        cout<<"Enter name:";
        cin>>stu[i].name;
        cout<<"Enter roll:";
        cin>>stu[i].rol;
        cout<<"Enter mark in three subjects:\n";
        cin>>stu[i].eng>>stu[i].math>>stu[i].sci;
        i++;
    }
    i=0;
    while(i<size1)
    {

        cout<<"Percentage of " <<stu[i].name <<"(Roll No.: "<<stu[i].rol<<")" <<" is:"<<stu[i].per()<<"%. And he is: "<<stu[i].remak()<<"\n";
        i++;
    }

    return 0;
}
