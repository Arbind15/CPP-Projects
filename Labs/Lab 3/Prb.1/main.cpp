#include <iostream>

using namespace std;

class NP
{
    float rup, pai;
public:
    void getrs()
    {
        cout<<"Enter Rs in Rupee and paisa: "<<endl;
        cin>>rup>>pai;
    }

    float getrup(){return rup;}
    float getpai(){return pai;}

};

class US
{
    float dol, cen;

public:
    US(NP np)
    {
        float tnp=np.getrup()+(np.getpai()/100);
        cen=(tnp/(98.51))*100;
        dol=int(cen/100);
        cen=((cen/100)-int(cen/100))*100;
    }
    US(){}  //default constructor

    void show()
    {
        cout<<"Equivalent USD is: "<<dol<<" $ "<<cen<<" cents "<<endl;
    }
};

int main()
{
    NP np;
    US us;

    np.getrs();

    us=np;

    us.show();

    return 0;
}
