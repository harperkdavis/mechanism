//
// Created by harperkdavis on 4/17/2022.
//

#ifndef MECHANISM_ENVIRONMENT_H
#define MECHANISM_ENVIRONMENT_H

#include <string>
#include <unordered_map>
#include <any>
#include <json/json.hpp>

#define MCH_CONFIG_HEADER "cfg"

class Environment {
public:

    explicit Environment(std::string configFilePath);
    ~Environment() = default;

    void setBool(const std::string& path, bool value);
    void setInt(const std::string& path, int value);
    void setFloat(const std::string& path, float value);
    void setString(const std::string& path, std::string value);

    bool getBool(const std::string& path);
    int getInt(const std::string& path);
    float getFloat(const std::string& path);
    std::string getString(const std::string& path);

    void loadConfigFile();
    void saveConfigFile();

private:

    std::string configFilePath;
    std::unordered_map<std::string, bool> boolValues;
    std::unordered_map<std::string, int> intValues;
    std::unordered_map<std::string, float> floatValues;
    std::unordered_map<std::string, std::string> stringValues;

    void setDefaultValues();
    void saveDefaultConfigFile();

    template<typename T>
    void loadFromJson(const std::string& header, const nlohmann::json& json, std::unordered_map<std::string, T>& map);

    template<typename T>
    void saveToJson(const std::string& header, nlohmann::json& json, std::unordered_map<std::string, T>& map);

};

#endif //MECHANISM_ENVIRONMENT_H
