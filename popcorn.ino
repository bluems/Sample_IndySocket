#include <YunServer.h>
#include <YunClient.h>
#include <Console.h>
#include <Process.h>

//Motor Lib
//#include <Stepper.h>

//EEPROM
#include <EEPROM.h>


//CurrentSenSor
#define CURRENT_SENSOR A0

//Relay Comm.
#define relayPin 11

//ultraSonic Sensor
#define ultraSonicTrig 7
#define ultraSonicEcho 8
#define LED 13

//Motor
#define startPin 9
#define clockPin 6
#define rotatePin 10
#define stepsPerRevolution 200


int incomingByte;

//Currnet Sensor Value
float amplitude_current;//전류값
float effective_value;//실효값
int sensor_max;

//Ultra Sonic
//int maximumRange=400;
//int minimumRange=0;
//long duration, distance;

//time
Process date, day;
int /*seconds,*/minutes;
//int lastSecond = -1;
int cnt;


YunServer server;


//Stepper myStepper(stepsPerRevolution,clockPin,rotatePin);

void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode(CURRENT_SENSOR, INPUT);
  //pinMode(ultraSonicTrig, OUTPUT);
  //pinMode(ultraSonicEcho, INPUT);
  pinMode(LED,OUTPUT);
  //pinMode(startPin,OUTPUT);
  //pinMode(clockPin,OUTPUT);
  //pinMode(rotatePin,OUTPUT);
  Serial.begin(9600);
  Serial.println(F("Start."));
  Bridge.begin();
  Console.begin();
  server.begin();

  //EEPROM
  if(EEPROM.read(0)==0) {
    EEPROM.write(0,5);
  }

  cnt=0;
  
  if (!date.running()) {
    date.begin("date");
    date.addParameter("+%T");
    date.run();
  }
  if (!day.running()) {
    day.begin("date");
    day.addParameter("-I");
    day.run();
  }
  //myStepper.setSpeed(300);
  //digitalWrite(rotatePin,LOW);
  //digitalWrite(clockPin,HIGH);
  //digitalWrite(startPin,HIGH);
}


void loop() {
  YunClient client = server.accept();

  /* REST통신에 의한 데이터 처리 */
  if (client) {
    process(client);
    client.stop();
  }
  delay(50);

  if (!date.running()) {
    date.begin("date");
    date.addParameter("+%T");
    date.run();
  }
  if (!day.running()) {
    day.begin("date");
    day.addParameter("-I");
    day.run();
  }
  sensorAmp();
  //usonic();
  //calc();
  delay(50);
  Sender();
}
//End Loop
/*
void calc(){
    //Calc
  distance=duration/58.2;// us/cm = 58.2
  if(distance>=maximumRange || distance <=minimumRange){
    Console.println(F("Range Out"));
    distance=0;
    digitalWrite(LED,HIGH);
  }else
  {
    Console.println(distance);
    if(distance<=30)
      //myStepper.step(stepsPerRevolution);
      delay(1000);
    digitalWrite(LED,LOW);
  }
}
*/
void Sender(){
  String daytime = time_calc();
  int t=EEPROM.read(0);
  if (/*seconds*/minutes % t == 0 && cnt==0) {
    Process p;
    char relay_status;
    if (digitalRead(relayPin) == 0)
      relay_status = 'N';
    else
      relay_status = 'Y';


  String uuid = "06545562-9551-4E28-BC10-2744574C6811";
  String device_name = "Yun_A";
  String host="conoha.nazuna.kr";
    Serial.println("Send Status.");
    //Serial.println("curl \"http://conoha.nazuna.kr/insert.php?uuid="+uuid+"&device_name="+device_name+"&relay_status="+relay_status+"&rms="+effective_value+"&date="+daytime+"&distance="+distance+"\"");
    //p.runShellCommand("curl \"http://"+host+"/insert.php?uuid="+uuid+"&device_name="+device_name+"&relay_status="+relay_status+"&rms="+effective_value+"&date="+daytime+"&distance="+distance+"\"");
    while (p.running());
    Serial.println("Success.");
    cnt=1;
  }
  if(minutes % t !=0)
    cnt=0;
}
/*
void usonic(){
  // put your main code here, to run repeatedly:
  digitalWrite(ultraSonicTrig, LOW);
  delayMicroseconds(2); //Why?
  digitalWrite(ultraSonicTrig, HIGH);
  delayMicroseconds(10); //Trig Timing
  digitalWrite(ultraSonicTrig, LOW);
  duration=pulseIn(ultraSonicEcho,HIGH);
}*/

