#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include<iostream>
#include <gdiplus.h>
#include<sstream>
#include<io.h>
#include<stdio.h>
#include<conio.h>
#include<iostream>
#include<winsock2.h>
#include<thread>
#include<cstring>
#include<fstream>
#include<string>
#include<stdlib.h>
#define server_ip "192.168.43.156"
#define server_port 8858
#define REQUESTED_FRND 'f'
#define ATTACH_FIL 'g'
#define REC_LABEL 'x'
#define IDC_LISTBOX_TEXT 333
#define SEND 's'
#define REFRESH 'r'
#define PREVIEW 'w'
#define OLD_MSG 'o'
#define LOGIN 'e'
#define SIGNUPHOME 'c'
#define FILEMENU 'a'
#define HLPMNU 'b'
#define ACTREF 'q'
#define SIGNUP 'd'

using namespace Gdiplus;
using namespace std;

/*______________________________________Socket_Stuff______________________________*/

ofstream outfilesen,outfilerec;
ifstream infilesen,infilerec;
HMENU hmnu;
int n,selindx=0;
HWND  hndlrec, usr,pas,usl,psl,snup,lgn,emll,eml,pas2,psl2,cncl,ulo,plo,err,*rqfrn,listbox,cusr,re,sen,msgsen,attacfl,preview,actvref;
int linenums=70,linenumr=70,t_size=1024;
bool attfil=0,prevflg=0,exflg=0;
char rec[1024],msg[1024],temp[1024],data1[50000],data2[1024],buffer[1024];
char usrtxt[100],pastxt[100],emltxt[100],dir[200],recfilnam[200];
char filnam[200],frndnam[100];
void AddMnuHOME(HWND);
void AddCntrlHOME(HWND);
void AddcntrlSNUP(HWND);
void AddCntrlLOGIN(HWND);
int AddLoginStuff();
void create_own_Server();
void AddSignup(HWND);
void AddLogin(HWND);
void message_box(HWND);
void SendMsg(HWND);
void openfile(HWND);


class Socket
{
    WSADATA wsa;
    SOCKET s , new_socket;
    struct sockaddr_in server , client;
public:
    int Initilize_Winshock()
    {
        if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
        {
            printf("Failed. Error Code : %d",WSAGetLastError());
            return -1;
        }
    }

    SOCKET Create_Socket()
    {
        if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
        {
            printf("Could not create socket : %d" , WSAGetLastError());
            return INVALID_SOCKET;
        }
        return s;
    }

    void Prepare_Socket(char *IP, u_short PORT)
    {
        client.sin_family = AF_INET;
        client.sin_addr.s_addr = inet_addr(IP);
        client.sin_port = htons( PORT );
    }

    int Bind(char *IP, u_short PORT)
    {
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr(IP);
        server.sin_port = htons( PORT );

        if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
        {
            printf("Bind failed with error code : %d" , WSAGetLastError());
            return -1;
        }
    }

    int Listen(int number_of_backlock)
    {
        listen(s , number_of_backlock);
    }

    SOCKET Accept()
    {
        int c;
        c=sizeof(struct sockaddr_in);
        new_socket = accept(s, (struct sockaddr *)&client, &c);//&client and &c is optional argument

        if (new_socket == INVALID_SOCKET)
        {
            printf("accept failed with error code : %d" , WSAGetLastError());
            return 1;
        }

        return new_socket;
    }

    int Connect()
    {
        int iResult=connect(s, (struct sockaddr *)&client, sizeof(client));
        if(iResult<0)
        {
            printf("\nConnection Failed \n");
            exit(-1);
        }
        new_socket=s;
        return iResult;
    }


    int Send(char *Message,int Message_Size)
    {
        int iResult;
        iResult = send(new_socket, Message, Message_Size, 0);
        if (iResult == SOCKET_ERROR)
        {
            wprintf(L"send failed with error: %d\n", WSAGetLastError());
        }
        return iResult;
    }

    int Receive(char *buffer, int buffer_size)
    {
        int iResult;
        iResult=recv(new_socket,buffer,buffer_size,0);
        if ( iResult > 0 )
        {
            wprintf(L"Bytes received: %d\n", iResult);
            return iResult;
        }

        else if ( iResult == 0 )
        {
            wprintf(L"Connection closed\n");
            return iResult;
        }

        else
        {
             wprintf(L"recv failed with error: %d\n", WSAGetLastError());
             return WSAGetLastError();
        }
    }

    SOCKET return_New_socket()
    {
        return new_socket;
    }
    void Close()
    {
        closesocket(s);
        WSACleanup();
    }

};

Socket c_skt;
Socket s_skt;
Socket nclie;



