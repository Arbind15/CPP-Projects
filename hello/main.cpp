#include <iostream>

using namespace std;

int main()
{
    char word[50];
    int i=0;
    cout << "Enter a word:";
    cin >> word;
    for(i=0;i<=225;i++)
    {
       cout << word <<"\t" <<i << "\n";
    }

    return 0;
}
