#include <iostream>
#include <cstring>

using namespace std;

class String
{
    int l;
    char *strin;
public:

    ~String()
    {
        delete []strin;
        cout<<"deleted"<<endl;
    }

    void getdata()
    {
        cout<<"Enter number of character:"<<endl;
        cin>>l;
        strin=new char[l+1];
        cout<<"Enter character:"<<endl;
        cin>>strin;//cin.getline not working
    }

    void showdata()
    {
        cout<<"Final string is: ";
        cout<<strin<<endl;
    }

    String operator +(String s1)
    {
        String s;
        s.l=l+s1.l;
        s.strin=new char[s.l+1];
        strcpy(s.strin,strin);
        strcat(s.strin,s1.strin);
        return s;
    }

    bool operator ==(String s1)
    {

        if(s1.l!=l)
            return 0;

        for(int i=0;i<s1.l;i++)
        {
            if(int(s1.strin[i])!=int(strin[i]))
            {
                    return 0;

            }

        }

        return 1;


    }

    void operator =(String s1)
    {

    l=s1.l;
    strin =new char[l+1];
    for(int i=0;i<s1.l;i++)
    {
        strin[i]=s1.strin[i];
    }
        strin[l]='\0';
    }


};



int main()
{
    String s1,s2,s3;

    s1.getdata();
    s2.getdata();

    s3=s1+s2;
    s3.showdata();
    if(s1==s2)
        cout<<"Two string are same!"<<endl;
    else
        cout<<"Two string are not same!"<<endl;

    return 0;
}
