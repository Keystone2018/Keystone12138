#include <kipr/botball.h>
#include <math.h>
//#0 left +
//#1 right -
//analog(0)>=3500 black
//low : low servo position f
//high : high servo position

void forward(int velocity,int distance)
{
    clear_motor_position_counter(0);
    clear_motor_position_counter(1);
    mtp(0,velocity,distance);
    mtp(1,velocity,-distance);
    msleep(abs((float)distance/((float)velocity/1000)));
    //forward(velocity,distance as tik);
    //1cm = 100tik
}

void turn(int direction)
{
    clear_motor_position_counter(0);
    clear_motor_position_counter(1);
    mtp(direction,1000,1250*pow(-1,direction));
    mtp(pow(0.5,direction-1)-1,1000,1250*pow(-1,direction));
    msleep(2200);
    //turn(n);
    //right: n = 0
    //left: n = 1
    //1300ms
}

void turna(int motor,int direction)
{
    clear_motor_position_counter(0);
    clear_motor_position_counter(1);
    mtp(motor,1000,2525*direction);
    msleep(2550);
    //turn(m,n);
    //m : motor #
    //n : direction
}

int main()
{
    int bound;
    int boundl;
    int boundr;
    int tsd;
    int tsdl;
    int tsdr;
    while(1)
    {
        tsd = analog(2);
        tsdl = analog(2)-100;
        tsdr = analog(2)+100;
        mav(0,1200);
        mav(1,-1200);
        while(1)
        {
            if (analog(2)>tsdr)
            {
                mav(0,1300);
                mav(1,-1200);
            }
            else if(analog(2)<tsdl)
            {
                mav(0,1200);
                mav(1,-1300);
            }
            else
            {
                mav(0,1200);
                mav(1,-1200);
            }
        }
    }
}