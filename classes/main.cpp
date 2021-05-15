#include <iostream>

using namespace std;

class parent
{

public:
    int num;
    char nam[50];
    void display()
    {
        cout << "Number of member is:" << num <<"and parent name is:" << nam[0];
    }
};

int main()
{
    parent par1;
    par1.num=10;
    par1.nam[6]='Arbind';
    par1.display();
    return 0;
}
