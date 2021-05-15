#include <iostream>

using namespace std;
class number
{
    float num;
public:
    void get_num()
    {
        cout<<"Enter number:\n";
        cin>>num;
    }
    float extract()
    {
        return num;
    }
};

void find_result(float n1, float n2, float n3)
    {
        float ar[3],temp;
        ar[0]=n1;
        ar[1]=n2;
        ar[2]=n3;

        for (int i=0;i<2;i++)
        {
            for(int j=1;j<3;j++)
            {
                if(ar[i]>ar[j])
                {
                    temp=ar[j];
                    ar[j]=ar[i];
                    ar[i]=temp;
                }
            }
        }

        cout<<"Greater Number is: "<<ar[2]<<"\nSmaller Number is: "<<ar[0];

    }

int main()
{
    number n1,n2,n3;

    n1.get_num();
    n2.get_num();
    n3.get_num();

    find_result(n1.extract(),n2.extract(),n3.extract());

    return 0;
}
