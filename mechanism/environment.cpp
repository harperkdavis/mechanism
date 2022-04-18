//
// Created by harperkdavis on 4/17/2022.
//

#include "environment.h"
#include "mechanism.h"

#include <plog/Log.h>
#include <fstream>
#include <iostream>
#include <utility>

using namespace nlohmann;

// Simple constructor
Environment::Environment(std::string configFilePath) {
    this->configFilePath = std::move(configFilePath);
}

// Loads the mechanism configuration file, including many properties
void Environment::loadConfigFile() {

    PLOGI << "Loading configuration...";

    std::ifstream is(configFilePath);
    json cfg;

    // Check if the file doesn't exist
    if (is.fail()) {
        PLOGW << "Failed to read config file at \"" << configFilePath << "\", creating new file with default values.";

        // Create the default configuration file
        saveDefaultConfigFile();

        // Then, re-read the config file
        is = std::ifstream(configFilePath);
        if (is.fail()) {
            PLOGF << "Failed to create new config file!";
            throw std::logic_error("Failed to create new config file!");
        }
    }
    is >> cfg;

    // Set the default configuration values
    setDefaultValues();

    // Load the values from the configuration file
    loadFromJson<bool>(MCH_CONFIG_HEADER, cfg, boolValues);
    loadFromJson<int>(MCH_CONFIG_HEADER, cfg, intValues);
    loadFromJson<float>(MCH_CONFIG_HEADER, cfg, floatValues);
    loadFromJson<std::string>(MCH_CONFIG_HEADER, cfg, stringValues);

    PLOGI << "Configuration loaded!";

    saveConfigFile();
}

// Saves the configuration file
void Environment::saveConfigFile() {
    json cfg;

    saveToJson<bool>(MCH_CONFIG_HEADER, cfg, boolValues);
    saveToJson<int>(MCH_CONFIG_HEADER, cfg, intValues);
    saveToJson<float>(MCH_CONFIG_HEADER, cfg, floatValues);
    saveToJson<std::string>(MCH_CONFIG_HEADER, cfg, stringValues);

    std::ofstream o(configFilePath);
    o << std::setw(2) << cfg << std::endl;
}

// Sets the default env values
void Environment::setDefaultValues() {
    setString("version", MCH_VERSION);
    setBool(std::string(MCH_CONFIG_HEADER) + ".server", false);

    setInt(std::string(MCH_CONFIG_HEADER) + ".graphics.window.width", 1920);
    setInt(std::string(MCH_CONFIG_HEADER) + ".graphics.window.height", 900);
    setInt(std::string(MCH_CONFIG_HEADER) + ".graphics.window.mode", 2);

    setString(std::string(MCH_CONFIG_HEADER) + ".graphics.window.title", "among us (in real life)");
}

// Sets the default values, then saves a configuration file
void Environment::saveDefaultConfigFile() {
    setDefaultValues();
    saveConfigFile();
}

void Environment::setBool(const std::string& path, bool value) {
    boolValues[path] = value;
}

void Environment::setInt(const std::string& path, int value) {
    intValues[path] = value;
}

void Environment::setFloat(const std::string& path, float value) {
    floatValues[path] = value;
}

void Environment::setString(const std::string& path, std::string value) {
    stringValues[path] = std::move(value);
}

bool Environment::getBool(const std::string &path) {
    return boolValues[path];
}

int Environment::getInt(const std::string &path) {
    return intValues[path];
}

float Environment::getFloat(const std::string &path) {
    return floatValues[path];
}

std::string Environment::getString(const std::string &path) {
    return stringValues[path];
}

// Loads environment values from a json object, taking the keys from a map.
template<typename T>
void Environment::loadFromJson(const std::string& header, const json& json, std::unordered_map<std::string, T>& map) {
    // Iterate through map
    for (auto pair : map) {
        std::string key = pair.first;

        // Exit if not a part of the configuration
        if (key.rfind(header, 0) != 0) {
            PLOGD << "Skipping value on load: " << key;
            continue;
        }

        // Attempt to get value from json, will catch if value is not present
        try {
            std::stringstream ss(key.substr(header.length() + 1));
            std::string seg;

            std::string path;
            while (std::getline(ss, seg, '.')) {
                path += "/" + seg;
            }

            map[key] = json.at(json::json_pointer(path));
        } catch (json::exception& e) {
            PLOGW << "Error while reading config file: " << e.what();
            PLOGW << "Invalid config file (missing value?) at: " << key;
        }
    }
}

// Loads environment values into a json object
template<typename T>
void Environment::saveToJson(const std::string &header, json& json, std::unordered_map<std::string, T> &map) {
    // Iterate through map
    for (auto pair : map) {
        std::string key = pair.first;

        // Exit if not a part of the configuration
        if (key.rfind(header, 0) != 0) {
            continue;
        }

        try {
            std::stringstream ss(key.substr(header.length() + 1));
            std::string seg;

            std::string path;
            while (std::getline(ss, seg, '.')) {
                path += "/" + seg;
            }

            json[json::json_pointer(path)] = map[key];
        } catch (json::exception& e) {
            PLOGW << "Error while saving config file: " << e.what();
        }
    }
}

