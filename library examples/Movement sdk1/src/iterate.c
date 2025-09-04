#include "iterate.h"


int App_Iterate(SDK_Display *display, SDK_Time *time, SDK_Input *input, Player *player){

    bool running = 1;
    
    while(running){

        if(App_Events(display, time, input, player)){
            running = 0;
        }

        if(render(display, time, input, player)){
            return 1;
        }

        SDK_TimeFunctions(time);
    }


    return 0;
}