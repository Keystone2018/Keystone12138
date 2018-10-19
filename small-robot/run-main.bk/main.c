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
    mtp(direction,1000,1250*pow(-1,direction));
    mtp(pow(0.5,direction-1)-1,1000,1250*pow(-1,direction));
    msleep(2200);
    //turn(n);
    //left: n = 1
    //right: n = 0
    //1300ms
}


int main()
{
    forward(1500,1000);
    /*
    int n;
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
    turn(0);
    mav(0,1000);
    mav(1,-1000);
    n=0;
    while (n<=50)
    {
        if (analog(0)>=3500)
        {
            mav(0,900);
            mav(1,-1100);
            msleep(10);
            n=n+1;
        }
        if (analog(0)<=3500)
        {
            mav(0,1100);
            mav(1,-900);
            msleep(10);
            n=n+1;
        }
    }

/*
    while (analog(1)<3500)
    {
        if (analog(0)>=3500)
        {
            mav(0,900);
            mav(1,-1100);
            msleep(10);
            n=n+1;
        }
        if (analog(0)<=3500)
        {
            mav(0,1100);
            mav(1,-900);
            msleep(10);
            n=n+1;
        }
    }
*/
    return 0;
}
