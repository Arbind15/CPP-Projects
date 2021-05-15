#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include<iostream>
#include<string>
#include<stdio.h>
using namespace Gdiplus;
using namespace std;
void LoadTree(HDC);
void UserPromt(HDC);


class Node;
class Data;
void DrawNode(Node *,int,int,HDC);
void InorderTransverse(Node *);
void PreorderTransverse(Node *);
void PostorderTransverse(Node *);
Node* DeleteNode(Node*,Data);


class Data{
private:
    int info;
    int level;

public:
    int getInfo(){
        return info;
    }
    void setInfo(int x){
        info=x;
    }


};

class Node{
private:
    Data data;
    int level;
    Node *left_Child,*right_Child;

public:
    Node(){
        left_Child=nullptr;
        right_Child=nullptr;
        data.setInfo(-1);
        level=-1;
        //printf("node ");
    }
    void setData(Data d){
        data=d;
    }
    void setLevel(int x){
        level=x;
    }
    int getLevel(){
        return level;
    }

    Data getData(){
        return data;
    }
    void setLeftChild(Node *x){
        left_Child=x;
    }
    void setRightChild(Node *x){
        right_Child=x;
    }
    Node * getLeftChild(){
        return left_Child;
    }

    Node * getRightChild(){
        return right_Child;
    }
};

class BinarySearchTree{
private:
    Node *root;
public:
    BinarySearchTree(){
       root = new Node;
       //printf("tree");
    }

    void insertData(Data d){
        if((root->getData().getInfo())==-1){
            root->setData(d);
            root->setLevel(0);
            //printf("root\n");
        }
        else{
            Node *ptr=root;
            Node *parent= new Node;
            Node *new_node= new Node;
            new_node->setData(d);
            int x =0;
            while(ptr!=nullptr){

                parent=ptr;

                if(d.getInfo() < ptr->getData().getInfo()){
                    ptr=ptr->getLeftChild();
                }
                else{
                    ptr=ptr->getRightChild();
                }
                x++;
            }

            new_node->setLevel(x);

            if(d.getInfo() < parent->getData().getInfo()){
                parent->setLeftChild(new_node);
            }
            else{
                parent->setRightChild(new_node);
            }
        }

    }

    void Display(HDC);

    void Transversal();

    Node * Search(Data);

    Node * Delete(Data da){
        DeleteNode(root,da);
    }

};

void BinarySearchTree::Transversal(){
        Node *ptr;
        ptr=root;
        cout<<"Inorder Transversal:\n";
        InorderTransverse(ptr);
        cout<<endl;

        cout<<"Postorder Transversal:\n";
        PostorderTransverse(ptr);
        cout<<endl;

        cout<<"Preorder Transversal:\n";
        PreorderTransverse(ptr);
        cout<<endl;

}

Node * BinarySearchTree::Search(Data da){
    Node *ptr;
    ptr=root;

    while(ptr!=nullptr){
        if(ptr->getData().getInfo()==da.getInfo()){
            return ptr;
        }
        else if(da.getInfo()<ptr->getData().getInfo()){
            ptr=ptr->getLeftChild();
        }
        else{
            ptr=ptr->getRightChild();
        }
    }

    return ptr;
}

void InorderTransverse(Node *ptr){
    if(ptr!=nullptr){
            InorderTransverse(ptr->getLeftChild());
            cout<<ptr->getData().getInfo()<<"  ";
            InorderTransverse(ptr->getRightChild());
    }
}

void PreorderTransverse(Node *ptr){
    if(ptr!=nullptr){
            cout<<ptr->getData().getInfo()<<"  ";
            InorderTransverse(ptr->getLeftChild());
            InorderTransverse(ptr->getRightChild());
    }
}

void PostorderTransverse(Node *ptr){
    if(ptr!=nullptr){

            PostorderTransverse(ptr->getLeftChild());
            PostorderTransverse(ptr->getRightChild());
            cout<<ptr->getData().getInfo()<<"  ";


    }
}

Data InorderSucessor(Node *ptr){
    while(ptr->getLeftChild()!=nullptr){
        ptr=ptr->getLeftChild();
    }
    return ptr->getData();

}

