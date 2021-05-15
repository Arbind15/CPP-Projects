#include <iostream>
#include<cstring>

using namespace std;

class Inventory
{
private:
    int quant;
    int reorder;
    double price;
    char *descrip;
public:
    Inventory(int q, int r, double p, char *d)
    {
        quant=q;
        reorder=r;
        price=p;
        descrip=new char[int(sizeof(d)+1)];
        strcpy(descrip,d);
    }
    ~Inventory()
    {
        delete []descrip;
    }
    void print()
    {
        cout<<"Total quantity: "<<quant<<endl;
        cout<<"Total reorder: "<<reorder<<endl;
        cout<<"Price: $ "<<price<<endl;
        cout<<"Description: "<<descrip<<endl;
    }
};

class Auto:public Inventory
{
    char *manufacture;
public:
    Auto(int q, int r, double p, char *d, char *man):Inventory(q,r,p,d)
    {
        strcpy(manufacture,man);
    }
    ~Auto()
    {
        delete []manufacture;
    }
    void print()
    {
        Inventory::print();
        cout<<"Manufacture: "<<manufacture<<endl;
    }
};

class Transmission:public Inventory
{
    char *vendor;
public:
    Transmission(int q, int r, double p, char * d, char *ven):Inventory(q,r,p,d)
    {
        vendor=new char[int(sizeof(ven)+1)];
        strcpy(vendor,ven);
    }

    ~ Transmission ()
    {
        delete []vendor;
    }
    void print()
    {
        Inventory::print();
        cout<<"Vendor is: "<<vendor<<endl;
    }
};

int main()
{
    Auto Car(5,2,15544.91,"Car obtained from the Toyota","Unknown");
    Car.print();
    Transmission T(25,10,1789.98,"Car obtained from the Toyota","Aztec Inc.");
    T.print();
    return 0;
}
