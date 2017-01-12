/* SoftwareSerial +MQTT, send sample (esp8266)
*/
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

SoftwareSerial mySerial(4, 5); /* RX:D4, TX:D5 */
const char* ssid = "";
const char* password = "";

const char* host = "api.thingspeak.com";
String mAPI_KEY=" ";
const char* mClient_id = "cliennt-arduino-0629";
byte localserver[] = {192, 168, 10, 120 };
//const char* mqtt_server = "test.mosquitto.org";
char mTopicIn[]="item-kuc-arc-f/device-1/serial_1";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
uint32_t mTimer;
//uint32_t mTimerPost;
char msg[50];
int value = 0;
int mMaxMatrix=20;
//String mWDAT="";
String mBuff="";

String mHtypOne="01";
String mHtypScr="02";

int mSTAT=0;
//int mSTAT_1_WDAT=1;
//int mSTAT_2_Temp=2;
//int mSTAT_3_WDAT=3;
//int mSTAT_4_Hum =4;

//
void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(9600);
  mySerial.begin( 9600 );
  
  setup_wifi();
//  client.setServer(mqtt_server, 1883);
  client.setServer(localserver, 1883);
  client.setCallback(callback);
}

void setup_wifi() {
//  mSTAT=mSTAT_1_WDAT;
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  //Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  //Serial.println("IP address: ");
  //Serial.println(WiFi.localIP());
}

//
void callback(char* topic, byte* payload, unsigned int length) {
  //Serial.print("Message arrived [");
  //Serial.print(topic);
  //Serial.print("] ");
  String sTopi=String( mTopicIn );
  String sTopi_in =String( topic );
  //String sLine="";
  mBuff="";
  String sCRLF="\r\n";  
  if( sTopi.equals( sTopi_in ) ){
    //Serial.print("011");
    for (int i=0;i<length;i++) {
//      Serial.print((char)payload[i]);
      String sPay= String( (char)payload[i] );
      mBuff += sPay;
    }
   }
}

//
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect( mClient_id )) {
      Serial.println("connected");
      client.subscribe(mTopicIn);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

//
void loop() {
  //delay(100);
  //Serial.println("#Loop");
   if (!client.connected()) {
    reconnect();
  }
  client.loop();
  //mBuff
  if(millis() > mTimer ){
    mTimer = mTimer+500;
    char cD1[10+1];
    if(mBuff.length() > 0 ){
    sprintf(cD1 , "d1%08s", mBuff.c_str() );
    mySerial.print( cD1 );
    mBuff="";
Serial.print("cD1=");
Serial.println(cD1  );       
    }
  }
  
}