class Recevclin{
public:
    void operator()(Socket s)
    {
        int iResult;
        char frn[200],te[200],filnam[1024];

        while(1)
        {
            char *rec;
            rec= new char[t_size];
            ofstream ofil;
            iResult = recv(s.return_New_socket(),rec,t_size,0);
            cout<<"Recevclin  "<<rec[0]<<endl;
            if(rec[0]=='F')
            {
                char ex[100],tt[100];
                cout<<"F ... "<<rec<<endl;
                exflg=0;
                strcpy(ex,strstr(rec,"F:")+2);
                strcpy(te,strstr(rec,":SIZE:")+6);
                ex[strlen(ex)-(strlen(te)+6)]='\0';
                t_size=atoi(te);

                cout<<"ex  "<<ex<<" t_size "<<t_size<<endl;
                if(exflg==0)
                {
                    strcpy(recfilnam,ex);
                    exflg=1;
                }
                ofil.open(ex,ios::out|ios::binary);

            }

            else if(rec[0]=='D')
            {
                    //recv(s.return_New_socket(),con,50000,0);
                    //cout<<con<<endl;
                    ofil.write(strstr(rec,"D:")+2,t_size-2);
                    prevflg=1;
                    ofil.close();
                    t_size=1024;
            }

            else
            {
                strcpy(frn,strstr(rec,"M:")+2);
                strcpy(te,strstr(frn,"::")+2);
                frn[strlen(frn)-(strlen(te)+2)]='\0';
                strcpy(filnam,frn);
                strcat(filnam,".txt");
                strcpy(te,strstr(rec,"::")+2);
                outfilerec.open(filnam,ios::app);
                outfilerec<<rec<<endl;
                //cout<<te<< "   n" <<endl;
                std::cout<<"Received(in thread): "<<frn<<"  "<<rec<<std::endl;
                outfilerec.close();
            }

            /*ofstream otemp;
            otemp.open("temp.txt",ios::app);
            otemp<<te<<endl;
            otemp.close();
            //SendMessage(hndlrec,(UINT)REC_LABEL,NULL,NULL);
            //SendMessageCallback(hndlrec,UINT(REC_LABEL),NULL,NULL,(SENDASYNCPROC)callbackfun,NULL);*/

            delete []rec;
        }
    }
};



class Recever{
public:
    void operator ()(Socket s)
    {
        int iResult;
        char frn[200],te[200],filnam[1024];
        //cout<<"Rececived stsrsted: "<<endl;
        while(true)
        {

            char *rec;
            rec=new char[t_size];
            char prt1[200],ip1[200],us[100];
            ofstream ofil;
            s.Receive(rec,t_size);
            cout<<"connected to Recever"<<rec<<endl;

            if(rec[0]=='C')
            {
                cout<<" c   ..insside our connet server"<<endl;
                //cout<<rec<<endl;

                strcpy(us,strstr(rec,"C:")+2);
                strcpy(ip1,strstr(rec,":IP:")+4);
                strcpy(prt1,strstr(rec,":PRT:")+5);
                us[strlen(us)-(strlen(ip1)+4)]='\0';
                ip1[strlen(ip1)-(strlen(prt1)+5)]='\0';

                cout<<us<<endl;
                cout<<ip1<<endl;
                cout<<prt1<<endl;
                //system("pause");
                cout<<"Connecting to requesting client...."<<endl;
/*_____________connecting to requested client_________________________*/

                nclie.Initilize_Winshock();
                nclie.Create_Socket();
                nclie.Prepare_Socket(ip1,atoi(prt1));
                nclie.Connect();
                char t[200];
                strcpy(t,"Hand shacked with ");
                strcat(t,usrtxt);
                nclie.Send(t,1024);
                cout<<"Sent"<<endl;
                //cout<<"bfr thrd"<<endl;
                //system("pause");
                /*thread sender((Sender()),nclie);
                sender.join();*/
                thread recver((Recevclin()),nclie);
                recver.detach();
                 //s_skt.Send("Done",1024);*/
            }
            else if(rec[0]=='H')
            {
                cout<<rec<<"(H  ..Testing)"<<endl;
                /*s_skt.Send("Don return",1024);
                thread recver((Recever()),s_skt);
                recver.detach();
                //cout<<"bfr thrd"<<endl;
                thread sender((Sender()),s_skt);
                sender.join();*/

            }
            else if(rec[0]=='M')
            {
                cout<<rec<<"(through server M)"<<endl;
                char frn[200],te[200],filnam[1024];
                strcpy(frn,strstr(rec,"M:")+2);
                strcpy(te,strstr(frn,"::")+2);
                frn[strlen(frn)-(strlen(te)+2)]='\0';
                strcpy(filnam,frn);
                strcat(filnam,".txt");
                strcpy(te,strstr(rec,"::")+2);
                outfilerec.open(filnam,ios::app);
                outfilerec<<rec<<endl;
                outfilerec.close();
                //s_skt.Send("Don return",1024);
                /*iResult = recv(s.return_New_socket(),rec,1024,0);
                strcpy(frn,strstr(rec,"M:")+2);
                strcpy(te,strstr(frn,"::")+2);
                frn[strlen(frn)-(strlen(te)+2)]='\0';
                strcpy(filnam,frn);
                strcat(filnam,".txt");
                outfilerec.open(filnam,ios::app);
                outfilerec<<rec<<endl;
                std::cout<<"Rececived: "<<frn<<std::endl;*/
                //cout<<"bfr thrd"<<endl;
                thread recvs((Recevclin()),s);
                recvs.detach();

            }
            else if(rec[0]=='F')
            {

                    char ex[100],tt[100];
                    cout<<"F ... "<<rec<<endl;
                    exflg=0;
                    strcpy(ex,strstr(rec,"F:")+2);
                    strcpy(te,strstr(rec,":SIZE:")+6);
                    ex[strlen(ex)-(strlen(te)+6)]='\0';
                    t_size=atoi(te+2);

                    cout<<"ex  "<<ex<<" t_size "<<t_size<<endl;
                    if(exflg==0)
                    {
                        strcpy(recfilnam,ex);
                        exflg=1;
                    }
                    ofil.open(ex,ios::out|ios::binary);
                }
            else if(rec[0]=='D')
            {
                    //recv(s.return_New_socket(),con,50000,0);
                    //cout<<con<<endl;
                    ofil.write(strstr(rec,"D:")+2,t_size-2);
                    prevflg=1;
                    ofil.close();
                    t_size=1024;
            }

            else
            {
                cout<<"else  ..."<<rec<<endl;
            }

            delete []rec;

        }
    }

};

