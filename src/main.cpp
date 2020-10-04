#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <math.h>

class Particle {
private:
    sf::RectangleShape rect;
    float lifetime;
    sf::Vector2f position;

public:
    Particle(sf::Vector2f pos) {
        position = pos;
        rect.setSize(sf::Vector2f(100.0f, 100.0f));
        rect.setOrigin(sf::Vector2f(rect.getSize().x / 2, rect.getSize().y / 2));
        rect.setPosition(pos);
        lifetime = 255.0f;
    }

    void draw(sf::RenderTarget &target, float FPS, sf::Clock clock, sf::Vector3f color, sf::Vector2f dispersion) {
        target.draw(rect);
        rect.rotate(0.01f * FPS);
        if(2.0f <= clock.getElapsedTime().asSeconds() && lifetime > 0.0f) {
            //lifetime = lifetime - 5.0f;
        }
        rect.setFillColor(sf::Color(color.x, color.y, color.z, lifetime));
        rect.setPosition(position.x + rand() % (int)dispersion.x, position.y + rand() % (int)dispersion.y);
    }

};

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "DEUTSCH-SAUEN", sf::Style::Titlebar | sf::Style::Close);
    //window.setFramerateLimit(60);

    Particle p1(sf::Vector2f(100.0f, 100.0f));
    Particle p2(sf::Vector2f(200.0f, 100.0f));
    Particle p3(sf::Vector2f(300.0f, 100.0f));
    Particle p4(sf::Vector2f(400.0f, 100.0f));
    Particle p5(sf::Vector2f(500.0f, 100.0f));
    Particle p6(sf::Vector2f(100.0f, 200.0f));
    Particle p7(sf::Vector2f(200.0f, 200.0f));
    Particle p8(sf::Vector2f(300.0f, 200.0f));
    Particle p9(sf::Vector2f(400.0f, 200.0f));

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
        std::cout << FPS << "\n";

        window.clear();

        p1.draw(window, FPS, clock2, sf::Vector3f(204.0f, 36.0f, 20.0f), sf::Vector2f(50.0f, 50.0f));
        p2.draw(window, FPS, clock2, sf::Vector3f(52.0f, 73.0f, 235.0f), sf::Vector2f(50.0f, 50.0f));
        p3.draw(window, FPS, clock2, sf::Vector3f(67.0f, 235.0f, 52.0f), sf::Vector2f(50.0f, 50.0f));
        p4.draw(window, FPS, clock2, sf::Vector3f(235.0f, 217.0f, 52.0f), sf::Vector2f(50.0f, 50.0f));
        p5.draw(window, FPS, clock2, sf::Vector3f(235.0f, 52.0f, 223.0f), sf::Vector2f(50.0f, 50.0f));
        p6.draw(window, FPS, clock2, sf::Vector3f(52.0f, 225.0f, 235.0f), sf::Vector2f(50.0f, 50.0f));
        p7.draw(window, FPS, clock2, sf::Vector3f(95.0f, 235.0f, 52.0f), sf::Vector2f(50.0f, 50.0f));
        p8.draw(window, FPS, clock2, sf::Vector3f(182.0f, 43.0f, 207.0f), sf::Vector2f(50.0f, 50.0f));
        p9.draw(window, FPS, clock2, sf::Vector3f(207.0f, 100.0f, 29.0f), sf::Vector2f(50.0f, 50.0f));

        window.display();
    }
    
    return 0;
}