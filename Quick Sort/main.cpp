#include <iostream>
#include<stdio.h>


using namespace std;

int orginal_arr[]={5,0,3,4,20};
int arr_size=sizeof(orginal_arr)/sizeof(orginal_arr[0]);



void DisplayArr(){
    for(int i=0;i<arr_size;i++){
        cout<<orginal_arr[i]<<"   ";
    }
    cout<<endl;
}

int Partition(int low, int high){
    int pivot=orginal_arr[high];
    int i=(low-1);

    cout<<"\nPivot = "<<pivot<<endl;

    for(int j=low;j<=(high-1);j++){
        if(orginal_arr[j]<=pivot){
            i++;

            cout<<"Since, "<<orginal_arr[j]<<" is less than pivot. Swap "<<orginal_arr[i]<<" and "<<orginal_arr[j]<<"\n\t";
            int temp;
            temp = orginal_arr[i];
            orginal_arr[i]=orginal_arr[j];
            orginal_arr[j]=temp;

            DisplayArr();

        }
    }

    cout<<"Swap "<<orginal_arr[i+1]<<" and "<<orginal_arr[high]<<"\n\t";
    int temp1;
    temp1 = orginal_arr[i+1];
    orginal_arr[i+1]=orginal_arr[high];
    orginal_arr[high]=temp1;
    DisplayArr();

    return i+1;

}

void QuickSort(int low, int high){
    if(low<high){
        int pi = Partition(low,high);
        cout << "\nCall QuickSort("<<low<<", "<<(pi-1)<<")"<<endl;
        QuickSort(low,pi-1);
        cout << "\nCall QuickSort("<<(pi+1)<<", "<<high<<")"<<endl;
        QuickSort(pi+1,high);
    }
    else{
        cout<<"Lower index is greater than higher index!!!\n";
    }
}




int main()
{
    cout << "\n\t\t\t\t\t\tQuick Sort\n" << endl;
    cout << "\nOriginal Array:\n\t";
    DisplayArr();
    cout << "Array Size= "<<arr_size<<endl;
    cout << "\nCall QuickSort(0, "<<(arr_size-1)<<")"<<endl;

    QuickSort(0,(arr_size-1));

    cout << "\nSorted Array:\n\t";
    DisplayArr();
    return 0;
}
