#include <kipr/botball.h>
#include <math.h>
//#0 left +
//#1 right -
//analog(0)>=3500 black
//low : low servo position 手臂放下
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

void arm(int stat)
{
    if (stat==0) {
        set_servo_position(0,400);//手臂抬起
    }
    else{
        set_servo_position(0,800);//手臂落下
    }
    enable_servo(0); //舵机号待定
    msleep(500);
    disable_servo(0);
    //arm(n);
    //抬起 : 0
}

int main()
{
    int count=0
    int cstat=0
    clear_motor_position_counter(0);
    clear_motor_position_counter(1);
    while (get_motor_position_counter(0)<16500&&cstat<3)
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
        if (analog(1)<=n &&cstat=0)
        {
            count=count+1
            cstat=1
        }
        if (analog(1)>=n &&cstat=1)
        {
            cstat=0
        }
    }
    ao();


    turn(0);
    turn(0);
    turn(0);
    turn(0);
    turn(0);
    turn(0);
    turn(0);
    turn(0);
    turn(0);
    turn(0);
    turn(0);
    turn(0);
    return 0;
}
