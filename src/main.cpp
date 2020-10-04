#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <math.h>

class Particle {
private:
    sf::RectangleShape rect;
    float lifetime;

public:
    Particle(sf::Vector2f pos) {
        rect.setSize(sf::Vector2f(100.0f, 100.0f));
        rect.setOrigin(sf::Vector2f(rect.getSize().x / 2, rect.getSize().y / 2));
        rect.setPosition(pos);
        lifetime = 255.0f;
    }

    void draw(sf::RenderTarget &target, float FPS, sf::Clock clock, sf::Vector3f color) {
        target.draw(rect);
        rect.rotate(0.01f * FPS);
        if(2.0f <= clock.getElapsedTime().asSeconds() && lifetime > 0.0f) {
            //lifetime = lifetime - 5.0f;
        }
        rect.setFillColor(sf::Color(color.x, color.y, color.z, lifetime));
        rect.setPosition(rand() % 1200, rand() % 640);
    }

};

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "DEUTSCH-SAUEN", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    Particle p1(sf::Vector2f(1280 / 2, 720 / 2));
    Particle p2(sf::Vector2f(1280 / 2, 720 / 2));
    Particle p3(sf::Vector2f(1280 / 2, 720 / 2));
    Particle p4(sf::Vector2f(1280 / 2, 720 / 2));
    Particle p5(sf::Vector2f(1280 / 2, 720 / 2));

    sf::Clock clock;
    sf::Clock clock2;

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }

        float FPS = 1.0f / clock.restart().asSeconds();

        window.clear();

        p1.draw(window, FPS, clock2, sf::Vector3f(204.0f, 36.0f, 20.0f));
        p2.draw(window, FPS, clock2, sf::Vector3f(52.0f, 73.0f, 235.0f));
        p3.draw(window, FPS, clock2, sf::Vector3f(67.0f, 235.0f, 52.0f));
        p4.draw(window, FPS, clock2, sf::Vector3f(235.0f, 217.0f, 52.0f));
        p5.draw(window, FPS, clock2, sf::Vector3f(235.0f, 52.0f, 223.0f));

        window.display();
    }
    
    return 0;
}