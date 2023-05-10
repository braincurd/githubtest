#include <Arduino.h>
#include <WiFi.h>
#include <ota.h>

// This string should correspond to github tag used for Releasing (via. Github Actions)
#define VERSION "0.0.2"

// Replace your_username/your_repo with your values (ex. axcap/Esp-GitHub-OTA)
// This is a link to repo where your firmware updates will be pulled from
// #define RELEASE_URL "https://api.github.com/repos/your_username/your_repo/releases/latest"

// Use this version of the URL together with init_ota(VERSION, true) under debugging
// to spare yourself from getting timeout from GitHub API
#define RELEASE_URL "https://github.com/braincurd/githubtest.git"

#define DELAY_MS 20

#define SSID "aLANdin"
#define PASSWORD "50737simplenetz"
#define HOSTNAME "ESP32 OTA"
#define LED_BUILTIN 2

void setup_wifi();
void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  setup_wifi();
  init_ota(VERSION);
}

void loop()
{
  handle_ota(RELEASE_URL);

  // Your code goes here
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(DELAY_MS);                  // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(DELAY_MS);                  // wait for a second
}

void setup_wifi(){
  Serial.println("Initialize WiFi");
  WiFi.hostname(HOSTNAME);
  WiFi.begin(SSID, PASSWORD);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}