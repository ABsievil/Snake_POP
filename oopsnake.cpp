#include <iostream> 
#include<windows.h>  
#include<vector>
#include<cstdlib>  //hàm random rand
#include<ctime>    //hàm random theo time srand
#include<conio.h>  //thư viện để sử dụng hàm kbhit() và hàm getch()-phát hiện nhấn nút
#include<string>
using namespace std;

//biến toàn cục

// khai báo class
class Snake;
class Direction;
class point;

//khai báo function
void setframe();
void gotoxy(int,int);


int main(){
    setframe();
    Direction huong();
    huong.right();
    system("pause");
    return 0;
}


void gotoxy(int x,int y)   //hàm tọa độ
{
  static HANDLE h = NULL;  
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };  
  SetConsoleCursorPosition(h,c);
};


class Snake{    //rắn
    public:
       vector<string> Point_Snake;
       vector<int> x_Point_Snake;
       vector<int> y_Point_Snake;
    public:
       Snake();
       void set_Point_Snake();
       void print_Snake();
    friend class Diretion; 
};

Snake::Snake(){   //constructor tạo đốt và tọa độ 3 đốt đầu tiên
     Point_Snake.push_back("*");
     Point_Snake.push_back("*");
     Point_Snake.push_back("*");    
     srand(time(NULL));
    x_Point_Snake.push_back(rand()%(45-5+1)+5);
    y_Point_Snake.push_back(rand()%(20-5+1)+5);
    x_Point_Snake.push_back(x_Point_Snake[0]-1);
    x_Point_Snake.push_back(x_Point_Snake[1]-1);
    y_Point_Snake.push_back(y_Point_Snake[0]-1);
    y_Point_Snake.push_back(y_Point_Snake[1]-1);    

}

void Snake::set_Point_Snake(){ 
     
}

void Snake::print_Snake(){
    for(int i=0;i<Point_Snake.size();i++){
      gotoxy(x_Point_Snake[i],y_Point_Snake[i]);cout<<Point_Snake[i];
    }
}

class Direction:public Snake{   //hướng di chuyển
    private:
       
    public:
       Direction();
       void left();void right();void bottom();void top();  
};

Direction::Direction(){

}

class point{     //mồi
    private:
      int x_point,y_point;
    public:
       void setpoint();   
};

void point::setpoint(){
    srand(time(NULL));
    x_point=rand()%(49-1+1)+1;
    y_point=rand()%(24-1+1)+1;
}

void setframe(){
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

void Direction::right(){
for(int j=0;j<Point_Snake.size();j++) print_Snake();  //in 3 đốt đầu tiên

    for(int i=x_Point_Snake[0]+1;i<=50;i++){   //gắn tọa độ
        x_Point_Snake[0]=i;          //gắn tọa độ đốt đầu tiên
        for(int k=1;k<Point_Snake.size();k++){   //gắn tọa độ các đốt phía sau
           x_Point_Snake[k]=x_Point_Snake[k-1]-1;
        }


        for(int j=0;j<Point_Snake.size();j++) print_Snake();
    } 
    for(int j=0;j<Point_Snake.size();j++){
        
    }   
    
}