#include <iostream> //bản demo 12/12 hoàn thành cơ bản ..13/12 hoàn thành cơ bản chức năng ..14/12 đồ họa cơ bản,chức năng pause  16/12 thiếu nhiều c/n nhỏ.....3/1 up thêm tính năng màn chơi thứ 2, fix một số bug ẩn...15/1 hiệu chỉnh lại đồ họa game......16/1 fix bug xóa tọa độ (0,0)
#include<windows.h>  
#include<vector>
#include<cstdlib>  //hàm random rand
#include<ctime>    //hàm random theo time srand
#include<conio.h>  //thư viện để sử dụng hàm kbhit() và hàm getch()-phát hiện nhấn nút
#include<string>
using namespace std;
//(còn nhiều bug ẩn) bug xóa tọa độ 0,0 . game nặng quá nhiều khi không in ra con rắn or do máy cấu hình yếu, một phần do random ngẫu nhiên nên nếu random trúng tường phải mất time random lại

// các biến toàn cục
int a,b,A,B;   //tọa độ mồi 
vector<string> v;
int arx[100],ary[100];   
int mucdo;  //chọn độ khó trò chơi
int pt[5]={0,0,0,0,0},point=0;   //pt là mảng lưu điểm cho mỗi lần chơi, point là lần chơi thứ point
string name[5];                  //mảng lưu tên cho mỗi lần chơi
int bxh[5];                      //mảng lưu điểm để in ra bxh
int man;              //man là biến lưu màn đã chọn, manchoi[man] là mảng chọn màn chơi hiện tại
 int tdx0,tdy0;       //tọa độ đốt đầu tiên lúc ban đầu 

struct toado{
   int x,y;
};
struct toado td;      

//khai báo hàm
void dieukhienlentren(toado td);
void dieukhienxuongduoi(toado td);
void dieukhiensangtrai(toado td);
void dieukhiensangphai(toado td);
void tentaikhoan();
void gotoxy(int x, int y);
void bangxephang();
void moi();
void menu();
void giaodienstart();
void sapxepdiem();
int main();
void SetColor(int backgound_color, int text_color);
void Nocursortype();
void Yescursortype();
void khungtrochoi();





