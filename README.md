# Led Animations
Implementation of led animations for the Eva social robot.

 ## Installation
Packages required to develop and compile the animations of the led light arrangement.

```bash
sudo apt-get install matrixio-creator-init libmatrixio-creator-hal libmatrixio-creator-hal-dev
```

## Compilation 
To compile the animations for the Matrix Voice's leds array we need to execute the following command, where we must change <app> to the name of the files that we want to obtain as a result of the compilation process and <app.cpp> to the name of the file that contains the implementation of the animation that we want to compile.
 
```bash
g++ -o app app.cpp -std=c++11 -lmatrix_creator_hal
```

## Usage
For Eva's main application to use the compiled animations, they must be found in the leds folder. 
