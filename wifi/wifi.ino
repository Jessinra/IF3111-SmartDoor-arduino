
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Ra wifi";
const char* password = "dragonra";

//const char* ssid = "Funworld";
//const char* password = "20192019";
 
/* main link */
const char* doorUrl = "http://us-central1-if3111-smartdoor.cloudfunctions.net/arduinoHandler";
const char* historyLoggerUrl = "http://us-central1-if3111-smartdoor.cloudfunctions.net/newHistoryLogger";
const char* changeDoorStateUrl = "http://us-central1-if3111-smartdoor.cloudfunctions.net/newDashboardHandler";
const char* notificationUrl = "http://us-central1-if3111-smartdoor.cloudfunctions.net/newPushNotification";

/* backup link */
const char* backupLoggerLockUrl = "http://us-central1-if3111-smartdoor.cloudfunctions.net/arduinoHistoryLogLock";
const char* backupLoggerUnlockUrl = "http://us-central1-if3111-smartdoor.cloudfunctions.net/arduinoHistoryLogUnlock";
const char* backupLockUrl = "http://us-central1-if3111-smartdoor.cloudfunctions.net/arduinoLock";
const char* backupUnlockUrl = "http://us-central1-if3111-smartdoor.cloudfunctions.net/arduinoUnlock";

String action;
bool actionReady = false;

String sendGET(String url) {
  HTTPClient http;
  String payload;

  http.begin(url);
  int httpCode = http.GET();

  if (httpCode > 0) {
    payload = http.getString();
  }

  // Terminate process
  http.end();
  return payload;
}

void fetchDoorState() {
  String payload = sendGET(doorUrl);
  Serial.println(payload);
//  if(payload == "unlock"){
//    Serial.println("U");
//  }
//  else if (payload == "lock"){
//    Serial.println("L");
//  }
//  else{
//    Serial.println("?");
//  }
}

void sendPushNotification(){
  sendGET(notificationUrl);
}

void backupLock() {
  sendGET(backupLockUrl);
  sendGET(backupLoggerLockUrl);
}

void backupUnlock() {
  sendGET(backupUnlockUrl);
  sendGET(backupLoggerUnlockUrl);
}

void changeLockState(String lockState) {

  HTTPClient http;    //Declare object of class HTTPClient
  HTTPClient http2;

  http.begin(historyLoggerUrl);      //Specify request destination
  http.addHeader("User-Agent", "Mozilla/5.0");
  http.addHeader("Content-Type", "application/json");

  http2.begin(changeDoorStateUrl);
  http2.addHeader("User-Agent", "Mozilla/5.0");
  http2.addHeader("Content-Type", "application/json");

  String payload = "{"
                   "\"secretCode\":\"seara\","
                   "\"userToken\":\"1234512345\","
                   "\"buildingId\":\"1\","
                   "\"buildingLockState\":\""
                   + lockState +
                   "\"}";

  int httpCode = http.POST(payload);
  int httpCode2 = http2.POST(payload);

  http.end();  //Close connection
  http2.end();  //Close connection

  // Run backup code
  if (httpCode != 200 || httpCode2 != 200){
    if (lockState == "locked"){
      backupLock();
    }
    else if (lockState == "unlocked"){
      backupUnlock();
    }
  }
}

void setup () {

  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("\nConnecting..");
  }
  Serial.println("Connected");
}

void loop() {

  //Check WiFi connection status 
  if (WiFi.status() == WL_CONNECTED) {

    while (Serial.available()) {
      char c = Serial.read();
      
      if (c == '\n') {
        actionReady = true;
      } else {
        action += c;
      }
    }

    if (!actionReady) {
      delay(2000);
      return;
    }
    
    Serial.println(action);
    
    if (action.equals("GET\n") || action.equals("GET\0") || action.equals("GET\r") || action.equals("GET")) {
      fetchDoorState();
    }
    if (action.equals("LOCK\n") || action.equals("LOCK\0") || action.equals("LOCK\r") || action.equals("LOCK")) {
      changeLockState("locked");
    }
    if (action.equals("UNLOCK\n") || action.equals("UNLOCK\0") || action.equals("UNLOCK\r") || action.equals("UNLOCK")) {
      changeLockState("unlocked");
    }
    if(action.equals("NOTIFY\n") || action.equals("NOTIFY\0") || action.equals("NOTIFY\r") || action.equals("NOTIFY")){
      sendPushNotification();
    }
  }

  if (actionReady) {
    action = "";
  }

  actionReady = false;
  delay(3000);
}