int main(){
if(point==5){point=0;pt[0]=0;pt[1]=0;pt[2]=0;pt[3]=0;pt[4]=0;pt[5]=0;}
system("cls");
Yescursortype();   //hiện trỏ chuột
pt[point];         //mảng bảng điểm
v.clear();         //xóa all phần tử trong vector v (xóa đốt con rắn)
v.push_back("*"); //đẩy * vào vector v
v.push_back("*"); 
v.push_back("*");

SetColor(0,2);   //màu(nền,chữ);
SetConsoleOutputCP(65001);   //tiếng việt not hàm
giaodienstart(); 
Nocursortype();//ẩn trỏ chuột
khungtrochoi();
moi();
menu();

//khởi tạo tọa độ đốt đầu tiên
  //nếu tọa độ 3 đốt đầu trùng với tọa độ mồi thì random lại
 if(man==1){ 
 srand(time(NULL));
 td.x=rand()%(47-3+1)+3;
 td.y=rand()%(22-3+1)+3;
 tdx0=td.x;tdy0=td.y;    //lưu tọa độ ban đầu vào tdx0 và tdy0
 }

else if(man==2){       //nếu chọn màn 2 mà tọa độ ban đầu trùng với tường phía bên trong khung trò chơi thì random lại 
  
  srand(time(NULL));
  int mienvitri=rand()%(5-1+1)+1;   //chọn một trong các vùng trống để khởi tạo vị trí rắn
  if(mienvitri==1){
 srand(time(NULL));
 td.x=rand()%(47-3+1)+3;
 td.y=rand()%(5-3+1)+3;
  }
  else if(mienvitri==2){
    srand(time(NULL));
 td.x=rand()%(47-3+1)+3;
 td.y=rand()%(22-19+1)+3;
  }
  else if(mienvitri==3){
    srand(time(NULL));
 td.x=rand()%(7-3+1)+3;
 td.y=rand()%(22-3+1)+3;
  }
  else if(mienvitri==4){
    srand(time(NULL));
 td.x=rand()%(27-23+1)+3;
 td.y=rand()%(22-3+1)+3;
  }
  else if(mienvitri==5){
    srand(time(NULL));
 td.x=rand()%(47-43+1)+3;
 td.y=rand()%(22-3+1)+3;
  }
  tdx0=td.x; tdy0=td.y;
}

int dichuyenngaunhien;    //tự động random hướng di chuyển ban đầu gòm 4 hướng kí hiệu từ 1 đến 4
 srand(time(NULL));
 dichuyenngaunhien=rand()%(4-1+1)+1;
 if(dichuyenngaunhien==1){       //di chuyển sang phải
  for(td.x;td.x<=50;td.x++){   
     if(td.x==tdx0){   //vị trí rắn ban đầu    
       for(int k=0;k<v.size();k++){   //gán tọa độ cho 3 đốt đầu tiên
     arx[k]=td.x-k;ary[k]=td.y;
      }    
     for(int i=0;i<v.size();i++){    //cout ra 3 đốt đầu tiên
      gotoxy(arx[i],ary[i]);cout<<v[i];
        }
     }
     else if(td.x==50){           // đụng tường thì chết
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang();      
     }

     else{   //code chính điều khiển hướng đi của rắn
for(int m=v.size()-1;m>=0;m--){
 if(m>0) {arx[m]=arx[m-1];ary[m]=ary[m-1];}  //gắn tọa độ các đốt phía sau
  
 else if(m==0){arx[m]=td.x;//gắn tọa độ đốt ban đầu
    if(arx[m]==a && ary[m]==b){ //nếu ăn được mồi thì tăng thêm một đốt
          v.push_back("*");
          arx[v.size()-1]=arx[v.size()-2];ary[v.size()-1]=ary[v.size()-2];
          pt[point]++;          //mồi nhỏ cộng 1 point
          moi();
          gotoxy(58,1);cout<<pt[point];
    }
 }  
  
}     
     for(int u=0;u<v.size()-1;u++) {gotoxy(arx[u],ary[u]);cout<<v[u];}   //in ra các đốt
}

if(man==2){
      for(int k=10;k<=40;k++){
    if(k<=20){
if((td.x==k && td.y==8)||(td.x==k && td.y==16)){
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang();
}
    }
    else if(30<=k && k<=40){
if((td.x==k && td.y==8)||(td.x==k && td.y==16)){
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang();
      }     
    }
}
  for(int z=8;z<=16;z++){
    if((td.x==10 && td.y==z)||(td.x==20 && td.y==z)||(td.x==30 && td.y==z)||(td.x==40 && td.y==z)){
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang();
     }
 }
}

if(kbhit()){    //phát hiện nhấn phím
          char dieukhien=getch();
          if(dieukhien==77){  // điều khiển sang phải
          dieukhiensangphai(td);
          }       
          else if(dieukhien==75){  // điều khiển sang trái
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang();       
          }  
          else if(dieukhien==80){ // điều khiển xuống dưới
          dieukhienxuongduoi(td);
          } 
          else if(dieukhien==72){  // điều khiển lên trên
          dieukhienlentren(td);
          }
          else if(dieukhien==32) {gotoxy(0,26); system("pause");}    //tạm dừng game
          else if(dieukhien==13) main();
         }
   
    Sleep(mucdo);  
    if(td.x<50){gotoxy(arx[v.size()-1],ary[v.size()-1]);cout<<" ";}  //tọa độ đốt cuối cùng sẽ bị xóa

  }
 }
 else if(dichuyenngaunhien==2){  //di chuyển sang trái
   for(td.x;td.x>=0;td.x--){
    if(td.x==tdx0){
      for(int k=0;k<v.size();td.x++){
        arx[k]=td.x+k;ary[k]=td.y;
      }
      for(int i=0;i<v.size();i++){    //cout ra 3 đốt đầu tiên
      gotoxy(arx[i],ary[i]);cout<<v[i];
        }
    }

    else if(td.x==0){           // đụng tường thì chết
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang();      
     }

    else{   //code chính điều khiển hướng đi của rắn
for(int m=v.size()-1;m>=0;m--){
 if(m>0) {arx[m]=arx[m-1];ary[m]=ary[m-1];}  //gắn tọa độ các đốt phía sau
  
 else if(m==0){arx[m]=td.x;//gắn tọa độ đốt ban đầu
    if((arx[m]==a && ary[m]==b)){ //nếu ăn được mồi thì tăng thêm một đốt
          v.push_back("*");
          arx[v.size()-1]=arx[v.size()-2];ary[v.size()-1]=ary[v.size()-2];
          pt[point]++;          //mồi nhỏ cộng 1 point
          moi();
          gotoxy(58,1);cout<<pt[point];
    }
 }  
  
}     
     for(int u=0;u<v.size()-1;u++) {gotoxy(arx[u],ary[u]);cout<<v[u];}   //in ra các đốt
}

if(man==2){
      for(int k=10;k<=40;k++){
    if(k<=20){
if((td.x==k && td.y==8)||(td.x==k && td.y==16)){
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang();
}
    }
    else if(30<=k & k<=40){
if((td.x==k && td.y==8)||(td.x==k && td.y==16)){
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang();
      }     
    }
}
  for(int z=8;z<=16;z++){
    if((td.x==10 && td.y==z)||(td.x==20 && td.y==z)||(td.x==30 && td.y==z)||(td.x==40 && td.y==z)){
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang();
     }
 }
}

if(kbhit()){    //phát hiện nhấn phím
          char dieukhien=getch();
          if(dieukhien==77){  // điều khiển sang phải
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang(); 
          }       
          else if(dieukhien==75){  // điều khiển sang trái
          dieukhiensangtrai(td);      
          }  
          else if(dieukhien==80){ // điều khiển xuống dưới
          dieukhienxuongduoi(td);
          } 
          else if(dieukhien==72){  // điều khiển lên trên
          dieukhienlentren(td);
          }
          else if(dieukhien==32) {gotoxy(0,26); system("pause");}    //tạm dừng game
          else if(dieukhien==13) main();
         }
   
    Sleep(mucdo);  
    if(td.x<50){gotoxy(arx[v.size()-1],ary[v.size()-1]);cout<<" ";}  //tọa độ đốt cuối cùng sẽ bị xóa

   }
 }
 else if(dichuyenngaunhien==3){  //di chuyển lên trên
  for(td.y;td.y>=0;td.y--){
    if(td.y==tdy0){
      for(int k=0;k<v.size();k++){
        arx[k]=td.x;ary[k]=td.y+k;
      }
      for(int i=0;i<v.size();i++){    //cout ra 3 đốt đầu tiên
      gotoxy(arx[i],ary[i]);cout<<v[i];
        }
    }

    else if(td.y==0){           // đụng tường thì chết
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang();      
     }
  
    else{   //code chính điều khiển hướng đi của rắn
for(int m=v.size()-1;m>=0;m--){
 if(m>0) {arx[m]=arx[m-1];ary[m]=ary[m-1];}  //gắn tọa độ các đốt phía sau
  
 else if(m==0){ary[m]=td.y;//gắn tọa độ đốt ban đầu
    if((arx[m]==a && ary[m]==b)){ //nếu ăn được mồi thì tăng thêm một đốt
          v.push_back("*");
          arx[v.size()-1]=arx[v.size()-2];ary[v.size()-1]=ary[v.size()-2];
          pt[point]++;          //mồi nhỏ cộng 1 point
          moi();
          gotoxy(58,1);cout<<pt[point];
    }
 }  
  
}     
     for(int u=0;u<v.size()-1;u++) {gotoxy(arx[u],ary[u]);cout<<v[u];}   //in ra các đốt
}

if(man==2){
      for(int k=10;k<=40;k++){
    if(k<=20){
if((td.x==k && td.y==8)||(td.x==k && td.y==16)){
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang();
}
    }
    else if(30<=k && k<=40){
if((td.x==k && td.y==8)||(td.x==k && td.y==16)){
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang();
      }     
    }
}
  for(int z=8;z<=16;z++){
    if((td.x==10 && td.y==z)||(td.x==20 && td.y==z)||(td.x==30 && td.y==z)||(td.x==40 && td.y==z)){
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang();
     }
 }
}

if(kbhit()){    //phát hiện nhấn phím
          char dieukhien=getch();
          if(dieukhien==77){  // điều khiển sang phải
          dieukhiensangphai(td);
          }       
          else if(dieukhien==75){  // điều khiển sang trái
          dieukhiensangtrai(td);      
          }  
          else if(dieukhien==80){ // điều khiển xuống dưới
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang();  
          } 
          else if(dieukhien==72){  // điều khiển lên trên
          dieukhienlentren(td);
          }
          else if(dieukhien==32) {gotoxy(0,26); system("pause");}    //tạm dừng game
          else if(dieukhien==13) main();
         }
   
    Sleep(mucdo);  
    if(td.x<50){gotoxy(arx[v.size()-1],ary[v.size()-1]);cout<<" ";}  //tọa độ đốt cuối cùng sẽ bị xóa

  }
 }
 else if(dichuyenngaunhien==4){  //di chuyển xuống dưới
   for(td.y;td.y<=25;td.y++){
    if(td.y==tdy0){
      for(int k=0;k<v.size();k++){
        arx[k]=td.x;ary[k]=td.y-k;
      }
      for(int i=0;i<v.size();i++){    //cout ra 3 đốt đầu tiên
      gotoxy(arx[i],ary[i]);cout<<v[i];
        }
    }

    else if(td.y==25){           // đụng tường thì chết
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang();      
     }
 
    else{   //code chính điều khiển hướng đi của rắn
for(int m=v.size()-1;m>=0;m--){
 if(m>0) {arx[m]=arx[m-1];ary[m]=ary[m-1];}  //gắn tọa độ các đốt phía sau
  
 else if(m==0){ary[m]=td.y;//gắn tọa độ đốt ban đầu
    if((arx[m]==a && ary[m]==b)){ //nếu ăn được mồi thì tăng thêm một đốt
          v.push_back("*");
          arx[v.size()-1]=arx[v.size()-2];ary[v.size()-1]=ary[v.size()-2];
          pt[point]++;          //mồi nhỏ cộng 1 point
          moi();
          gotoxy(58,1);cout<<pt[point];
    }
 }  
  
}     
     for(int u=0;u<v.size()-1;u++) {gotoxy(arx[u],ary[u]);cout<<v[u];}   //in ra các đốt
}

if(man==2){
      for(int k=10;k<=40;k++){
    if(k<=20){
if((td.x==k && td.y==8)||(td.x==k && td.y==16)){
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang();
}
    }
    else if(30<=k && k<=40){
if((td.x==k &td.y==8)||(td.x==k && td.y==16)){
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang();
      }     
    }
}
  for(int z=8;z<=16;z++){
    if((td.x==10 && td.y==z)||(td.x==20 && td.y==z)||(td.x==30 && td.y==z)||(td.x==40 &&td.y==z)){
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang();
     }
 }
}

if(kbhit()){    //phát hiện nhấn phím
          char dieukhien=getch();
          if(dieukhien==77){  // điều khiển sang phải
          dieukhiensangphai(td);
          }       
          else if(dieukhien==75){  // điều khiển sang trái
          dieukhiensangtrai(td);       
          }  
          else if(dieukhien==80){ // điều khiển xuống dưới
          dieukhienxuongduoi(td);
          } 
          else if(dieukhien==72){  // điều khiển lên trên
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang(); 
          }
          else if(dieukhien==32) {gotoxy(0,26); system("pause");}    //tạm dừng game
          else if(dieukhien==13) main();
         }
   
    Sleep(mucdo);  
    if(td.x<50){gotoxy(arx[v.size()-1],ary[v.size()-1]);cout<<" ";}  //tọa độ đốt cuối cùng sẽ bị xóa
   }
}


return 0;
}


