//
// Created by harperkdavis on 4/11/2022.
//

#include "mechanism.h"

#include <plog/Log.h>

#include <ctime>

// Initializes the mechanism game engine
void Mechanism::initialize() {

    const std::time_t startInitTime = std::time(nullptr);

    PLOGI << "Initializing mechanism...";

    loadConfig();

    const unsigned int initTime = std::time(nullptr) - startInitTime;
    PLOGI << "Mechanism initialized! (" << initTime << " ms)";

}

void Mechanism::loadConfig() {
    env.loadConfigFile();
}

