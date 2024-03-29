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
int limite=150,ledInicio=0,pos=0,posn=0,posdo=0,posndo=0,until=0;
bool direccion = true,start=true,rebaso=true;
while(true)
{
	for (int i = 0; i < 18; i++)
	{
		everloop_image.leds[i].red=0;
		everloop_image.leds[i].blue=0;
		if (direccion)
		{
			everloop_image.leds[i].green = everloop_image.leds[i].green > 0 ? (everloop_image.leds[i].green < limite ? everloop_image.leds[i].green + 3 : limite) : 0;
		} else
		{
			everloop_image.leds[i].green = everloop_image.leds[i].green < limite ? (everloop_image.leds[i].green > 0 ? everloop_image.leds[i].green - 3 : 0) : limite;
		}		
	}

	start = true;
	until = direccion ? 0 : 4;
	while (start)
	{
		pos = (ledInicio + until >= 18) ? (ledInicio + until - 18) : (ledInicio + until);
		posdo = (pos + 9 >= 18) ? (pos + 9) - 18: (pos + 9);
		posn = (ledInicio - until < 0) ? (18 + (ledInicio - until)) : (ledInicio - until);
		posndo = (posn + 9 >= 18) ? (posn + 9) - 18: (posn + 9);

		if (everloop_image.leds[pos].green == 0 && direccion)
		{
			everloop_image.leds[pos].green = 3;
			everloop_image.leds[posdo].green = 3;
			everloop_image.leds[posn].green = 3;
			everloop_image.leds[posndo].green = 3;
			start = false;
		}
		if (everloop_image.leds[pos].green == limite && !direccion)
		{
			everloop_image.leds[pos].green = limite - 3;
			everloop_image.leds[posdo].green = limite - 3;
			everloop_image.leds[posn].green = limite - 3;
			everloop_image.leds[posndo].green = limite - 3;
			start = false;
		}
		until = direccion ? until + 1 : until - 1;
		if (until > 4 || until < 0)
		{
			start = false;
		}
	}
	
	rebaso = true;
	for (int i = 0; i < 18; i++)
	{
		if (direccion)
		{
			if (everloop_image.leds[i].green < limite)
			{
				rebaso = false;
			}
		} else {
			if (everloop_image.leds[i].green > 0)
			{
				rebaso = false;
			}
		}
			
	}
	if (rebaso)
	{
		direccion = !direccion;
		if (direccion)
		{
			int temp = ledInicio + 2 >= 18 ? ledInicio + 2 - 18 : ledInicio + 2;
			ledInicio = temp;
		}
	}
	everloop.Write(&everloop_image);	
	usleep(40000);
}   
return 0;
}

