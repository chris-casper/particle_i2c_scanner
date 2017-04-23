// --------------------------------------
//
// i2c_scanner
//
//  This only handles 7 bit addresses. Anything with higher bit addresses may not work well.
//
//

 
#include "application.h"
 
 
void setup()
{
    
  Wire.begin();
  Serial.begin(9600);  
  while (!Serial);             

}
 
 
void loop()
{
    
  byte error, address;
  int i2cDevices;
 
  Serial.println("Scanning");  
  
  // If connected to USB, on command line use " particle monitor serial "
  // It doesn't talk to a cloud variable or function.  
 
  i2cDevices = 0; // Count of i2c devices
  
  for(address = 1; address < 127; address++ )
  {
    
    // Begin i2c read for address
    
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
        
      // Found something    
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
 
      i2cDevices++;  // Increment number of i2c devices
    }
    else if (error==4)
    {
      
      // Found error  
      Serial.print("Error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
      
    }    
  }
  
  // Scanning complete, let serial know if we found anything or not 
  if (i2cDevices == 0)
    Serial.println("No I2C address found\n");
  else
    Serial.println("Scan complete.\n");
 
  delay(10000);           // wait 10 seconds

}