Node * DeleteNode(Node *ptr,Data da){
    Node *parent,*tmp_root;
    tmp_root=ptr;
    while((ptr!=nullptr) && (da.getInfo()!=ptr->getData().getInfo())){
        parent=ptr;
        if(da.getInfo()<ptr->getData().getInfo()){
            ptr=ptr->getLeftChild();
        }
        else{
            ptr=ptr->getRightChild();
        }
    }

    if(ptr==nullptr){
        return nullptr;
    }
    else if(ptr->getLeftChild()==nullptr && ptr->getRightChild()==nullptr){
        if(da.getInfo()<parent->getData().getInfo()){
            parent->setLeftChild(nullptr);
        }
        else{
            parent->setRightChild(nullptr);
        }
    }
    else if(ptr->getLeftChild()==nullptr || ptr->getRightChild()==nullptr){
        if(da.getInfo()<parent->getData().getInfo()){
            if(ptr->getLeftChild()==nullptr){
                parent->setLeftChild(ptr->getRightChild());
            }
            else{
                parent->setLeftChild(ptr->getLeftChild());
            }
        }
        else{
            if(ptr->getLeftChild()==nullptr){
                parent->setRightChild(ptr->getRightChild());
            }
            else{
                parent->setRightChild(ptr->getLeftChild());
            }
        }
    }

    else{
        Data d;
        d=InorderSucessor(ptr->getRightChild());
        DeleteNode(tmp_root,d);
        ptr->setData(d);
    }
}


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
   HWND                hWnd;
   MSG                 msg;
   WNDCLASS            wndClass;
   GdiplusStartupInput gdiplusStartupInput;
   ULONG_PTR           gdiplusToken;

   // Initialize GDI+.
   GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

   wndClass.style          = CS_HREDRAW | CS_VREDRAW;
   wndClass.lpfnWndProc    = WndProc;
   wndClass.cbClsExtra     = 0;
   wndClass.cbWndExtra     = 0;
   wndClass.hInstance      = hInstance;
   wndClass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
   wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
   wndClass.hbrBackground  = (HBRUSH)GetStockObject(WHITE_BRUSH);
   wndClass.lpszMenuName   = NULL;
   wndClass.lpszClassName  = TEXT("GettingStarted");

   RegisterClass(&wndClass);

   hWnd = CreateWindow(
      TEXT("GettingStarted"),   // window class name
      TEXT("Trees"),  // window caption
      WS_OVERLAPPEDWINDOW,      // window style
      CW_USEDEFAULT,            // initial x position
      CW_USEDEFAULT,            // initial y position
      CW_USEDEFAULT,            // initial x size
      CW_USEDEFAULT,            // initial y size
      NULL,                     // parent window handle
      NULL,                     // window menu handle
      hInstance,                // program instance handle
      NULL);                    // creation parameters

   ShowWindow(hWnd, iCmdShow);
   UpdateWindow(hWnd);

   while(GetMessage(&msg, NULL, 0, 0))
   {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
   }

   GdiplusShutdown(gdiplusToken);
   return msg.wParam;
}  // WinMain

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
   WPARAM wParam, LPARAM lParam)
{
   HDC          hdc;
   PAINTSTRUCT  ps;

   switch(message)
   {
   case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);
      LoadTree(hdc);
      EndPaint(hWnd, &ps);
      //UserPromt(hdc);
      return 0;
   case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
   default:
      return DefWindowProc(hWnd, message, wParam, lParam);
   }
} // WndProc

int circle_X=500,circle_Y=50;

void BinarySearchTree:: Display(HDC hdc){



    /*for(int i=0;i<5;i++){




        wchar_t label[256]=L"kk";


         //wchar_t l[10]=std::to_wstring(5);

         //std::cout<<"d";
         //swprintf(label,L"%d",i);
        //int len = std::swprintf( label, 100, L"%s", L"Hello world" );


        circle_Y=circle_Y+100;

    }*/

    //printf("%d",root->getRightChild()->getData().getInfo());

    Node *temp;
    temp=root;

    /*Graphics    graphics(hdc);
    Pen      lineColor(Color(255, 76, 62, 59));
    SolidBrush  circleColor(Color(255, 128, 255, 64));
    SolidBrush  textColor(Color(255, 231, 104, 56));
    FontFamily  fontFamily(L"Times New Roman");
    Font        font(&fontFamily, 15, FontStyleRegular, UnitPixel);
    PointF      textPos(text_X, text_Y);


    graphics.FillEllipse(&circleColor,circle_X,circle_Y,50,50);
    graphics.DrawString(L"XX", -1, &font, textPos, &textColor);*/

    /*while((temp->getLeftChild()!=nullptr)||(temp->getRightChild()!=nullptr){
        DrawNode(temp->getRightChild(),circle_X,circle_Y,hdc);
        circle_X=circle_X+70;
        circle_Y=circle_Y+70;
        DrawNode(temp->getRightChild(),circle_X,circle_Y,hdc);
    }*/

    DrawNode(root,circle_X,circle_Y,hdc);

}

