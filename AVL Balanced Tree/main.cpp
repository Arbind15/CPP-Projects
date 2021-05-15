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

void CalculateHeightDifference(Node*,int);


class Data{
private:
    int info;

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
    int level,diff,depth;
    Node *left_Child,*right_Child;

public:
    Node(){
        left_Child=nullptr;
        right_Child=nullptr;
        data.setInfo(-1);
        level=-1;
        diff=0;
        depth=0;

        //printf("node ");
    }
    void setData(Data d){
        data=d;
    }
    void setDepth(int x){
        depth=x;
    }
    void setLevel(int x){
        level=x;
    }
    int getDepth(){
        return depth;
    }
    int getLevel(){
        return level;
    }

    int getDiff(){
        return diff;
    }

    void setDiff(int x){
        diff=x;
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
    int Height;
public:
    BinarySearchTree(){
       root = new Node;
       Height=0;
       //printf("tree");
    }

    void InsertDataAVL(Data);

    void Display(HDC);

    void Transversal();

    Node * Search(Data);

    Node * Delete(Data da){
        DeleteNode(root,da);
    }

};

void BinarySearchTree::InsertDataAVL(Data d){

    if((root->getData().getInfo())==-1){
            root->setData(d);
            root->setLevel(0);
            root->setDiff(0);
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

        new_node->setDepth(x);
        Height=x;

        if(d.getInfo() < parent->getData().getInfo()){
            parent->setLeftChild(new_node);
        }
        else{
            parent->setRightChild(new_node);
        }
    }

    CalculateHeightDifference(root,0);
}

void CalculateHeightDifference(Node *ptr,int i){
    if(ptr!=nullptr){
        CalculateHeightDifference(ptr->getLeftChild(),i);
        i++;
        CalculateHeightDifference(ptr->getRightChild(),i);
        i--;
    }

}

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

    Node *temp;
    temp=root;

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

    graphics.FillEllipse(&circleColor,circle_X,circle_Y,50,50);
    graphics.DrawString(label, -1, &font, textPos, &textColor);

     inf=n->getDiff();
    //int inf=n->getLevel();
    s = std::to_string(inf);
    wstring cc1;
    for(int i=0;i<s.length();i++){
        cc1+=(wchar_t)s[i];
    }
    label = cc1.c_str();

    PointF      textPosDiff(text_X+25, text_Y-25);
    graphics.DrawString(label, -1, &font, textPosDiff, &textColor);


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

    data.setInfo(20);
    T.InsertDataAVL(data);

    data.setInfo(2);
    T.InsertDataAVL(data);

    data.setInfo(22);
    T.InsertDataAVL(data);

    data.setInfo(10);
    T.InsertDataAVL(data);

    data.setInfo(12);
    T.InsertDataAVL(data);

    data.setInfo(3);
    T.InsertDataAVL(data);

    data.setInfo(11);
    T.InsertDataAVL(data);


    T.Display(hdc);


}
