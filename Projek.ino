#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <HTTPClient.h>

// ================================
//        KONFIG TELEGRAM
// ================================
String botToken = "8246350136:AAGFOIwz7yjegv980iABeJSZ5wXfJ0dN3Zw";
String chatID   = "6235226366";

// ================================
//        KONFIG LCD
// ================================
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ================================
//        PIN DEFINITIONS
// ================================
#define TRIG 5
#define ECHO 18

#define BTN_ARRIVE 33
#define BTN_GO     32

#define LED_PIN    26
#define BUZZER_PIN 25

// ================================
//        VARIABEL LOGIKA
// ================================
bool modeArrive = false;
bool modeGo     = false;

bool itemPresent  = false;
int thresholdDist = 15; 

// ================================
//        WIFI CONFIG
// ================================
const char* ssid     = "iPhone";
const char* password = "nabilganteng";

// ================================
//        FUNGSI AMBIL JARAK
// ================================
long getDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH);
  long distance = duration * 0.034 / 2; 
  return distance;
}

// ================================
//       FUNGSI TELEGRAM
// ================================
void sendTelegram(String text) {
  if (WiFi.status() != WL_CONNECTED) return;

  String url = "https://api.telegram.org/bot" + botToken +
               "/sendMessage?chat_id=" + chatID +
               "&text=" + text;

  url.replace(" ", "%20");

  HTTPClient http;
  http.begin(url);
  http.GET();
  http.end();
}

// ================================
//         ALARM
// ================================
void alarmShortContinuous() {
  digitalWrite(BUZZER_PIN, HIGH);
  digitalWrite(LED_PIN, HIGH);
  delay(200);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
  delay(200);
}

void alarmLong() {
  for (int i=0; i<5; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
    delay(300);
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
    delay(150);
  }
}

void buzz() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(150);
  digitalWrite(BUZZER_PIN, LOW);
}

// ================================
//           SETUP 
// ================================
void setup() {
  Serial.begin(115200);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Smart Desk Init");

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(BTN_ARRIVE, INPUT_PULLUP);
  pinMode(BTN_GO, INPUT_PULLUP);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  WiFi.begin(ssid, password);
  lcd.setCursor(0,1);
  lcd.print("WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  lcd.clear();
  lcd.print("Ready");
  delay(800);
  lcd.clear();
}

// ================================
//            LOOP
// ================================
void loop() {

  long jarakLive = getDistance();

  // ============================
  //     TOMBOL ARRIVE
  // ============================
  if (digitalRead(BTN_ARRIVE) == LOW) {
    modeArrive = true;
    modeGo = false;
    itemPresent = false;
    buzz();

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("ARRIVE mode");
    delay(400);
  }

  // ============================
  //     TOMBOL GO
  // ============================
  if (digitalRead(BTN_GO) == LOW) {
    modeGo = true;
    modeArrive = false;
    buzz();

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("GO mode");
    delay(400);
  }

  // ============================
  //       MODE ARRIVE
  // ============================
  if (modeArrive) {

    lcd.setCursor(0,0);
    lcd.print("ARRIVE mode    ");

    long jarakNow = getDistance();
    bool itemNow = (jarakNow < thresholdDist);

    if (!itemNow) {

      delay(3000);

      long jarakConfirm = getDistance();
      bool itemConfirm = (jarakConfirm < thresholdDist);

      if (!itemConfirm) {
        lcd.setCursor(0,1);
        lcd.print("Barang: TIDAK   ");
        alarmShortContinuous();

        sendTelegram("⚠ Barang belum ditaruh di meja!");
      }
      else {
        lcd.setCursor(0,1);
        lcd.print("Barang: ADA     ");
        digitalWrite(LED_PIN, HIGH);
        itemPresent = true;
      }
    }
    else {
      lcd.setCursor(0,1);
      lcd.print("Barang: ADA     ");
      digitalWrite(LED_PIN, HIGH);
      itemPresent = true;
    }

    delay(100);
  }

  // ============================
  //       MODE GO
  // ============================
  if (modeGo) {

    long jarakNow = getDistance();
    bool itemNow = (jarakNow < thresholdDist);

    lcd.setCursor(0,0);
    lcd.print("GO mode        ");

    if (itemPresent && !itemNow) {
      lcd.setCursor(0,1);
      lcd.print("Barang: Aman    ");
      sendTelegram("🟩 Barang sudah kamu bawa.");
      digitalWrite(LED_PIN, LOW);
    }
    else if (itemPresent && itemNow) {
      lcd.setCursor(0,1);
      lcd.print("Tertinggal!     ");
      sendTelegram("🚨 WARNING! Barang masih tertinggal!");
      alarmLong();
    }
    else {
      lcd.setCursor(0,1);
      lcd.print("Tidak ada item  ");
      sendTelegram("ℹ Tidak ada barang tercatat saat ARRIVE.");
    }

    modeGo = false;
    delay(300);
  }
}