#include <kipr/botball.h>
#include <math.h>
//#0 left +
//#1 right -
//analog(0)>=3500 black
//low : low servo position
//high : high servo position

void initservos(int delay)
{
    disable_servos();
    msleep(delay);
    enable_servos();
}

void gyro_forward(int distance)
{
    clear_motor_position_counter(0);
    clear_motor_position_counter(1);
    gyro_calibrate();
    while (get_motor_position_counter(0)<distance)
    {
        printf("%d\n",gyro_z());
        if (gyro_z()>=15)
        {
            mav(0,1000+(float)gyro_z()*(float)3.0);
            mav(1,-1000);
            msleep(10);
        }
        if (gyro_z()<=15)
        {
            mav(0,1000);
            mav(1,-1000+(float)gyro_z()*(float)4.5);
            msleep(10);
        }
    }
}

void followline(int distance)
{
    clear_motor_position_counter(0);
    clear_motor_position_counter(1);
    while (get_motor_position_counter(0)<distance)
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

void followlineReverse(int distance)
{
    clear_motor_position_counter(0);
    clear_motor_position_counter(1);
    while (get_motor_position_counter(0)<distance)
    {
        if (analog(0)<=3500)
        {
            mav(0,600);
            mav(1,-1200);
            msleep(10);
        }
        if (analog(0)>=3500)
        {
            mav(0,1200);
            mav(1,-600);
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
    mav(2,80);
    msleep(4300);
    mav(0,900);
    mav(1,-900);
    while(get_motor_position_counter(0)<4600){ //4600
        msleep(100);
    }
    ao();
    //get the arm off
    mav(2,-70);
    msleep(5500);
    freeze(2);
    //go to the second arm
    mav(0,800);
    mav(1,300);
    msleep(500);
    ao();
    mav(2,-250);
    msleep(1000);
    freeze(2);
    followlineReverse(5000);
    forward(1000,1300);
    mav(2,180);
    msleep(800);
    ao();
    msleep(2000);
    //arrive at the second arm
    /*
    mav(0,-500);
    mav(1,500);
    msleep(7800);*/
    forward(800,-1600);
    ao();
    freeze(2);
    //take it down
    mav(2,250);
    msleep(5000);
    ao();
}


int main()
{
    gyro_forward(10000);
    return 0;
}