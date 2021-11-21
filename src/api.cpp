#include <api.h>

// Relay variables.
#define RELAY_PIN 0
bool relay_state = false;

// Endpoints.
#define ENDPOINT "/bulb"

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

AsyncCallbackJsonWebHandler *setRelayState = new AsyncCallbackJsonWebHandler(
    ENDPOINT, [](AsyncWebServerRequest *request, JsonVariant &json) {
        // Get the request body.
        JsonObject doc = json.as<JsonObject>();

        // Debug printing.
        Serial.print("POST Received. request body: ");
        serializeJson(doc, Serial);
        Serial.println();

        // Set relay state as per request body.
        relay_state = doc["bulb"];

        // Debug printing.
        Serial.print("Setting relay to: ");
        Serial.println(relay_state);

        if (relay_state) {
            digitalWrite(RELAY_PIN, LOW);

        } else {
            digitalWrite(RELAY_PIN, HIGH);
        }

        char message[50];
        doc["bulb"] = relay_state;
        serializeJson(doc, message);
        request->send_P(200, "application/json", message);
    });

void getRelayState(AsyncWebServerRequest *request) {
    // Debug printing.
    Serial.print("GET Received. relay at: ");
    Serial.println(relay_state);

    DynamicJsonDocument doc(128);
    char                message[50];

    // Return the relay state.
    doc["bulb"] = relay_state;
    serializeJson(doc, message);
    request->send_P(200, "application/json", message);
}

void loadServerRoutes() {
    // Set the GPIO
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW);

    // Start the server
    server.begin();
    Serial.println("Server started");
    server.addHandler(setRelayState);
    server.on(ENDPOINT, HTTP_GET, getRelayState);
    server.onNotFound(notFound);
}
