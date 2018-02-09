//use camera to figure out the color of each area
#include <kipr/botball.h>

int main()
{
    int y;
    int r;
    int g;
    g=0;

    
    camera_open();
    msleep(3000);
    mav(0,-1000);
    mav(1,1000); 


    wait_for_milliseconds(3000);
    ao();
    msleep(1000);
    camera_update();
    if (get_object_count(0)>=1)
    {
        y = 1;
        printf("zone1 y=%d\n",y);
    }
    else 
    {
        if (get_object_count(1)>=1)
    {
        r = 1;
        printf("zone1 r=%d\n",r);
    }
    else
    {
        if (get_object_count(2)>=1)
    {
        g = 1;
        printf("zone1 g=%d\n",g);
    }
    }
    }
        

    mav(0,-1000);
    mav(1,1000); 
    wait_for_milliseconds(3000);
    camera_update();
    if (get_object_count(0)>=1)
    {
        y = 2;
        printf("zone2 y=%d\n",y);
    }
    else 
    {
        if (get_object_count(1)>=1)
    {
        r = 2;
        printf("zone2 r=%d\n",r);
    }
    else 
    {
        if (get_object_count(2)>=1)
    {
        g = 2;
        printf("zone2 g=%d\n",g);
    }
    }
    }
    
    wait_for_milliseconds(3000);
    camera_update();
    if (get_object_count(0)>=1)
    {
        y = 3;
        printf("zone3 y=%d\n",y);
    }
    else 
    {
        if (get_object_count(1)>=1)
    {
        r = 3;
        printf("zone3 r=%d\n",r);
     }
    else 
    {
        if (get_object_count(2)>=1)
    {
        g = 3;
        printf("zone3 g=%d\n",g);
    }
    }
    }
    printf("y:%d,r:%d,g:%d\n",y,r,g);
    return 0;
}
