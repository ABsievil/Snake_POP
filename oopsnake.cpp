#include <iostream> 
#include<windows.h>  
#include<vector>
#include<cstdlib>  //hàm random rand
#include<ctime>    //hàm random theo time srand
#include<conio.h>  //thư viện để sử dụng hàm kbhit() và hàm getch()-phát hiện nhấn nút
#include<string>
using namespace std;

//biến toàn cục
int man,mucdo;
int tdx0,tdy0;

// khai báo lớp
class Point;
class Account;
class Menu;
class BXH;
class Control;
class Snake;

// khai báo hàm
void Frame();
void gotoxy(int,int);
void SetColor(int,int);
void Start();
void Left();
void Right();
void Top();
void Bottom();
void Main_activity();

int main(){
SetColor(0,2);   //màu(nền,chữ);
SetConsoleOutputCP(65001);  

Main_activity();

//Start();  
//Frame();


  system("pause");
  return 0;
}

class Point{
    private:
      int x_Point,y_Point,diem=0;
    public:
      void set_Point();
      int get_diem(){return diem;}
};
void Point::set_Point(){
     srand(time(NULL));
     x_Point=rand()%(49-1+1)+1;
     y_Point=rand()%(24-1+1)+1;
}

class Account{
    private:
       string name;
    public:
       void set_Account();   
       string get_name(){
        return name;
       }
};
void Account::set_Account(){
     cout<<"nhập tên tài khoản:";
     cin.ignore(1,'\n');
     getline(cin,name);
}

class Menu:public Point, public Account{
     public:
       void set_Menu();
};
void Menu::set_Menu(){
  gotoxy(52,0);cout<<"tài khoản:"<<get_name();
  gotoxy(52,1);cout<<"Point:";
  gotoxy(58,1);cout<<get_diem();
  gotoxy(52,3);cout<<"I> PAUSE:   Nhấn Space";
  gotoxy(52,5);cout<<"play again: Nhấn Enter ";
  gotoxy(52,7);cout<<"suggest: nhấn nút di chuyển liên tục để rắn chạy nhanh hơn";  
  gotoxy(52,9);cout<<"ĐIỀU KHIỂN:";
  gotoxy(56,10);cout<<"▲";
  gotoxy(54,11);cout<<"◄   ►";
  gotoxy(56,12);cout<<"▼";
}

class BXH: public Menu{  //kế thừa thuộc tính điểm và name
     public:
        void set_BXH();  
};
void BXH::set_BXH(){
  gotoxy(24,13);cout<<"4";Sleep(1000);gotoxy(25,13);cout<<" ";
  gotoxy(24,13);cout<<"3";Sleep(1000);gotoxy(25,13);cout<<" ";
  gotoxy(24,13);cout<<"2";Sleep(1000);gotoxy(25,13);cout<<" ";
  gotoxy(24,13);cout<<"1";Sleep(1000);system("cls");
  SetColor(0,2);
  gotoxy(1,0);cout<<"RANK";
  gotoxy(1,2);cout<<"1";
  gotoxy(1,3);cout<<"2";
  gotoxy(1,4);cout<<"3";
  gotoxy(1,5);cout<<"4";
  gotoxy(1,6);cout<<"5";
  for(int m=0;m<31;m++){gotoxy(m,1);cout<<"-";
                        gotoxy(m,7);cout<<"-";}
  for(int i=0;i<7;i++){gotoxy(5,i);cout<<"|";}
  gotoxy(6,0);cout<<"     ACCOUNT";
  for(int j=0;j<7;j++){gotoxy(25,j);cout<<"|";}
  gotoxy(26,0);cout<<"POINT";
  gotoxy(0,8);cout<<"play again: Nhấn Enter ";

label:        //nếu nhấn phím enter thì play again
          if(kbhit){
        char dieukhien=getch();
        if(dieukhien==13){main();}
        else {goto label;}     //nếu không phải phím enter mà phím khác thì ko nhận mà cho phép bấm đến khi nào là phím enter thì thoi
         
       }
}

class Snake{
     private:
        vector<string> v;   //hình ảnh mỗi đốt
        vector<int> x_v,y_v;    //tọa độ mỗi đốt
     public:
        void set_Snake(); 
        int get_v(){return v.size();}
        int get_x_v(){return x_v[0];}
        int get_y_v(){return y_v[0];}
        void Right();
};
void Snake::set_Snake(){
v.push_back("*");
v.push_back("*");
v.push_back("*");
x_v.push_back(tdx0);y_v.push_back(tdy0);
}

class Control:public Snake{
      private:
          
      public:  
         void random_Control();
};
void Control::random_Control(){
    //con rắn di chuyển theo hướng ngẫu nhiên
    srand(time(NULL));
    switch(2){//rand()%(4-1+1)+1
    case 1:Left();break;
    case 2:Right();break;
    case 3:Top();break;
    case 4:Bottom();break;
    }
    
}


void Snake::Right(){
  Snake snake;
    for(int i=snake.get_x_v();i<=50;i++){
       if(x_v[0]==tdx0)
       { 
         //gán tọa độ các đốt phía sau
        for(int i=1;i<get_v();i++){
          x_v.push_back(x_v[i-1]);  y_v.push_back(y_v[i-1]);
        }
        //cout hình ảnh các đốt
         for(int j=0;j<get_v();j++){
          gotoxy(x_v[j],y_v[j]); cout<<v[j];
        }
       }
       else if(x_v[0]==50) cout<<"GAME OVER";
       else 
       {
        x_v[0]=i;
        //gán tọa độ các đốt phía sau
        for(int i=1;i<get_v();i++){
        x_v[i]=x_v[i-1];y_v[i]=y_v[i-1];
        }
        //cout hình ảnh các đốt
         for(int j=0;j<get_v();j++){
          gotoxy(x_v[j],y_v[j]); cout<<v[j];
        }                
       }
    }
};




