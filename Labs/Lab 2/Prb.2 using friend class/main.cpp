#include <iostream>

using namespace std;

class us_currency;

class nepal_currency
{
    float rs;

public:
    void read_rs()
    {
        cout<<"Enter currency(Rs):"<<endl;
        cin>>rs;
    }

    void show_rs()
    {
        cout<<"currency(Rs): "<<rs<<endl;

    }
    friend class us_currency;

};

class us_currency
{
    float dollar;
public:
    void read_usd()
    {
        cout<<"Enter currency(USD):"<<endl;
        cin>>dollar;
    }

    void show_us()
    {
        cout<<"currency(USD): "<<dollar<<endl;

    }



    bool operator >(nepal_currency np)
    {

    if((dollar*101.36)>np.rs)
        return 1;
    else
        return 0;

    }

    bool operator ==(nepal_currency np)
    {

    if((float)(dollar*101.36)==(float)np.rs)
        return 1;
    else
        return 0;
    }

};


int main()
{
    nepal_currency np;
    us_currency usd;
    np.read_rs();
    usd.read_usd();

    if(usd==np)
        cout<<"Both are equal!"<<endl;
    else if(usd>np)
        cout<<"USD is greater than Rs!"<<endl;
    else
        cout<<"RS is greater than !"<<endl;

    return 0;
}