class Sender{
public:
    void operator ()(Socket s)
    {
        int iResult;
        char msg[1024];
        //usrtxt you buffer your friend

        while(true)
        {
            cout<<"Enter message to be sent: "<<endl;
            //cin.getline(msg,1024,'\n');
            //cin>>msg;
            //strcpy(msg,"hehehehehe");

            iResult = send(s.return_New_socket(), "Rajkishor+Arbind", 1024, 0);
            if (iResult == SOCKET_ERROR)
            {
                cout<<"send failed with error: \n"<< WSAGetLastError()<<endl;
            }
            else
            {
                cout<<"MSG sent: "<<endl;

            }

        }
    }

};

class Detect_Handler
{
    const int te=0;
public:
     Detect_Handler()
    {

    }
    int detct()
    {
        return te;
    }
};



/*______________________________________End of socket stuff______________________________*/



/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");


/*VOID OnPaint(HDC hdc)
{
   Graphics graphics(hdc);
   Pen      pen(Color(224, 255, 22, 158));
   graphics.DrawLine(&pen, 500, 200, 50,200 );
}
*/
int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{

/*___________________________________________________Socket________________________________*/

    thread ser(create_own_Server);
    ser.detach();

    c_skt.Initilize_Winshock();

    c_skt.Create_Socket();

    c_skt.Prepare_Socket("192.168.43.173",8889);        //main server
    c_skt.Connect();

/*___________________________________________________End Socket________________________________*/


    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR           gdiplusToken;

     // Initialize GDI+.
    //GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    //FreeConsole();
    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Let's Chat"),       /* Title Text */
           WS_OVERLAPPEDWINDOW|WS_VSCROLL, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           600,                 /* The programs width */
           400,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);
    hndlrec=hwnd;
    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

   // GdiplusShutdown(gdiplusToken);

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     /*HDC          hdc;
     PAINTSTRUCT  ps;
*/
    hwnd=hwnd;
    switch (message)                  /* handle the messages */
    {
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDC_LISTBOX_TEXT:
                {
                    switch(HIWORD(wParam))
                    {
                    case LBN_SELCHANGE:
                        {
                            char te[1024];
                            int index=SendMessage((HWND)lParam,LB_GETCARETINDEX,0,0);
                            selindx=index;
                            SendMessage((HWND)lParam,LB_GETTEXT,(LPARAM)index,(WPARAM)buffer);
                            cout<<buffer<<endl;
                            //cout<<selindx<<endl;
                            strcpy(te,"C:");
                            strcat(te,buffer);
                            strcat(te,":IP:");
                            strcat(te,server_ip);
                            strcat(te,":PRT:");
                            stringstream a;
                            a<<server_port;
                            string m=a.str();
                            const char* p=m.c_str();
                            strcat(te,p);
                            c_skt.Send(te,1024);
                            cout<<te<<endl;
                            cout<<"Connecting...."<<endl;
                            message_box(hwnd);

                    }
                    }
                }break;
            }
            switch(wParam)
            {

            /*case WM_PAINT:
                  hdc = BeginPaint(hwnd, &ps);
                  OnPaint(hdc);
                  EndPaint(hwnd, &ps);
                  return 0;
*/
            case FILEMENU:
                {
                    MessageBeep(MB_OK);

                }break;

            case HLPMNU:
                MessageBeep(MB_OK);
                break;

            case LOGIN:
                {
                     AddLogin(hwnd);
                   /* hdc = BeginPaint(hwnd, &ps);
                    OnPaint(hdc);
                    EndPaint(hwnd, &ps);
    */

                }break;


            case ATTACH_FIL:
                {
                   cout<<"Attached"<<endl;
                   openfile(hwnd);


                }break;


            case SIGNUPHOME:
                {
                    //cout<<"ji"<<endl;
                    DestroyWindow(usr);
                    DestroyWindow(pas);
                    DestroyWindow(usl);
                    DestroyWindow(psl);
                    DestroyWindow(snup);
                    DestroyWindow(lgn);
                    AddcntrlSNUP(hwnd);

                }break;

            case SIGNUP:
                {
                     AddSignup(hwnd);

                } break;

            case SEND:
                {
                     SendMsg(hwnd);

                } break;

            case REFRESH:
                {
                    char dat1[200][200],dat2[200],t[200],f1[100],f2[100];

                    cout<<"refreshed"<<endl;
                    if(prevflg==1)
                    {
                        cout<<"insid prev"<<endl;
                        preview=CreateWindow("button","File Received",WS_VISIBLE|WS_CHILD|SS_RIGHT,150,220,150,25,hwnd,(HMENU)PREVIEW,NULL,NULL);
                        cout<<"out prev"<<endl;
                    }
                    ifstream inn;
                    cout<<"buffer "<<buffer<<endl;
                    strcpy(t,buffer);
                    strcat(t,".txt");
                    inn.open(t,ios::in);
                    cout<<t<<endl;
                    inn.getline(dat2,200);
                    int i=0;
                    strcpy(dat1[i],dat2);
                    while(!inn.eof())
                    {

                        inn.getline(dat2,200);

                        strcpy(dat1[i],dat2);
                        //cout<<dat2<<endl;

                        if(strstr(dat2,buffer)!=nullptr)
                            {
                                i++;
                                strcpy(dat1[i],dat2);

                            }
                        /*if((strstr(dat2,"M:")!=nullptr)&& (strstr(dat2,"::")!=nullptr))
                        {
                            strcpy(f1,strstr(dat2,"M:")+2);
                            strcpy(f2,strstr(f1,"::")+2);
                            f1[strlen(f1)-(strlen(f2)+2)]='\0';
                            if(strcmp(f1,usrtxt)!=0)
                            {
                                 cout<<dat2<<endl;
                                 i+=1;
                                 strcpy(dat1[i],dat2);
                            }
                        }*/



                    }
                    i++;
                    cout<<"oyt"<<i<<endl;
                    inn.close();
                    if(i>=5)
                    {
                        for(int j=(i-5);j<i;j++)
                        {
                            if(strstr(dat1[j],buffer)!=nullptr)
                            {
                                strcpy(t,(strstr(dat1[j],buffer)+strlen(buffer)+2));
                                usl=CreateWindow("static",t,WS_VISIBLE|WS_CHILD|SS_LEFT,330,linenumr,200,25,hndlrec,NULL,NULL,NULL);
                                linenumr+=30;
                                if(linenumr>=220)
                                    linenumr=70;
                            }

                        }
                    }
                    else
                    {
                        for(int j=0;j<i;j++)
                        {
                            if(strstr(dat1[j],buffer)!=nullptr)
                            {
                                strcpy(t,(strstr(dat1[j],buffer)+strlen(buffer)+2));
                                usl=CreateWindow("static",t,WS_VISIBLE|WS_CHILD|SS_LEFT,330,linenumr,200,25,hndlrec,NULL,NULL,NULL);
                                linenumr+=30;
                                if(linenumr>=220)
                                    linenumr=70;
                            }
                        }
                    }
                }break;


                   // cout<<dat1[0];





            case PREVIEW:
            {
                cout<<"previewed"<<endl;
                prevflg=0;
                cout<<"recfilnam  "<<recfilnam<<endl;
                //cout<<ex<<endl;
                ShellExecute(NULL,"open",recfilnam,NULL,NULL,SW_SHOWDEFAULT);
                DestroyWindow(preview);

            }break;


            case ACTREF:
            {
                char ty[50000];
                cout<<"ACTREF"<<endl;
                c_skt.Send("R:",1024);
                cout<<"sent"<<endl;
                c_skt.Receive(data1,50000);
                strcpy(ty,"C");
                strcat(ty,data1);
                strcpy(data1,ty);
                if((strstr(data1,"C::U:")!=nullptr)&&(strstr(data1,"PRT~2:")!=nullptr))
                {
                     cout<<data1<<endl;
                     DestroyWindow(listbox);
                     AddCntrlLOGIN(hwnd);
                }
                else
                {
                    cout<<"Unable to refresh"<<endl;
                }

               //AddCntrlLOGIN(hwnd);

            }break;

            case OLD_MSG:
            {
                char te[100];
                strcpy(te,buffer);
                strcat(te,".txt");
                ShellExecute(NULL,"open",te,NULL,NULL,SW_SHOWDEFAULT);

            } break;


            case REQUESTED_FRND:
                {
                    char tx[100];


                   // GetWindowText(h,tx,100);

                    cout<<tx<<endl;
                }

         /* {
               int i;

               for(i=0;i<n;i++)
            {


            case h.detec():
                {

                    cout<<i<<endl;

                } break;


            }
           }*/





            }
            break;

        case WM_CREATE:
            AddMnuHOME(hwnd);
            AddCntrlHOME(hwnd);
            break;

        case WM_DESTROY:
            cout<<"win closed"<<endl;

            strcpy(msg,"X:");
            strcat(msg,usrtxt);
            c_skt.Send(msg,1024);



            outfilesen.close();
            outfilerec.close();
            infilerec.close();
            infilesen.close();
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;

        case REC_LABEL:
            cout<<"msg called";
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

