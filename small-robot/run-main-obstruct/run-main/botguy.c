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
void wait_for_collide_reverse(int velocity);
void wait_for_collide_suck();
void gyro_forward(int distance);
void obstruct_init();
void obstruct_main();

int main()
{

    shut_down_in(120);
    forward(1500,4000);
    turn(0);
    while(analog(0)<3500){
        mav(0,1500);
        mav(1,-1500);
    } 
    freeze(0);
    freeze(1);
    turn(1);
    followline(9500);//go to the other side
    turn(1);
    int count = 0;
    while(count<=4)
    {
        wait_for_collide_reverse(1500);
        turn_with_back(1);
        count++;
    }
    turn(0);
    forward(1000,-500);
    turn(0);
    followline(6000);
    count=0;
    while(count<=4)
    {
        wait_for_collide_reverse(1500);
        turn_with_back(1);
        count++;
    }
    forward(1500,-5000);
    while(1)
    {
        wait_for_collide_suck();
        if (rand()<=1073741823)
        {
            turn_with_back(0);
        }
        else
        {
            turn_with_back(1);
        }
    }

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
    mtp(0,velocity,distance);
    mtp(1,velocity,-distance);
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
    while(!(digital(0)&&digital(1)))
    {
        mav(0,velocity);
        mav(1,-velocity+12);
    }
    freeze(0);
    freeze(1);
}

void wait_for_collide_reverse(int velocity)
{
    while(!(digital(0)&&digital(1)))
    {
        mav(0,velocity);
        mav(1,-velocity);
    }
    freeze(0);
    freeze(1);
}

void wait_for_collide_suck()
{
    while(!(digital(0)&&digital(1)))
    {
        mav(0,1500);
        mav(1,-1200);
    }
    freeze(0);
    freeze(1);
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

void obstruct_init()
{
    enable_servos();
    //set_servo_position(0,)
}