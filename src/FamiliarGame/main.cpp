#include "ApplicationCore.hpp"

using namespace FamiliarEngine;

int main()
{
    ApplicationCore core;
    core.launch();

    while (core.getState() == CoreState::OK) {
        core.handleEvents();
    }

    return core.getState();
}
