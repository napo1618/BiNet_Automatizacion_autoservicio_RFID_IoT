//Programa prueba para conectar ESP32 con módulo MAX7219 7 segmentos
//El programa escribe "Arduino" haciendo una combinación de escritura por setChar(Character) y 
// setRow(escritura hexadecimal o bit por bit)

//Programa adaptado de arduino a ESP32 

//We always have to include the library
#include "LedController.hpp"

/*
 Now we need a LedControl to work with. 
 ***** These pin numbers will probably not work with your hardware *****
 pin 22 is connected to the DataIn 
 pin 18 is connected to the CLK 
 pin 5 is connected to LOAD 
 Sólo tenemos un chip MAX7219 en el módulo, con capacidad máxima de controlar 8 digitos
 */
LedController lc;

/* we always wait a bit between updates of the display */
unsigned long delaytime=2500;

void setup() {

  lc=LedController(22,18,5,1);

  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.activateAllSegments();
  /* Set the brightness to a medium values */
  lc.setIntensity(1);
  /* and clear the display */
  lc.clearMatrix();
}


/*
 This method will display the characters for the
 word "Arduino" one after the other on digit 0. 
 */
 
void writeArduinoOn7Segment() {
  lc.setRow(0,7,0x00);            //Display 7
  //delay(delaytime);
  lc.setChar(0,6,'A',false);      //Display 6
  //delay(delaytime);
  lc.setRow(0,5,0x05);            //Display 5
  //delay(delaytime);
  lc.setChar(0,4,'d',false);      //Display 4
  //delay(delaytime);
  lc.setRow(0,3,0x1c);            //Display 3
  //delay(delaytime);
  lc.setRow(0,2,B00010000);       //Display 2
  //delay(delaytime);
  lc.setRow(0,1,0x15);            //Display 1
  //delay(delaytime);
  lc.setRow(0,0,0x1D);            //Display 0
  //delay(delaytime);
  //lc.clearMatrix();
  //delay(delaytime);
} 
*/
/*
  This method will scroll all the hexa-decimal
 numbers and letters on the display. You will need at least
 four 7-Segment digits. otherwise it won't really look that good.
 
void scrollDigits() {
  for(int i=0;i<13;i++) {
    lc.setDigit(0,3,i,false);
    lc.setDigit(0,2,i+1,false);
    lc.setDigit(0,1,i+2,false);
    lc.setDigit(0,0,i+3,false);
    delay(delaytime);
  }
  lc.clearMatrix();
  delay(delaytime);
}

void loop() { 
  writeArduinoOn7Segment();
  //scrollDigits();
 
}
