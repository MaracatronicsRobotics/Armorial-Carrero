/***
 * Maracatronics Robotics
 * Federal University of Pernambuco (UFPE) at Recife
 * http://www.maracatronics.com/
 *
 * This file is part of Armorial project.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ***/

#include <QApplication>
#include <iostream>

#include <entity/armorialvisionclient/armorialvisionclient.h>
#include <entity/armorialvisionupdater/armorialvisionupdater.h>

#include <QApplication>
#include <iostream>

#include <utils/fieldareas.h>
#include <utils/fieldtypes.h>

#include "exithandler.h"

#include "samico.h"

#define debug false

Samico *samico;

void samico_drawThread(){
    samico->drawWindow();
}

void printUsage() {
    std::cout << ">> Usage: ./vision [port] [field-type] [field-limit] [debug-detection] [debug-geometry]" << std::endl;
    std::cout << ">>> address: the address that the application will listen to. (default is 224.5.23.2)" << std::endl;
    std::cout << ">>> port: the port that the application will listen to. (default is 10002)" << std::endl;
    std::cout << ">>> field-type: competition field size, 'vision', 'ssl2015', 'ssl2012' or 'vss'. (default is 'vision')" << std::endl;
    std::cout << ">>> field-limit: limit vision to field area, 'q1', 'q2', 'q3', 'q4', 'top', 'bottom', 'right', 'left' or 'all'. (default is 'all')" << std::endl;
    std::cout << ">>> debug-detection: enable debug detection, 0 or 1. (default is 0)" << std::endl;
    std::cout << ">>> debug-geometry: enable debug geometry, 0 or 1. (default is 0)" << std::endl;
}
int main(int argc, char** argv) {

// Run Samico
    if(debug){
        samico = new Samico();
        samico->getWindow()->setActive(false); // deactivating samico in main thread
        thread first (samico_drawThread);
        first.detach();
    }

    QApplication app(argc, argv);
    string visionSystemAddress = "224.5.23.2";
    int visionSystemPort = 10002;
    FieldTypes::FieldType fieldType = FieldTypes::VISION;
    FieldAreas::FieldArea fieldLimit = FieldAreas::ALL;
    bool debugDetection = false;
    bool debugGeometry = false;
    /*******************************************/
    /*********** EXIT HANDLER (CTRL+C) *********/
    /*******************************************/
    ExitHandler::setApplication(&app);
    ExitHandler::setup();
    /*******************************************/
    /************ ARGUMENT CHECK ***************/
    /*******************************************/
    if(argc>=2) {
        // Help
        if((strcmp(argv[1], "help") == 0) ||
           (strcmp(argv[1], "-help") == 0) ||
           (strcmp(argv[1], "--help") == 0) ||
           (strcmp(argv[1], "-h") == 0)) {
            printUsage();
            return EXIT_SUCCESS;
        }
        bool isNumber=false;
        QString param;
        // Address
        if(argc >= 2) {
            param = argv[1];
            string address = param.toStdString();
            visionSystemAddress = address;
        }
        // Port
        if(argc >= 3) {
            param = argv[2];
            int port = param.toInt(&isNumber);
            if(!isNumber) {
                std::cout << ">> ArmorialVision: [ERROR] Invalid arguments." << std::endl;
                return EXIT_FAILURE;
            }
            if(port < 1 || port > 65535) {
                std::cout << ">> ArmorialVision: [ERROR] Invalid port." << std::endl;
                return EXIT_FAILURE;
            }
            visionSystemPort = port;
        }
        // Field type (graphicalClient)
        if(argc >= 4) {
            param = argv[3];
            param = param.toLower();
            if(param=="vision")
                fieldType = FieldTypes::VISION;
            else if(param=="ssl2012")
                fieldType = FieldTypes::SSL2012;
            else if(param=="ssl2015")
                fieldType = FieldTypes::SSL2015;
            else if(param == "vss")
                fieldType = FieldTypes::VSS2008;
            else {
                std::cout << ">> ArmorialVision: [ERROR] Invalid field type argument." << std::endl;
                return EXIT_FAILURE;
            }
        }
        // Field limit for vision
        if(argc >= 5) {
            param = argv[4];
            param = param.toLower();
            if(param=="all")
                fieldLimit = FieldAreas::ALL;
            else if(param == "top")
                fieldLimit = FieldAreas::TOP;
            else if(param == "bottom")
                fieldLimit = FieldAreas::BOTTOM;
            else if(param == "q1")
                fieldLimit = FieldAreas::Q1;
            else if(param == "q2")
                fieldLimit = FieldAreas::Q2;
            else if(param == "q3")
                fieldLimit = FieldAreas::Q3;
            else if(param == "q4")
                fieldLimit = FieldAreas::Q4;
            else if(param=="right")
                fieldLimit = FieldAreas::RIGHT;
            else if(param == "left")
                fieldLimit = FieldAreas::LEFT;
            else {
                std::cout << ">> ArmorialVision: [ERROR] Invalid field side limit argument." << std::endl;
                return EXIT_FAILURE;
            }
        }
        // Debug detection
        if(argc >= 6) {
            param = argv[5];
            if(param.toInt() == 0 || param.toInt() == 1) {
                debugDetection = param.toInt();
                if(debugDetection)
                    std::cout << ">> ArmorialVision: debug detection enabled." << std::endl;
            } else {
                std::cout << ">> ArmorialVision: [ERROR] Invalid debug detection argument." << std::endl;
                return EXIT_FAILURE;
            }
        }
        // Debug geometry
        if(argc >= 7) {
            param = argv[6];
            if(param.toInt() == 0 || param.toInt() == 1) {
                debugGeometry = param.toInt();
                if(debugGeometry)
                    std::cout << ">> ArmorialVision: debug geometry enabled." << std::endl;
            } else {
                std::cout << ">> ArmorialVision: [ERROR] Invalid debug geometry argument." << std::endl;
                return EXIT_FAILURE;
            }
        }
        if(argc > 7) {
            std::cout << ">> ArmorialVision: [ERROR] Invalid number of arguments." << std::endl;
            return EXIT_FAILURE;
        }
    }
    /******************************************/
    /************* EYE THREADS ****************/
    /******************************************/
    // Filters
    const bool enableLossFilter = true;
    const bool enableKalmanFilter = true;
    const bool enableNoiseFilter = true;
    // Create modules
    ArmorialVisionClient eyeClient(visionSystemPort, visionSystemAddress);
    ArmorialVisionUpdater eyeUpdater(&eyeClient, fieldLimit, enableLossFilter, enableKalmanFilter, enableNoiseFilter, debugDetection, debugGeometry, samico);

    // Start modules
    eyeClient.start();
    eyeUpdater.start();

    // Run app
    bool exec = app.exec();
    // Stop modules
    eyeClient.terminate(); // blocking thread, need to terminate
    eyeUpdater.stopRunning();

    // Wait for modules threads
    eyeClient.wait();
    eyeUpdater.wait();

    return exec;
}
