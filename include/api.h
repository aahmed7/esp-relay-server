#ifndef _API_H
#define _API_H

#if defined(ESP8266)
#include <ESPAsyncTCP.h>
#endif
#include <Arduino.h>
#include <ArduinoJson.h>
#include <AsyncJson.h>
#include <ESPAsyncWebServer.h>

void loadServerRoutes();

#endif