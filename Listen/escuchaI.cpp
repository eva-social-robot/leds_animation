#include <unistd.h>
#include <iostream>
#include <cmath>
#include "matrix_hal/everloop.h"
#include "matrix_hal/everloop_image.h"
#include "matrix_hal/matrixio_bus.h"

int main() {
matrix_hal::MatrixIOBus bus;
if (!bus.Init()) return false;
int ledCount = bus.MatrixLeds();
matrix_hal::EverloopImage everloop_image(ledCount);
matrix_hal::Everloop everloop;
everloop.Setup(&bus);
long counter = 0;
int i=0,aumenta=0,ledInicio=2,numLeds=2,min=25,max=50,otro=0,colorApagado=0,pos;
while(1) {
 // For each led in everloop_image.leds, set led value to 0
 for (matrix_hal::LedValue &led : everloop_image.leds) {/// Turn off Everloop
   led.red = colorApagado;
   led.green = colorApagado;
   led.blue = colorApagado;
   led.white = colorApagado;
  }
	for(int j=0;j<numLeds;j++){
		pos=ledInicio+((counter/7)%everloop_image.leds.size())+j;
		if(pos>=18){
		pos-=18;
		everloop_image.leds[pos].green = 20;
		}
	
	 	everloop_image.leds[pos].green=20;

	}
    everloop.Write(&everloop_image);
	if(i < min)
	{
		counter++;
		i++;
	}
	if(i >= min && i < max)
	{
		counter--;
		i++;
	}
	if( i >=max)
	{
		i=0;
	}


    // Sleep for 20000 microseconds
    usleep(20000);
//   aumenta=0;
}

return 0;
}
