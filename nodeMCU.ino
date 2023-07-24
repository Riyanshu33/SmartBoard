#include <ESP8266WiFi.h>
#define relay1Pin D5
#define relay2Pin D6
#define relay3Pin D7
#define relay4Pin D8

WiFiClient client;
WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  WiFi.disconnect(true);
  delay(100);

  WiFi.begin("riyanshu", "1234");

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    delay(1000);
  }

  Serial.println();
  Serial.println("NodeMCU is connected");
  Serial.println(WiFi.localIP());

  server.begin();
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  pinMode(relay3Pin, OUTPUT);
  pinMode(relay4Pin, OUTPUT);
  digitalWrite(relay1Pin,HIGH);
  digitalWrite(relay2Pin,HIGH);
  digitalWrite(relay3Pin,HIGH);
  digitalWrite(relay4Pin,HIGH);
}

void loop() {
  client = server.available();

  if (client) {
    String request = client.readStringUntil('\n');
    Serial.println(request);
    request.trim();

    if (request == "GET /relay1on HTTP/1.1") {
      digitalWrite(relay1Pin, LOW);
    }
    if (request == "GET /relay1off HTTP/1.1") {
      digitalWrite(relay1Pin, HIGH);
    }
    if (request == "GET /relay2on HTTP/1.1") {
      digitalWrite(relay2Pin, LOW);
    }
    if (request == "GET /relay2off HTTP/1.1") {
      digitalWrite(relay2Pin, HIGH);
    }
    if (request == "GET /relay3on HTTP/1.1") {
      digitalWrite(relay3Pin, LOW);
    }
    if (request == "GET /relay3off HTTP/1.1") {
      digitalWrite(relay3Pin, HIGH);
    }
    if (request == "GET /relay4on HTTP/1.1") {
      digitalWrite(relay4Pin, HIGH);
    }
    if (request == "GET /relay4off HTTP/1.1") {
      digitalWrite(relay4Pin, LOW);
    }
  }

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("  <title>Relay Control</title>");
  client.println("  <style>");
  client.println("    body {");
  client.println("      display: flex;");
  client.println("      flex-direction: column;");
  client.println("      align-items: center;");
  client.println("      justify-content: center;");
  client.println("      height: 100vh;");
  client.println("      margin: 0;");
  client.println("    }");
  client.println("    h1 {");
  client.println("      text-align: center;");
  client.println("      font-size: 32px;");
  client.println("    }");
  client.println("    .slider-container {");
  client.println("      display: grid;");
  client.println("      grid-template-columns: repeat(2, 1fr);");
  client.println("      grid-gap: 20px;");
  client.println("    }");
  client.println("    .switch {");
  client.println("      position: relative;");
  client.println("      display: inline-block;");
  client.println("      width: 80px;");
  client.println("      height: 48px;");
  client.println("    }");
  client.println("    .switch input {");
  client.println("      opacity: 0;");
  client.println("      width: 0;");
  client.println("      height: 0;");
  client.println("    }");
  client.println("    .slider {");
  client.println("      position: absolute;");
  client.println("      cursor: pointer;");
  client.println("      top: 0;");
  client.println("      right: 0;");
  client.println("      bottom: 0;");
  client.println("      left: 0;");
  client.println("      background-color: red;");
  client.println("      transition: .4s;");
  client.println("    }");
  client.println("    .slider:before {");
  client.println("      position: absolute;");
  client.println("      content: '';");
  client.println("      height: 38px;");
  client.println("      width: 38px;");
  client.println("      left: 5px;");
  client.println("      bottom: 5px;");
  client.println("      background-color: white;");
  client.println("      transition: .4s;");
  client.println("      border-radius: 50%;");
  client.println("    }");
  client.println("    input:checked + .slider {");
  client.println("      background-color: green;");
  client.println("    }");
  client.println("    input:focus + .slider {");
  client.println("      box-shadow: 0 0 1px #2196F3;");
  client.println("    }");
  client.println("    input:checked + .slider:before {");
  client.println("      transform: translateX(32px);");
  client.println("    }");
  client.println("    .slider.round {");
  client.println("      border-radius: 48px;");
  client.println("    }");
  client.println("    .slider.round:before {");
  client.println("      border-radius: 50%;");
  client.println("    }");
  client.println("    @media screen and (max-width: 768px) {");
  client.println("      .slider-container {");
  client.println("        grid-template-columns: 1fr;");
  client.println("      }");
  client.println("    }");
  client.println("  </style>");
  client.println("</head>");
  client.println("<body>");
  client.println("  <h1>Relay Control</h1>");
  client.println("  <div class='slider-container'>");
  client.println("    <div>");
  client.println("      <h3>Relay 1</h3>");
  client.println("      <label class='switch'>");
  client.println("        <input type='checkbox' onchange='toggleRelay(1)' id='relay1'>");
  client.println("        <span class='slider round'></span>");
  client.println("      </label>");
  client.println("    </div>");
  client.println("    <div>");
  client.println("      <h3>Relay 2</h3>");
  client.println("      <label class='switch'>");
  client.println("        <input type='checkbox' onchange='toggleRelay(2)' id='relay2'>");
  client.println("        <span class='slider round'></span>");
  client.println("      </label>");
  client.println("    </div>");
  client.println("    <div>");
  client.println("      <h3>Relay 3</h3>");
  client.println("      <label class='switch'>");
  client.println("        <input type='checkbox' onchange='toggleRelay(3)' id='relay3'>");
  client.println("        <span class='slider round'></span>");
  client.println("      </label>");
  client.println("    </div>");
  client.println("    <div>");
  client.println("      <h3>Relay 4</h3>");
  client.println("      <label class='switch'>");
  client.println("        <input type='checkbox' onchange='toggleRelay(4)' id='relay4'>");
  client.println("        <span class='slider round'></span>");
  client.println("      </label>");
  client.println("    </div>");
  client.println("  </div>");
  client.println("  <script>");
  client.println("    function toggleRelay(relayNum) {");
  client.println("      var xhttp = new XMLHttpRequest();");
  client.println("      var checkbox = document.getElementById('relay' + relayNum);");
  client.println("      if (checkbox.checked) {");
  client.println("        xhttp.open('GET', '/relay' + relayNum + 'on', true);");
  client.println("      } else {");
  client.println("        xhttp.open('GET', '/relay' + relayNum + 'off', true);");
  client.println("      }");
  client.println("      xhttp.send();");
  client.println("    }");
  client.println("  </script>");
  client.println("</body>");
  client.println("</html>");
}
