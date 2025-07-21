#include <Adafruit_Fingerprint.h>
#include <Wire.h>
#include <RTClib.h>

// Initialize devices
SoftwareSerial mySerial(2, 3); // RX, TX
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
RTC_DS3231 rtc;

void setup() {
  Serial.begin(9600);
  mySerial.begin(57600);

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (!finger.begin()) {
    Serial.println("Fingerprint sensor not detected");
    while (1);
  }

  finger.getTemplateCount();
  Serial.print("Sensor contains ");
  Serial.print(finger.templateCount);
  Serial.println(" templates");
}

void loop() {
  getFingerprintID();
  delay(1000);
}

int getFingerprintID() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK) return -1;

  DateTime now = rtc.now();

  Serial.print("ATTEND:");
  Serial.print(finger.fingerID);
  Serial.print(",");
  Serial.print(now.hour());
  Serial.print(":");
  Serial.print(now.minute());
  Serial.print(":");
  Serial.print(now.second());
  Serial.print(",");
  Serial.print(now.day());
  Serial.print("/");
  Serial.print(now.month());
  Serial.print("/");
  Serial.println(now.year());

  return finger.fingerID;
}
