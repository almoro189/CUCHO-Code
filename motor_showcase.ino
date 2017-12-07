
void forward(int POW){
  digitalWrite(8,HIGH);
  digitalWrite(7,LOW);
  digitalWrite(6,HIGH);
  digitalWrite(5,LOW);
  analogWrite(9,POW);
  analogWrite(3,POW);
}
void back(int POW){
  digitalWrite(8,LOW);
  digitalWrite(7,HIGH);
  digitalWrite(6,LOW);
  digitalWrite(5,HIGH);
  analogWrite(9,POW);
  analogWrite(3,POW);
}

void parar(){
  digitalWrite(8,LOW);
  digitalWrite(7,LOW);
  digitalWrite(6,LOW);
  digitalWrite(5,LOW);
}

void cturnl(int POW){
  digitalWrite(8,HIGH);
  digitalWrite(7,LOW);
  digitalWrite(6,LOW);
  digitalWrite(5,HIGH);
  analogWrite(9,POW);
  analogWrite(3,POW);
}


void cturnr(int POW){
  digitalWrite(8,LOW);
  digitalWrite(7,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(5,LOW);
  analogWrite(9,POW);
  analogWrite(3,POW);
}

void forwturn(int POWL,int POWR){
  digitalWrite(8,HIGH);
  digitalWrite(7,LOW);
  digitalWrite(6,HIGH);
  digitalWrite(5,LOW);
  analogWrite(9,POWL);
  analogWrite(3,POWR);
}
void backturn(int POWL,int POWR){
  digitalWrite(8,LOW);
  digitalWrite(7,HIGH);
  digitalWrite(6,LOW);
  digitalWrite(5,HIGH);
  analogWrite(9,POWL);
  analogWrite(3,POWR);
}
void setup() {
  pinMode(9,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(3,OUTPUT);

  digitalWrite(8,LOW);
  digitalWrite(7,LOW);
  digitalWrite(6,LOW);
  digitalWrite(5,LOW);
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(3000);
  forward(175);
  delay(2000);
  parar();
  delay(700);
  back(175);
  delay(2000);
  parar();
  delay(700);
  cturnl(175);
  delay(2000);
  parar();
  delay(700);
  cturnr(175);
  delay(2000);
  parar();
  delay(700);
  forwturn(150,255);
  delay(1800);
  forwturn(255,125);
  delay(1800);
  parar();
  delay(700);
  backturn(255,125);
  delay(1800);
  backturn(125,255);
  delay(1800);
  parar();
  delay(5000);
}
