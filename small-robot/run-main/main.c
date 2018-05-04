#include <kipr/botball.h>
#include <math.h>
//#0 left +
//#1 right -
//analog(0)>=3500 black
//low : low servo position 手臂放下
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
    mav(2,70);
    msleep(5000);
    mav(0,700);
    mav(1,-700);
    msleep(6000);
    freeze(0);
    freeze(2);
    mav(2,500);
    msleep(1000);
    mav(0,700);
    mav(1,-700);
    msleep(2000);
}

int main()
{
    disable_servos();
    arm(1);
    mav(2,-1000);
    msleep(1100);
    freeze(2);
    enable_servos();
    arm(1);
    turna(0,1);
    //go to box
    forward(1000,1500);
    followline(16800);
    turn(1);
    mav(2,-90);
    msleep(1200);
    freeze(2);
    turn(1);
    blackring();
    return 0;
 }