#include <Servo.h>

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
  Serial.begin(9600);
  
  serv0.attach(servoPin);
  serv1.attach(servoPin1);
  serv2.attach(servoPin2);
  serv3.attach(servoPin3);
  serv4.attach(servoPin4);
  servr.attach(servoPinr);
}

void loop() {
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
