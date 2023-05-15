//#define Ethernet

#include <Arduino.h>
#ifdef Ethernet
#include <ETH.h>
#else
#include <WiFi.h>
#endif

#include <ota.h>

// This string should correspond to github tag used for Releasing (via. Github Actions)
#define VERSION "0.1.0"

// Use this version of the URL together with init_ota(VERSION, true) under debugging
// to spare yourself from getting timeout from GitHub API
#define RELEASE_URL "https://api.github.com/repos/braincurd/githubtest/releases/latest"

#define DELAY_MS 5000
#define LED 2

#ifdef Ethernet
////////////////////////////////////DEFINE ETHERNET//////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define ETH_ADDR 0
#define ETH_POWER_PIN 12
#define ETH_MDC_PIN 23
#define ETH_MDIO_PIN 18
#define ETH_TYPE ETH_PHY_LAN8720
#define ETH_CLK_MODE ETH_CLOCK_GPIO17_OUT

WiFiUDP udp;                      // Create UDP object
unsigned int localUdpPort = 9005; // local port
IPAddress local_ip(192, 168, 188, 245);
IPAddress gateway(192, 168, 188, 1);
IPAddress subnet(255, 255, 255, 0);

char udpBuffer[256];        // Buffer to store received UDP message
bool newUdpMessage = false; // Flag to indicate whether a new UDP message has been received

// Define the remote IP address and port as variables
IPAddress remote_ip(192, 168, 188, 95);
uint16_t remote_port = 12345;

#else
#define SSID "aLANdin"
#define PASSWORD "50737simplenetz"
#define HOSTNAME "ESP32 OTA"

void setup_wifi();
#endif



#ifdef Ethernet
void setup_ethernet()
{
  // Initialize the Ethernet and UDP connections
  ETH.begin(ETH_ADDR, ETH_POWER_PIN, ETH_MDC_PIN, ETH_MDIO_PIN, ETH_TYPE, ETH_CLK_MODE);
  ETH.config(local_ip, gateway, subnet);
  udp.begin(localUdpPort);
  Serial.println("Ethernet connected");
  Serial.print("IP address: ");
  Serial.println(ETH.localIP());
}
#else

void setup_wifi()
{
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
#endif
void setup()
{
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
#ifdef Ethernet
setup_ethernet();
#else
  setup_wifi();
#endif
  init_ota(VERSION);
  delay(1000);
}

void loop()
{
  handle_ota(RELEASE_URL);

  // Your code goes here
  digitalWrite(LED, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(DELAY_MS);         // wait for a second
  digitalWrite(LED, LOW);  // turn the LED off by making the voltage LOW
  delay(DELAY_MS);
  Serial.println(VERSION); // wait for a second
}
