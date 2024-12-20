// main.cpp
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "Car.h"
#include "Road.h"
#include <bits/stdc++.h>

using namespace std;

const sf::Keyboard::Key Left = sf::Keyboard::A;
const sf::Keyboard::Key Up = sf::Keyboard::W;
const sf::Keyboard::Key Right = sf::Keyboard::D;
const sf::Keyboard::Key Down = sf::Keyboard::S;

bool is_there_any_intersections(Car car, Road road) {
    sf::FloatRect tek(sf::Vector2f(car.X_Car - car.L / 2, car.Y_Car - car.L_width / 2), sf::Vector2f(car.L, car.L_width));
    for (auto vec : road.some_points) {
        sf::Vector2f current = sf::Vector2f(vec.first, vec.second);
        sf::Transform t;
        t.rotate((-car.theta) * 180 / acos(-1), car.X_Car, car.Y_Car);
        current = t.transformPoint(current);
        if (tek.contains(current)) {
            return true;
        }
    }
    return false;
}

vector<pair<long double, long double>> update_distances(Car car, Road road) {
    vector<pair<long double, long double>> result(8);
    for (int i = 0; i < 8; i++) {
        long double ksi;
        ksi = car.theta + car.angles[car.directions[i]];
        long double x1, y1, x2, y2;
        x1 = car.X_Car;
        y1 = car.Y_Car;
        x2 = car.X_Car + cos(ksi) * 100;
        y2 = car.Y_Car + sin(ksi) * 100;
        long double l_a, l_b, l_c;
        l_a = y1 - y2;
        l_b = x2 - x1;
        l_c = x1 * y2 - x2 * y1;
        long double x3, y3;
        long double rrr = 100000;
        for (auto u : road.some_points) {
            long double dist = abs((l_a * u.first + l_b * u.second + l_c) / sqrt(l_a * l_a + l_b * l_b));
            if (dist < 2) {
                long double k1, k2;
                k1 = (x2 - x1) * (u.first - x1);
                k2 = (y2 - y1) * (u.second - y1);
                if ((k1 > -1e-7) && (k2 > -1e-7)) {
                    if (sqrt((u.first - x1) * (u.first - x1) + (u.second - y1) * (u.second - y1)) < rrr) {
                        x3 = u.first;
                        y3 = u.second;
                        rrr = sqrt((u.first - x1) * (u.first - x1) + (u.second - y1) * (u.second - y1));
                    }
                }
            }
        }
        result[i] = {x3, y3};
    }
    return result;
}

vector<int> is_it_started(Car car, Road road) {
    vector<int> result = road.color_start_finish;
    sf::FloatRect tek(sf::Vector2f(car.X_Car - car.L / 2, car.Y_Car - car.L_width / 2), sf::Vector2f(car.L, car.L_width));
    for (int i = 0; i < (int)(road.start_finish.size()); i++) {
        for (auto vec : road.some_points_start_finish[i]) {
            sf::Vector2f current = sf::Vector2f(vec.first, vec.second);
            sf::Transform t;
            t.rotate((-car.theta) * 180 / acos(-1), car.X_Car, car.Y_Car);
            current = t.transformPoint(current);
            if (tek.contains(current)) {
                if (i == 0) {
                    result[i] = 1;
                    if (result[(int)result.size() - 2] == 1) {
                        result.back() = 1;
                    }
                } else if (result[i - 1] == 1) {
                    result[i] = 1;
                }
            }
        }
    }
    return result;
}

/*void draw_lines(Car car, sf::RenderWindow &window)
{
    for (int i = 0; i < 8; i++) {
        sf::Vertex line[]{
                sf::Vertex(sf::Vector2f(car.X_Car, car.Y_Car), sf::Color::Black),
                sf::Vertex(sf::Vector2f(car.points_on_lines[i].first, car.points_on_lines[i].second), sf::Color::Black)
        };
        window.draw(line, 2, sf::Lines);
    }
}*/

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1920, 1000), "CAR", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    sf::Font font;
    font.loadFromFile("C:/calibri/calibri.ttf");

    sf::Text text("Road for a car", font, 40);
    text.setPosition(5.f, 5.f);
    text.setFillColor(sf::Color::Black);

    Road road;
    road.setPosition(sf::Vector2f(road.x_start, road.y_start));
    road.Points();

    sf::Event event;
    Car car(road.x_start, road.y_start);
    bool key_L, key_R, key_U, key_D;
    key_L = false;
    key_R = false;
    key_U = false;
    key_D = false;
    long double start = clock();
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }
        if (sf::Keyboard::isKeyPressed(Left)) {
            key_L = true;
        } else {
            key_L = false;
        }
        if (sf::Keyboard::isKeyPressed(Right)) {
            key_R = true;
        } else {
            key_R = false;
        }
        if (sf::Keyboard::isKeyPressed(Up)) {
            key_U = true;
        } else {
            key_U = false;
        }
        if (sf::Keyboard::isKeyPressed(Down)) {
            key_D = true;
        } else {
            key_D = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
            car.V = 0;
            car.delta = 0;
            car.Car_color = sf::Color::White;
            car.theta = 3 * acos(-1) / 2;
            car.X_Car = road.x_start;
            car.Y_Car = road.y_start;
            car.Car_rectangle.setPosition(car.X_Car - car.L / 2, car.Y_Car - car.L_width / 2);
            road.color_start_finish.clear();
            road.color_start_finish.resize((int)(road.start_finish.size()) + 1, 0);
            start = clock();
        }
        if (key_L) car.Move('L');
        if (key_R) car.Move('R');
        if (key_U) car.Move('U');
        if (key_D) car.Move('D');
        window.clear(sf::Color::Green);
        window.draw(text);
        sf::Text text1(to_string(((long double)(clock()) - start) / CLOCKS_PER_SEC), font, 40);
        sf::Text text2(to_string(road.best), font, 40);
        text1.setPosition(1000.f, 5.f);
        text1.setFillColor(sf::Color::Black);
        text2.setPosition(1400.f, 5.f);
        text2.setFillColor(sf::Color::Black);
        window.draw(text1);
        window.draw(text2);
        road.color_start_finish = is_it_started(car, road);
        if (road.color_start_finish.back() == 1) {
            road.best = min(road.best, ((long double)(clock()) - start) / CLOCKS_PER_SEC);
        }
        window.draw(road);
        car.Next_Pos();
        if(is_there_any_intersections(car, road)) {
            car.V = 0;
            car.delta = 0;
            car.Car_color = sf::Color::Red;
        }
        car.points_on_lines = update_distances(car, road);
        for (int i = 0; i < 8; i++) {
            sf::Vertex line[]{
                    sf::Vertex(sf::Vector2f(car.X_Car, car.Y_Car), sf::Color::Black),
                    sf::Vertex(sf::Vector2f(car.points_on_lines[i].first, car.points_on_lines[i].second), sf::Color::Black)
            };
            window.draw(line, 2, sf::Lines);
        }
        window.draw(car);
        window.display();
    }

    return 0;
}