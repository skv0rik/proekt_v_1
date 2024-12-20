#include "Road.h"
#include <bits/stdc++.h>

#define ld long double

Road::Road()
{
    cin >> road_sz;
    moves.resize(road_sz);
    for (int i = 0; i < road_sz; i++) {
        char x;
        int y;
        y = -1;
        cin >> x;
        if (x == 'S') {
            cin >> y;
        }
        moves[i] = {x, y};
    }
    Init();
}

void Road::Init()
{
    best = 1000;
    int x_pred, y_pred;
    x_pred = 0;
    y_pred = 0;
    int angle = 0;
    for (int i = 0; i < road_sz; i++) {
        int type = moves[i].first;
        int len = moves[i].second;
        if (type == 'S') {
            if (angle == 0) {
                my_lines.push_back({x_pred - ROAD_SIZE / 2, y_pred, x_pred - ROAD_SIZE / 2, y_pred - len});
                my_lines.push_back({x_pred + ROAD_SIZE / 2, y_pred, x_pred + ROAD_SIZE / 2, y_pred - len});
                start_finish.push_back({(ld)(x_pred - ROAD_SIZE / 2), (ld)y_pred, (ld)(x_pred + ROAD_SIZE / 2), (ld)y_pred});
                start_finish.push_back({(ld)(x_pred - ROAD_SIZE / 2), (ld)(y_pred - len), (ld)(x_pred + ROAD_SIZE / 2), (ld)(y_pred - len)});
                y_pred -= len;
            }
            if (angle == 90) {
                my_lines.push_back({x_pred, y_pred - ROAD_SIZE / 2, x_pred + len, y_pred - ROAD_SIZE / 2});
                my_lines.push_back({x_pred, y_pred + ROAD_SIZE / 2, x_pred + len, y_pred + ROAD_SIZE / 2});
                start_finish.push_back({(ld)(x_pred), (ld)(y_pred - ROAD_SIZE / 2), (ld)(x_pred), (ld)(y_pred + ROAD_SIZE / 2)});
                start_finish.push_back({(ld)(x_pred + len), (ld)(y_pred - ROAD_SIZE / 2), (ld)(x_pred + len), (ld)(y_pred + ROAD_SIZE / 2)});
                x_pred += len;
            }
            if (angle == 180) {
                my_lines.push_back({x_pred - ROAD_SIZE / 2, y_pred, x_pred - ROAD_SIZE / 2, y_pred + len});
                my_lines.push_back({x_pred + ROAD_SIZE / 2, y_pred, x_pred + ROAD_SIZE / 2, y_pred + len});
                start_finish.push_back({(ld)(x_pred - ROAD_SIZE / 2), (ld)(y_pred), (ld)(x_pred + ROAD_SIZE / 2), (ld)(y_pred)});
                start_finish.push_back({(ld)(x_pred - ROAD_SIZE / 2), (ld)(y_pred + len), (ld)(x_pred + ROAD_SIZE / 2), (ld)(y_pred + len)});
                y_pred += len;
            }
            if (angle == 270) {
                my_lines.push_back({x_pred, y_pred - ROAD_SIZE / 2, x_pred - len, y_pred - ROAD_SIZE / 2});
                my_lines.push_back({x_pred, y_pred + ROAD_SIZE / 2, x_pred - len, y_pred + ROAD_SIZE / 2});
                start_finish.push_back({(ld)(x_pred), (ld)(y_pred - ROAD_SIZE / 2), (ld)(x_pred), (ld)(y_pred + ROAD_SIZE / 2)});
                start_finish.push_back({(ld)(x_pred - len), (ld)(y_pred - ROAD_SIZE / 2), (ld)(x_pred - len), (ld)(y_pred + ROAD_SIZE / 2)});
                x_pred -= len;
            }
        } else {
            if (type == 'L') {
                if (angle == 0) {
                    my_turns.push_back({x_pred - ROAD_SIZE, y_pred, 1});
                    x_pred -= ROAD_SIZE;
                    y_pred -= ROAD_SIZE;
                }
                if (angle == 90) {
                    my_turns.push_back({x_pred, y_pred - ROAD_SIZE, 2});
                    x_pred += ROAD_SIZE;
                    y_pred -= ROAD_SIZE;
                }
                if (angle == 180) {
                    my_turns.push_back({x_pred + ROAD_SIZE, y_pred, 3});
                    x_pred += ROAD_SIZE;
                    y_pred += ROAD_SIZE;
                }
                if (angle == 270) {
                    my_turns.push_back({x_pred, y_pred + ROAD_SIZE, 4});
                    x_pred -= ROAD_SIZE;
                    y_pred += ROAD_SIZE;
                }
                angle += 270;
                angle %= 360;
            }
            if (type == 'R') {
                if (angle == 0) {
                    my_turns.push_back({x_pred + ROAD_SIZE, y_pred, 4});
                    x_pred += ROAD_SIZE;
                    y_pred -= ROAD_SIZE;
                }
                if (angle == 90) {
                    my_turns.push_back({x_pred, y_pred + ROAD_SIZE, 1});
                    x_pred += ROAD_SIZE;
                    y_pred += ROAD_SIZE;
                }
                if (angle == 180) {
                    my_turns.push_back({x_pred - ROAD_SIZE, y_pred, 2});
                    x_pred -= ROAD_SIZE;
                    y_pred += ROAD_SIZE;
                }
                if (angle == 270) {
                    my_turns.push_back({x_pred, y_pred - ROAD_SIZE, 3});
                    x_pred -= ROAD_SIZE;
                    y_pred -= ROAD_SIZE;
                }
                angle += 90;
                angle %= 360;
            }
        }
    }
    color_start_finish.resize((int)start_finish.size() + 1, 0);
    int x_min, y_min;
    x_min = 0;
    y_min = 0;
    for (auto vec : my_lines) {
        x_min = min({x_min, vec[0], vec[2]});
        y_min = min({y_min, vec[1], vec[3]});
    }
    x_start = (long double)(50 - x_min);
    y_start = (long double)(50 - y_min);
    cout << "lines:\n";
    for (auto vec : my_lines) {
        for (auto v : vec) {
            cout << v << " ";
        }
        cout << endl;
    }
    cout << "turns:\n";
    for (auto vec : my_turns) {
        for (auto v : vec) {
            cout << v << " ";
        }
        cout << endl;
    }
}

