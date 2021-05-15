#include <iostream>

using namespace std;

class String
{
    int l;
    char strin[100];
public:
    void getdata()
    {
        cout<<"Enter number of character:"<<endl;
        cin>>l;

        cout<<"Enter character:"<<endl;
        cin>>strin;
        strin[l]='\0';
    }

    void showdata()
    {
        cout<<"Final string is: "<<endl;
        cout<<strin<<endl;
    }

    friend String operator +(String,String);
    friend bool operator ==(String,String);

};

String operator +(String s1,String s2)
{
    int i,j=0;
    String s;
    s.l=s1.l+s2.l;
    for(i=0;i<s1.l;i++)
    {
        s.strin[i]=s1.strin[i];
    }
    for(i+1;i<s.l;i++)
    {
        s.strin[i]=s2.strin[j];
        j++;
    }
    s.strin[i]='\n';
        return s;
}

bool operator ==(String s1, String s2)
{

        if(s1.l!=s2.l)
            return 0;

        for(int i=0;i<s1.l;i++)
        {
            if(int(s1.strin[i])!=int(s2.strin[i]))
            {
                    return 0;

            }

        }

        return 1;


}

int main()
{
    String s1,s2,s3;

    s1.getdata();
    s2.getdata();

    s3=s1+s2;
    s3.showdata();

    bool flag;//by default this is 0
    flag=(s1==s2);
    cout<<"Result of comparision is: "<<flag<<endl;

    return 0;
}
