#include <SoftwareSerial.h>
#include <PID_v1.h>

SoftwareSerial BT2(12, 13);   // Pines RX y TX del modulo 2
SoftwareSerial BT3(10, 11);   //Pines RX y TX del modulo 3


bool iterando = false; //Setup del bluetooth
bool serialBT2 = false; //Actualmente se trabaja en el modulo 2
bool serialBT3 = false; //Actualmente se trabaja en el modulo 3
String resBT2 = "";
String resBT3 = "";
double rssi2;
//int RSSI2;
double rssi3;
//int RSSI3;
long delta;
//----------------------------------------------------------
//Variables distancias
double SetpointDis, InputDis, OutputDis;
double Dis;
//Variables direccion
double SetpointDir, InputDir, OutputDir;
double Dir;
// Constantes PID Direccion y Distancia
double KpDir=2, KiDir=5, KdDir=1;
double KpDis=2,KiDis=5,KdDis=1;

//Variables Intensidad de Señal
double IR,IL;
//Distancia minima para activar diferencia de direccion
float MinDir=5;

//Variables de potencia
double POWL;
double POWR;

//PID Distancia
PID DIS(&InputDis, &OutputDis, &SetpointDis, KpDis, KiDis, KdDis, DIRECT);

//PID Direccion
PID DIR(&InputDir, &OutputDir, &SetpointDir, KpDir, KiDir, KdDir, DIRECT);
//--------------------------------------------------------------------------
long funcionDani(String Signal){
  String resultado;
    if (Signal.substring(13,19) == "708B76"){
      resultado=Signal.substring(22,26);
    }
    //Serial.println(resultado);
    long Rssi = hexToDec(resultado);
    return Rssi; 
  }

long hexToDec(String hexString) {
  long decValue = 0;
  int nextInt;
  for (int i = 0; i < hexString.length(); i++) {
    nextInt = int(hexString.charAt(i));

    if (nextInt >= 48 && nextInt <= 57) nextInt = map(nextInt, 48, 57, 0, 9);

    if (nextInt >= 65 && nextInt <= 70) nextInt = map(nextInt, 65, 70, 10, 15);

    if (nextInt >= 97 && nextInt <= 102) nextInt = map(nextInt, 97, 102, 10, 15);

    nextInt = constrain(nextInt, 0, 15);
    decValue = (decValue * 16) + nextInt;

  }
  return decValue;
}


void setup() {
  //------------------------------------------------
  pinMode(9,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(3,OUTPUT);

  //Inicialización PID
  IL=10;
  IR=10;
  InputDir=IL-IR;
  InputDis=(IL + IR)/2;
  SetpointDir=0;//dIRECCION
  SetpointDis=65460.0;//dISTANCIA
  //Encender PID
  DIS.SetMode(AUTOMATIC);
  DIR.SetMode(AUTOMATIC);



  //Puente H
  digitalWrite(8,HIGH);
  digitalWrite(7,LOW);
  digitalWrite(6,HIGH);
  digitalWrite(5,LOW);
  
  
  BT2.begin(38400); //Inicializa modulo numero 2

  BT3.begin(38400); //Inicializa modulo numero 3

  Serial.begin(9600); //Inicializa puerto serial

  Serial.print("setpointDIS = "); Serial.println(SetpointDis);
  
  while (!Serial)
  {
    ;
  }
}

void loop() {
  if (!iterando){   //Setup de ambos modulos bluetooth
    Serial.println("inicializando");
    
    BT2.write("at+reset\r\n");
    delay(500);
    BT2.write("at+role=1\r\n");
    delay(500);
    BT2.write("at+iac=9e8b33\r\n");
    delay(500);
    BT2.write("at+class=0\r\n");
    delay(500);
    BT2.write("at+inqm=1,2,3\r\n");
    delay(500);
    BT2.write("at+init\r\n");
    delay(500);
    
    BT3.write("at+reset\r\n");
    delay(500);
    BT3.write("at+role=1\r\n");
    delay(500);
    BT3.write("at+iac=9e8b33\r\n");
    delay(500);
    BT3.write("at+class=0\r\n");
    delay(500);
    BT3.write("at+inqm=1,2,3\r\n");
    delay(500);
    BT3.write("at+init\r\n");
    delay(500);

    Serial.println("inicializado");
    iterando = true;
    Serial.println("iterando");
  }

  if (iterando){     //Iteracion de ambos bluetooth para obtener rssi
    serialBT2 = true;
    
    if(serialBT2){
      BT2.listen();
      resBT2 = "";
      BT2.write("at+inq\r\n");
      Serial.println("scan module 2");
      float tiempo = 0.0;
      while (tiempo < 1){
        resBT2 = BT2.readString();
        if (resBT2 == ""){
          delay(1);
          tiempo = tiempo + 0.1*2;
        }
        else if (resBT2.substring(0,19) == "+INQ:98D3:32:708B76"){
          Serial.print(resBT2);  
          rssi2 = funcionDani(resBT2);    //Funcion que recibe el string y devuelve el rssi2
          //Serial.println(resBT2.substring(22,26));
          tiempo = 1;
        }
        else{
          Serial.print(resBT2);
          delay(1);
          tiempo = tiempo + 0.1*2;
        }
      }

      //Serial.println(rssi2);
      serialBT2 = false;
    }
    serialBT3 = true;

    if(serialBT3){
      BT3.listen();
      resBT3 = "";
      BT3.write("at+inq\r\n");
      Serial.println("scan module 3");
      float tiempo = 0.0;
      while (tiempo < 1){
        resBT3 = BT3.readString();
        if (resBT3 == ""){
          delay(1);
          tiempo = tiempo + 0.1*2;
        }
        else if (resBT3.substring(0,19) == "+INQ:98D3:32:708B76"){
          Serial.print(resBT3);  
          rssi3 = funcionDani(resBT3);    //Funcion que recibe el string y devuelve el rssi2
          //Serial.println(resBT3.substring(22,26));
          tiempo = 1;
        }
        else{
          Serial.print(resBT3);
          delay(1);
          tiempo = tiempo + 0.1*2;
        }
      }

      //Serial.println(rssi3);
      serialBT3 = false;
    }  
      long ajuste = 10;
      delta = rssi3 - rssi2 - ajuste;
      Serial.print("RSSI 2 = "); Serial.println(rssi2);
      Serial.print("RSSI 3 = "); Serial.println(rssi3);
      //Serial.print("delta = "); Serial.println(delta);

    //RSSI2 = rssi2;
    //RSSI3 = rssi3;
    //Serial.print("RSSI2 = "); Serial.println(RSSI2);
    //Serial.print("RSSI3 = "); Serial.println(RSSI3);
  }
  

 //PID
 IL=rssi2;
 //Serial.println(IL);
 //Serial.println(pow(IL,2.0));
 IR=rssi3;
 //Serial.println(IR);
 //Serial.println(pow(IR,2.0));
 InputDir=IL-IR;
 InputDis= (IL + IR)/2;
 Serial.print("inputDis = "); Serial.println(InputDis);

 DIS.Compute();
 DIR.Compute();

 POWL=OutputDis*10/4;
 POWR=POWL;

 if(abs(OutputDir)>MinDir){
  POWR=POWR+OutputDir;
  POWL=POWL-OutputDir;
 }
  Serial.println(POWL);
  Serial.println(POWR);
  analogWrite(9,POWL);
  analogWrite(3,POWR);

}
//Modulo 3 tiene mejor sensibilidad que modulo 2

