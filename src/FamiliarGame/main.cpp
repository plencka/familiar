#include "MainWindow.hpp"

int main()
{
    auto window = new MainWindow();
    window->open();

    while (window->update());

    delete window;
    return 0;
}
