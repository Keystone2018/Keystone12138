#include <kipr/botball.h>
#include <math.h>
void forward(int velocity,int distance)
{
    clear_motor_position_counter(0);
    clear_motor_position_counter(1);
    mtp(0,velocity,distance);
    mtp(1,velocity,-distance);
    msleep(abs((float)distance/((float)velocity/1000)));
    //forward(velocity,distance as tik);
    //10cm = 1000tik
}

void turn(int direction)
{
    clear_motor_position_counter(0);
    clear_motor_position_counter(1);
    mtp(direction,1000,2150*pow(-1,direction));
    mtp(pow(0.5,direction-1)-1,1000,2150*pow(-1,direction));
    msleep(2200);
    //turn(n);
    //left: n = 1
    //right: n = 0
    //1300ms
}


int main()
{
    forward(1500,2000);
    turn(1);
    forward(15000);
}
