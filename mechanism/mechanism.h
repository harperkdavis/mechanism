//
// Created by harperkdavis on 4/11/2022.
//

#ifndef MECHANISM_MECHANISM_H
#define MECHANISM_MECHANISM_H

#include <string>
#include "environment.h"

// The current mechanism version
#define MCH_VERSION "0.1"

// Path to where the env files should be located
#define MCH_PATH "../mch/"
#define MCH_CONFIG_FILENAME "cfg.json"

// Class for the main mechanism engine data
class Mechanism {
public:

    Mechanism() = default;
    ~Mechanism() = default;

    void initialize();

private:

    Environment env = Environment(std::string(MCH_PATH) + std::string(MCH_CONFIG_FILENAME));;

    void loadConfig();
    void loadGraphics();
};

#endif //MECHANISM_MECHANISM_H
