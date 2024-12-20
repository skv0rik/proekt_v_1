#include "Car.h"
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

using namespace std;

Car::Car(int x_start, int y_start) {
    Car_color = sf::Color::White;
    L = 40;
    L_c_rear = 20;
    L_width = 20;
    V = 0;
    X_Car = x_start;
    Y_Car = y_start;
    delta = 0;
    theta = 3 * acos(-1) / 2;
    Car_rectangle.setSize(sf::Vector2f(L, L_width));
    Car_rectangle.setPosition(X_Car - L / 2, Y_Car - L_width / 2);
    directions = {"UU", "UL", "LL", "LD", "DD", "DR", "RR", "RU"};
    long double current = (long double)(0);
    for (int i = 0; i < 8; i++) {
        angles[directions[i]] = current;
        current += acos(-1) / 4;
    }
    points_on_lines.resize(8);
}

void Car::Move(char c) {
    if (c == 'U') {
        V += 0.01;
    }
    if (c == 'D') {
        V -= 0.03;
        V = max(V, (long double)(0));
    }
    if (c == 'L') {
        delta -= 0.01;
        delta = max(delta, (long double)(-0.6));
    }
    if (c == 'R') {
        delta += 0.01;
        delta = min(delta, (long double)(0.6));
    }
}

void Car::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::RectangleShape rectangle = Car_rectangle;
    sf::Transform t;
    t.rotate(theta * 180 / acos(-1), X_Car, Y_Car);
    rectangle.setFillColor(Car_color);
    target.draw(rectangle, t);
}

void Car::Next_Pos() {
    long double betta = atan(L_c_rear * tan(delta) / L);
    long double x_dot, y_dot, theta_dot;
    x_dot = V * cos(theta + betta);
    y_dot = V * sin(theta + betta);
    theta_dot = V * tan(delta) * cos(betta) / L;
    X_Car += x_dot;
    Y_Car += y_dot;
    theta += theta_dot;
    Car_rectangle.setSize(sf::Vector2f(L, L_width));
    Car_rectangle.setPosition(X_Car - L / 2, Y_Car - L_width / 2);
}