String time_calc() {
  String /*secString, */timeString, dayString, minString;
  while (date.available() > 0) {
    timeString = date.readString();
    Serial.println(timeString);
    int firstColon = timeString.indexOf(":");
    int secondColon = timeString.lastIndexOf(":");
    minString = timeString.substring(firstColon+1, secondColon);
    //secString = timeString.substring(secondColon + 1);

    //lastSecond = seconds;
    minutes = minString.toInt();
    //seconds = secString.toInt();
  }
  while (day.available() > 0) {
    dayString = day.readString();
  }

  String Result = dayString.substring(0,10) + "%20" + timeString.substring(0,8);
  return Result;
  //}
}

//REST 입력 정보 ; http://ip/arduino/argu1/argu2/argu3...
//REST 정보에서 두번째 인자 판별
void process(YunClient client) {
  String command = client.readStringUntil('/');

  if (command == "digital") {
    digitalCommand(client);
  }
  if (command == "analog") {
    analogCommand(client);
  }
  if (command == "config") {
    configCommand(client);
  }
}

//Config
void configCommand(YunClient client){
  String set = client.readStringUntil('/');
  int value = client.parseInt();
  if(set == "logtime") {
    EEPROM.write(0,value);
    client.print("set to ");
    int eep=EEPROM.read(0);
    client.println(eep);
  }
  
}

//DIGITAL PIN
void digitalCommand(YunClient client) {
  int pin, value;

  pin = client.parseInt();

  if (client.read() == '/') {
    value = client.parseInt();
    digitalWrite(pin, value);
  }
  else {
    value = digitalRead(pin);
  }


  client.print(F("Relay set to "));
  client.println(value);

  String key = "D";
  key += pin;
  Bridge.put(key, String(value));
}

//Analog PIN
void analogCommand(YunClient client) {
  int pin, value;

  pin = client.parseInt();

  if (client.read() == '/') {
    value = client.parseInt();
    analogWrite(pin, value);

    // Send feedback to client
    client.print(F("Pin D"));
    client.print(pin);
    client.print(F(" set to analog "));
    client.println(value);

    String key = "D";
    key += pin;
    Bridge.put(key, String(value));
  }
  else {
    value = analogRead(pin);
    client.print(F("{\"sensor_max\" : \""));
    sensorAmp();
    client.print(sensor_max);
    client.print(F("\",\"amplitude\" : \""));
    client.print(amplitude_current, 1); //Only one number after the decimal point
    client.print(F("\",\"effective_value\" : \""));
    client.print(effective_value, 1);
    client.print(F("\",\"A"));
    client.print(pin);
    client.print(F("\" : \""));
    //client.print(F(" reads analog "));
    client.print(value);//Arduino Analog 값 표기
    client.print(F("\"}"));

    String key = "A";
    key += pin;
    Bridge.put(key, String(value));
  }
}


//Current Sensor 실측값
int sensorAmp() {
  sensor_max = getMaxValue();

  //the VCC on the Grove interface of the sensor is 5v
  current(sensor_max);
  //minimum_current=1/1024*5/185*1000000/1.414=18.7(mA)
  //Only for sinusoidal alternating current
  return sensor_max;
}

void current(int sensor_max) {
  amplitude_current = (float)(sensor_max - 512) / 1024 * 5 / 185 * 1000000;
  effective_value = amplitude_current / 1.414;
}

//Arduino 현재 센서값 연산.
int getMaxValue() {
  int sensorValue;
  int sensorMax = 1024; //최대 표기 허용수치
  uint32_t start_time = millis();
  while ((millis() - start_time) < 2000)
  {
    sensorValue = analogRead(CURRENT_SENSOR);
    if (sensorValue < sensorMax) {
      sensorMax = sensorValue;
    }
  }
  return sensorMax;
}
