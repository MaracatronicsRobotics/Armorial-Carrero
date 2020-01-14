 
/***
 * Maracatronics Robotics
 * Federal University of Pernambuco (UFPE) at Recife
 * http://www.maracatronics.com/
 *
 * This file is part of Armorial project.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ***/

#ifndef SAMICO_H
#define SAMICO_H

#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>
#include <SFML/Graphics.hpp>
#include "Ball/ball.h"
#include "Robot/robot.h"
#include "types/frame.h"

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
    sf::RenderWindow *getWindow();

private:
    void drawBall();
    void drawRobots();
    void zoomViewAt(sf::Vector2i pixel, sf::RenderWindow *window, double zoom);

private:
    // desenhos do samico
    sf::RenderWindow *window;
    Frame *frame_received=new Frame(8,100);
    sf::RectangleShape *fundoSamico;
    sf::CircleShape *circuloCentral;
    sf::ContextSettings settings;
    const double zoomAmount = 1.1;

    // textura e sprite dos robos
    sf::Texture texture;
    sf::Sprite sprite;

    // bola
    sf::CircleShape *ball = new sf::CircleShape(ballRadius);

    // vetor de linhas externas
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

    // vetor do gol esquerdo (baixo)
    sf::Vertex golEsquerdo[6] =
    {
        sf::Vertex(sf::Vector2f((max_x/2.0) - 1000.f, deslocamentoBorda)),
        sf::Vertex(sf::Vector2f((max_x/2.0) - 1000.f, 1000.f + deslocamentoBorda)),
        sf::Vertex(sf::Vector2f((max_x/2.0) + 1000.f, deslocamentoBorda)),
        sf::Vertex(sf::Vector2f((max_x/2.0) + 1000.f, 1000.f + deslocamentoBorda)),
        sf::Vertex(sf::Vector2f((max_x/2.0) - 1000.f, 1000.f + deslocamentoBorda)),
        sf::Vertex(sf::Vector2f((max_x/2.0) + 1000.f, 1000.f + deslocamentoBorda))
    };

    // vetor do gol direito (cima)
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
