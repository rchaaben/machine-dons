#include <Servo.h>
/*  
lire un fichier net avec une info
basé sur le script de tweet de Tom Igoe

* Ethernet shield attached to pins 10, 11, 12, 13

This code is in the public domain.

*/
#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0x1C, 0x5D };
IPAddress ip(192,168,1,20);

// initialize the library instance:
EthernetClient client;

const unsigned long requestInterval = 60000;  // delay between requests

char serverName[] = "anisayari.com";

boolean requested;                   // whether you've made a request since connecting
unsigned long lastAttemptTime = 0;   // last time you connected to the server, in milliseconds

String currentLine = "";            // string to hold the text from server
String message = "";                  // string to hold the message
boolean lecture = false;       // if you're currently reading the message

//déclaration des 5 servomoteurs des doigts et le servomoteur du rideau
Servo serv0 ;
Servo serv1 ;
Servo serv2 ;
Servo serv3 ;
Servo serv4 ;
Servo servr ;

//les 6 pwm PINs
int servoPin  = 9  ;
int servoPin1 = 10 ;
int servoPin2 = 6  ;
int servoPin3 = 5  ;
int servoPin4 = 3  ;
int servoPinr = 11 ;

boolean bouton=true;
int nbrValeurs=9;

//la matrice de la danse
int valeurs0[9]={0,0,90,0,0,0,0,0,0};
int valeurs1[9]={90,90,90,90,30,90,90,90,90};
int valeurs2[9]={50,90,90,90,90,90,90,90,50};
int valeurs3[9]={90,90,90,90,90,90,50,50,90};
int valeurs4[9]={90,90,180,180,180,180,180,90,90};


void setup() {
 // reserve space for the strings:
 currentLine.reserve(256);
 message.reserve(150);

 // Open serial communications and wait for port to open:
 Serial.begin(9600);
 while (!Serial) {
   ; // wait for serial port to connect. Needed for Leonardo only
 }

 // attempt a DHCP connection:
 Serial.println("Attempting to get an IP address using DHCP:");
 if (!Ethernet.begin(mac)) {
   // if DHCP fails, start with a hard-coded address:
   Serial.println("failed to get an IP address using DHCP, trying manually");
   Ethernet.begin(mac, ip);
 }
 Serial.print("Mon adresse:");
 Serial.println(Ethernet.localIP());
 // premiere connection :
 connectToServer();
 serv0.attach(servoPin);
 serv1.attach(servoPin1);
 serv2.attach(servoPin2);
 serv3.attach(servoPin3);
 serv4.attach(servoPin4);
 servr.attach(servoPinr);
}

void loop(){
 if(message.length() > 0 && lecture==false){
   Serial.print("je viens de recevoir un message : ");
  Serial.println(message);
  if (message =="1"){
  Serial.print("lancer la marionnette");
  //lancer la marionnette
  if (bouton==true){
           servr.write(0);
           delay(3000);
           for (int i=0;i<5;i++){
             marionnette();
           }
           bouton = false;
           servr.write(180);
         }
  }
 message=""; 
 }
 
 if (client.connected()) {
   checke_page(); 
 }
 else if (millis() - lastAttemptTime > requestInterval) {
   // if you're not connected, and two minutes have passed since
   // your last connection, then attempt to connect again:
   connectToServer();
 } 
}

void checke_page(){
 if (client.available()) {
   // read incoming bytes:
   char inChar = client.read();

   // add incoming byte to end of line:
   currentLine += inChar; 

   // si on a un retour chariot, c'est que ce n'est pas encore le debut, on supprime:
   if (inChar == '\n') {
     currentLine = "";
   } 

   // si on trouve le message <text>, c'est 
   // que le message suit:
   if ( currentLine.endsWith("<info>")) {

     // debut du message, on vide la string message:
     lecture = true; 
     message = "";
     inChar = client.read(); // lire le caractere suivant
   }
   // on lit caractere par caractere,
   // et les ajoute au message
   if (lecture) {
     if (inChar != '<') {
       message += inChar;
     } 
     else {
       // isi vous avez un "<",
       // c'est la fin du message:
       lecture = false;
          
       // fermer la connexion au serveur:
       client.stop(); 
     }
   }
 }
}

void connectToServer() {
 // attempt to connect, and wait a millisecond:
 Serial.println("connecting to server...");
 if (client.connect(serverName, 80)) {
   Serial.println("making HTTP request...");
   // make HTTP GET request:
   client.println("GET /projetdev/check.php HTTP/1.1");
   client.println("Host: anisayari.com");
   client.println();
 }
 // remettre le compteur a zero pour la prochaine connexion:
 lastAttemptTime = millis();
}  

void marionnette(){   
         for (int i=0;i<9;i++){
           serv4.write(valeurs0[i]);
           serv2.write(valeurs1[i]);
           serv3.write(valeurs2[i]);
           serv1.write(valeurs3[i]);
           serv0.write(valeurs4[i]);
           delay(500);
         }      
}
