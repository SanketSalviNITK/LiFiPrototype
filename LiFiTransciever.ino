// Pin for transmitting light through LED
const int delayDuration = 10;
// String to be sent
String myText ;
int ascii;

String t = "00000000";
String br = "";
int val;
int THRESHOLD = 0;
int x, y, te, j, k, temp = 0;
int m = 7;
void setup()
{
  pinMode(A0, INPUT);
   pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  Serial.begin(2000000);
}
void LEDON(){
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH);
  }
void LEDOFF(){
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
}

void loop()
{
  receive();
  if (Serial.available())
  {
    myText = Serial.readString();
    send_data(" DEVICE : ");
    send_data(myText);
    send_data("\n");
    //Serial.println();
    Serial.print(" ME : ");
    Serial.println(myText);
    Serial.flush();
  }
  else
  {
    LEDOFF();
    
  }
}

void send_data(String msg)
{
  for (int i = 0; i < msg.length(); i++)
  {
    ascii = msg[i];
    //digitalWrite(data, HIGH);
    LEDON();
    delay(delayDuration);
    //digitalWrite(data, LOW);
    LEDOFF();
    delay(delayDuration);
    //digitalWrite(data, LOW);
    LEDOFF();
    delay(delayDuration);
    //digitalWrite(data, HIGH);
    LEDON();
    delay(delayDuration);
    //digitalWrite(data, HIGH);
    LEDON();
    delay(delayDuration);
    //digitalWrite(data, LOW);
    LEDOFF();
    delay(delayDuration);
    //digitalWrite(data, LOW);
    LEDOFF();
    delay(delayDuration);
    //digitalWrite(data, HIGH);
    LEDON();
    delay(delayDuration);
    for (int j1 = 7; j1 >= 0; j1--)
    {
      if (bitRead(ascii, j1) == 1)
      {
        //digitalWrite(data, HIGH);
        LEDON();
        delay(delayDuration);
        //digitalWrite(data, LOW);
        LEDOFF();
        delay(delayDuration);
        //Serial.print("10");
      }
      else
      {
        //digitalWrite(data, LOW);
        LEDOFF();
        delay(delayDuration);
        //digitalWrite(data, HIGH);
        LEDON();
        delay(delayDuration);
        //Serial.print("01");
      }
    }
    //Serial.println(" ");
  }
  //Serial.println("Sent");
}

void receive()
{
  val = analogRead(A0);
  //Serial.println(val);
  k++;
  temp += val;
  if (val > THRESHOLD)
    t = t.substring(1) + "1";
  else
    t = t.substring(1) + "0";
  if (t.equals("10011001"))
  {
    y = 0;
    for (int i = 15; i >= 0; i--)
    {
      delay(delayDuration);
      val = analogRead(A0);
      k++;
      temp += val;
      if (val > THRESHOLD)
        br = br + "1";
      else
        br = br + "0";
      //Serial.print(br);
      if (br.equals("01"))
      {
        x = 0;
        br = "";
        /*j = m;
          te = 1;
          while (j--)
          te = te * 2;*/
        y += 0;
        m--;
      }
      else if (br.equals("10"))
      {
        x = 1;
        br = "";
        j = m;
        te = 1;
        while (j--)
          te = te * 2;
        y += x * te;
        m--;
      }
      else if (br.length() > 2)
        br = "";
      //Serial.print(br);
    }
    m = 7;
    t = "00000000";
    Serial.print((char)y);
    /*if (k >= 24)
      {
       k = 0;
       THRESHOLD = temp / 24;
      // Serial.print("Threshold1 : ");
       //Serial.println(THRESHOLD);
       temp = 0;
      }*/
  }
  if (k >= 24)
  {
    THRESHOLD = temp / k;
    k = 0;
    // Serial.print("Threshold2 : ");
    // Serial.println(THRESHOLD);
    temp = 0;
    //Serial.println();
  }
  delay(delayDuration);
}
