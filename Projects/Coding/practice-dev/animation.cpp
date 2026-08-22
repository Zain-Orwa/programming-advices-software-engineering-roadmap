#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

const int WIDTH = 800;
const int HEIGHT = 600;
const double RAD = 0.01;
const int N = 2;

struct Element {
    sf::CircleShape shape;
    double x, y;

    Element(double x_, double y_) : x(x_), y(y_) {
        shape.setRadius(10);
        shape.setFillColor(sf::Color::White);
        shape.setOrigin(10, 10);
    }

    void updatePosition() {
        shape.setPosition(static_cast<float>(x), static_cast<float>(y));
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Animated Elements");
    window.setFramerateLimit(60);

    std::vector<Element> elems = {
        Element(WIDTH / 2.0, HEIGHT / 2.0),
        Element(WIDTH / 2.0 + 50.0, HEIGHT / 2.0 + 50.0)
    };

    int frm = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        double pointer_x = WIDTH / 2.0;
        double pointer_y = HEIGHT / 2.0;
        double ax = (std::cos(3.0 * frm) * RAD * WIDTH) / HEIGHT;
        double ay = (std::sin(4.0 * frm) * RAD * HEIGHT) / WIDTH;

        elems[0].x += (ax + pointer_x - elems[0].x) / 10.0;
        elems[0].y += (ay + pointer_y - elems[0].y) / 10.0;

        for (int i = 1; i < N; ++i) {
            double a = std::atan2(elems[i].y - elems[i - 1].y, elems[i].x - elems[i - 1].x);
            elems[i].x += (elems[i - 1].x - elems[i].x + (std::cos(a) * (100.0 - i)) / 5.0) / 4.0;
            elems[i].y += (elems[i - 1].y - elems[i].y + (std::sin(a) * (100.0 - i)) / 5.0) / 4.0;
        }

        for (auto& e : elems) {
            e.updatePosition();
        }

        window.clear();
        for (const auto& e : elems) {
            window.draw(e.shape);
        }
        window.display();

        ++frm;
    }
    return 0;
}

