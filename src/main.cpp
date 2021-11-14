#include <SFML/Graphics.hpp>

int main()
{
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        return -1;
    }

    sf::RenderWindow window(sf::VideoMode(200, 200), "Hello world!");
    sf::Text text;
    text.setFont(font);
    text.setString(__DATE__);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(text);
        window.display();
    }

    return 0;
}
