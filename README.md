# ESP relay server

Controls a single array using esp-01.

## GPIO

Relay is to be connected to GPIO. Defined by `RELAY_PIN` inside `src/api.cpp`

## Endpoints

### GET

Get the bulb state from the `"/bulb"` endpoint

```bash
 curl http://192.168.2.111/bulb
```

### POST

Post a json object of the form `{"bulb":<bool>}` to the `"/bulb"` endpoint, where `<bool>` is a boolean indicating the desired state of the relay.

e.g.

```bash
 curl -X POST -H "Content-Type: application/json"  -d '{"bulb":true}' http://192.168.2.111/bulb
```
