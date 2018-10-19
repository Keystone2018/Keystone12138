#include <kipr/botball.h>
#include <math.h>
#define PI 3.141592654
#define CREATE_WHEEL_DIAMETER 25.3   //cal:25.46
void createSpin(int speed, float degress)
{
	int time =( (PI * CREATE_WHEEL_DIAMETER/2.) / speed ) * 20000. * 0.812 * abs(degress)/360.;
	if(speed < 0)
		speed = -speed;
	if(degress > 0){
		create_spin_CW(speed);
		msleep(time);
	}
    else{
		create_spin_CCW(speed);
		msleep(time);
	}
	create_stop();
}

void createTurn(int speed, float degress)
{
	int time =( (2*PI * CREATE_WHEEL_DIAMETER) / speed ) * 10 * 1000 * abs(degress)/360.;// 
	if(speed < 0)
		speed = -speed;
	if(degress > 0){
		create_drive_direct(speed,0);
		msleep(time);
	}
	else{
		create_drive_direct(0,speed);
		msleep(time);
	}	
	create_stop();
}

/*void forward(int velocity,int time)
{
    create_drive_direct(velocity,velocity);
    msleep(time);
    create_stop();
}*/

void forward(int velocity,int distance)
{
    distance = distance*((float)10/9);
    //100=90
    set_create_distance(0);
    create_drive_straight(velocity);
       
    while (get_create_distance()<=distance)
    {
        msleep(1);
    }
    create_stop();
}

void turnL(int n)
{
    create_drive_direct(0,200);
    msleep(2100*n);
}

void turnR(int n)
{
    create_drive_direct(200,0);
    msleep(2100*n);
}

void position(int which_hand,int which_servo_position)
{ 
    set_servo_position(which_hand,which_servo_position);
}

void Cstop()
{
    create_stop();
    msleep(2000);
}


int main(){
    printf("lyjmyxjj");
    create_connect();
    //forward(100,500);
    createSpin(200,90);
    msleep(1000);
    Cstop();
    return 0;
}

/*
int main(){
    create_connect();
    int lift=200;
    int down=1265;

    int close=0;
    int open=1500;
    int arm=1;
    int claw=2;

    

    

    enable_servo(arm);
    enable_servo(claw);
    set_servo_position(arm,down);
    set_servo_position(claw,close);
    create_stop();
    //wait_for_light(1);
    //shut_down_in(120);
    forward(-100,500);//initializing session
    forward(200,500);//initial going
    Cstop();
    createTurn(200, -90); 
    create_stop();
    
    //forward(-75,4000);//correct
    forward(200,4800);//center
    
    Cstop();


    create_drive_direct(200,-200);
    msleep(800);


    forward(-100,1000);//move to the big yellow front back

    Cstop();
    position(claw,open);
   
    position(arm,down);//attention:extreme
    position(claw,open);
    forward(100,1800);//move to the big yellow front
    Cstop();
    position(claw,close);
    Cstop();
    forward(-100,1800);
    Cstop();
        
    create_drive_direct(100,-100);
    msleep(3000);
    forward(-100,200);
    Cstop();
    position(claw,open);//put 1st yellow
    Cstop();

    forward(-100,500);//back
    Cstop();
    position(arm,950);//grab 2nd
    Cstop();
    position(claw,close);
    Cstop();
    position(arm,950);
    Cstop();
    forward(-100,800);
    create_drive_direct(0,-200);
    msleep(1000);
    position(arm,1200);
    Cstop();
    forward(100,1200);
    Cstop();
   
    position(claw,open);
    
   
    create_drive_direct(-200,200);
    msleep(2000);
    Cstop();//back over














    //90 degrees turn CCW
    //create_drive_direct(-200,200);
    //msleep(1000);

    position(arm,1490);
    Cstop();
    position(claw,2000);
    Cstop();
    forward(50,4700);
    Cstop();
    position(claw,1500);
    forward(50,3200);

    position(claw,close);
    Cstop();
    forward(-50,7000);
    Cstop();
    create_drive_direct(-100,100);
    msleep(2000);

    position(arm,1000);
    forward(50,200);
    position(arm,700);
    forward(-50,200);
    position(arm,500);
    forward(50,200);
    position(arm,200);
    Cstop();

   
   
    forward(50,7000);
    Cstop();
    position(arm,500);
    Cstop();
    position(claw,open);
}
*/

/*
    create_drive_direct(-200,200);//first spin Anti-Clockwise to make out//totally 4 turns
    msleep(1000);

    forward(100,2000);

    create_drive_direct(200,-200);//second spin
    msleep(1000);

    forward(100,500);

    create_drive_direct(200,-200);//third spin
    msleep(800);

    forward(100,1500);

    create_drive_direct(100,-100);//last spin 90 left
    msleep(1800);
    Cstop();

    forward(100,5500);

    */
