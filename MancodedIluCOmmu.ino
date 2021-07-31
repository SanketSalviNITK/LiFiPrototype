char msg[]="HELLO WORLD\n";
void setup() {
  // put your setup code here, to run once:
  DDRD = DDRD | B01010011;
  PORTD = B00000000;
Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly
  //illuminationPhase();
  communicationPhase();
}
void illuminationPhase()
{
  for(int i=0;i<500;i++)
  {
    zero();  
  }
  
}
void communicationPhase()
{
  for(int i=0;i<100;i++){
  String msgLen="";
  for(int i=0;i<8;i++)
  {
    one();
  }
  //zero();
  //Serial.print("H");
  //Serial.println(sizeof(msg));
  if(sizeof(msg)<10)
  msgLen=String("00")+String(sizeof(msg));
  else if(sizeof(msg)>10 && sizeof(msg)<100)
  msgLen=String("0")+String(sizeof(msg));
  else if(sizeof(msg)>100 && sizeof(msg)<1000)
  msgLen=String(sizeof(msg));
  //Serial.println(msgLen);
 // Serial.println("L");
  String msg2=msgLen+msg;
  //Serial.println(msg2);
  for(int j=0;j<=msg2.length();j++)
  {
    printBits(msg2.charAt(j));
  }
  //Serial.println();
  }
}

void printBits(byte myByte){
 for(byte mask = 0x80; mask; mask >>= 1){
   if(mask  & myByte)
       one();
   else
       zero();
 }
}
void one()
{
  PORTD = PORTD & B00000000;
  delayMicroseconds(1000);
  PORTD = PORTD | B01010011;
  delayMicroseconds(1000);
  //Serial.print("01");
}
void zero()
{
  PORTD = PORTD | B01010011;
  delayMicroseconds(1000);
  PORTD = PORTD & B00000000;
  delayMicroseconds(1000);
  // Serial.print("10");
}
