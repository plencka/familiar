#include "MainWindow.hpp"

int main()
{
    std::unique_ptr<MainWindow> window = std::make_unique<MainWindow>();
    window->open();

    while (window->update());
    return 0;
}
