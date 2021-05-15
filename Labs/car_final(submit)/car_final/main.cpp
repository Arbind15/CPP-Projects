#include <iostream>
#include<cstdlib>
#include<conio.h>
#include<fstream>
#include <cwchar>
#include<ctime>
#include<windows.h>
#include<cmath>
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ENTER_KEY 13
#define ESC_KEY 27
#define park_size 100

using namespace std;

void SetCursorPosition(int, int);

float return_charge(float t_hr)
{
    float amt;
    if(t_hr<=3.0)
        amt=2.0;

    else if(t_hr>3.0&&t_hr<=24.0)
    {
        amt=((t_hr-3)*0.50)+(t_hr*2);
    }

    else if(t_hr>24.0)
        amt=((t_hr/24.0)*8.0);

    return amt;
}

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
    char car_owner[50];
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

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
        if(car_count>=park_size)
        {
            cout<<"Sorry no enough space available!!!"<<endl;
            getch();
        }
        else
        {
            car_count++;

            for(int i=0;i<car_count;i++)
            {
                if(park_area[i].flag==0)
                {


                    cout<<"Enter Car number:"<<endl;
                    int num;
                    cin>>num;
                    bool flg=0;
                    for(int j=0;j<car_count;j++)
                    {
                        if(park_area[j].car_number==num)
                            flg=1;
                    }
                    if(flg==1)
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
                        cout<<"Your Car Number must be Unique!!!"<<endl;
                        getch();
                        return;
                    }
                    park_area[i].car_number=num;
                    cout<<"Enter Car owner name:"<<endl;
                    cin.ignore();
                    cin.getline(park_area[i].car_owner,50);
                    park_area[i].in_date.getdateandtime();
                    park_area[i].flag=1;
                    park_area[i].slot_num=i+1;
                    cout<<"Car added successfully:"<<endl;
                    getch();
                    return;
                }
            }

        }

    }

     void remove_car()
    {
        int temp_num;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
        cout<<"Enter Car number to be removed:"<<endl;
        cin>>temp_num;
        for(int i=0;i<car_count;i++)
        {
            if((temp_num==park_area[i].car_number)&&(park_area[i].flag==1))
            {
                float payamt,actulamt;
                park_area[i].out_date.getdateandtime();
                calculate_charge(park_area[i]);
                cout<<"Make payment($): ";
                cin>>payamt;
                actulamt=calculate_charge(park_area[i],true);
                if(round(payamt)==round(actulamt))
                {
                    park_area[i].flag=0;
                    cout<<"Car number "<<temp_num<<" is removed successfully!!!"<<endl;
                    getch();
                    return;
                }
                else if(round(payamt)>round(actulamt))
                {
                    park_area[i].flag=0;
                    cout<<"Change Amount: $"<<payamt-actulamt<<endl;
                    cout<<"Car number "<<temp_num<<" is removed successfully!!!"<<endl;
                    getch();
                    return;
                }

                else if(round(payamt)<round(actulamt))
                {
                    cout<<"Payment is not enough!!!\n Exiting... "<<endl;
                    getch();
                    return;
                }

                //cout<<i+1;

            }
        }
        cout<<"No Car found!!!"<<endl;
        getch();

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
        	getch();
        	return;
		}


        int jump=0;
        int c,active;
		while(1)
        {

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
            SetCursorPosition(10,28);
            //cout<<jump;
            cout<<"Press (\"UP and DOWN Key\" to select, \"Enter\" to view info and \"ECS\" to goto main menu)"<<endl;
            SetCursorPosition(0,0);
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

            int j=0;
            for(int i =0;i<car_count;i++)
            {
                if(park_area[i].flag==1)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
                    if(jump==j)
                    {
                        active=i;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),30);
                    }

                    cout.setf(ios::left);
                    cout.width(8);
                    cout<<left<<j+1;
                    j=j+1;
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

            c=0;

            switch((c=getch()))
            {
                case KEY_UP:
                    jump-=1;
                    system("CLS");
                    break;
                case KEY_DOWN:
                    jump+=1;
                    system("CLS");
                    break;
                case ESC_KEY:
                    system("CLS");
                    return;
                case ENTER_KEY:
                    system("CLS");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                    cout.width(50);
                    cout<<left<<"Car Informations:"<<endl;
                    cout.width(50);
                    cout<<right<<"Slot Number: "<< left<<park_area[active].slot_num<<endl;
                     cout.width(50);
                    cout<<right<<"Car Number: "<< left<<park_area[active].car_number<<endl;
                     cout.width(50);
                    cout<<right<<"Car Owner Name: "<<left<< park_area[active].car_owner<<endl;
                     cout.width(50);
                    cout<<right<<"Entry Date and Time: "<<left;
                    park_area[active].in_date.showdateandtime();
                     cout.width(50);
                    cout<<right<<"Current Date and Time: ";
                    park_area[active].out_date.getdateandtime();
                    park_area[active].out_date.showdateandtime();
                    calculate_charge( park_area[active],false);
                    getch();
                    break;
                default:
                    break;
            }
            if(jump>=j)
            {
                jump=0;
            }
            if(jump<0)
            {
                jump=j-1;
            }


        }
        getch();

    }

    float calculate_charge(Car c,bool getamt=false)
    {
        double in_hr;
		in_hr=((c.in_date.yy*12*30*24)+(c.in_date.mm*30*24)
                          +c.in_date.dd*24+c.in_date.hr+(c.in_date.mi/60.0)+(c.in_date.sec/3600.0));
        double ou_hr;
		ou_hr=((c.out_date.yy*12*30*24)+(c.out_date.mm*30*24)
                          +c.out_date.dd*24+c.out_date.hr+(c.out_date.mi/60.0)+(c.out_date.sec/3600.0));

        double t_hr=ou_hr-in_hr;

        if(getamt)
            return return_charge(t_hr);
        else
        {
            //cout<<in_hr<<" "<<ou_hr<<endl;
            if(t_hr<24.0)
                cout<<"Total parking hour is: "<<t_hr<<endl;
            else if(t_hr>=24)
                cout<<"Total parking day is: "<<(t_hr/24.0)<<endl;
            if(t_hr<=3.0)
                cout<<"Total parking charge is: $2.0"<<endl;

            else if(t_hr>3.0&&t_hr<=24.0)
            {
                cout<<"Total parking charge is: $"<<((t_hr-3)*0.50)+(t_hr*2)<<endl;
            }

            else if(t_hr>24.0)
                cout<<"Total parking charge is: $"<<((t_hr/24.0)*8.0)<<endl;

        }
        return 0;
    }

    void dump_objs()
    {
        ofstream fout;
        fout.open("park.dat",ios::out|ios::binary);

        for(int i=0; i<car_count;i++)
        {
                fout.write((char*)(&park_area[i]),sizeof(Car));
                //cout<<park_area[i].car_number<<endl;

        }

         fout.close();
    }

    int get_slot_num()
    {
        int num=0;
        for(int i =0;i<car_count;i++)
        {
            if(park_area[i].flag==1)
            {
                num+=1;
            }
        }
        return num;
    }

    void load_objs()
    {
        Car c1;
        ifstream fin;
        fin.open("park.dat",ios::in|ios::binary);
        //cout<<fin<<endl;
        if(!fin)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
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

void SetCursorPosition(int x, int y)
{
    HANDLE output=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos={x,y};
    SetConsoleCursorPosition(output,pos);
}

int main()
{
    Park p;
    int choice;


    p.load_objs();
    int i=0;
    //SetCursorPosition(100,20);
    //cout<<"AKL";
    while(true)
    {
        int jump=0;
        while(1)
        {

            SetCursorPosition(90,28);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
            cout<<"Total Available Slot(s): "<<park_size-p.get_slot_num()<<endl;
            SetCursorPosition(0,0);


            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),9);
            cout<<"\n\n"<<endl;
            cout.setf(ios::right);
            cout.width(195);


            cout<<"WELCOME TO MEHTA GARAGE!!!\n\n"<<endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
            cout<<"\t\t   Please Select an Action:\n"<<endl;

            if(jump>3)
                jump=0;
            if(jump<0)
                jump=3;
            if(jump==0)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);
                cout<<"\t\t-> Add new car."<<endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                cout<<"\t\t   Remove car."<<endl;
                cout<<"\t\t   View park information."<<endl;
                cout<<"\t\t   Exit."<<endl;
            }
            else if(jump==1)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                cout<<"\t\t   Add new car."<<endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);
                cout<<"\t\t-> Remove car."<<endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                cout<<"\t\t   View park information."<<endl;
                cout<<"\t\t   Exit."<<endl;
            }

            else if(jump==2)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                cout<<"\t\t   Add new car."<<endl;
                cout<<"\t\t   Remove car."<<endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);
                cout<<"\t\t-> View park information."<<endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                cout<<"\t\t   Exit."<<endl;
            }

            else if(jump==3)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                cout<<"\t\t   Add new car."<<endl;
                cout<<"\t\t   Remove car."<<endl;
                cout<<"\t\t   View park information."<<endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);
                cout<<"\t\t-> Exit."<<endl;
            }



            int c = 0;
            switch((c=getch()))
            {
                case KEY_UP:
                    jump-=1;
                    break;
                case KEY_DOWN:
                    jump+=1;
                    break;
                case ENTER_KEY:
                    {
                        system("CLS");
                        switch(jump)
                        {
                        case 0:
                            p.add_car();
                            system ("CLS");
                            break;

                        case 1:
                            p.remove_car();
                            system ("CLS");
                            break;

                        case 2:
                            p.showinfo();
                            system ("CLS");
                            break;

                        case 3:
                            p.dump_objs();
                            cout<<"Thank you, Visit again!!!"<<endl;
                            exit(1);
                        default:
                            break;
                        }
                    }
                    break;
                default:
                    break;


            }
            system("CLS");

        }
        system("CLS");

    }

    return 0;
}
