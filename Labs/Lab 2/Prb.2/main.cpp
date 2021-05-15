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

    friend bool operator >(nepal_currency,us_currency);
    friend bool operator ==(nepal_currency,us_currency);

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

    friend bool operator >(nepal_currency,us_currency);
    friend bool operator ==(nepal_currency,us_currency);
};

bool operator >(nepal_currency np, us_currency usd)
{

    if((usd.dollar*101.36)<np.rs)
        return 1;
    else
        return 0;

}

bool operator ==(nepal_currency np,us_currency usd)
{

    if((float)(usd.dollar*101.36)==(float)np.rs)
        return 1;
    else
        return 0;
}

int main()
{
    nepal_currency np;
    us_currency usd;
    np.read_rs();
    usd.read_usd();

    if(np==usd)
        cout<<"Both are equal!"<<endl;
    else if(np>usd)
        cout<<"RS is greater than USD!"<<endl;
    else
        cout<<"USD is greater than RS!"<<endl;

    return 0;
}
