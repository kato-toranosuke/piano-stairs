/*
********************************************************************************
SOHOSAI 2019 at TSUKUBA Univ.
Piano Stairs
********************************************************************************
*/

import processing.serial.*;
import ddf.minim.*;

// Define the number of sensors
final int N_SENSORS = 19;
// Prepare the variable for  storing demanded sensor no 
int sensor_no;

Serial port_A;
Serial port_B;

Minim minim;
AudioSample[] piano = new AudioSample[N_SENSORS];

void setup(){
  //Set Serial port
  port_A = new Serial(this, "/dev/cu.SLAB_USBtoUART4", 9600);
  port_B = new Serial(this, "/dev/cu.SLAB_USBtoUART", 9600);
  
  // Load Audio Sample File
  minim = new Minim(this);
  for(int i = 0; i < N_SENSORS; i++){
    piano[i] = minim.loadSample("piano-"+ i +".mp3", 2048);
  }
}

void draw(){
  while(port_A.available() > 0){
    sensor_no = port_A.read();
    if((sensor_no >= 0) && (sensor_no < N_SENSORS)){
       piano[sensor_no].trigger();
       println(sensor_no);
    }
  }
  
  
  while(port_B.available() > 0){
    sensor_no = port_B.read();
    if((sensor_no >= 0) && (sensor_no < N_SENSORS)){
       piano[sensor_no].trigger();
       println(sensor_no);
    }
  }
  
}


/*
「Error, disabling serialEvent() for {port name}
null」
という
*/
/*
void serialEvent(Serial p){
  sensor_no = p.read();
  //piano[sensor_no].trigger();
  //println(sensor_no);
  // Check for a valid value & play audio sample
  if((sensor_no >= 0) && (sensor_no < N_SENSORS)){
    piano[sensor_no].trigger();
    println(sensor_no);
  }
}
*/

void stop(){
  for(int i = 0; i < N_SENSORS; i++){
    piano[i].close();
  }
 minim.stop();
 super.stop();
}