void AddMnuHOME(HWND hwnd)
{
    hmnu=CreateMenu();
    HMENU flmnu=CreateMenu();
    HMENU hlpmnu=CreateMenu();

    AppendMenu(flmnu,MF_STRING,FILEMENU,"Exit");
    AppendMenu(hlpmnu,MF_STRING,HLPMNU,"Updates");
    AppendMenu(flmnu,MF_SEPARATOR,NULL,NULL);
    AppendMenu(hmnu,MF_POPUP,(UINT_PTR)flmnu,"File");
    AppendMenu(hmnu,MF_POPUP,(UINT_PTR)hlpmnu,"Help");

    SetMenu(hwnd,hmnu);
}

void AddCntrlHOME(HWND hwnd)
{
    usl=CreateWindowW(L"static",L"Username: ",WS_VISIBLE|WS_CHILD|SS_RIGHT,100,100,150,25,hwnd,NULL,NULL,NULL);
    psl=CreateWindowW(L"static",L"Password: ",WS_VISIBLE|WS_CHILD|SS_RIGHT,100,150,150,25,hwnd,NULL,NULL,NULL);
    usr=CreateWindowW(L"edit",L"",WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL,255,100,150,25,hwnd,NULL,NULL,NULL);
    pas=CreateWindowW(L"edit",L"",WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_PASSWORD,255,150,150,25,hwnd,NULL,NULL,NULL);
    lgn=CreateWindowW(L"Button",L"Login",WS_VISIBLE|WS_CHILD,290,200,55,30,hwnd,(HMENU)LOGIN,NULL,NULL);
    snup=CreateWindowW(L"Button",L"SignUp",WS_VISIBLE|WS_CHILD,170,200,65,30,hwnd,(HMENU)SIGNUPHOME,NULL,NULL);

}

