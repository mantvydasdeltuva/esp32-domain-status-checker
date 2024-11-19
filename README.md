<div align="center">
  <img src="assets/banner-dark.png#gh-dark-mode-only" alt="Banner" style="width: 600px; height: auto;">
  <img src="assets/banner-light.png#gh-light-mode-only" alt="Banner" style="width: 600px; height: auto;">
</div>

---

### Overview

This repository implements a program that checks the availability of two-letter domains registered in Lithuania via the `www.domreg.lt` API. If a domain is found to be available, it sends an email notification using SMTP.

---

### Events in the Simulation

The simulation revolves around two types of **events**:
1. **Domain Check Event:** The system checks the availability of a two-letter domain through the API.
2. **Email Notification Event:** If an available domain is found, an email notification is sent.

---

### Event Determination Process

The program determines which event occurs next based on a fixed interval check:
  - **Domain Check:** The program checks the availability of all two-letter domains every 43 minutes. Each domain is checked every 2 seconds.
  - **Email Notification:** If an available domain is found, an email is sent to the specified recipient.

---

### Simulation Parameters

- **WiFi SSID:** The network SSID to connect the ESP32 device.
- **WiFi Password:** The password for the WiFi network.
- **Sender Email:** The email address from which notifications are sent.
- **Sender Email Password:** The password for the sender's email account.
- **Recipient Email:** The email address where notifications are sent.

```cpp
#define WIFI_SSID "your_wifi_ssid"
#define WIFI_PASSWORD "your_wifi_password"
#define AUTHOR_EMAIL "your_email@example.com"
#define AUTHOR_PASSWORD "your_email_password"
#define RECIPIENT_EMAIL "recipient_email@example.com"
```

---

### Running the Program

1. Clone the repository:
    ```bash
    git clone https://github.com/mantvydasdeltuva/esp32-domain-status-checker.git
    cd esp32-domain-status-checker
    ```
2. Open the main.ino file in the Arduino IDE.
3. Update the necessary constants in the code.
4. Upload the code to your ESP32 board.
5. The program will start checking the availability of domains and send email notifications accordingly.

---

### Dependencies

- Arduino IDE (Recommended version: 1.8.13 or later).
- ESP32 Board added to the Arduino IDE.
- Libraries:
  - WiFi
  - HTTPClient
  - ArduinoJson
  - ESP_Mail_Client

---

### License

This project is licensed under the MIT License - see the LICENSE file for details.

---

### Contributions

Contributions and suggestions are welcome. Please feel free to submit an issue or a pull request for improvements.