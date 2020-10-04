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
    Particle() {
        position = sf::Vector2f(0.0f, 0.0f);
        rect.setSize(sf::Vector2f(10.0f, 10.0f));
        rect.setOrigin(sf::Vector2f(rect.getSize().x / 2, rect.getSize().y / 2));
        rect.setPosition(position);
        lifetime = 255.0f;
    }

    Particle(sf::Vector2f pos, sf::Vector2f size) {
        position = pos;
        rect.setSize(size);
        rect.setOrigin(sf::Vector2f(rect.getSize().x / 2, rect.getSize().y / 2));
        rect.setPosition(pos);
        lifetime = 255.0f;
    }

    void set(sf::Vector2f pos, sf::Vector2f size) {
        position = pos;
        rect.setSize(size);
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

class ParticleSystem {
private:
    Particle particles[1000];

public:
    ParticleSystem(sf::Vector2f pos, int particleNum) {
        for(int i = 0; i < particleNum; ++i) {
            particles[i].set(pos, sf::Vector2f(10.0f, 10.0f));
        }
    }

    void draw(sf::RenderTarget &target, float FPS, sf::Clock clock, sf::Vector3f color, sf::Vector2f dispersion, int particleNum) {
        for(int j = 0; j < particleNum; ++j) {
            particles[j].draw(target, FPS, clock, color, dispersion);
        }
    }

};

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "DEUTSCH-SAUEN", sf::Style::Titlebar | sf::Style::Close);
    //window.setFramerateLimit(60);

    ParticleSystem ps1(sf::Vector2f(0, 0), 100);

    //Particle p1(sf::Vector2f(100.0f, 100.0f), sf::Vector2f(10.0f, 10.0f));

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

        ps1.draw(window, FPS, clock2, sf::Vector3f(204.0f, 36.0f, 20.0f), sf::Vector2f(1280.0f, 720.0f), 100);
        //p1.draw(window, FPS, clock2, sf::Vector3f(204.0f, 36.0f, 20.0f), sf::Vector2f(50.0f, 50.0f));

        window.display();
    }
    
    return 0;
}