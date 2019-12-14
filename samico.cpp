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

#include "samico.h"
#include <thread>

Samico::Samico()
{

    mat = (bool **) malloc(max_y/10 * sizeof(bool *));
    for(int x = 0; x < max_y/10; x++){
        mat[x] = (bool *) malloc(max_x/5 * sizeof(bool));
        memset(mat[x], true, max_x/5);
    }

    // fundo do samico
    fundoSamico = new sf::RectangleShape(sf::Vector2f((float) max_x, (float) max_y));
    fundoSamico->setFillColor(sf::Color(0, 100, 0, 255));

    // fonte dos numeros nos jogadores

    if(!font.loadFromFile("../utils/arial.ttf")){
        printf("Error loading font.\n");
        exit(-1);
    }

    /* circulo central */
    circuloCentral = new sf::CircleShape(centralCirleRadius);
    circuloCentral->setFillColor(sf::Color(0, 0, 0, 0));
    circuloCentral->setOutlineThickness(10.f);
    circuloCentral->setOutlineColor(sf::Color(255, 255, 255, 255));
    circuloCentral->setPointCount(circlePrecision);
    circuloCentral->setPosition((max_x/2.0) - centralCirleRadius, (max_y/2.0) - centralCirleRadius);

    // texto e sprite do time azul
    for(int x = 0; x < maxRobots; x++){
        blueText[x].setFont(font);
        char teste[5];
        sprintf(teste, "%d", x);
        blueText[x].setString(teste);
        blueText[x].setCharacterSize(160);
        blueText[x].setFillColor(sf::Color::Black);

        blueRobots_shape[x].setRadius(robotRadius);
        blueRobots_shape[x].setFillColor(sf::Color::Blue);
        blueRobots_shape[x].setOutlineColor(sf::Color::Black);
        blueRobots_shape[x].setOutlineThickness(12.f);
        blueRobots_shape[x].setPointCount(100.f);
    }

    // texto e sprite do time amarelo
    for(int x = 0; x < maxRobots; x++){
        yellowText[x].setFont(font);
        char teste[5];
        sprintf(teste, "%d", x);
        yellowText[x].setString(teste);
        yellowText[x].setCharacterSize(160);
        yellowText[x].setFillColor(sf::Color::Black);

        yellowRobots_shape[x].setRadius(robotRadius);
        yellowRobots_shape[x].setFillColor(sf::Color::Yellow);
        yellowRobots_shape[x].setOutlineColor(sf::Color::Black);
        yellowRobots_shape[x].setOutlineThickness(12.f);
        yellowRobots_shape[x].setPointCount(100.f);
    }

    // bola

    ball->setFillColor(sf::Color(255, 69, 0, 255));
    ball->setPointCount(circlePrecision);

    // configurações e criação da tela principal
    settings.antialiasingLevel = 8;

    double width = (max_x)/12.5;
    double height = (max_y)/12.5;

    window = new sf::RenderWindow(sf::VideoMode(width, height), "Armorial Samico", sf::Style::Default, settings);
    window->setFramerateLimit(60);

    zoomViewAt(sf::Vector2i(0, 0), window, max_x / width);

}

void Samico::drawBall(){
    if(frame_received->_ball.getBallPosition().isValid()){

        double ballx = abs(((frame_received->_ball.getPosition().x()*1000)-(max_x_campo / 2.0))/((max_x_campo / 2.0)/(max_y/2.0)));
        double bally = abs(((frame_received->_ball.getPosition().y()*1000)-(max_y_campo / 2.0))/((max_y_campo / 2.0)/(max_x/2.0)));

        ball->setPosition(bally - ballRadius, ballx - ballRadius);
        ball->setOutlineColor(sf::Color::Black);
        ball->setOutlineThickness(12.f);
        window->draw(*ball);

        ball_position = make_pair((int) bally/10.0, (int) ballx/10.0);
    }
}

