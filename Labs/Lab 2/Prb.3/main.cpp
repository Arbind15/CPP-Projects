#include <iostream>

using namespace std;

class Complex
{
    float rel, img;
public:
    Complex(float r,float i)
    {
        rel=r;
        img=i;
    }
    Complex()
    {

    }

    void show()
    {
        cout<<"Real Part: "<<rel<<endl;
         cout<<"Imaginary Part: "<<img<<endl;
    }

    friend Complex operator +(Complex,Complex);
    friend Complex operator +(Complex,float);
    friend Complex operator -(Complex,Complex);
    friend Complex operator *(Complex,Complex);
    friend Complex operator /(Complex,Complex);

};

Complex operator +(Complex c1,Complex c2)
{
    Complex temp;
    temp.rel=c2.rel+c1.rel;
    temp.img=c2.img+c1.img;

    return temp;
}

Complex operator -(Complex c1,Complex c2)
{
    Complex temp;
    temp.rel=c2.rel-c1.rel;
    temp.img=c2.img-c1.img;

    return temp;
}

Complex operator +(Complex c1,float f)
{
    Complex temp;
    temp.rel=c1.rel+f;
    temp.img=c1.img+f;

    return temp;
}

Complex operator *(Complex c1,Complex c2)
{

    //for complex multiplication (x+yi)(u+vi)=(x*u-y*v)+(x*v+y*u)i

    Complex temp;
    temp.rel=((c1.rel*c2.rel)-(c1.img*c2.img));
    temp.img=((c1.rel*c2.img)+(c1.img*c2.rel));

    return temp;
}
Complex operator /(Complex c1,Complex c2)
{
    //for complex division (a+ib)/(c+id)=((ac+bd)/(cc+dd))+((bc-ad)/(cc+dd))i

    Complex temp;
    temp.rel=(((c1.rel*c1.rel)+(c1.img*c2.img)) / ((c2.rel*c2.rel)+(c2.img*c2.img)));
    temp.img=(((c1.img*c2.rel)-(c1.rel*c2.img)) / ((c2.rel*c2.rel)+(c2.img*c2.img)));

    return temp;
}

int main()
{
    Complex c1(1,-1),c2(1,1),c3,c4,c5,c6,c7;

    c3=c1+c2;
    c4=c1-c2;
    c5=c1+100;
    c6=c1*c2;
    c7=c1/c2;

    /*c3.show();
    c4.show();
    c5.show();
    c6.show();*/
    c7.show();
    return 0;
}