void Road::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    sf::Color color = sf::Color::Black;
    for (auto vec : my_lines) {
        sf::Vertex line[] {
            sf::Vertex(sf::Vector2f(vec[0], vec[1]), sf::Color::Black),
            sf::Vertex(sf::Vector2f(vec[2], vec[3]), sf::Color::Black)
        };
        target.draw(line, 2, sf::Lines, states);
    }
    sf::VertexArray Turn(sf::Points, 2000);
    for (int i = 0; i < 1000; i++) {
        Turn[i].position = sf::Vector2f(ROAD_SIZE / 2 * cos(acos(-1) / 2000 * (i - 1000)), ROAD_SIZE / 2 * sin(acos(-1) / 2000 * (i - 1000)));
        Turn[i].color = sf::Color::Black;
    }
    for (int i = 1000; i < 2000; i++) {
        Turn[i].position = sf::Vector2f(3 * ROAD_SIZE / 2 * cos(acos(-1) / 2000 * (i - 2000)), 3 * ROAD_SIZE / 2 * sin(acos(-1) / 2000 * (i - 2000)));
        Turn[i].color = sf::Color::Black;
    }
    for (auto vec : my_turns) {
        int x, y, type;
        x = vec[0];
        y = vec[1];
        type = vec[2];
        sf::VertexArray current_turn(sf::Points, 2000);
        current_turn = Turn;
        sf::Transform t;
        t.translate(sf::Vector2f(x, y)).rotate((type - 1) * 90);
        sf::RenderStates current_states = states;
        current_states.transform *= t;
        target.draw(Turn, current_states);
    }
    for (int i = 0; i < (int)start_finish.size(); i++) {
        auto vec = start_finish[i];
        if (color_start_finish[i] == 0) {
            sf::Vertex line[]{
                    sf::Vertex(sf::Vector2f(vec[0], vec[1]), sf::Color::Red),
                    sf::Vertex(sf::Vector2f(vec[2], vec[3]), sf::Color::Red)
            };
            target.draw(line, 2, sf::Lines, states);
        } else {
            sf::Vertex line[]{
                    sf::Vertex(sf::Vector2f(vec[0], vec[1]), sf::Color::Yellow),
                    sf::Vertex(sf::Vector2f(vec[2], vec[3]), sf::Color::Yellow)
            };
            target.draw(line, 2, sf::Lines, states);
        }
    }
}

void Road::Points() {
    sf::VertexArray Turn(sf::Points, 2000);
    for (int i = 0; i < 1000; i++) {
        Turn[i].position = sf::Vector2f(ROAD_SIZE / 2 * cos(acos(-1) / 2000 * (i - 1000)), ROAD_SIZE / 2 * sin(acos(-1) / 2000 * (i - 1000)));
        Turn[i].color = sf::Color::Black;
    }
    for (int i = 1000; i < 2000; i++) {
        Turn[i].position = sf::Vector2f(3 * ROAD_SIZE / 2 * cos(acos(-1) / 2000 * (i - 2000)), 3 * ROAD_SIZE / 2 * sin(acos(-1) / 2000 * (i - 2000)));
        Turn[i].color = sf::Color::Black;
    }
    for (auto vec: my_turns) {
        int x, y, type;
        x = vec[0];
        y = vec[1];
        type = vec[2];
        sf::VertexArray current_turn(sf::Points, 2000);
        current_turn = Turn;
        sf::Transform t;
        t.translate(sf::Vector2f(x, y)).rotate((type - 1) * 90);
        for (int i = 0; i < 2000; i++) {
            if (i % 10 == 5) {
                sf::Vector2f current = t.transformPoint(Turn[i].position);
                some_points.push_back({current.x + x_start, current.y + y_start});
            }
        }
    }
    for (auto vec: my_lines) {
        sf::Vector2f v1((long double)vec[0], (long double)vec[1]);
        sf::Vector2f v2((long double)vec[2], (long double)vec[3]);
        for (long double i = (long double)0.5; i < (long double)1000; i += (long double)1) {
            long double x = v1.x * i + v2.x * ((long double)(1000) - i);
            long double y = v1.y * i + v2.y * ((long double)(1000) - i);
            x = x / ((long double)1000);
            y = y / ((long double)1000);
            some_points.push_back({x + x_start, y + y_start});
        }
    }
    some_points_start_finish.resize(start_finish.size());
    for (int j = 0; j < (int)start_finish.size(); j++) {
        auto vec = start_finish[j];
        sf::Vector2f v1((long double)vec[0], (long double)vec[1]);
        sf::Vector2f v2((long double)vec[2], (long double)vec[3]);
        for (long double i = (long double)0.5; i < (long double)200; i += (long double)1) {
            long double x = v1.x * i + v2.x * ((long double)(200) - i);
            long double y = v1.y * i + v2.y * ((long double)(200) - i);
            x = x / ((long double)200);
            y = y / ((long double)200);
            some_points_start_finish[j].push_back({x + x_start, y + y_start});
        }
    }
}