void SetColor(int backgound_color, int text_color) //hàm màu
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    int color_code = backgound_color * 16 + text_color;
    SetConsoleTextAttribute(hStdout, color_code);
}

void gotoxy( int x,int y)   //hàm tọa độ
{
  static HANDLE h = NULL;  
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };  
  SetConsoleCursorPosition(h,c);
};

void Nocursortype()        //hàm ẩn trỏ chuột
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void Yescursortype()        //hàm hiện trỏ chuột
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = TRUE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void giaodienstart(){
cout<<"chào mừng bạn đến với trò chơi"<<endl;
cout<<endl<<"            START            "<<endl;
cout<<"(nhấn 1 để bắt đầu trò chơi)"<<endl<<"════════════════════════════"<<endl;
int start;                                   
do{gotoxy(0,5);cin>>start;}while(start!=1);
system("cls");
tentaikhoan();
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
cout<<"hãy chọn độ khó:"<<"KHÁCH TEST GAME VUI LÒNG CHỌN CẤP 1(mấy cấp sau bị delay nma do dev lười nên chưa fix)"<<endl<<endl<<"CỰC KHÓ(nhấn 1)"<<endl<<"KHÓ(nhấn 2)"<<endl<<"BÌNH THƯỜNG(nhấn 3)"<<endl<<"DỄ(nhấn 4)"<<endl<<"---------------------------"<<endl;
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

void tentaikhoan(){         //nhập tên tài khoản
     cout<<"nhập tên tài khoản:";
     cin>>name[point];
}

void moi(){                //tạo mồi
  if(pt[point]%5==0 && pt[point]!=0){       //mồi lớn
   srand(time(NULL));
   A=rand()%(49-1+1)+1;
   B=rand()%(24-1+1)+1;
   if(man==2){
      for(int k=10;k<=40;k++){
    if(k<=20){
      for(int u=8;u<=16;u++){
        do{srand(time(NULL));
        A=rand()%(49-1+1)+1;
        B=rand()%(24-1+1)+1;}while(A==k && B==u);
      }
    }
    else if(30<=k && k<=40){
       for(int u=8;u<=16;u++){
        do{srand(time(NULL));
        A=rand()%(49-1+1)+1;
        B=rand()%(24-1+1)+1;}while(A==k && B==u);
      } 
    }
 }
}

   gotoxy(A,B);cout<<"O";
  }
  else {                                   //mồi nhỏ
   srand(time(NULL));
   a=rand()%(49-1+1)+1;
   b=rand()%(24-1+1)+1;
   if(man==2){
      for(int k=10;k<=40;k++){
    if(k<=20){
      for(int u=8;u<=16;u++){
        do{srand(time(NULL));
        a=rand()%(49-1+1)+1;
        b=rand()%(24-1+1)+1;}while(a==k && b==u);
      }
    }
    else if(30<=k && k<=40){
       for(int u=8;u<=16;u++){
        do{srand(time(NULL));
        a=rand()%(49-1+1)+1;
        b=rand()%(24-1+1)+1;}while(a==k && b==u);
      } 
    }
 }
}

   gotoxy(a,b);cout<<"o";
   }
  
};

void khungtrochoi(){  //buld khung trò chơi gồm màn 1 và màn 2
if(man==1){
gotoxy(0,0);cout<<"╔";
gotoxy(50,0);cout<<"╗";
gotoxy(0,25);cout<<"╚";
gotoxy(50,25);cout<<"╝";
for(int i=1;i<50;i++){
  gotoxy(i,0);cout<<"═";
  gotoxy(i,25);cout<<"═";
}
for(int j=1;j<25;j++){
  gotoxy(0,j);cout<<"║";
  gotoxy(50,j);cout<<"║";
}
}

else if(man==2){
gotoxy(0,0);cout<<"╔";
gotoxy(50,0);cout<<"╗";
gotoxy(0,25);cout<<"╚";
gotoxy(50,25);cout<<"╝";
for(int i=1;i<50;i++){
  gotoxy(i,0);cout<<"═";
  gotoxy(i,25);cout<<"═";
}
for(int j=1;j<25;j++){
  gotoxy(0,j);cout<<"║";
  gotoxy(50,j);cout<<"║";
}
//code phía dưới thêm 2 khung nhỏ của màn 2
//khung bên trái:
gotoxy(10,8);cout<<"╔";
gotoxy(20,8);cout<<"╗";
gotoxy(10,16);cout<<"╚";
gotoxy(20,16);cout<<"╝";
for(int i=11;i<20;i++){
  gotoxy(i,8);cout<<"═";
  gotoxy(i,16);cout<<"═";
}
for(int j=9;j<16;j++){
  gotoxy(10,j);cout<<"║";
  gotoxy(20,j);cout<<"║";
}
//khung bên phải:
gotoxy(30,8);cout<<"╔";
gotoxy(40,8);cout<<"╗";
gotoxy(30,16);cout<<"╚";
gotoxy(40,16);cout<<"╝";
for(int i=31;i<40;i++){
  gotoxy(i,8);cout<<"═";
  gotoxy(i,16);cout<<"═";
}
for(int j=9;j<16;j++){
  gotoxy(30,j);cout<<"║";
  gotoxy(40,j);cout<<"║";
}
}
};

void menu(){           //hiển thị menu khi chơi
  gotoxy(52,0);cout<<"tài khoản:"<<name[point];
  gotoxy(52,1);cout<<"Point:";
  gotoxy(58,1);cout<<pt[point];
  gotoxy(52,3);cout<<"I> PAUSE:   Nhấn Space";
  gotoxy(52,5);cout<<"play again: Nhấn Enter ";
  gotoxy(52,7);cout<<"suggest: nhấn nút di chuyển liên tục để rắn chạy nhanh hơn";  
  gotoxy(52,9);cout<<"ĐIỀU KHIỂN:";
  gotoxy(56,10);cout<<"▲";
  gotoxy(54,11);cout<<"◄   ►";
  gotoxy(56,12);cout<<"▼";
}

void sapxepdiem(){      //sx điểm trong mục bxh
for(int m=0;m<4;m++){   // sắp xếp điểm sau đó lưu điểm và tên vào tên theo thứ tự từ 1-4
   for(int i=0;i<4;i++){
       if(pt[i]<pt[i+1]){
        int c;string d;
        c=pt[i];pt[i]=pt[i+1];pt[i+1]=c;
        d=name[i];name[i]=name[i+1];name[i+1]=d;
       }
   }
}
for(int u=0;u<5;u++)bxh[u]=pt[u];
}

void bangxephang(){
  gotoxy(24,13);cout<<"4";Sleep(1000);gotoxy(25,13);cout<<" ";
  gotoxy(24,13);cout<<"3";Sleep(1000);gotoxy(25,13);cout<<" ";
  gotoxy(24,13);cout<<"2";Sleep(1000);gotoxy(25,13);cout<<" ";
  gotoxy(24,13);cout<<"1";Sleep(1000);system("cls");
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

sapxepdiem();
for(int u=0;u<=::point;u++){
  gotoxy(6,2+u);cout<<name[u];
  gotoxy(28,2+u);cout<<bxh[u];
}   
label:        //nếu nhấn phím enter thì play again
          if(kbhit){
        char dieukhien=getch();
        if(dieukhien==13){::point++;main();}
        else {goto label;}     //nếu không phải phím enter mà phím khác thì ko nhận mà cho phép bấm đến khi nào là phím enter thì thoi
         
       }

};

void dieukhienlentren(toado td){
        gotoxy(arx[v.size()-1],ary[v.size()-1]);cout<<" ";
        for(td.y--;td.y>=0;td.y--){
           for(int d=v.size()-1;d>=0;d--){
            if(d>0){arx[d]=arx[d-1];ary[d]=ary[d-1];}
            else if(d==0){ary[d]=td.y;
                if((arx[d]==a && ary[d]==b)||(arx[d]==A && ary[d]==B)){ //nếu ăn được mồi thì tăng thêm một đốt
           v.push_back("*");
           arx[v.size()-1]=arx[v.size()-2];ary[v.size()-1]=ary[v.size()-2];
           if(arx[d]==a && ary[d]==b)pt[point]++;
           else if(arx[d]==A && ary[d]==B)pt[point]+=2;
           moi();
           gotoxy(58,1);cout<<pt[point];
           if(arx[d]==A && ary[d]==B) {::A=80;::B=0;}
    }
    if(ary[d]==0){ gotoxy(20,12);cout<<"GAME OVER";
       bangxephang();       
   }
    if(man==2){
      for(int k=10;k<=40;k++){
    if(k<=20){
if((td.x==k && td.y==8)||(td.x==k && td.y==16)){
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang();
}
    }
    else if(30<=k && k<=40){
if((td.x==k && td.y==8)||(td.x==k && td.y==16)){
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang();
      }     
    }
}
  for(int z=8;z<=16;z++){
    if((td.x==10 && td.y==z)||(td.x==20 && td.y==z)||(td.x==30 && td.y==z)||(td.x==40 && td.y==z)){
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang();
     }
 }
}
     for(int p=1;p<v.size();p++){
      if(arx[p]==arx[0] && ary[p]==ary[0]){
      gotoxy(20,12);cout<<"GAME OVER";
      bangxephang();
}
              }  
            }
           }
       for(int u=0;u<v.size()-1;u++) {gotoxy(arx[u],ary[u]);cout<<v[u];}
       if(kbhit()){
          char dieukhien=getch();
          if(dieukhien==77){  // điều khiển sang phải
          dieukhiensangphai(td);
          }       
          else if(dieukhien==75){  // điều khiển sang trái
           dieukhiensangtrai(td);
          }  
          else if(dieukhien==80){ // điều khiển xuống dưới
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang();
          } 
          else if(dieukhien==72){  // điều khiển lên trên
          dieukhienlentren(td);
          }
          else if(dieukhien==32) {gotoxy(0,26); system("pause");}
          else if(dieukhien==13){::point++;main();}
         }

       Sleep(mucdo+mucdo/2);
       if(td.y>0){gotoxy(arx[v.size()-1],ary[v.size()-1]);cout<<" ";}
        }
}
void dieukhienxuongduoi(toado td){
        gotoxy(arx[v.size()-1],ary[v.size()-1]);cout<<" ";
           for(td.y++;td.y<=25;td.y++){
            for(int d=v.size()-1;d>=0;d--){
              if(d>0) {arx[d]=arx[d-1];ary[d]=ary[d-1];}
              else if(d==0){ary[d]=td.y;
       if((arx[d]==a && ary[d]==b)||(arx[d]==A && ary[d]==B)){ //nếu ăn được mồi thì tăng thêm một đốt
         v.push_back("*");
         arx[v.size()-1]=arx[v.size()-2];ary[v.size()-1]=ary[v.size()-2];
         if(arx[d]==a && ary[d]==b)pt[point]++;
         else if(arx[d]==A && ary[d]==B)pt[point]+=2;
         moi();
         gotoxy(58,1);cout<<pt[point];
         if(arx[d]==A && ary[d]==B) {::A=80;::B=0;}
    }
       if(ary[d]==25){ gotoxy(20,12);cout<<"GAME OVER";
       bangxephang();
       }
       if(man==2){
      for(int k=10;k<=40;k++){
    if(k<=20){
if((td.x==k && td.y==8)||(td.x==k && td.y==16)){
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang();
}
    }
    else if(30<=k && k<=40){
if((td.x==k && td.y==8)||(td.x==k &&td.y==16)){
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang();
      }     
    }
}
  for(int z=8;z<=16;z++){
    if((td.x==10 && td.y==z)||(td.x==20 && td.y==z)||(td.x==30 && td.y==z)||(td.x==40 && td.y==z)){
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang();
     }
 }
}
        for(int p=1;p<v.size();p++){
      if(arx[p]==arx[0] && ary[p]==ary[0]){
      gotoxy(20,12);cout<<"GAME OVER";
      bangxephang();   
}
     }
              }
            }

       for(int u=0;u<v.size()-1;u++) {gotoxy(arx[u],ary[u]);cout<<v[u];}
       if(kbhit()){
          char dieukhien=getch();
          if(dieukhien==77){  // điều khiển sang phải
          dieukhiensangphai(td);
          }       
          else if(dieukhien==75){  // điều khiển sang trái
           dieukhiensangtrai(td);
          }  
          else if(dieukhien==80){ // điều khiển xuống dưới
          dieukhienxuongduoi(td);
          } 
          else if(dieukhien==72){  // điều khiển lên trên
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang();
          }
          else if(dieukhien==32){gotoxy(0,26); system("pause");}
          else if(dieukhien==13) {::point++;main();}
         }

       Sleep(mucdo+mucdo/2);
       if(td.y<25){gotoxy(arx[v.size()-1],ary[v.size()-1]);cout<<" ";}
           }
}
void dieukhiensangtrai(toado td){
    gotoxy(arx[v.size()-1],ary[v.size()-1]);cout<<" ";
        for(td.x--;td.x>=0;td.x--){
           for(int d=v.size()-1;d>=0;d--){
            if(d>0){arx[d]=arx[d-1];ary[d]=ary[d-1];}
            else if(d==0){arx[d]=td.x;
       if((arx[d]==a && ary[d]==b)||(arx[d]==A && ary[d]==B)){ //nếu ăn được mồi thì tăng thêm một đốt
          v.push_back("*");
          arx[v.size()-1]=arx[v.size()-2];ary[v.size()-1]=ary[v.size()-2];
          if(arx[d]==a && ary[d]==b)pt[point]++;
          else if(arx[d]==A && ary[d]==B)pt[point]+=2;
          moi();
          gotoxy(58,1);cout<<pt[point];
          if(arx[d]==A && ary[d]==B) {::A=80;::B=0;}
    }
       if(arx[d]==0){ gotoxy(20,12);cout<<"GAME OVER";
       bangxephang();     
       }
       if(man==2){
      for(int k=10;k<=40;k++){
    if(k<=20){
if((td.x==k && td.y==8)||(td.x==k && td.y==16)){
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang();
}
    }
    else if(30<=k &&  k<=40){
if((td.x==k &td.y==8)||(td.x==k && td.y==16)){
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang();
      }     
    }
}
  for(int z=8;z<=16;z++){
    if((td.x==10 && td.y==z)||(td.x==20 && td.y==z)||(td.x==30 && td.y==z)||(td.x==40 && td.y==z)){
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang();
     }
 }
}
     for(int p=1;p<v.size();p++){
      if(arx[p]==arx[0] && ary[p]==ary[0]){
      gotoxy(20,12);cout<<"GAME OVER";
      bangxephang();     
}
     }       
            }
           }
       for(int u=0;u<v.size()-1;u++) {gotoxy(arx[u],ary[u]);cout<<v[u];}
       if(kbhit()){
          char dieukhien=getch();
          if(dieukhien==77){  // điều khiển sang phải
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang();     
          }       
          else if(dieukhien==75){  // điều khiển sang trái
           dieukhiensangtrai(td);
          }  
          else if(dieukhien==80){ // điều khiển xuống dưới
          dieukhienxuongduoi(td);
          } 
          else if(dieukhien==72){  // điều khiển lên trên
          dieukhienlentren(td);
          }
          else if(dieukhien==32){gotoxy(0,26); system("pause");}
          else if(dieukhien==13) {::point++;main();}
         }

       Sleep(mucdo);
       if(td.x>0){gotoxy(arx[v.size()-1],ary[v.size()-1]);cout<<" ";}
        }
}
void dieukhiensangphai(toado td){
 gotoxy(arx[v.size()-1],ary[v.size()-1]);cout<<" ";
           for(td.x++;td.x<=50;td.x++){
            for(int d=v.size()-1;d>=0;d--){
              if(d>0) {arx[d]=arx[d-1];ary[d]=ary[d-1];}
              else if(d==0){arx[d]=td.x;
        if((arx[d]==a && ary[d]==b)||(arx[d]==A && ary[d]==B)){ //nếu ăn được mồi thì tăng thêm một đốt
          v.push_back("*");
          arx[v.size()-1]=arx[v.size()-2];ary[v.size()-1]=ary[v.size()-2];
          if(arx[d]==a && ary[d]==b)pt[point]++;
          else if(arx[d]==A && ary[d]==B)pt[point]+=2;
          moi();
          gotoxy(58,1);cout<<pt[point];          
          if(arx[d]==A && ary[d]==B) {::A=80;::B=0;}
    }
       if(arx[d]==50){ gotoxy(20,12);cout<<"GAME OVER";
       bangxephang();
       }
       if(man==2){
      for(int k=10;k<=40;k++){
    if(k<=20){
if((td.x==k && td.y==8)||(td.x==k && td.y==16)){
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang();
}
    }
    else if(30<=k &&  k<=40){
if((td.x==k && td.y==8)||(td.x==k && td.y==16)){
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang();
      }     
    }
}
  for(int z=8;z<=16;z++){
    if((td.x==10 && td.y==z)||(td.x==20 && td.y==z)||(td.x==30 && td.y==z)||(td.x==40 && td.y==z)){
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang();
     }
 }
}
     for(int p=1;p<v.size();p++){
      if(arx[p]==arx[0] &&  ary[p]==ary[0]){
      gotoxy(20,12);cout<<"GAME OVER";
      bangxephang();      
}
     }       
              }
            }

       for(int u=0;u<v.size()-1;u++) {gotoxy(arx[u],ary[u]);cout<<v[u];}
       if(kbhit()){
          char dieukhien=getch();
          if(dieukhien==77){  // điều khiển sang phải
          dieukhiensangphai(td);
          }       
          else if(dieukhien==75){  // điều khiển sang trái
          gotoxy(20,12);cout<<"GAME OVER";
          bangxephang();    
          }  
          else if(dieukhien==80){ // điều khiển xuống dưới
          dieukhienxuongduoi(td);
          } 
          else if(dieukhien==72){  // điều khiển lên trên
          dieukhienlentren(td);
          }
          else if(dieukhien==32){gotoxy(0,26); system("pause");}
          else if(dieukhien==13){::point++;main();}
         }

       Sleep(mucdo);
       if(td.x<50){gotoxy(arx[v.size()-1],ary[v.size()-1]);cout<<" ";}
           }
}