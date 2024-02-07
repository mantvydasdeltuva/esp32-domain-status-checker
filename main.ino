#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP_Mail_Client.h>

// Define WiFi and SMTP credentials
#define WIFI_SSID "YOUR_WIFI_SSID"                    // Change!
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"            // Change!
#define SMTP_HOST "smtp.gmail.com"                    // Depends on provider
#define SMTP_PORT 465                                 // Depends on provider
#define AUTHOR_EMAIL "ESP_EMAIL@PROVIDER.com"         // Change!
#define AUTHOR_PASSWORD "ESP_PASSWORD"                // Change!
#define RECIPIENT_EMAIL "YOUR_EMAIL@PROVIDER.com"     // Change!

// Declare constant and variables for generating domains
const char characters[37] = "abcdefghijklmnopqrstuvwxyz0123456789";
int current_index[2] = {0, 0};
bool RETRY = false;

// Declare global used domain path
const char* HTTP_HOST = "https://www.domreg.lt/api/whois/status/";
String HTTP_DOMAIN;
const char* HTTP_END = ".lt";

// Declare HTTPClient object
HTTPClient http;

// Declare variables for decoding JSON response
StaticJsonDocument<200> doc;

// Declare Session_Config and SMTP_Message objects
Session_Config config;
SMTP_Message message;

// Function prototypes
void generateTwoLetterDomain();
void sendEmail();

void setup() {
  Serial.begin(9600); 

  // Connect to WiFi
  Serial.println("Connecting");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println("Connected to WiFi network");

  // Configure SMTP server and message
  config.server.host_name = SMTP_HOST;
  config.server.port = SMTP_PORT;
  config.login.email = AUTHOR_EMAIL;
  config.login.password = AUTHOR_PASSWORD;
  config.login.user_domain = "";

  message.sender.name = F("ESP");
  message.sender.email = AUTHOR_EMAIL;
  message.subject = F("ESP Found Domain");
  message.addRecipient(F("Mantvydas"), RECIPIENT_EMAIL);
  message.text.charSet = "us-ascii";
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
  message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_low;
  message.response.notify = esp_mail_smtp_notify_success | esp_mail_smtp_notify_failure | esp_mail_smtp_notify_delay;
}

void loop() {
  // Generate domain to check
  if (!RETRY)
    generateTwoLetterDomain();
  else
    RETRY = false;

  // Delay for to frequent requests
  delay(1000);

  // Perform HTTP GET request to check domain status
  http.begin(HTTP_HOST + HTTP_DOMAIN + HTTP_END);
  int httpCode = http.GET();

  // Check for errors in HTTP request
  if(httpCode > 0) {
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();

      // Deserialize JSON response
      DeserializationError error = deserializeJson(doc, payload);
      if (!error) {
        const char* domainStatus = doc["domainstatus"];

        // Handle different domain statuses
        if (strcmp(domainStatus, "available") == 0) {
          Serial.printf("%s is available\n", HTTP_DOMAIN);
          sendEmail();
        } else if (strcmp(domainStatus, "registered") == 0) {
          Serial.printf("%s is registered\n", HTTP_DOMAIN);
        } else if (strcmp(domainStatus, "restrictedDisposal") == 0) {
          Serial.printf("%s is restrictedDisposal\n", HTTP_DOMAIN);
        } else if (strcmp(domainStatus, "pendingDelete") == 0) {
          Serial.printf("%s is pendingDelete\n", HTTP_DOMAIN);
        } else {
          Serial.printf("%s is unknown\n", HTTP_DOMAIN);
        }
      }
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    if (strcmp(http.errorToString(httpCode).c_str(), "send header failed") == 0)
      RETRY = true;
  }
  http.end();

  // Delay for to frequent requests
  delay(1000);
}

// Function to generate two-letter domain
void generateTwoLetterDomain() {
  HTTP_DOMAIN = characters[current_index[0]];
  HTTP_DOMAIN += characters[current_index[1]++];

  // Increment indices for next domain generation
  if (current_index[1] == 36) {
    current_index[0]++;
    current_index[1] = 0;
  }

  if (current_index[0] == 36) {
    current_index[0] = 0;
    current_index[1] = 0;
  }
}

// Function to send email
void sendEmail() {
    // Initiating SMTP session
    SMTPSession smtp;
    smtp.debug(0);

    if (!smtp.connect(&config)){
      ESP_MAIL_PRINTF("Connection error, Status Code: %d, Error Code: %d, Reason: %s", smtp.statusCode(), smtp.errorCode(), smtp.errorReason().c_str());
      return;
    }

    if (!smtp.isLoggedIn()){
      Serial.println("\nNot yet logged in.");
    }
    else{
      if (smtp.isAuthenticated())
        Serial.println("\nSuccessfully logged in.");
      else
        Serial.println("\nConnected with no Auth.");
    }
    
    // Message in the email
    String textMsg = "Domain (" + HTTP_DOMAIN + HTTP_END + ") is available";
    message.text.content = textMsg.c_str();

    // Sending email and closing SMTP session
    if (!MailClient.sendMail(&smtp, &message))
      ESP_MAIL_PRINTF("Error, Status Code: %d, Error Code: %d, Reason: %s", smtp.statusCode(), smtp.errorCode(), smtp.errorReason().c_str());
    
    smtp.sendingResult.clear();
}
