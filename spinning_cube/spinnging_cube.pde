import processing.serial.*;

Serial myPort;  // Create object from Serial class
String input;      // Data received from the serial port
int[] values;
final int X = 0, Y = 1, Z = 2, C = 3, B = 4;
final int RED = 0, YELLOW = 1, GREEN = 2, BLUE = 3;
int angleX, angleY, zoom, bright;
Cube cube;

void setup() 
{
  size(640, 360, P3D);
  String portName = "COM4";
  myPort = new Serial(this, portName, 9600);
  
  cube = new Cube(300, 300, 300);
  
  angleX = 0;
  angleY = 0;
  zoom = -130;
  bright = 255;
}

void draw()
{
  if ( myPort.available() > 0) {  // If data is available,
    input = myPort.readStringUntil(';');         // read it and store it in val
    values = parseInput(input);
    println(values[X] + ", " + values[Y] + ", " + values[Z] + ", " + values[C] + ", " + values[B]);
    
    angleX += values[Y];
    angleY += values[X];
    zoom = -1 * values[Z];
    bright = values[B];
    
    switch(values[C]) {
      case RED:
        fill(bright, 0, 0);
        stroke(bright, 0, 0);
        break;
      case YELLOW:
        fill(bright, bright, 0);
        stroke(bright, bright, 0);
        break;
      case GREEN:
        fill(0, bright, 0);
        stroke(0, bright, 0);
        break;
      case BLUE:
        fill(0, 0, bright);
        stroke(0, 0, bright);
        break;
      default:
        noFill();
        stroke(bright);
    }
    
    background(50);
    lights();
    
    translate(width/2, height/2, zoom);
    rotateX(radians(angleX));
    rotateY(radians(angleY));
    cube.create();
  }  
}

int[] parseInput(String input) {
  
  if (input == null) {
    return values;
  }
 
 //Count the number of values in the input 
 int numValues = 1; 
 int i = 0;
 while (input.charAt(i) != ';') {
   if (input.charAt(i) == ',') {
     numValues++;
   }
   i++;
 }
  
 int[] output = new int[numValues];
 int currVal = 0;
 String val = "";
 
 //Split the input, convert to int, store in output
 i = 0;
 while (currVal < numValues) {   
   if (input.charAt(i) == ',') {
     output[currVal] = int(val);
     currVal++;
     i += 1;
     val = "";
   } else if (input.charAt(i) == ';') {
     output[currVal] = int(val);
     currVal++;
     val = "";
   }
   val = val + input.charAt(i);
   i += 1;
 } 
 return output;
}