void Left(){
};



void Top(){};

void Bottom(){};

void Main_activity(){
    //random ngẫu nhiên tọa độ con rắn 
    srand(time(NULL));
    tdx0=rand()%(45-5+1)+5;
    tdy0=rand()%(20-5+1)+5;
    Snake snake;
    snake.set_Snake();
    Control control;
    control.random_Control();

};


void gotoxy( int x,int y)   //hàm tọa độ
{
  static HANDLE h = NULL;  
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };  
  SetConsoleCursorPosition(h,c);
};

void SetColor(int backgound_color, int text_color) //hàm màu
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    int color_code = backgound_color * 16 + text_color;
    SetConsoleTextAttribute(hStdout, color_code);
}

void Frame(){   //khung trò chơi
   for(int i=0;i<=50;i++){
     for(int j=0;j<=25;j++){
        if(j==0 || j==25){
            gotoxy(i,j); cout<<"-";
        }
        else if(i==0 || i==50){
            gotoxy(i,j); cout<<"|";
        }
     }
   }
}

void Start(){     // giao diện khởi động
cout<<"\n\t------------> Welcome to Snake Game <-----------\n";
cout<<"             ----->(nhấn 1 để bắt đầu trò chơi)<-----"<<endl<<"                  ══════════════════════════════"<<endl;
SetColor(0,5);    
    cout<<"\n                             . ***.*.*";
    cout<<"\n                           * *****XXX ****";
    cout<<"\n  __                      * **** * *       *";
    cout<<"\n |  |     |\\    |      //||*                *      /\\      |  /  |_____";
    cout<<"\n  \\       | \\   |     // ||*                *     /  \\     | /   |";
    cout<<"\n   \\      |  \\  |           *               *    /____\\    |/    |---";
    cout<<"\n |  |     |   \\ |            *             *    /      \\   | \\   |";
    cout<<"\n  --      |    \\|             *           *    /        \\  |  \\  |_____";
    cout<<"\n                               *        *";
    cout<<"\n                               *......*";
    cout<<"\n                              *.....*";
    cout<<"\n                             *....*.*.*..*.";
    cout<<"\n                            *....*......... **.*.*";
    cout<<"\n                           *....** * * * ..........*****";
    cout<<"\n                           *.....**       *.****.* .......*";
    cout<<"\n                             *.* *            *.*  ****....*";
    cout<<"\n                                            *.......****...*";
    cout<<"\n                                           *....**........*";
    cout<<"\n                               *.*.*       *...*    ****";
    cout<<"\n                             *.......*     *...*";
    cout<<"\n                           *...*  *....*..*....*";
    cout<<"\n                         *..*        **.......*";
    cout<<"\n                       *.*              **.**";
    cout<<"\n                     **";
    cout<<"\n                    *";
int start;   
SetColor(0,2);                                
do{gotoxy(0,5);cin>>start;}while(start!=1);
system("cls");
if(start==1){

//màn bình thường
    for(int i=0;i<=20;i++){
gotoxy(i,0);cout<<"=";
gotoxy(i,10);cout<<"=";
}
for(int j=1;j<10;j++){
    gotoxy(0,j);cout<<"|";
    gotoxy(20,j);cout<<"|";
}
gotoxy(5,12);cout<<"MÀN 1(nhấn 1)";
//màn có vật cản
    for(int i=30;i<=50;i++){
gotoxy(i,0);cout<<"=";
gotoxy(i,10);cout<<"=";
}
for(int j=1;j<10;j++){
    gotoxy(30,j);cout<<"|";
    gotoxy(50,j);cout<<"|";
}
  for(int k=33;k<=47;k++){
    if(k<=37){
gotoxy(k,3);cout<<"=";
gotoxy(k,7);cout<<"=";
    }
    else if(43<=k & k<=47){
gotoxy(k,3);cout<<"=";
gotoxy(k,7);cout<<"=";      
    }
  }
  for(int z=4;z<=6;z++){
    gotoxy(33,z);cout<<"|";
    gotoxy(37,z);cout<<"|";   
    gotoxy(43,z);cout<<"|";
    gotoxy(47,z);cout<<"|";  
    
  }
gotoxy(35,12);cout<<"MÀN 2(nhấn 2)";
gotoxy(0,14);cout<<"hãy chọn màn chơi:";
gotoxy(18,14); cin>>man; 
system("cls");
cout<<"hãy chọn độ khó:"<<endl<<endl<<"CỰC KHÓ(nhấn 1)"<<endl<<"KHÓ(nhấn 2)"<<endl<<"BÌNH THƯỜNG(nhấn 3)"<<endl<<"DỄ(nhấn 4)"<<endl<<"---------------------------"<<endl;
int dokho;
do{cin>>dokho;}while(dokho!=1 && dokho!=2 && dokho!=3 && dokho!=4);
system("cls");
cout<<"4";
Sleep(1000);
system("cls");
cout<<"3";
Sleep(1000);
system("cls");
cout<<"2";
Sleep(1000);
system("cls");
cout<<"1";
Sleep(1000);
system("cls");
cout<<"GO!";
Sleep(1000);
system("cls");

if(dokho==4){mucdo=200;}
else if(dokho==3){mucdo=150;}
else if(dokho==2){mucdo=130;}
else if(dokho==1){mucdo=100;}
}
}