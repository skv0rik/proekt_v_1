#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

const int CAR_SZ = 24;
using namespace std;

class Car : public sf::Drawable, public sf::Transformable
{
public:
    sf::RectangleShape Car_rectangle;
    sf::Color Car_color;
    int L;
    int L_c_rear;
    int L_width;
    long double V;
    long double X_Car, Y_Car;
    long double delta;
    long double theta;
    map<string, long double> distances;
    map<string, long double> angles;
    vector<string> directions;
    vector<pair<long double, long double>> points_on_lines;
public:
    Car(int x_start, int y_start);
    void Init();
    void Next_Pos();
    void Move(char c);
public:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
