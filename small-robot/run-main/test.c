#include <kipr/botball.h>
#include <math.h>
//#0 left +
//#1 right -
//analog(0)>=3500 black
//low : low servo position f
//high : high servo position

void followline(int d)
{
    clear_motor_position_counter(0);
    clear_motor_position_counter(1);
    while (get_motor_position_counter(0)<d)
    {
        if (analog(0)>=3500)
        {
            mav(0,800);
            mav(1,-1000);
            msleep(10);
        }
        if (analog(0)<=3500)
        {
            mav(0,1000);
            mav(1,-800);
            msleep(10);
        }
    }
}

void followlineReverse(int d)
{
    clear_motor_position_counter(0);
    clear_motor_position_counter(1);
    while (get_motor_position_counter(0)<d)
    {
        if (analog(0)<=3500)
        {
            mav(0,800);
            mav(1,-1000);
            msleep(10);
        }
        if (analog(0)>=3500)
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
    mtp(direction,1000,920*pow(-1,direction));
    mtp(pow(0.5,direction-1)-1,1000,920*pow(-1,direction));
    msleep(1000);
    //turn(n);
    //right: n = 0
    //left: n = 1
    //1300ms
}

void turna(int motor,int direction)
{
    clear_motor_position_counter(0);
    clear_motor_position_counter(1);
    mtp(motor,1000,1900*direction);
    msleep(2000);
    //turn(m,n);
    //m : motor #
    //n : direction
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

void blackring()
{
    freeze(0);
    freeze(1);
    //lift the first ring
    clear_motor_position_counter(0);
    mav(2,76);
    msleep(4300);
    while(get_motor_position_counter(0)<4600){
        mav(0,900);
        mav(1,-900);
    }
    ao();
    //get the arm off
    mav(2,-100);
    msleep(3900);
    freeze(2);
    //go to the second arm
    mav(0,800);
    mav(1,300);
    msleep(500);
    followlineReverse(10800);
    freeze(0);
    freeze(1);
    //arrive at the second arm
    mav(0,-500);
    mav(1,500);
    msleep(6800);
    freeze(0);
    freeze(2);
    //take it down
    mav(0,-50);
    mav(1,50);
    mav(2,250);
    msleep(6000);
}

int main()
{
    forward(1000,2000);
    return 0;
}