void AddcntrlSNUP(HWND hwnd)
{
    usl=CreateWindowW(L"static",L"Username: ",WS_VISIBLE|WS_CHILD|SS_RIGHT,100,50,150,25,hwnd,NULL,NULL,NULL);
    emll=CreateWindowW(L"static",L"Email: ",WS_VISIBLE|WS_CHILD|SS_RIGHT,100,100,150,25,hwnd,NULL,NULL,NULL);
    psl=CreateWindowW(L"static",L"Password: ",WS_VISIBLE|WS_CHILD|SS_RIGHT,100,150,150,25,hwnd,NULL,NULL,NULL);
    psl2=CreateWindowW(L"static",L"Re-Type: ",WS_VISIBLE|WS_CHILD|SS_RIGHT,100,200,150,25,hwnd,NULL,NULL,NULL);
    usr=CreateWindowW(L"edit",L"",WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL,255,50,150,25,hwnd,NULL,NULL,NULL);
    eml=CreateWindowW(L"edit",L"",WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL,255,100,150,25,hwnd,NULL,NULL,NULL);
    pas=CreateWindowW(L"edit",L"",WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_PASSWORD,255,150,150,25,hwnd,NULL,NULL,NULL);
    pas2=CreateWindowW(L"edit",L"",WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_PASSWORD,255,200,150,25,hwnd,NULL,NULL,NULL);
    cncl=CreateWindowW(L"Button",L"Cancel",WS_VISIBLE|WS_CHILD,170,250,65,30,hwnd,(HMENU)SIGNUPHOME,NULL,NULL);
    snup=CreateWindowW(L"Button",L"SignUp",WS_VISIBLE|WS_CHILD,290,250,60,30,hwnd,(HMENU)SIGNUP,NULL,NULL);
}
void openfile(HWND hwnd)
{
        OPENFILENAME opn;
        ZeroMemory(&opn,sizeof(OPENFILENAME));
        opn.lStructSize=sizeof(OPENFILENAME);
        opn.hwndOwner=hwnd;
        opn.lpstrFile=dir;
        opn.lpstrFile[0]='\0';
        opn.nMaxFile=200;
        opn.lpstrFilter="All Files\0*.*\0";
        opn.nFilterIndex=1;
        opn.Flags=OFN_EXPLORER|OFN_FILEMUSTEXIST|OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT;
        GetOpenFileName(&opn);
        SetWindowText(msgsen,dir);
        attfil=1;
        //cout<<dir<<endl;
}
void SendMsg(HWND hwnd)
{


    if(attfil==1)
    {
        cout<<"filsent"<<endl;
        char ff[100];
        attfil=0;
        int t_size,iR;

        streampos begin,end;
       ifstream myfile (dir,ios::binary);
       begin = myfile.tellg();
       myfile.seekg (0, ios::end);
       end = myfile.tellg();
       myfile.close();
       cout << "size is: " << (end-begin) << " bytes.\n";
        t_size=(end-begin);

        //sending file info

        while(strstr(dir,"\\")!=nullptr)
        {
            strcpy(ff,strstr(dir,"\\")+1);
            strcpy(dir,strstr(dir,"\\")+1);

        }
        char k[200];
        strcpy(k,"F:");
        strcat(k,ff);
        strcat(k,":SIZE:");
        stringstream ss;
        ss<<t_size;
        string m=ss.str();
        const char* p=m.c_str();
        strcat(k,p);
        cout<<k<<endl;
        iR = send(nclie.return_New_socket(), k, 1024, 0);
        if (iR == SOCKET_ERROR)
        {
            iR = send(s_skt.return_New_socket(), k, 1024, 0);
            if (iR == SOCKET_ERROR)
            {
                cout<<"send failed with error: \n"<< WSAGetLastError()<<endl;
            }

        }

        cout<<"sending file..."<<endl;
        ifstream infil;
        char *mm;
        mm=new char[t_size];
        char *mn;
        mn=new char[t_size];
        strcpy(mn,"D:");
        infil.open(dir,ios::binary);
        infil.read(mm,1024);
        strcat(mn,mm);
        while(!infil.eof())
        {
            infil.read(mm,1024);
            strcat(mn,mm);
            cout<<mm<<endl;
        }
        infil.close();
        /*int stepsize=1024,step=0,last_step_size;
            char data[stepsize];
            if((t_size%stepsize)==0)
        {
            step=int(t_size/stepsize);
            cout<<"exact step "<<step<<endl;
            for(int i=0;i<=step;i++)
              {
                  infil.read(data,stepsize);

                  cout<<data<<endl;
                  strcat(mn,data);
              }
              infil.close();

        }
        else if((t_size/stepsize)<=0)
        {
            last_step_size=t_size;
            cout<<"last_step_size "<<last_step_size<<endl;
            infil.read(data,last_step_size);
            infil.close();
            cout<<data<<endl;
            strcat(mn,data);


        }
        else
        {
            step=int(t_size/stepsize);
            last_step_size=(t_size%stepsize);
            cout<<"step "<<step<<" last_step_size "<<last_step_size<<endl;
            for(int i=0;i<=step;i++)
              {
                  infil.read(data,stepsize);
                  cout<<data<<endl;
                  strcat(mn,data);
              }
            infil.read(data,last_step_size);
            infil.close();
            strcat(mn,data);
        }
        cout<<mn<<endl;*/



        iR = send(nclie.return_New_socket(), mn, (t_size+2), 0);
        if (iR == SOCKET_ERROR)
        {
            iR = send(s_skt.return_New_socket(), mn, (t_size+2), 0);
            if (iR == SOCKET_ERROR)
            {
                cout<<"send failed with error: \n"<< WSAGetLastError()<<endl;
            }
            else
            {
                 SetWindowText(msgsen,"");
            }
        }
        else
            {
                 SetWindowText(msgsen,"");
            }

         cout<<"file sent ..."<<endl;
        /* ofstream o;
         ifstream pl;
        pl.open("x.png",ios::binary);
        if(!o)
            cout<<"cant"<<endl;
        char d[t_size];
        pl.read(d,t_size);
        o.open("dfsnasfnadkjnafdkng.png",ios::binary);
        o.write(d,t_size);
        pl.close();
        o.close();*/

        /* ofstream o;
        o.open("101l.png",ios::binary);
        if(!o)
            cout<<"cant"<<endl;
        o.write(strstr(mn,"D:")+2,t_size);
        o.close();*/

         //cout<<mn<<endl;
         cout<<sizeof(mn)<<endl;
        delete []mm;
        delete []mn;



    }
    else
    {
        int iResult;
        //cout<<"seeeent"<<endl;
        char ms[1024],bu[1024];
        strcpy(ms,"M:");
        strcat(ms,usrtxt);
        strcat(ms,"::");
        GetWindowText(msgsen,bu,1024);
        strcat(ms,bu);
        cout<<ms<<endl;

        iResult = send(nclie.return_New_socket(), ms, 1024, 0);
        if (iResult == SOCKET_ERROR)
        {
            //cout<<"send failed with error: \n"<< WSAGetLastError()<<endl;
            iResult = send(s_skt.return_New_socket(), ms, 1024, 0);
            if (iResult == SOCKET_ERROR)
            {
                cout<<"send failed with error: \n"<< WSAGetLastError()<<endl;
            }

             else
            {
                if(linenums>=220)
                {
                     linenums=70;

                }
                strcpy(filnam,buffer);
                strcat(filnam,".txt");
                outfilesen.open(filnam,ios::app);
                outfilesen<<ms<<endl;
                usl=CreateWindow("static",bu,WS_VISIBLE|WS_CHILD|SS_LEFT,40,linenums,200,25,hwnd,NULL,NULL,NULL);
                linenums+=30;
                cout<<"MSG sent: "<<endl;
                SetWindowText(msgsen,"");

            }


        }
         else
        {
            if(linenums>=220)
            {
                linenums=70;
            }
            strcpy(filnam,buffer);
            strcat(filnam,".txt");
            outfilesen.open(filnam,ios::app);
            outfilesen<<ms<<endl;
            usl=CreateWindow("static",bu,WS_VISIBLE|WS_CHILD|SS_LEFT,40,linenums,200,25,hwnd,NULL,NULL,NULL);
            linenums+=30;
            cout<<"MSG sent: "<<endl;
            SetWindowText(msgsen,"");

        }
        outfilesen.close();

    }





   /* try
    {
        iResult = send(nclie.return_New_socket(), ms, 1024, 0);
        if (iResult == SOCKET_ERROR)
        {
            //cout<<"send failed with error: \n"<< WSAGetLastError()<<endl;
            throw 1;
        }
         else
        {
            strcpy(filnam,buffer);
            strcat(filnam,".txt");
            outfilesen.open(filnam,ios::app);
            outfilesen<<ms<<endl;
            usl=CreateWindow("static",bu,WS_VISIBLE|WS_CHILD|SS_LEFT,40,linenums,200,25,hwnd,NULL,NULL,NULL);
            linenums+=30;
            if(linenums>=220)
                linenums=70;
            cout<<"MSG sent: "<<endl;

        }

    }
    catch(int)
    {
        iResult = send(s_skt.return_New_socket(), ms, 1024, 0);
        if (iResult == SOCKET_ERROR)
        {
            //cout<<"send failed with error: \n"<< WSAGetLastError()<<endl;
            throw ;
        }
         else
        {
            strcpy(filnam,buffer);
            strcat(filnam,".txt");
            outfilesen.open(filnam,ios::app);
            outfilesen<<ms<<endl;
            usl=CreateWindow("static",bu,WS_VISIBLE|WS_CHILD|SS_LEFT,40,linenums,200,25,hwnd,NULL,NULL,NULL);
            linenums+=30;
            if(linenums>=220)
                linenums=70;
            cout<<"MSG sent: "<<endl;

        }
    }
    catch(...)
    {
            cout<<"send failed with error: \n"<< WSAGetLastError()<<endl;
    }*/


}

