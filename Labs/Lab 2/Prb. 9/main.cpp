#include <iostream>

using namespace std;

class Matrix
{
    int m,n;
    int M[10][10];

public:
    void read()
    {
        cout<<"Enter number of row and column of matrix:"<<endl;
        cin>>m>>n;
        cout<<"Enter elements of matrix:"<<endl;
        for(int i=0;i<m;i++)
        {
            for (int j=0;j<n;j++)
            {
                cin>>M[i][j];
            }
        }
    }

    void display()
    {
        cout<<"Matrix is:"<<endl;
        for(int i=0;i<m;i++)
        {
            for (int j=0;j<n;j++)
            {
                cout<<M[i][j]<<"  ";
            }
            cout<<endl;
        }
    }

    friend Matrix operator +(Matrix,Matrix);
    friend bool is_valid (Matrix,Matrix);
};

Matrix operator +(Matrix m1,Matrix m2)
{
    Matrix m;
    m.m=m1.m;
    m.n=m1.n;
    for(int i=0;i<m.m;i++)
    {
        for(int j=0;j<m.n;j++)
        {
            m.M[i][j]=m1.M[i][j]+m2.M[i][j];
        }
    }

    return m;
}

bool is_valid(Matrix m1, Matrix m2)
{
    if((m1.m==m2.m)&&m1.n==m2.n)
        return true;
    else
        return false;
}

int main()
{
    Matrix m1,m2,m3;

    m1.read();
    m2.read();
    if (is_valid(m1,m2))
    {
        m3=m1+m2;
        m3.display();
    }
    else
        cout<<"Invalid matrices!!!";




    return 0;
}
