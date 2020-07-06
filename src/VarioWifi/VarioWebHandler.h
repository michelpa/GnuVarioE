/* VarioWebHandler
 *
 * Copyright 2020 Pascal MICHEL
 * 
 * This file is part of GNUVario.
 *
 * GNUVario is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GNUVario is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef VARIO_WEBHANDLER_H
#define VARIO_WEBHANDLER_H

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "FS.h"
#include "SD.h"
#include <VarioIgcParser.h>
#include <VarioSqlFlight.h>

class VarioWebHandler
{
public:
    // Récupération de la liste des fichiers du répertoire vols au format json
    AsyncResponseStream *handleListFlights(AsyncWebServerRequest *request);

    //récupération de la liste du contenu de la carte SD
    AsyncResponseStream *handlePrintDirectory(AsyncWebServerRequest *request);

    // Récupération du contenu du fichier parameters.jso
    AsyncWebServerResponse *handleParams(AsyncWebServerRequest *request);

    //telechargement d'un fichier dont le nom complet avec chemin se trouve en param
    AsyncWebServerResponse *handleFileDownload(AsyncWebServerRequest *request);

    //suppression d'un fichier dont le nom complet avec chemin se trouve en param
    AsyncWebServerResponse *handleFileDelete(AsyncWebServerRequest *request);

    // sauvegarde des parametres
    static void handleSaveParams(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);

    // mise à jour OTA
    static void handleOtaUpdate(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final);

    // upload d'un fichier, le chemin de destination se trouve dans le nom du fichier posté
    static void handleFileUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final);

    //creation d'un fichier ou d'un repertoire
    static void handleFileCreate(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);

    //récupération du contenu du fichier wifi
    AsyncWebServerResponse *handleWifi(AsyncWebServerRequest *request);

    // sauvegarde des parametres
    static void handleSaveWifi(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);

    //récupération du contenu du fichier preference
    AsyncWebServerResponse *handleWebConfig(AsyncWebServerRequest *request);

    // sauvegarde du contenu du fichier preference
    static void handleSaveWebConfig(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);

    // parsage d'un fichier IGC
    AsyncWebServerResponse *handleParseIgc(AsyncWebServerRequest *request);

private:
    String getFileSizeStringFromBytes(int bytes);
    void printDirectoryRecurse(AsyncResponseStream *response, String path, boolean isRecursive);
    void deleteRecursive(String path);
    static void backupFile(String pathOrig, String pathBack);
};

#endif //VARIO_WEBHANDLER_H