void message_box(HWND hwnd)
{
    DestroyWindow(listbox);
    DestroyWindow(usl);
    DestroyWindow(cusr);
    DestroyWindow(actvref);
    //DestroyWindow(actvref);
    cusr=CreateWindow("static",usrtxt,WS_VISIBLE|WS_CHILD|SS_CENTER,40,20,200,25,hwnd,NULL,NULL,NULL);
    usr=CreateWindow("static",buffer,WS_VISIBLE|WS_CHILD|SS_CENTER,330,20,200,25,hwnd,NULL,NULL,NULL);
    int j=40;
    /*for(int i=0; i<3;i++)
    {
        j+=30;
        usl=CreateWindowW(L"static",L"Hi1, ",WS_VISIBLE|WS_CHILD|SS_RIGHT,40,j,200,25,hwnd,NULL,NULL,NULL);
    }
    j=40;
    for(int i=0; i<3;i++)
    {
        j+=30;
        usl=CreateWindowW(L"static",L"Hi1, ",WS_VISIBLE|WS_CHILD|SS_RIGHT,330,j,200,25,hwnd,NULL,NULL,NULL);
    }*/

    msgsen=CreateWindowW(L"edit",L"",WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL,100,250,400,50,hwnd,NULL,NULL,NULL);
    attacfl=CreateWindowW(L"Button",L"Attach file",WS_VISIBLE|WS_CHILD,305,310,100,30,hwnd,(HMENU)ATTACH_FIL,NULL,NULL);
    sen=CreateWindowW(L"Button",L"Send",WS_VISIBLE|WS_CHILD,430,310,65,30,hwnd,(HMENU)SEND,NULL,NULL);
    re=CreateWindowW(L"Button",L"View Old Conversation",WS_VISIBLE|WS_CHILD,110,310,170,30,hwnd,(HMENU)OLD_MSG,NULL,NULL);
    re=CreateWindowW(L"Button",L"Refresh",WS_VISIBLE|WS_CHILD,350,220,170,20,hwnd,(HMENU)REFRESH,NULL,NULL);
}


