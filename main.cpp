#include <iostream>
#include <json/json.hpp>

#include <plog/Log.h>
#include "plog/Initializers/RollingFileInitializer.h"
#include "plog/Appenders/ColorConsoleAppender.h"

#include "mechanism/mechanism.h"

Mechanism gMechanism;

int main() {

    plog::init(plog::debug, "out.log")
        .addAppender(new plog::ColorConsoleAppender<plog::TxtFormatter>());

    PLOGI << "Starting mechanism v" << MCH_VERSION << "...";

    gMechanism.initialize();

    return 0;
}
