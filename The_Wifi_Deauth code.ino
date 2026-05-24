#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Wi-Fi Access Point credentials
const char* apSSID = "Cypherr";
const char* apPassword = "zed01";

ESP8266WebServer server(80);

// Store last received data here
String lastReceivedData = "";

// HTML page with deauth button and data submission form
String htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>ESP8266 Deauth Simulator</title>
  <style>
    body { background-color: #111; color: #0f0; font-family: monospace; text-align: center; padding-top: 50px; }
    button, input[type="submit"] { background-color: #0f0; color: #111; padding: 12px 24px; font-size: 18px; border: none; cursor: pointer; margin-top: 10px; }
    input[type="text"] { font-size: 18px; padding: 6px; width: 300px; }
    #status { margin-top: 20px; font-size: 20px; }
  </style>
</head>
<body>
  <h1>🚨 Deauth Attack Simulator</h1>

  <button onclick="startDeauth()">Start Deauth Simulation</button>
  <div id="status"></div>

  <h2>Send Data to ESP8266</h2>
  <form action="/submit" method="POST">
    <input name="userdata" type="text" placeholder="Enter data here" required />
    <input type="submit" value="Send Data" />
  </form>

  <script>
    function startDeauth() {
      fetch("/start").then(response => response.text()).then(data => {
        document.getElementById("status").innerText = data;
      });
    }
  </script>
</body>
</html>
)rawliteral";

// Serve the main HTML page
void handleRoot() {
  server.send(200, "text/html", htmlPage);
}

// Handle the deauth button click (fake simulation)
void handleStart() {
  Serial.println("Deauth Simulation Triggered from Web!");
  server.send(200, "text/plain", "✅ Deauth simulation started (fake)");
}

// Handle form submission and receive data
void handleSubmit() {
  if (server.hasArg("userdata")) {
    lastReceivedData = server.arg("userdata");
    Serial.println("Received data: " + lastReceivedData);
    server.send(200, "text/html", "<h2>Data received:</h2><p>" + lastReceivedData + "</p><a href='/'>Go back</a>");
  } else {
    server.send(400, "text/plain", "Bad Request: No userdata");
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(apSSID, apPassword);

  Serial.println("ESP8266 is now an Access Point!");
  Serial.print("SSID: "); Serial.println(apSSID);
  Serial.print("IP address: "); Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/start", handleStart);
  server.on("/submit", HTTP_POST, handleSubmit);

  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
}
