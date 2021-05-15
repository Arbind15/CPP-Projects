#include<io.h>
#include<stdio.h>
#include<winsock2.h>
#include<iostream>
#include<thread>
#include<stdlib.h>
#include<cstring>
#include<unistd.h>
#include<typeinfo>
#include<string>
#include<mysql.h>
#include<sstream>
#define Server_ip "192.168.43.173"
#define Server_port 8889

using namespace std;

class Socket
{
    WSADATA wsa;
    SOCKET s , new_socket;
    struct sockaddr_in server , client,client_add;
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
        new_socket = accept(s, (struct sockaddr *)&client_add, &c);//&client and &c is optional argument

        //cout<<client_add.sin_addr.s_addr;

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
            cout<<WSAGetLastError();
            return -1;
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
            return 1;
        }

        else if ( iResult == 0 )
            {
                wprintf(L"Connection closed\n");
                return 0;
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


class Recever{
public:
    void operator ()(Socket s)
    {
        int iResult;
        char rec[1024];
        do {
                iResult = recv(s.return_New_socket(),rec,1024,0);
                std::cout<<"Rececived: "<<rec<<std::endl;
            } while (iResult!=SOCKET_ERROR);
    }

};

class Sender{
public:
    void operator ()(Socket s)
    {
        int iResult;
        char msg[1024];
        do {
                cout<<"Enter message to be sent: "<<endl;
                cin.getline(msg,1024,'\n');
                iResult = send(s.return_New_socket(), msg, 1024, 0);
                if (iResult == SOCKET_ERROR)
                {
                    cout<<"send failed with error: \n"<< WSAGetLastError()<<endl;
                }
                cout<<"MSG sent: "<<endl;
            } while (iResult!=WSAGetLastError());
    }

};


/*class Get_Client{
public:
    void operator ()(Socket skt)
    {

        char rec[1024],flg;
        std::cout<<"trying..\n";
        skt.Receive(rec,1024);
        std::cout<<"Rececived: "<<rec<<std::endl;
        flg=rec[0];
         if(flg=='S')
        {
            cout<<"inside create"<<endl;
            char usr[200],eml[200],psw[100];

            strcpy(usr,strstr(rec,"U:")+2);
            strcpy(eml,strstr(usr,"E:")+2);
            strcpy(psw,strstr(eml,"P:")+2);
            usr[strlen(usr)-(strlen(eml)+2)]='\0';
            eml[strlen(eml)-(strlen(psw)+2)]='\0';

            //strcpy(eml,strstr(usr,"E:")+2);

            cout<<usr<<endl;
            cout<<eml<<endl;
            cout<<psw<<endl;
            skt.Send("A/c created sucessfully",1024);
        }


        if(flg=='L')
        {
            cout<<"inside login"<<endl;
            char id[200],psw[100];

            strcpy(id,strstr(rec,"ID:")+2);
            strcpy(psw,strstr(rec,"P:")+2);
            id[strlen(id)-(strlen(psw)+2)]='\0';


            cout<<id<<endl;
            cout<<psw<<endl;
            skt.Send("logged in sucessfully",1024);
        }

        if(flg=='M')
        {
            cout<<"inside msg"<<endl;
            char prt[20],ip[50],msg[1024];

            strcpy(msg,strstr(rec,"M~:")+3);
            strcpy(ip,strstr(rec,"IP~:")+4);
            strcpy(prt,strstr(rec,"PRT~:")+5);
            msg[strlen(msg)-(strlen(ip)+4)]='\0';
            ip[strlen(ip)-(strlen(prt)+5)]='\0';



            //strcpy(eml,strstr(usr,"E:")+2);

            cout<<ip<<endl;
            cout<<prt<<endl;
            cout<<msg<<endl;
            skt.Send("msg sucessfully",1024);
        }
        if(flg=='C')
        {
            cout<<"inside connet"<<endl;
            char prt1[20],ip1[50],prt2[20],ip2[50];

            strcpy(ip1,strstr(rec,"IP~1:")+5);
            strcpy(prt1,strstr(rec,"PRT~1:")+6);

            strcpy(ip2,strstr(rec,"IP~2:")+5);
            strcpy(prt2,strstr(rec,"PRT~2:")+6);

            ip1[strlen(ip1)-(strlen(prt1)+6)]='\0';
            prt1[strlen(prt1)-(strlen(ip2)+5)]='\0';
            ip2[strlen(ip2)-(strlen(prt2)+6)]='\0';

            skt.Send("Connecting...",1024);
            Socket c_skt;

            c_skt.Initilize_Winshock();

            c_skt.Create_Socket();

            c_skt.Prepare_Socket(ip2,atoi(prt2));
            //c_skt.Prepare_Socket("192.168.137.1",8888);

            c_skt.Connect();

            c_skt.Send(rec,1024);


        }


        //int iResult;

        /*thread recver((Recever()),skt);
        recver.detach();

        thread sender((Sender()),skt);
        sender.detach();
    }

};
*/

void i()
{

        //cskt.Close();
}

MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;
int qstate=0;
stringstream query;
char msg[1024];



class Get_Client{
public:
    void operator ()(Socket skt)
    {

        while(1)
         {


            char rec[1024],flg;
            std::cout<<"trying..\n";
            skt.Receive(rec,1024);
            std::cout<<"Rececived: "<<rec<<std::endl;
            flg=rec[0];
             if(flg=='S')
            {
                cout<<"inside create"<<endl;
                char usr[200],eml[200],psw[100],i[50],p[10];

                strcpy(usr,strstr(rec,"U:")+2);
                strcpy(eml,strstr(usr,"E:")+2);
                strcpy(psw,strstr(eml,"P:")+2);
                strcpy(i,strstr(psw,"IP~:")+4);
                strcpy(p,strstr(i,"PRT:")+4);
                usr[strlen(usr)-(strlen(eml)+2)]='\0';
                eml[strlen(eml)-(strlen(psw)+2)]='\0';
                psw[strlen(psw)-(strlen(i)+4)]='\0';
                i[strlen(i)-(strlen(p)+4)]='\0';

                cout<<usr<<endl;
                cout<<eml<<endl;
                cout<<psw<<endl;
                cout<<i<<endl;
                cout<<p<<endl;
                query<<"INSERT INTO user_data(username,email,password,ip,port) VALUES('"<<usr<<"','"<<eml<<"','"<<psw<<"','"<<i<<"','"<<p<<"')";
                string qu=query.str();
                const char* q=qu.c_str();
                qstate=mysql_query(conn,q);
                if(qstate==0)
                {
                    cout<<"inserted"<<endl;
                    skt.Send("1",1024);
                }
                else
                {
                    cout<<"Insertation failed "<<endl;
                    skt.Send("0",1024);
                }
                //strcpy(eml,strstr(usr,"E:")+2);

                //cout<<usr<<endl;
                //cout<<eml<<endl;
                //cout<<psw<<endl;

            }


            if(flg=='L')
            {
                cout<<"inside login"<<endl;
                char id[200],psw[100],ipp[50],ppr[10];

                strcpy(id,strstr(rec,"ID:")+3);
                strcpy(psw,strstr(rec,"P:")+2);
                strcpy(ipp,strstr(rec,"IP:")+3);
                strcpy(ppr,strstr(rec,"PRT:")+4);
                id[strlen(id)-(strlen(psw)+2)]='\0';
                psw[strlen(psw)-(strlen(ipp)+3)]='\0';
                ipp[strlen(ipp)-(strlen(ppr)+4)]='\0';
                cout<<id<<endl;
                cout<<psw<<endl;
                cout<<ipp<<endl;
                cout<<ppr<<endl;
                char src[1024];
                strcpy(src,"SELECT * FROM user_data WHERE username='");
                strcat(src,id);
                strcat(src,"'");
                qstate=mysql_query(conn,src);
                //cout<<rec;
                bool ff=0;
                if(qstate==0)
                {
                    cout<<"searched"<<endl;
                    res=mysql_store_result(conn);

                    while(row=mysql_fetch_row(res))
                    {
                        cout<<row[0]<<endl;
                        if(strcmp(row[2],psw)==0)
                        {
                            skt.Send("1",1024);
                            ff=1;

                            strcpy(src,"UPDATE user_data SET ip='");
                            strcat(src,ipp);
                            strcat(src,"', remark=1 , port=");
                            strcat(src,ppr);
                            strcat(src," WHERE username='");
                            strcat(src,id);
                            strcat(src,"'");
                            cout<<src<<endl;
                            qstate=0;
                            qstate=mysql_query(conn,src);
                            if(qstate==0)
                            {
                                cout<<"info updated!"<<endl;
                            }

                            strcpy(src,"SELECT * FROM user_data where remark=1");
                            qstate=0;
                            qstate=mysql_query(conn,src);
                            if(qstate==0)
                            {
                                res=mysql_store_result(conn);
                                char data1[1024],data2[1024];
                                int i=0;
                                strcpy(msg,"C:");
                                while(row=mysql_fetch_row(res))
                                {

                                    strcat(msg,":U:");
                                    strcat(msg,row[0]);
                                    strcat(msg,"IP~2:");
                                    strcat(msg,row[3]);
                                    strcat(msg,"PRT~2:");
                                    strcat(msg,row[4]);
                                    i++;
                                }

                                strcat(msg,"L~:");
                    //converting int to constant  char* array
                                stringstream a;
                                a << i;
                                string myString = a.str();
                                const char* p=myString.c_str();
                                //itoa(i,str,10)
                                strcat(msg,p);
                                strcat(msg,":");
                                cout<<msg<<endl;
                                skt.Send(msg,50000);

                            }


                        }
                    }
                }
                if(ff==0)
                {

                    skt.Send("0",1024);
                }




                //cout<<id<<endl;
                //cout<<psw<<endl;

            }

            if(flg=='X')
            {
                char idd[100],ss[200];
                strcpy(idd,strstr(rec,"X:")+2);
                cout<<"logging out...... "<<idd<<endl;
                strcpy(ss,"UPDATE user_data SET remark=0 WHERE username='");
                strcat(ss,idd);
                strcat(ss,"'");
                int qstate=0;
                qstate=mysql_query(conn,ss);
                if(qstate==0)
                {
                    cout<<"successfully logged out! "<<endl;
                    break;
                }


            }

            if(flg=='R')
            {
                cout<<"targetd"<<endl;
                char s[200];
                strcpy(s,"SELECT * FROM user_data where remark=1");
                int qstate=0;
                qstate=mysql_query(conn,s);
                if(qstate==0)
                {
                    res=mysql_store_result(conn);
                    int i=0;
                    strcpy(msg,":");
                    while(row=mysql_fetch_row(res))
                    {

                        strcat(msg,":U:");
                        strcat(msg,row[0]);
                        strcat(msg,"IP~2:");
                        strcat(msg,row[3]);
                        strcat(msg,"PRT~2:");
                        strcat(msg,row[4]);
                        i++;
                    }

                    strcat(msg,"L~:");
        //converting int to constant  char* array
                    stringstream a;
                    a << i;
                    string myString = a.str();
                    const char* p=myString.c_str();
                    //itoa(i,str,10)
                    strcat(msg,p);
                    strcat(msg,":");
                    cout<<msg<<endl;
                    skt.Send(msg,50000);
                }



            }

            if(flg=='M')
            {
                cout<<"inside msg"<<endl;
                char prt[20],ip[50],msg[1024];

                strcpy(msg,strstr(rec,"M~:")+3);
                strcpy(ip,strstr(rec,"IP~:")+4);
                strcpy(prt,strstr(rec,"PRT~:")+5);
                msg[strlen(msg)-(strlen(ip)+4)]='\0';
                ip[strlen(ip)-(strlen(prt)+5)]='\0';



                //strcpy(eml,strstr(usr,"E:")+2);

                cout<<ip<<endl;
                cout<<prt<<endl;
                cout<<msg<<endl;
                skt.Send("msg sucessfully",1024);
            }
            if(flg=='C')
            {

                //cout<<data1<<endl;
                char prt1[20],ip1[50],te[1024],src[1024];
                /*strcpy(te,strstr(rec,"C:")+2);
                strcpy(ip1,strstr(te,":IP:")+4);
                strcpy(prt1,strstr(ip1,":PRT:")+5);
                te[strlen(te)-(strlen(ip1)+4)]='\0';
                ip1[strlen(ip1)-(strlen(prt1)+5)]='\0';
                cout<<te<<endl;
                cout<<ip1<<endl;
                cout<<prt1<<endl;*/
                strcpy(te,strstr(rec,"C:")+2);
                strcpy(ip1,strstr(te,":IP:")+4);//only to extract requested user
                te[strlen(te)-(strlen(ip1)+4)]='\0';
                //cout<<te<<endl;
                cout<<"inside connet"<<endl;
                strcpy(src,"SELECT * FROM user_data where username='");
                strcat(src,te);
                strcat(src,"'");
                qstate=0;
                qstate=mysql_query(conn,src);
                if(qstate==0)
                {
                    res=mysql_store_result(conn);
                    while(row=mysql_fetch_row(res))
                    {
                        strcpy(ip1,row[3]);
                        strcpy(prt1,row[4]);
                    }
                }


                /*strcpy(ip1,strstr(rec,"IP~1:")+5);
                strcpy(prt1,strstr(rec,"PRT~1:")+6);

                strcpy(ip2,strstr(rec,"IP~2:")+5);
                strcpy(prt2,strstr(rec,"PRT~2:")+6);

                ip1[strlen(ip1)-(strlen(prt1)+6)]='\0';
                prt1[strlen(prt1)-(strlen(ip2)+5)]='\0';
                ip2[strlen(ip2)-(strlen(prt2)+6)]='\0';

                skt.Send("Connecting...",1024);*/

                //skt.Close();
                //thread t(i);
                //t.detach();

                Socket cskt;
                cskt.Initilize_Winshock();
                cskt.Create_Socket();
                cskt.Prepare_Socket(ip1,atoi(prt1));
                //cskt.Prepare_Socket("192.168.43.156",8888);
                cskt.Connect();
                cout<<"connecting,,....."<<endl;
                //system("pause");
                cskt.Send(rec,1024);


                //c_skt.Close();
                //char r[1024];
                //c_skt.Receive(r,1024);
                //cout<<r<<endl;*/

            }
         }
         }

};


int main()
{

    conn= mysql_init(0);
    conn=mysql_real_connect(conn,Server_ip,"Arbind","arbind@123","User_info",0,NULL,0);
    if(conn)
    {
        cout<<"Database connected"<<endl;

    }else
    {
        cout<<"Database not connected"<<endl;
    }


    Socket skt;

    skt.Initilize_Winshock();

    skt.Create_Socket();

    skt.Bind(Server_ip,Server_port);

    skt.Listen(10);

    cout<<"L";
    while( skt.Accept() != INVALID_SOCKET )
    {
        cout<<"m";
        thread client((Get_Client()),skt);
        client.detach();
        cout<<"n";

    }

    return 0;
}
