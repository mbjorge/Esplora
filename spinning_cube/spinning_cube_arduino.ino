/*
  Esplora Accelerometer 
 
 This  sketch shows you how to read the values from the accelerometer.
 To see it in action, open the serial monitor and tilt the board. You'll see
 the accelerometer values for each axis change when you tilt the board 
 on that axis.
  
 Created on 22 Dec 2012
 by Tom Igoe
 
 This example is in the public domain.
 */

#include <Esplora.h>

int maxX = -1024, minX = 1024;
int maxY = -1024, minY = 1024;
int maxZ = -1024, minZ = 1024;
const int RED = 0, YELLOW = 1, GREEN = 2, BLUE = 3;
int color;
int bright;

void setup()
{
  Serial.begin(9600);        // initialize serial communications with your computer
} 

void loop()
{
  int xAxis = Esplora.readAccelerometer(X_AXIS);    // read the X axis
  int yAxis = Esplora.readAccelerometer(Y_AXIS);    // read the Y axis
  int zAxis = Esplora.readAccelerometer(Z_AXIS);    // read the Z axis
/*
  maxX = max(maxX, xAxis);
  minX = min(minX, xAxis);
  maxY = max(maxY, yAxis);
  minY = min(minY, yAxis);
  maxZ = max(maxZ, zAxis);
  minZ = min(minZ, zAxis);

  Serial.print(minX);
  Serial.print(", ");
  Serial.print(minY);
  Serial.print(", ");
  Serial.println(minZ);
  
  Serial.print(maxX);
  Serial.print(", ");
  Serial.print(maxY);
  Serial.print(", ");
  Serial.println(maxZ);
*/

  if (Esplora.readButton(SWITCH_DOWN) == LOW) {
    color = RED;
  } else if (Esplora.readButton(SWITCH_LEFT) == LOW ) {
    color = YELLOW;
  } else if (Esplora.readButton(SWITCH_UP) == LOW) {
    color = GREEN;
  } else if (Esplora.readButton(SWITCH_RIGHT) == LOW) {
    color = BLUE;
  } else if (Esplora.readJoystickButton() == LOW) {
    color = -1;
  }
  
  Serial.print(map(Esplora.readJoystickX(), -512, 512, -15, 15));
  Serial.print(',');
  Serial.print(map(Esplora.readJoystickY(), -512, 512, -15, 15));
  Serial.print(',');
  Serial.print(Esplora.readSlider());
  Serial.print(',');
  Serial.print(color);
  Serial.print(',');
  Serial.print(map(Esplora.readLightSensor(), 0, 1023, 0, 255));
  Serial.print(';');
  
  bright = map(Esplora.readSlider(), 0, 1023, 255, 1);
  
  switch (color) {
    case RED:
      Esplora.writeRGB(bright, 0, 0);
      break;
    case YELLOW:
      Esplora.writeRGB(bright, bright, 0);
      break;
    case GREEN:
      Esplora.writeRGB(0, bright, 0);
      break;
    case BLUE:
      Esplora.writeRGB(0, 0, bright);
      break;
     default:
      Esplora.writeRGB(bright, bright, bright);
  } 
  delay(75);
}