void Samico::drawRobots(){
    blueRobots_position.clear();
    yellowRobots_position.clear();

    for(int x = 0; x < frame_received->_blueRobots.size(); x++){
        double t = frame_received->_blueRobots[x].getOrientation().value(), newx, newy;
        char robotNumber[2];
        sprintf(robotNumber, "%d", frame_received->_blueRobots[x].robotId());
        blueText[x].setString(robotNumber);

        newx = abs(((frame_received->_blueRobots[x].getPosition().x()*1000.0)-(max_x_campo / 2.0))/((max_x_campo / 2.0)/(max_y/2.0)));
        newy = abs(((frame_received->_blueRobots[x].getPosition().y()*1000.0)-(max_y_campo / 2.0))/((max_y_campo / 2.0)/(max_x/2.0)));

        blueRobots_shape[x].setPosition(newy - robotRadius, newx - robotRadius);
        blueText[x].setPosition(newy - 40, newx - 85);

        if(frame_received->_blueRobots[x].getPosition().isValid()){
            window->draw(blueRobots_shape[x]);
            window->draw(blueText[x]);
            blueRobots_position.push_back(make_pair((int) newy/10.0, (int) newx/10.0));
        }
    }

    for(int x = 0; x < frame_received->_yellowRobots.size(); x++){
        double t = frame_received->_yellowRobots[x].getOrientation().value(), newx, newy;
        char robotNumber[2];
        sprintf(robotNumber, "%d", frame_received->_yellowRobots[x].robotId());
        yellowText[x].setString(robotNumber);

        newx = abs(((frame_received->_yellowRobots[x].getPosition().x()*1000.0)-(max_x_campo / 2.0))/((max_x_campo / 2.0)/(max_y/2.0)));
        newy = abs(((frame_received->_yellowRobots[x].getPosition().y()*1000.0)-(max_y_campo / 2.0))/((max_y_campo / 2.0)/(max_x/2.0)));

        yellowRobots_shape[x].setPosition(newy - robotRadius, newx - robotRadius);
        yellowText[x].setPosition(newy - 40, newx - 85);

        if(frame_received->_yellowRobots[x].getPosition().isValid()){
            window->draw(yellowRobots_shape[x]);
            window->draw(yellowText[x]);
            yellowRobots_position.push_back(make_pair((int) newy/10.0, (int) newx/10.0));
        }
    }
}

sf::RenderWindow *Samico::getWindow(){
    return this->window;
}

void Samico::zoomViewAt(sf::Vector2i pixel, sf::RenderWindow *window, double zoom){
    const sf::Vector2f beforeCoord{ window->mapPixelToCoords(pixel) };
    sf::View view{ window->getView() };
    view.zoom(zoom);
    window->setView(view);
    const sf::Vector2f afterCoord{ window->mapPixelToCoords(pixel) };
    const sf::Vector2f offsetCoords{ beforeCoord - afterCoord };
    view.move(offsetCoords);
    window->setView(view);
}

void Samico::setColisions(int index_at, bool isBlue){
    for(int y = 0; y < blueRobots_position.size(); y++){
        if(!isBlue || index_at != y){
            for(int i = blueRobots_position[y].first - robotRadius/5; i <= blueRobots_position[y].first + robotRadius/5; i++){
                for(int j = blueRobots_position[y].second - robotRadius/5; j <= blueRobots_position[y].second + robotRadius/5; j++){
                    mat[i][j] = false;
                }
            }
        }
    }
    for(int y = 0; y < yellowRobots_position.size(); y++){
        if(isBlue || index_at != y){
            for(int i = yellowRobots_position[y].first - robotRadius/5; i <= yellowRobots_position[y].first + robotRadius/5; i++){
                for(int j = yellowRobots_position[y].second - robotRadius/5; j <= yellowRobots_position[y].second + robotRadius/5; j++){
                    mat[i][j] = false;
                }
            }
        }
    }
}

