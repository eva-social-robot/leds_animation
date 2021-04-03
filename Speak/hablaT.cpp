#include <unistd.h>
#include <iostream>
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
int j=0, defineTiempo=0,colorApagado=0,lapso=13, permanece=10,intensidadBlue=50,limite=150;
//const float freq = 0.375;

// Ciclo del efecto 
while(1) {
    // For each led in everloop_image.leds, set led value
    for (matrix_hal::LedValue &led : everloop_image.leds) {
    // Transicion del color verde
    led.red =colorApagado;
    led.green =j>limite?limite:j;
    led.blue = intensidadBlue;
    }

//Tiempos de transicion de azul a cian y de cian a azul 
    if (defineTiempo>lapso && defineTiempo<=lapso*2)
        j+=3;
    if (defineTiempo>(lapso*2) && defineTiempo<=(lapso*2+permanece))
        j=j;
    if (defineTiempo>(lapso*2+permanece) && defineTiempo<=(lapso*3+permanece))
        j-=3;
    if (defineTiempo>(lapso*3+permanece)){
        defineTiempo=0;
        j=0;
    }

    // Updates the LEDs
    everloop.Write(&everloop_image);
    defineTiempo++;
    // Sleep for 40000 microseconds
    usleep(40000);
}
return 0;
}