void DrawNode(Node *n,int circle_X,int circle_Y, HDC hdc){
    int text_X,text_Y,line_X1,line_Y1,line_X2,line_Y2;

    text_X=circle_X+10;
    text_Y=circle_Y+17;
    line_X1=circle_X+10;
    line_Y1=circle_Y+45;
    line_X2=line_X1-80+(n->getLevel()*15);
    line_Y2=line_Y1+80;

    Graphics    graphics(hdc);

    SolidBrush  circleColor(Color(255, 128, 255, 64));
    SolidBrush  textColor(Color(255, 38,38,38));
    FontFamily  fontFamily(L"Times New Roman");
    Font        font(&fontFamily, 15, FontStyleRegular, UnitPixel);
    PointF      textPos(text_X, text_Y);


    int inf=n->getData().getInfo();
    //int inf=n->getLevel();
    std::string s = std::to_string(inf);

    wstring cc;
    for(int i=0;i<s.length();i++){
        cc+=(wchar_t)s[i];
    }
    const wchar_t* label = cc.c_str();
    std::wstring name( L"fg" );
    const wchar_t* szName = name.c_str();

    graphics.FillEllipse(&circleColor,circle_X,circle_Y,50,50);
    graphics.DrawString(label, -1, &font, textPos, &textColor);



    if(n->getLeftChild()!=nullptr){
        Pen      lineColor(Color(255,253,42,1),2);
        graphics.DrawLine(&lineColor,line_X1,line_Y1,line_X2,line_Y2);

        //DrawNode(n->getLeftChild(),(circle_X-100),(circle_Y+100),hdc);
        DrawNode(n->getLeftChild(),(circle_X-100+(n->getLevel()*15)),(circle_Y+100),hdc);


    }
    if(n->getRightChild()!=nullptr){
        Pen      lineColor(Color(255,160,6,162),2);
        graphics.DrawLine(&lineColor,line_X1+30,line_Y1,(line_X2+200-(n->getLevel()*30)),(line_Y2));

        //DrawNode(n->getRightChild(),(circle_X+100),(circle_Y+100),hdc);
        DrawNode(n->getRightChild(),(circle_X+100-(n->getLevel()*15)),(circle_Y+100),hdc);

    }

}


void LoadTree(HDC hdc){

    BinarySearchTree T;
    Data data;

    /*cout<<"\n\t\tWelcome to Binary Search Tree\n";
    cout<<"\n\tSelect operation\n";
    cout<<"\t1. Insert node\n";
    cout<<"\t2. Search node\n";
    cout<<"\t1. Delete node\n\t";
    int choice;

    cin>>choice;
    switch(choice){
    case 1:
        cout<<"\tEnter data to be inserted\n\t";
        int da;
        cin>>da;
        data.setInfo(da);
        T.insertData(data);
        break;

    default:
        cout<<"\tEnter valid choice!!!\n";
        break;
    }*/


    data.setInfo(15);
    T.insertData(data);

     data.setInfo(17);
    T.insertData(data);

    data.setInfo(20);
    T.insertData(data);

     data.setInfo(11);
    T.insertData(data);

    data.setInfo(10);
    T.insertData(data);

    data.setInfo(19);
    T.insertData(data);

    data.setInfo(29);
    T.insertData(data);

    data.setInfo(28);
    T.insertData(data);

    data.setInfo(21);
    T.insertData(data);

    data.setInfo(33);
    T.insertData(data);

    data.setInfo(31);
    T.insertData(data);

    data.setInfo(32);
    T.insertData(data);

    data.setInfo(98);
    T.insertData(data);



    data.setInfo(12);
    T.insertData(data);

    data.setInfo(5);
    T.insertData(data);

    data.setInfo(21);
    T.insertData(data);

    data.setInfo(6);
    T.insertData(data);

    data.setInfo(7);
    T.insertData(data);



    data.setInfo(8);
    T.insertData(data);

    data.setInfo(1);
    T.insertData(data);

    data.setInfo(3);
    T.insertData(data);

    data.setInfo(2);
    T.insertData(data);

    data.setInfo(4);
    T.insertData(data);



    data.setInfo(8);
    T.insertData(data);

    data.setInfo(30);
    T.insertData(data);

    data.setInfo(13);
    T.insertData(data);

    //data.setInfo(3);
    //T.insertData(data);

    //T.Transversal();

    /*data.setInfo(13);

    if(T.Search(data)!=nullptr){
        cout<<T.Search(data)->getData().getInfo();
    }*/

    data.setInfo(8);

    T.Delete(data);



    T.Display(hdc);


}

void UserPromt(HDC hdc){



    while(1){

        cout<<"\n\t\tWelcome to Binary Search Tree\n";
        cout<<"\n\tSelect operation\n";
        cout<<"\t1. Insert node\n";
        cout<<"\t2. Search node\n";
        cout<<"\t1. Delete node\n\t";
        int choice;
        cin>>choice;
        switch(choice){
        case 1:
            cout<<"\tEnter data to be inserted\n\t";
            int da;
            cin>>da;
            //data.setInfo(da);
            //T.insertData(data);
            break;

        default:
            cout<<"\tEnter valid choice!!!\n";
            break;
        }
    }
}
