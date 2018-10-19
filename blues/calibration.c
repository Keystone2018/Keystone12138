#include <kipr/botball.h>
#include <math.h>
#define s msleep(1)
//#0 right + open lift up
//#1 left - close put down
//analog(0)>=1000 black
int k;

void calibration()
{
    if (analog(0)<1000){
        
    }
    else{

    }
}

void followline(int d)
{
    clear_motor_position_counter(0);
    clear_motor_position_counter(1);
    while (get_motor_position_counter(0)>-d)
    {
        if (analog(0)<1000)
        {
            mav(0,-1500);
            mav(1,1200);
            msleep(15);
        }
        if (analog(1)<1000)
        {
            mav(0,-1200);
            mav(1,1500);
            msleep(15);
        }
        if((analog(0)>=1000 && analog(1)>=1000) || (analog(0)<=1000 && analog(1)<=1000)){
            mav(0,-1500);
            mav(1,1500);
            msleep(15);
        }
    }
    ao();
    msleep(1000);
}

void forward(int velocity,int distance)
{
    clear_motor_position_counter(0);
    clear_motor_position_counter(1);
    int i=0;
    while(i<abs((float)distance/((float)velocity/1000))){
        mav(0,velocity*(distance/abs(distance)));
        mav(1,-velocity*(distance/abs(distance)));
        msleep(100);
        i+=100;
    }
    ao();
    //forward(velocity,distance as tik);
    //1cm = 100tik
}

void turn(int direction)
{
    clear_motor_position_counter(0);
    clear_motor_position_counter(1);
    int i=0;
    while(i<255){
        mav(direction,1500*pow(-1,direction));
        mav(pow(0.5,direction-1)-1,1500*pow(-1,direction));
        msleep(1);
        i++;
    }
    /*mtp(direction,1500,1345*pow(-1,direction));
    mtp(pow(0.5,direction-1)-1,1500,1345*pow(-1,direction));
    msleep(920);*/
    freeze(0);
    freeze(1);
    //turn(n);
    //right: n = 0
    //left: n = 1
    //1300ms
}
void turna(int direction)
{
    clear_motor_position_counter(0);
    clear_motor_position_counter(1);
    mtp(pow(2,direction)-1,1500,2460*pow(-1,direction));
    msleep(3000);
    //turn(n);
    //left: n = 0
    //right: n = 1
    //1300ms
}

void arm(int st)
{
    if(st==1){
        set_servo_position(1,2000);
    }
    else {
        set_servo_position(1,900);
    }
}

int awe=0;
void valve()
{
    set_servo_position(2,250);
    msleep(100);
    int j=0;
    while(j<3){
        set_servo_position(1,700);
        msleep(50);
        set_servo_position(1,900);
        msleep(500);
        j++;
    }
    msleep(100);
    set_servo_position(2,1300);
    msleep(100);
    j=0;
    while(j<3){
        set_servo_position(1,700);
        msleep(100);
        set_servo_position(1,900);
        msleep(100);
        j++;
    }
    awe++;
}

void blues()
{
    int i=0;
    while(i<6){
        if(i>2&&i<6){
            followline(3100);//go to the next tree (the last three trees)
        }
        turn(1);
        msleep(1000);
        forward(1500,4000);
        ao();
        valve();  //let one ball fall to the other side

        forward(1500,-1000);
        valve(); //let one ball on our side
        
        while(analog(0)<1000&&analog(1)<1000){
            mav(0,-1500);
            mav(1,1500);
        }
        while(analog(0)>=1000&&analog(1)<1000){
            mav(0,0);
            mav(1,500);
            msleep(10);
        }
        while(analog(0)<1000&&analog(1)>=1000){
            mav(1,0);
            mav(0,-500);
            msleep(10);
        } //search for the black line for accuracy
        forward(500,-500);
        turn(0);
        if(i<3){
            followline(3400);//go to the next tree (the first three trees)
        }
        i++;
    }
}


int main()
{

    return 0;
}