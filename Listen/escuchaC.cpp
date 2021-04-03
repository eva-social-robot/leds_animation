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
long counter=0;
int i=0,ledInicio=6,aumenta=0,colorApagado=0,numLeds=3,min=25,max=50;
while(1)
{
		for (matrix_hal::LedValue &led : everloop_image.leds){
			led.red=colorApagado;
			led.green=colorApagado;
			led.blue=colorApagado;
			led.white=colorApagado;
		}
		for(int j=0;j<numLeds;j++){
			everloop_image.leds[ledInicio+((counter/7) % everloop_image.leds.size()+j)].green = 20;
			aumenta+=2;
		}
		everloop.Write(&everloop_image);
		if(i<min){
			counter++;
			i++;
		}
		if(i >= min && i < max)
		{
			counter--;
			i++;
		}
		if(i >= max)
		{
			i=0;
		}
		usleep(20000);
		aumenta=0;
}   
return 0;
}
