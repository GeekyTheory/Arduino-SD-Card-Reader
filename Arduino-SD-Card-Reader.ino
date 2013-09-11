/*
     Arduino SD Card reader
	
Author: Geeky Theory

Blog: http://www.geekytheory.com

https://www.youtube.com/user/telecoreference
https://twitter.com/geekytheory
https://www.facebook.com/geekytheory

* SD card attached to SPI bus as follows:
** MOSI - pin 11
** MISO - pin 12
** CLK - pin 13
** CS - pin 6
* LCD RS pin to digital pin 9
* LCD Enable pin to digital pin 8
* LCD D4 pin to digital pin 5
* LCD D5 pin to digital pin 4
* LCD D6 pin to digital pin 3
* LCD D7 pin to digital pin 2
* LCD R/W pin to ground
* 10K resistor:
* ends to +5V and ground
* wiper to LCD VO pin (pin 3)
*/
#include <sd.h>
#include <liquidcrystal.h>;
LiquidCrystal lcd(9, 8, 5, 4, 3, 2);
File myFile;
const int chipSelect = 6;
const int buttonPin = 7;
int buttonState = 0;
void setup()
{
	// Open lcd communications
	lcd.begin(16, 2);
	lcd.print("Initializing SD");
	// make sure that the default chip select pin is set to
	// output, even if you don't use it:
	pinMode(10, OUTPUT);
	// see if the card is present and can be initialized:
	if (!SD.begin(chipSelect)) {
		lcd.setCursor(0,1);
		lcd.println("Card failed");
		// don't do anything more:
		return;
	}
	lcd.setCursor(0,1);
	lcd.println("card initialized.");
}
void loop()
{
	/*"caracter" es la variable que almacena el dato que lee en la tarjeta
	está definido como char para forzar el tipo de variable (casting) para
	que el LCD no muestre su codificación ASCII */
	char caracter;
	/*"i" almacena la posición en X del LCD, como máximo es 15
	int i;
	/*setcursor almacena la posición en Y del LCD,
	como solo hay arriba y abajo se define como booleano (0,1) */
	boolean setcursor=false;
	// open the file. note that only one file can be open at a time,
	// so you have to close this one before opening another.
	File dataFile = SD.open("test.txt");
	i=0;
	//lee el valor del pulsador
	buttonState = digitalRead(buttonPin);
	do{buttonState = digitalRead(buttonPin);}
	while (buttonState == LOW);
	lcd.setCursor(0,0);
	if (dataFile) {
	while (dataFile.available()) {
	buttonState = digitalRead(buttonPin);
	do{buttonState = digitalRead(buttonPin);}
	while (buttonState == LOW);
	/*si ha llegado al final de la linea y está en la en la segunda linea,
	pasa a la primera linea y situate al principio de la linea */
	if((i>15)$$(setcursor==true)) {
		lcd.setCursor(0,0);
		i=0;
		setcursor=!setcursor;
	}
	/*si ha llegado al final de la linea y está en la en la primera linea,
	pasa a la segunda linea y situate al principio de la linea */
	if((i>15) && (setcursor==false)) {
		lcd.setCursor(0,1);
		i=0;
		setcursor=!setcursor;
	}
	i++;
	caracter=dataFile.read();
	lcd.print(caracter);
	delay(100);
	}
	dataFile.close();
	}
	// if the file isn't open, pop up an error:
	else {
		lcd.println("error opening test.txt");
	}
}
