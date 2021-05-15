#include <iostream>
#include<cstdlib>
#include<conio.h>
#include<fstream>
#include<graphics.h>
#include<ctime>
#include<windows.h>
#define park_size 100

using namespace std;

class DateAndTime
{
    int yy,mm,dd,hr,mi,sec;
public:
    void getdateandtime()
    {
    	time_t now=time(0);
    	tm *ltm=localtime(&now);
    	yy=int(1900 + ltm->tm_year);
    	mm=int(1 + ltm->tm_mon);
    	dd=int(ltm->tm_mday);
    	hr=int(1 + ltm->tm_hour);
    	mi=int(1 + ltm->tm_min);
    	sec=int(1 + ltm->tm_sec);
        //cout<<"Enter current date and time(YYYY MM DD Hr Min Sec):"<<endl;
        //cout<<yy<<mm<<dd<<hr<<mi<<sec;
    }

    void showdateandtime()
    {
    	
        cout<<yy<<"/"<<mm<<"/"<<dd<<", "<<hr<<":"<<mi<<":"<<sec<<endl;

    }
    friend class Park;

};

class Car
{
    int car_number,flag=0,slot_num;
    char car_owner[200];
    DateAndTime in_date,out_date;
    friend class Park;
};

class Park
{
    static int car_count;
    Car park_area[park_size];

public:
    void add_car()
    {

        if(car_count>=park_size)
        {
            cout<<"Sorry no enough space available!!!"<<endl;
        }
        else
        {
            car_count++;
            for(int i=0;i<car_count;i++)
            {
                if(park_area[i].flag==0)
                {
                    cout<<"Enter Car number:"<<endl;
                    cin>>park_area[i].car_number;
                    cout<<"Enter Car owner name:"<<endl;
                    cin>>park_area[i].car_owner;
                    park_area[i].in_date.getdateandtime();
                    park_area[i].flag=1;
                    park_area[i].slot_num=i+1;
                    cout<<"Car added successfully:"<<endl;
                    system("pause");
                    return;
                }
            }

        }

    }

     void remove_car()
    {
        int temp_num;
        cout<<"Enter Car number to be removed:"<<endl;
        cin>>temp_num;
        for(int i=0;i<car_count;i++)
        {
            if(temp_num==park_area[i].car_number)
            {
                park_area[i].out_date.getdateandtime();
                calculate_charge(park_area[i]);
                park_area[i].flag=0;
                cout<<"Car number "<<temp_num<<" is removed successfully!!!"<<endl;
                system("pause");
                return;
            }
        }
        cout<<"No Car found!!!"<<endl;
        system("pause");

    }

    void showinfo()
    {
        bool temp=0;
        
        for(int i =0;i<car_count;i++)
        {
            if(park_area[i].flag==1)
            {
         		temp=1;
			}
    	}
    	
    	if(temp==0)
		{
			cout<<"There is no Car in the Park!!!"<<endl;
        	system("pause");
        	return;
		}
            
   		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2); //changing color of text
    	cout.setf(ios::left);
    	cout.width(8);
        cout<<left<<"S.No ";
		cout.width(15);
		cout<<left<<"Slot Number ";
		cout.width(50);
		cout<<left<<"Car Owner Name ";
		cout.width(20);
		cout<<left<<"Car Number ";
		cout.width(20);
		cout<<left<<"Entry Date and Time "<<endl;		
        
        for(int i =0;i<car_count;i++)
        {
            if(park_area[i].flag==1)
            {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
		    	cout.setf(ios::left);
		    	cout.width(8);
                cout<<left<<i+1;
				cout.width(15);
				cout<<left<<park_area[i].slot_num;
				cout.width(50);
				cout<<left<<park_area[i].car_owner;
				cout.width(20);
				cout<<left<<park_area[i].car_number;
				cout.width(0);
                park_area[i].in_date.showdateandtime();
        
            }
        }
        system("pause");

    }

    void calculate_charge(Car c)
    {
        double in_hr;
		in_hr=((c.in_date.yy*12*30*24)+(c.in_date.mm*30*24)
                          +c.in_date.dd*24+c.in_date.hr+(c.in_date.mi/60.0)+(c.in_date.sec/3600.0));
        double ou_hr;
		ou_hr=((c.out_date.yy*12*30*24)+(c.out_date.mm*30*24)
                          +c.out_date.dd*24+c.out_date.hr+(c.out_date.mi/60.0)+(c.out_date.sec/3600.0));

        double t_hr=ou_hr-in_hr;

		//cout<<in_hr<<" "<<ou_hr<<endl;
        if(t_hr<24.0)
            cout<<"Total parking hour is:"<<t_hr<<endl;
        else if(t_hr>=24)
            cout<<"Total parking day is:"<<(t_hr/24.0)<<endl;
        if(t_hr<=3.0)
            cout<<"Total parking charge is: $"<<t_hr*2<<endl;

        else if(t_hr>3.0&&t_hr<=24.0)
        {
            cout<<"Total parking charge is: $"<<((t_hr-3)*0.50)+(t_hr*2)<<endl;
        }

        else if(t_hr>24.0)
            cout<<"Total parking charge is: $"<<((t_hr/24.0)*8.0)<<endl;
        
        

    }

    void dump_objs()
    {
        ofstream fout;
        fout.open("park.dat",ios::out|ios::binary);

        for(int i=0; i<car_count;i++)
        {
            if(park_area[i].flag==1)
            {
                fout.write((char*)(&park_area[i]),sizeof(Car));
                //cout<<park_area[i].car_number<<endl;
            }


        }

         fout.close();
    }
    void load_objs()
    {
        Car c1;
        ifstream fin;
        fin.open("park.dat",ios::in|ios::binary);
        //cout<<fin<<endl;
        if(!fin)
        {
            cout<<"Error in loading previous file."<<endl;
        }

        else
        {
            int i=0;
            fin.read((char*)&c1,sizeof(c1)); //if this is not done then loop will go through one more iteration.
            while(!fin.eof())
            {
                //cout<<c1.car_number<<endl;
                park_area[i]=c1;
                fin.read((char*)&c1,sizeof(c1));
                ++i;

            }
            car_count=i;

        fin.close();
        }

    }
};
int Park::car_count=0;

int main()
{
    Park p;
    int choice;


    p.load_objs();
    int i=0;
    while(true)
    {
    	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),9);
    	cout.setf(ios::right);
    	cout.width(190);
        cout<<"WELCOME to MEHTA Garage!!!"<<endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
        while(1)
        {
        	char c;
        	c=getchar();
        	cout<<c;
		}
        cout<<"Enter your choice:"<<endl;
        cout<<"1. To add new car."<<endl;
        cout<<"2. To remove car."<<endl;
        cout<<"3. To view park information."<<endl;
        cout<<"4. To exit."<<endl;
        cin>>choice;
        system("CLS");

        switch(choice)
        {
        case 1:
            p.add_car();
            system ("CLS");
            break;

        case 2:
            p.remove_car();
            system ("CLS");
            break;

        case 3:
            p.showinfo();
            system ("CLS");
            break;

        case 4:
            p.dump_objs();
            cout<<"Thank you, Visit again!!!"<<endl;
            exit(1);

        default:
            cout<<"Invalid choice!!!"<<endl;
           system("pause");
            system ("CLS");

        }

    }
	
    return 0;
}

