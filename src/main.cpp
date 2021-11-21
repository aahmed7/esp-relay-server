#include <api.h>
#include <wifi_init.h>

void setup() {
    Serial.begin(115200);

    setup_wifi();
    loadServerRoutes();
}

void loop() { delay(5); }
