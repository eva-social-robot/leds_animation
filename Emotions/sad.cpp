#include <unistd.h>
#include <iostream>
#include <cmath>
#include "matrix_hal/everloop.h"
#include "matrix_hal/everloop_image.h"
#include "matrix_hal/matrixio_bus.h"

int siguiente(int);
int anterior (int);

int main() {
matrix_hal::MatrixIOBus bus;
if (!bus.Init()) return false;
int ledCount = bus.MatrixLeds();
matrix_hal::EverloopImage everloop_image(ledCount);
matrix_hal::Everloop everloop;
everloop.Setup(&bus);
int ledInicio=0,tail=20,lizq=0,lder=0;

lizq = ledInicio;
lder = anterior(ledInicio);
while(true)
{
	for (int i = 0; i < 18; i++)
	{
		if (everloop_image.leds[i].blue == 80) {
			everloop_image.leds[i].blue = 50;
		} else if (everloop_image.leds[i].blue == 50) {
			everloop_image.leds[i].blue = 35;
		} else {
			everloop_image.leds[i].blue = 0;
		}
	}
	everloop_image.leds[lizq].blue = 80;
	everloop_image.leds[lder].blue = 80;
	lizq = anterior(lizq);
	lder = siguiente(lder);
	
	if (lizq <= lder)
	{
		lizq = ledInicio;
		lder = anterior(ledInicio);
	}

	everloop.Write(&everloop_image);	
	usleep(40000 * 7);
}   
return 0;
}

int siguiente(int value){
	return value + 1 >= 18 ? value - 17 : value + 1;
}

int anterior (int value){
	return value - 1 < 0 ? 18 + (value - 1) : value - 1;
}
