#include "OneWire.h"            // Biblioteca auxiliar para utilizar sensor de temperatura
#include "DallasTemperature.h"  // Biblioteca principal de utilização do sensor de temperatura
#include <Wire.h>               // Biblioteca que 
#include <ACROBOTIC_SSD1306.h>  // Biblioteca para utilizar o display OLED
 
#define buttonUP 12        // Botão que aumenta a temperatura desejada
#define buttonDown 14      // Botão que diminui a temperatura desejada
#define portrele 23        // Pino utilizado para acionar o relé
 
OneWire oneWire(19);
DallasTemperature tempSensor(&oneWire);
 
long setpoint;             // Valor da temperatura desejada
 
void setup(void){
    Wire.begin();
    oled.init();
    oled.clearDisplay();
    Serial.begin(115200);
    tempSensor.begin();
    pinMode(buttonUP, INPUT);
    pinMode(buttonDown, INPUT);
    pinMode(portrele, OUTPUT);
    setpoint=tempSensor.getTempCByIndex(0); // Inicialmente temperatura deseja recebe temperatura atual do sensor
}

// CONFIGURAÇÃO DA INTERFACE OLED
void draw(float temp){
    oled.setTextXY(0,0);              // Posiciona o cursor
    oled.putString("Temp:");
    oled.setTextXY(0,10);
    oled.putFloat(temp,2);
    oled.setTextXY(0,13);
    oled.putString("C");
 
    oled.setTextXY(1,0);
    oled.putString("Set: ");
    oled.setTextXY(1,10);
    oled.putNumber(setpoint);
    oled.setTextXY(1,13);
    oled.putString("C");
}

void loop(void){
    tempSensor.requestTemperaturesByIndex(0);
    float temp = tempSensor.getTempCByIndex(0);
    Serial.println(temp);

    if(digitalRead(buttonUP)){
        setpoint++;
    }
    if(digitalRead(buttonDown)){
        setpoint--;
    }
    draw(temp);
    long atual = (long)temp;
    if(atual<setpoint)
        digitalWrite(portrele,HIGH);
    else
        digitalWrite(portrele,LOW);
}
