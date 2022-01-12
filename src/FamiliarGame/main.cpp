#include "ApplicationCore.hpp"

using namespace FamiliarEngine;

int main()
{
    ApplicationCore core;

    while (core.getState() == CoreState::OK) {
        core.handleEvents();
    }

    return core.getState();
}
