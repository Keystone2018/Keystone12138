#include <kipr/botball.h>
void straight(int a, int b);
void CCW(int c, int d);
void CW(int e, int f);
int i=0;
int main()
{
    create_connect();
    create_full();
    
    //regulation
    create_drive_straight(-50);
    msleep(700);
    //turn step to right direction
    create_drive_direct(0,100);
    msleep(1300);
    //turn step to right direction
    straight(1,800);
    //turn step to right direction
    create_spin_CCW(200);
    msleep(600);
    //regulation and to wait
    straight(-1,1300);

    //go to the center of the own court
    straight(1,6200);
    //started be the right side relative botguy
    CW(90,100);
    //catch or pull down
    straight(-1,3000);
    create_stop();
    msleep(30000);
    //go catch yellow
    straight(1,2400); 
    //back throw yellow
    straight(-1,1000);
    //go catch botguy
    //back give the botguy to the top
    //go catch one flyplate
    CW(90,100);
    create_disconnect();
    return 0;
}

void straight(int a, int b)
{
    create_drive_direct(200*a,180*a);
    msleep(b);
}

void CCW(int c, int d) 
{ 
    set_create_total_angle(0);
    while(get_create_total_angle()<(c-1))
    {
        create_spin_CCW(d);
       
    }
}


void CW(int e, int f) 
{    set_create_total_angle(359);
     
 while(get_create_total_angle()>(360-e))
 {
     create_spin_CW(f);
    
 }



}























