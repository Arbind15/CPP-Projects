#include <iostream>

using namespace std;

class Store
{
   int store,order;

   public:
       void get_order()
       {
            cout<<"Enter the store quantity: ";
            cin>>store;

            cout<<"Enter the order quantity: ";
            cin>>order;
       }
       void analyse_order()
       {
            if(store<order)
            {
                cout<<"No enough quantity";
            }
            else
            {
                if(store<=40)
                {
                    if(order>=16)
                    {
                        cout<<"You cannot order more than 16 item ";
                    }
                    else
                    {
                        cout<<"Your order is accepted";
                    }
                }
                else
                {
                    cout<<"Your order is accepted";
                }
             }

       }
};

int main()
{
    Store order1;

    order1.get_order();
    order1.analyse_order();

    return 0;
}
