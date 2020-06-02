/*
  Instalar libreria MFRC522

  Autor: bitwiseAr

  El programa original (autor:bitwiseAr) creó el programa para usarse con Arduino, sólo haré
  las modificaciones necesarias para usar el programa con un ESP32

  Modificador: AndresCans
  
  * Typical pin layout used:
 * ---------------------------------------------------------------------------------------------------
 *             MFRC522      ESP32       Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD               Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin          Pin        Pin              Pin
 * ---------------------------------------------------------------------------------------------------
 * RST/Reset   RST           EN            9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)       21           10            53        D10        10               10
 * SPI MOSI    MOSI          23           11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO          19           12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK           18           13 / ICSP-3   52        D13        ICSP-3           15
 
*/

//Datos para ESP32
#include <SPI.h>              // incluye libreria bus SPI
#include <MFRC522.h>          // incluye libreria especifica para MFRC522

#define RST_PIN  4      // constante para referenciar pin de reset
#define SDA_PIN  21     // constante para referenciar pin de slave select

MFRC522 mfrc522(SDA_PIN, RST_PIN); // crea objeto mfrc522 enviando pines de slave select y reset

//Datos para MAX7219
#include "LedController.hpp"  // incluye libreria para control MAX7219 display 7 segmentos


LedController lc;        //el chip MAX7219 tiene capacidad máxima de controlar 8 dígitos

void setup() {
  Serial.begin(9600);     // inicializa comunicacion por monitor serie a 9600 bps
  
//Datos para ESP32 
  SPI.begin();        // inicializa bus SPI
  mfrc522.PCD_Init();     // inicializa modulo lector

//Datos para MAX7219
  lc=LedController(12,13,14,1);  //LedController(DIN(MISO), CLK(MOSI), CS, # de dispositivos(1-8))
  lc.activateAllSegments();
  lc.setIntensity(8);
  lc.clearMatrix();
  
}

void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) // si no hay una tarjeta presente
    return;         // retorna al loop esperando por una tarjeta
  
  if ( ! mfrc522.PICC_ReadCardSerial())   // si no puede obtener datos de la tarjeta
    return;         // retorna al loop esperando por otra tarjeta
    
  Serial.print("UID:");       // muestra texto UID:
  for (byte i = 0; i < mfrc522.uid.size; i++) { // bucle recorre de a un byte por vez el UID
    if (mfrc522.uid.uidByte[i] < 0x10){   // si el byte leido es menor a 0x10
      Serial.print(" 0");     // imprime espacio en blanco y numero cero
      }
      else{         // sino
      Serial.print(" ");      // imprime un espacio en blanco
      }
    Serial.print(mfrc522.uid.uidByte[i], HEX);  // imprime el byte del UID leido en hexadecimal  
    
  } 
 
  Serial.println();       // nueva linea
  mfrc522.PICC_HaltA();                   // detiene comunicacion con tarjeta
    char myString[8];
    String valores;
    for (byte i = 0; i <= mfrc522.uid.size; i++) { // bucle recorre de a un byte por vez el UID
    if (mfrc522.uid.uidByte[i] < 0x10){   // si el byte leido es menor a 0x10
      valores = valores + "0";
      valores = valores + String(mfrc522.uid.uidByte[i], HEX);
      }
      else{         // sino
      valores = valores + String(mfrc522.uid.uidByte[i], HEX);
      }
    }
    valores.toUpperCase();
    valores.toCharArray(myString, 9);

  lc.setChar(0,7,myString[0],false);            //Display 7
  lc.setChar(0,6,myString[1],false);            //Display 6
  lc.setChar(0,5,myString[2],false);            //Display 5
  lc.setChar(0,4,myString[3],false);            //Display 4
  lc.setChar(0,3,myString[4],false);            //Display 3
  lc.setChar(0,2,myString[5],false);            //Display 2
  lc.setChar(0,1,myString[6],false);            //Display 1
  lc.setChar(0,0,myString[7],false);            //Display 0

  Serial.print(valores);
  
}
