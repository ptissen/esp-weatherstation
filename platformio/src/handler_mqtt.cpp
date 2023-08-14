/*
 *   This file belongs to the Project ESP-WeatherStation
 *   Copyright (c) 2023 Peter Tißen, Stephan Brüning
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.

 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "handler_mqtt.h"

#include "config/config.h"
#include "config/secrets.h"
#include "logging.h"

MQTTHandler::MQTTHandler(Client& client) : PubSubClient(client)
{
}

void MQTTHandler::setup()
{
    logI.println("\n------------ MQTTHandler ------------");
    setServer(MQTT_BROKER, MQTT_PORT);
    setCallback(callback);

    String client_id = MQTT_CLIENT_ID;
    client_id += String(WiFi.macAddress());
    logD.printf("The client %s connects to the MQTT broker\n", client_id.c_str());
    logD.print("  Connect to broker  ");

    for (int i = 0; i < MQTT_MAX_TRY; i++) {
        logD.print(".");
        connect(client_id.c_str(), MQTT_USERNAME, MQTT_PASSWORD);
        if (connected()) {
            logD.println(" sucess");
            break;
        }
        delay(1000);
    }

    if(!connected()){
        logW.print("failed with state ");
        logW.println(state());
    }
}

void MQTTHandler::callback(char *topic, uint8_t *payload, unsigned int length) {
    logI.println("\n------------ MQTT Callback ------------");
    logI.print("Message arrived in topic: ");
    logI.println(topic);
    logI.print("Message:");
    for (int i = 0; i < length; i++) {
        logI.print((char) payload[i]);
    }
    logI.println();
}