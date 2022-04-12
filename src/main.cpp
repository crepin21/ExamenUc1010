/*
  Titre      : Controle Vitesse
  Auteur     : Crepin Vardin Fouelefack
  Date       : 12/04/2022
  Description: Utilisation d'un clavier matricielle et d'un servomoteur pour simuler le deplacement d'un conduit
  Version    : 0.0.1
*/

#include <Arduino.h>
#include "WIFI_NINA_Connector.h"
#include "MQTTConnector.h"
#include <Wire.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo


//Declaration des constantes
const int DIG_MOTEUR   = 1;
const int DIG_LED      = 0;

//Declaration des variables
int pos           = 0;    // variable to store the servo position
int ValeurChoisie = 0;    //Pour contenir la valeur I2C recue

void receiveEvent(int bytes);  //Initialisation de la fonction pour recevoir la variable I2C


void setup() {
  Serial.begin(9600);
 // wifiConnect();                  //Branchement au réseau WIFI
 // MQTTConnect();                  //Branchement au broker MQTT

 

  myservo.attach(1);                  // attaches the servo on pin 2 to the servo object
  
   // Start the I2C Bus as Slave on address 9
  Wire.begin(9); 
  // Attach a function to trigger when something is received.
  Wire.onReceive(receiveEvent);
 
}
void receiveEvent(int bytes){
  ValeurChoisie = Wire.read();    // read one character from the I2C

}


// Boucle infinie qui permet au uC de faire une ou plusieurs taches sans arrêt

void loop() 
{             
            //Pour une position immediate a 180*
      if(ValeurChoisie == 1)
        {
          pos = 180;
           myservo.write(pos);              // tell servo to go to position in variable 'pos'
           delay(13);                       // waits 15ms for the servo to reach the position
        }

           //Pour un deplacement d'un degree vers max
      if(ValeurChoisie == 2)
        {
          pos +=1;
           myservo.write(pos);              // tell servo to go to position in variable 'pos'
           delay(13);                       // waits 15ms for the servo to reach the position
        }

          //Pour un deplacement d'un degree vers min
      if(ValeurChoisie == 3)
        {
          pos -=1;
           myservo.write(pos);              // tell servo to go to position in variable 'pos'
           delay(13);                       // waits 15ms for the servo to reach the position
        }
      
          //Pour une position immediate a 0*
      if(ValeurChoisie == 4)
        {
          pos = 0;
           myservo.write(pos);              // tell servo to go to position in variable 'pos'
           delay(13);                       // waits 15ms for the servo to reach the position
        }
      if(pos != 0)
      {
        
      }
      
  //  appendPayload("Valeur", 20);  //Ajout de la valeur de la broche A1 au message MQTT
   // sendPayload();                                   //Envoie du message via le protocole MQTT
}