void AddCntrlLOGIN(HWND hwnd)
{
     //cout<<data1<<endl;
    listbox =CreateWindow("LISTBOX",NULL,WS_VISIBLE|WS_CHILD|LBS_STANDARD|LBS_NOTIFY,100,70,400,300,hwnd,(HMENU)IDC_LISTBOX_TEXT,(HINSTANCE)GetWindowLong(hwnd,GWLP_HINSTANCE),NULL);

    cusr=CreateWindow("static",usrtxt,WS_VISIBLE|WS_CHILD|SS_CENTER,240,5,100,25,hwnd,NULL,NULL,NULL);

    //converting part of char array to int
    char prt2[10];
    strcpy(prt2,strstr(data1,"L~:")+3);
    prt2[strlen(prt2)-1]='\0';
    n=atoi(prt2);
    //cout<<n;
    usl=CreateWindowW(L"static",L"Active Users ",WS_VISIBLE|WS_CHILD|SS_CENTER,150,40,300,25,hwnd,NULL,NULL,NULL);
    actvref=CreateWindowW(L"button",L"Refresh ",WS_VISIBLE|WS_CHILD|SS_CENTER,465,20,85,25,hwnd,(HMENU)ACTREF,NULL,NULL);
    //rqfrn=new HWND[n];
    int k=0;

    //strcpy(data2,data1);
    for(int i=0;i<n;i++)
    {
        char u[50000],ip[30],p[20];
        char te[50000];
        strcpy(u,strstr(data1,":U:")+3);
        strcpy(data1,strstr(u,"IP~2:"));
        strcpy(te,strstr(u,"IP~2:")+5);
        u[strlen(u)-(strlen(te)+5)]='\0';
        cout<<u<<endl;
        //LPVOID h=(LPVOID)rqfrn[i];
        //rqfrn[i]=CreateWindow("Button",u,WS_VISIBLE|WS_CHILD,370,70+(i*30),150,25,hwnd,(HMENU)REQUESTED_FRND,NULL,h);
       // cout<<te;
       if(strcmp(u,usrtxt)!=0)
       {
           SendMessage(GetDlgItem(hwnd,IDC_LISTBOX_TEXT),LB_ADDSTRING,0,(LPARAM)u);
       }

        strcpy(u,strstr(te,"PRT~2:")+6);
        te[strlen(te)-(strlen(u)+6)]='\0';
        strcpy(ip,te);
        cout<<ip<<endl;
        if(i!=(n-1))
       {
            strcpy(te,strstr(u,":U:"));
            u[strlen(u)-strlen(te)]='\0';
            strcpy(p,u);
            cout<<p<<endl;
       }
       else
       {
          strcpy(te,strstr(u,"L~:"));
          u[strlen(u)-strlen(te)]='\0';
          cout<<u;
       }


        /*stringstream a;
        a<<i;
        string m=a.str();
        const char* p=m.c_str();
        strcpy(t,p);*/
        //snup=CreateWindow("Button","llo",WS_VISIBLE|WS_CHILD,370,70+(i*30),150,25,hwnd,(HMENU)SIGNUP,NULL,NULL);
    }

}