void Samico::unsetColisions(int index_at, bool isBlue){
    for(int y = 0; y < blueRobots_position.size(); y++){
        for(int i = blueRobots_position[y].first - robotRadius/5; i <= blueRobots_position[y].first + robotRadius/5; i++){
            for(int j = blueRobots_position[y].second - robotRadius/5; j <= blueRobots_position[y].second + robotRadius/5; j++){
                mat[i][j] = true;
            }
        }
    }
    for(int y = 0; y < yellowRobots_position.size(); y++){
        for(int i = yellowRobots_position[y].first - robotRadius/5; i <= yellowRobots_position[y].first + robotRadius/5; i++){
            for(int j = yellowRobots_position[y].second - robotRadius/5; j <= yellowRobots_position[y].second + robotRadius/5; j++){
                mat[i][j] = true;
            }
        }
    }
}

void Samico::drawWindow(){
    bool moving = false;
    sf::Vector2f oldPos;
    while(window->isOpen()){
        sf::Event event;
        while(window->pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window->close();
                exit(-1);
            }
            if (event.type == sf::Event::MouseWheelScrolled){
                if (event.mouseWheelScroll.delta > 0)
                    zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, window, (1.f / zoomAmount));
                else if (event.mouseWheelScroll.delta < 0)
                    zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, window, zoomAmount);
            }
            if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == 0){
                    moving = true;
                    oldPos = window->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                }
            }
            if(event.type == sf::Event::MouseButtonReleased){
                if(event.mouseButton.button == 0){
                    moving = false;
                }
            }
            if(event.type == sf::Event::MouseMoved){
                if(moving){
                    const sf::Vector2f newPos = window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
                    const sf::Vector2f deltaPos = oldPos - newPos;
                    sf::View view = window->getView();

                    view.setCenter(view.getCenter() + deltaPos);
                    window->setView(view);

                    oldPos = window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
                }
            }
        }

        window->clear();

        // desenho das bordas do campo e do fundo
        window->draw(*fundoSamico);
        window->draw(linhasExternas, 10, sf::Lines);
        window->draw(golEsquerdo, 6, sf::Lines);
        window->draw(golDireito, 6, sf::Lines);
        window->draw(*circuloCentral);

        drawBall();
        drawRobots();
/*
        for(int x = 0; x < blueRobots_position.size(); x++){
            if(x == 0){
            setColisions(x, true);
            pathing.aStar(mat, blueRobots_position[x], ball_position, false, x);
            vector<pair<int, int>> vec = pathing.getPath(false, x);
            int sz = vec.size();
            for(int y = 0; y < sz - deslocamentoLinhas; y+=deslocamentoLinhas){
                sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f((float) vec[y].first * 10.0, (float) vec[y].second * 10.0)),
                    sf::Vertex(sf::Vector2f((float) vec[y+deslocamentoLinhas].first * 10.0, (float) vec[y+deslocamentoLinhas].second * 10.0))
                };
                line[0].color = sf::Color::Red;
                line[1].color = sf::Color::Red;
                window->draw(line, 2, sf::Lines);
            }
            unsetColisions(x, true);
            }
        }

        for(int x = 0; x < yellowRobots_position.size(); x++){
            if(x == 0){
            setColisions(x, false);
            pathing.aStar(mat, yellowRobots_position[x], ball_position, true, x);
            vector<pair<int, int>> vec = pathing.getPath(true, x);
            int sz = vec.size();
            for(int y = 0; y < sz - deslocamentoLinhas; y+=deslocamentoLinhas){
                sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f((float) vec[y].first * 10.0, (float) vec[y].second * 10.0)),
                    sf::Vertex(sf::Vector2f((float) vec[y+deslocamentoLinhas].first * 10.0, (float) vec[y+deslocamentoLinhas].second * 10.0))
                };
                line[0].color = sf::Color::Red;
                line[1].color = sf::Color::Red;
                window->draw(line, 2, sf::Lines);
            }

            unsetColisions(x, false);
            }
        }
*/
        window->display();
    }

}

void Samico::setFrame(Frame *newFrame){
    frame_received = newFrame;
}

pathPlanner Samico::getPath(){
    return pathing;
}
