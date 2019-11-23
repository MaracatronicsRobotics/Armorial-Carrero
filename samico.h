#ifndef SAMICO_H
#define SAMICO_H

#include <bits/stdc++.h>
//#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <SFML/Graphics.hpp>
#include "Ball/ball.h"
#include "Robot/robot.h"
#include "types/frame.h"
#include <PathPlanning/path.h>

using namespace std;

#define maxRobots 8
#define circlePrecision 100
#define ballRadius 50.f
#define centralCirleRadius 500.f
#define deslocamentoBorda 300.f

#define deslocamentoLinhas 1

#define max_x 7400
#define max_y 10400

#define max_x_campo 10400
#define max_y_campo 7400

#define robotRadius 110.f
#define robotRealRadius 180.f
#define border 1400

class Samico
{
public:
    Samico();
    void drawWindow();
    void setFrame(Frame *newFrame);
    pathPlanner getPath();
    sf::RenderWindow *getWindow();


private:
    void drawBall();
    void drawRobots();
    void zoomViewAt(sf::Vector2i pixel, sf::RenderWindow *window, double zoom);
    void setColisions(int index_at, bool isBlue);
    void unsetColisions(int index_at, bool isBlue);


private:
    Frame *frame_received=new Frame(8,100);

    pathPlanner pathing = pathPlanner(max_y/10.0, max_x/5.0);

    sf::CircleShape *ball = new sf::CircleShape(ballRadius);
    sf::RectangleShape *fundoSamico;
    sf::Font font;
    sf::CircleShape *circuloCentral;
    sf::Text blueText[maxRobots];
    sf::Sprite blueSprite[maxRobots];

    sf::CircleShape blueRobots_shape[maxRobots];
    sf::CircleShape yellowRobots_shape[maxRobots];

    sf::RenderWindow *window;

    sf::Text yellowText[maxRobots];
    sf::Sprite yellowSprite[maxRobots];
    sf::ContextSettings settings;

    bool **mat;
    vector<pair<int, int>> blueRobots_position;
    vector<pair<int, int>> yellowRobots_position;
    pair<int, int> ball_position;

    const double zoomAmount = 1.1;

    sf::Vertex linhasExternas[10] =
    {
        sf::Vertex(sf::Vector2f(deslocamentoBorda, deslocamentoBorda)),
        sf::Vertex(sf::Vector2f(max_x - deslocamentoBorda, deslocamentoBorda)),
        sf::Vertex(sf::Vector2f(max_x - deslocamentoBorda, deslocamentoBorda)),
        sf::Vertex(sf::Vector2f(max_x - deslocamentoBorda, max_y - deslocamentoBorda)),
        sf::Vertex(sf::Vector2f(max_x - deslocamentoBorda, max_y - deslocamentoBorda)),
        sf::Vertex(sf::Vector2f(deslocamentoBorda, max_y - deslocamentoBorda)),
        sf::Vertex(sf::Vector2f(deslocamentoBorda, max_y - deslocamentoBorda)),
        sf::Vertex(sf::Vector2f(deslocamentoBorda, deslocamentoBorda)),
        sf::Vertex(sf::Vector2f(deslocamentoBorda, max_y/2.0)),
        sf::Vertex(sf::Vector2f(max_x - deslocamentoBorda, max_y/2.0))
    };

    sf::Vertex golEsquerdo[6] =
    {
        sf::Vertex(sf::Vector2f((max_x/2.0) - 1000.f, deslocamentoBorda)),
        sf::Vertex(sf::Vector2f((max_x/2.0) - 1000.f, 1000.f + deslocamentoBorda)),
        sf::Vertex(sf::Vector2f((max_x/2.0) + 1000.f, deslocamentoBorda)),
        sf::Vertex(sf::Vector2f((max_x/2.0) + 1000.f, 1000.f + deslocamentoBorda)),
        sf::Vertex(sf::Vector2f((max_x/2.0) - 1000.f, 1000.f + deslocamentoBorda)),
        sf::Vertex(sf::Vector2f((max_x/2.0) + 1000.f, 1000.f + deslocamentoBorda))
    };

    sf::Vertex golDireito[6] =
    {
        sf::Vertex(sf::Vector2f((max_x/2.0) - 1000.f, max_y - deslocamentoBorda)),
        sf::Vertex(sf::Vector2f((max_x/2.0) - 1000.f, max_y - (1000.f + deslocamentoBorda))),
        sf::Vertex(sf::Vector2f((max_x/2.0) + 1000.f, max_y - deslocamentoBorda)),
        sf::Vertex(sf::Vector2f((max_x/2.0) + 1000.f, max_y - (1000.f + deslocamentoBorda))),
        sf::Vertex(sf::Vector2f((max_x/2.0) - 1000.f, max_y - (1000.f + deslocamentoBorda))),
        sf::Vertex(sf::Vector2f((max_x/2.0) + 1000.f, max_y - (1000.f + deslocamentoBorda)))
    };
};
#endif // SAMICO_H
