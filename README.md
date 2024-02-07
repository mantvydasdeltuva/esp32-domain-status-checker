![GitHub repo size](https://img.shields.io/github/repo-size/mantvydasdeltuva/esp32_domain-status-checker.svg)
![GitHub stars](https://img.shields.io/github/stars/mantvydasdeltuva/esp32_domain-status-checker.svg?style=social)
[![GitHub contributors](https://img.shields.io/github/contributors/mantvydasdeltuva/esp32_domain-status-checker.svg)](https://github.com/mantvydasdeltuva/esp32_domain-status-checker/graphs/contributors)
![GitHub license](https://img.shields.io/github/license/mantvydasdeltuva/esp32_domain-status-checker.svg)

# Domain Status Checker

🔍📧 This ESP32 program allows you to check the availability status of two-letter domains registered in Lithuania via the `www.domreg.lt` API. If a domain is found to be available, it sends an email notification using SMTP.

## Table of Contents

- [Getting Started](#🚀-getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#🛠️-usage)
- [Troubleshooting](#🚨-troubleshooting)
- [Contributing](#🤝-contributing)
- [License](#📝-license)

## 🚀 Getting Started

To get started with this project, follow these instructions:

### Prerequisites

- Arduino IDE installed on your system.
- ESP32 board added to the Arduino IDE.
- Necessary libraries installed:
  - WiFi
  - HTTPClient
  - ArduinoJson
  - ESP_Mail_Client

### Installation

1. Clone this repository to your local machine using `git clone https://github.com/mantvydasdeltuva/esp32_domain-status-checker.git`.
2. Open the `main.ino` file in the Arduino IDE.
3. Update the following constants in the code with your specific details:
   - `WIFI_SSID`: Your WiFi network SSID.
   - `WIFI_PASSWORD`: Your WiFi network password.
   - `AUTHOR_EMAIL`: Your email address from which notifications will be sent.
   - `AUTHOR_PASSWORD`: Your email password.
   - `RECIPIENT_EMAIL`: Email address where notifications will be sent.
4. Upload the code to your ESP32 board.

## 🛠️ Usage

Once the code is uploaded and running on your ESP32 board, it will continuously check the availability status of two-letter domains registered in Lithuania. If an available domain is found, it will send an email notification to the specified recipient email address.

## 🚨 Troubleshooting

- If you encounter any issues during setup or usage, please refer to the documentation of the libraries used or consult relevant forums for assistance.
- Ensure that your ESP32 board is properly connected to the internet and has access to the `www.domreg.lt` API.

## 🤝 Contributing

Contributions are welcome! Here's how you can contribute:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature/your_feature_name`).
3. Make your changes.
4. Commit your changes (`git commit -am 'Add some feature'`).
5. Push to the branch (`git push origin feature/your_feature_name`).
6. Create a new Pull Request.

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Frequently Asked Questions

### How often does the program check for domain availability?

The program checks for all possible two-symbol domain availability per 43 minutes. One single domain is checked approx. per 2 seconds.

### Can I modify the program to check domains from a different registry?

Yes, you can modify the `HTTP_HOST` constant to point to a different domain registry API. Keep in mind that you would probobly need to change the .json response handling.
