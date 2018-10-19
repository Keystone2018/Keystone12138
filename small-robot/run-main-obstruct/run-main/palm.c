#include<kipr/botball.h>
//#0 left +
//#1 right -
//analog(0)>=3500 black
//low : low servo position
//high : high servo position
void forward(int velocity,int distance);
void forward_calibrated(int velocity,int distance);
void turn(int direction);
void turn_with_back(int direction);
void followline(int distance);
void wait_for_black(int grayscale,int velocity);
void wait_for_collide(int velocity);
void gyro_forward(int distance);

int main()
{
    shut_down_in(120);
    forward(1500,4200);
    turn(0);
    while(analog(0)<3500){
        forward(1500,15);
    } 
    freeze(0);
    freeze(1);
    turn(1);
    followline(12000);//go to the other side
    go_around(0);
    forward(1500,3000);
    turn(0);
    go_around(1);
    forward(1500,6000);
    return 0;
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

void forward_calibrated(int velocity,int distance)
{
    clear_motor_position_counter(0);
    clear_motor_position_counter(1);
    mtp(0,velocity*1,distance);
    mtp(1,velocity*1.2,-distance);
    msleep(abs((float)distance/((float)velocity/1000)));
    //forward(velocity,distance as tik);
    //1cm = 100tik
}

void turn(int direction)
{
    mav(direction,direction ? (int)1000*pow(-1,direction) : 1000*pow(-1,direction));
    mav(pow(0.5,direction-1)-1,pow(0.5,direction-1)-1 ? (int)1000*pow(-1,direction) : 1000*pow(-1,direction));
    msleep(852);
    freeze(0);
    freeze(1);
    msleep(100);
    //turn right 0
    //turn left 1
}

void turn_with_back(int direction)
{
    //depend on "turn" and "forward"
    forward(500,-500);
    turn(direction);                                                                                                         
}

void followline(int distance)
{
    clear_motor_position_counter(0);
    clear_motor_position_counter(1);
    while (get_motor_position_counter(0)<distance)
    {
        if (analog(0)>=3500)
        {
            mav(0,700);
            mav(1,-1500);
            msleep(10);
        }
        if (analog(0)<=3500)
        {
            mav(0,1500);
            mav(1,-700);
            msleep(10);
        }
    }
}

void wait_for_black(int grayscale,int velocity)
{
    while(analog(0)<grayscale)
    {
        mav(0,velocity);
        mav(1,-velocity);
        msleep(10);
    }
}

void wait_for_collide(int velocity)
{
    gyro_calibrate();
    while(!(digital(0)&&digital(1)))
    {
        if (gyro_z()>=15)
        {
            mav(0,1000+(float)gyro_z()*(float)3.0);
            mav(1,-1000);
            msleep(10);
        }
        if (gyro_z()<=15)
        {
            mav(0,1000);
            mav(1,-1000+(float)gyro_z()*(float)3.0);
            msleep(10);
        }
    } 
}

void gyro_forward(int distance)
{
    clear_motor_position_counter(0);
    clear_motor_position_counter(1);
    gyro_calibrate();
    while (get_motor_position_counter(0)<distance)
    {
        if (gyro_z()>=15)
        {
            mav(0,1000+(float)gyro_z()*(float)3.0);
            mav(1,-1000);
            msleep(10);
        }
        if (gyro_z()<=15)
        {
            mav(0,1000);
            mav(1,-1000+(float)gyro_z()*(float)3.0);
            msleep(10);
        }
    }
}