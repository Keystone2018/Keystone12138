#include <kipr/botball.h>
#include <math.h>
//#0 left +
//#1 right -
//analog(0)>=2000 black
//low : low servo position f
//high : high servo position

void followlinel(int d)
{
    clear_motor_position_counter(0);
    clear_motor_position_counter(1);
    while (get_motor_position_counter(0)<d)
    {
        if (analog(0)>=2000)
        {
            mav(0,800);
            mav(1,-1000);
            msleep(10);
        }
        if (analog(0)<=2000)
        {
            mav(0,1000);
            mav(1,-800);
            msleep(10);
        }
    }
}

void followliner(int d)
{
    clear_motor_position_counter(0);
    clear_motor_position_counter(1);
    while (get_motor_position_counter(0)<d)
    {
        if (analog(0)<=2000)
        {
            mav(0,800);
            mav(1,-1000);
            msleep(10);
        }
        if (analog(0)>=2000)
        {
            mav(0,1000);
            mav(1,-800);
            msleep(10);
        }
    }
}

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

void arm(int stat)
{
    if (stat == 0) {
        set_servo_position(0,400);
    }
    else{
        set_servo_position(0,800);
    }
    enable_servo(0);
    msleep(500);
    disable_servo(0);
}


int main()
{
    disable_servos();
    while(analog(0)<=2000)
    {
        mav(0,1000);
        mav(1,-1000);
    }
    while(analog(0)>=2000)
    {
        mav(0,1000);
        mav(1,-1000);
    }
    while(analog(0)<=2000)
    {
        mav(0,1000);
        mav(1,-1000);
    }
    ao();
    turn(1);
    followliner(10000);
    mav(0,1000);
    mav(1,1000);
    msleep(100);
    ao();
    while(analog(0)<=2000)
    {
        mav(0,1000);
        mav(1,-1000);
    }
    mav(0,1000);
    mav(1,1000);
    msleep(300);
    ao();
    followliner(1000);
    forward(1500,2000);
    turn(0);
    return 0;
}