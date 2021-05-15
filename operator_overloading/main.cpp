#include <iostream>

using namespace std;

class counter
{
    int coun;
public:
    counter()       //default constructor (without argument)
    {
        coun=0;
    }

    counter(int c)  //counter with argument
    {
        coun=c;
    }

    ~counter()
    {
        cout<<"Destructor is called!!"<<endl;
    }

    void show_count()
    {
        cout<<coun<<endl;
    }

/*  void operator ++()
    {
        ++coun;
    }

    void operator --(int) //int is used to distinguish between pre and post increment
    {
        coun--;
    }
*/

    counter operator --(int) //int is used to distinguish between pre and post increment
    {
        counter temp;
        temp.coun=coun--;
        return temp;
    }

    counter operator ++()
    {
        return counter (++coun); //here hidden object is constructed and paranthesis is required as it is function call
    }
};

int main()
{
    counter c1,c2(20),c3,c4;

    ++c1;
    c2--;
    c1.show_count();
    c2.show_count();

    c3=++c1;
    c4=c2--;

    c1.show_count();
    c2.show_count();
    c3.show_count();
    c4.show_count();
    return 0;
}