int AddLoginStuff()
{
    GetWindowText(usr,usrtxt,100);
    GetWindowText(pas,pastxt,100);
    strcpy(msg,"L:");
    strcat(msg,"ID:");
    strcat(msg,usrtxt);
    strcat(msg,"P:");
    strcat(msg,pastxt);
    strcat(msg,"IP:");
    strcat(msg,server_ip);
    strcat(msg,"PRT:");
    stringstream pp;
    pp<<server_port;
    string m=pp.str();
    const char* p=m.c_str();
    strcat(msg,p);
    c_skt.Send(msg,1024);
    c_skt.Receive(rec,1024);
    //cout<<rec;
    if(atoi(rec)==1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    //cout<<usrtxt<<" "<<pastxt;

}

void AddSignup(HWND hwnd)
{

        GetWindowText(usr,usrtxt,100);
        GetWindowText(pas,pastxt,100);
        GetWindowText(eml,emltxt,100);
        strcpy(msg,"S:");
        strcat(msg,"U:");
        strcat(msg,usrtxt);
        strcat(msg,"E:");
        strcat(msg,emltxt);
        strcat(msg,"P:");
        strcat(msg,pastxt);
        strcat(msg,"IP~:");
        strcat(msg,server_ip);
        strcat(msg,"PRT:");
        stringstream ss;
        ss<<server_port;
        string m=ss.str();
        const char* p=m.c_str();
        strcat(msg,p);
        c_skt.Send(msg,1024);
        c_skt.Receive(rec,1024);
        //cout<<rec;
        if(atoi(rec)==1)
        {
            DestroyWindow(usr);
            DestroyWindow(pas);
            DestroyWindow(usl);
            DestroyWindow(psl2);
            DestroyWindow(psl);
            DestroyWindow(eml);
            DestroyWindow(emll);
            DestroyWindow(pas2);
            DestroyWindow(snup);
            DestroyWindow(lgn);
            DestroyWindow(cncl);
            //AddLogin(hwnd);
            AddCntrlHOME(hwnd);
        }
        else
        {
            usl=CreateWindowW(L"static",L"Some thing went wrong!",WS_VISIBLE|WS_CHILD|SS_CENTER,125,10,250,25,hwnd,NULL,NULL,NULL);
        }
}
void AddLogin(HWND hwnd)
{
    if(AddLoginStuff()==1)
    {
        DestroyWindow(usr);
        DestroyWindow(pas);
        DestroyWindow(usl);
        DestroyWindow(psl);
        DestroyWindow(snup);
        DestroyWindow(lgn);

        c_skt.Receive(data1,50000);
        //cout<<data1;
        AddCntrlLOGIN(hwnd);
    }
    else
    {
        usl=CreateWindowW(L"static",L"Incorrect username or password ",WS_VISIBLE|WS_CHILD|SS_CENTER,125,65,250,25,hwnd,NULL,NULL,NULL);
    }




}

void create_own_Server()
{



        s_skt.Initilize_Winshock();

        s_skt.Create_Socket();

        s_skt.Bind(server_ip,server_port);

        s_skt.Listen(5);
        //s.Listen(5);
        //cout<<"frm threas"<<endl;

        while( s_skt.Accept() != INVALID_SOCKET )
        {

            thread rec((Recever()),s_skt);
            rec.detach();
        }
        s_skt.Close();


}
