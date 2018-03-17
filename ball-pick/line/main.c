#include <kipr/botball.h>
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
    while (analog(0)<=3500)
    {
        mav(0,1500);
        mav(1,-1500);
    }
    while (analog(0)>=3500)
    {
        mav(0,1500);
        mav(1,-1500);
    }
    while (analog(0)<=3500)
    {
        mav(0,1500);
        mav(1,-1500);
    }
    mav(0,1000);
    mav(1,-1000);
    while (1)
    {
        if (analog(0)>=3500)
        {
            mav(0,900);
            mav(1,-1100);
            msleep(10);
        }
        if (analog(0)<=3500)
        {
            mav(0,1100);
            mav(1,-900);
            msleep(10);
        }
    }
}