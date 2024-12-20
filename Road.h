#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

using namespace std;

const int ROAD_SIZE = 24 * 5;

class Road : public sf::Drawable, public sf::Transformable
{
public:
    int road_sz;
    vector<pair<char, int>> moves;
    vector<vector<int>> elements;
    vector<vector<int>> my_lines;
    vector<vector<int>> my_turns;
    vector<pair<long double, long double>> some_points;
    vector<vector<long double>> start_finish;
    vector<int> color_start_finish;
    vector<vector<pair<long double, long double>>> some_points_start_finish;
    long double best;
public:
    long double x_start, y_start;
    Road();
    void Init();
    void Points();
public:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};