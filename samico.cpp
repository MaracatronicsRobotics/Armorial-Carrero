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

Samico::Samico(){

    // fundo do samico
    fundoSamico = new sf::RectangleShape(sf::Vector2f((float) max_x, (float) max_y));
    fundoSamico->setFillColor(sf::Color(0, 100, 0, 255));

    /* circulo central */
    circuloCentral = new sf::CircleShape(centralCirleRadius);
    circuloCentral->setFillColor(sf::Color(0, 0, 0, 0));
    circuloCentral->setOutlineThickness(10.f);
    circuloCentral->setOutlineColor(sf::Color(255, 255, 255, 255));
    circuloCentral->setPointCount(circlePrecision);
    circuloCentral->setPosition((max_x/2.0) - centralCirleRadius, (max_y/2.0) - centralCirleRadius);

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
    }
}

void Samico::drawRobots(){
    char direct[30];

    for(int x = 0; x < frame_received->_blueRobots.size(); x++){
        double t = frame_received->_blueRobots[x].getOrientation().value(), newx, newy;

        // carregando imagem para sprite e setando a textura
        sprintf(direct, "../textures/b%d.png\0", frame_received->_blueRobots[x].robotId());
        if(!texture.loadFromFile(direct)){
            printf("Error loading texture.\n");
            exit(-1);
        }
        sprite.setTexture(texture);
        sprite.setScale(0.43,0.43);

        // calculando novo x e y para representação do cliente grafico
        newx = abs(((frame_received->_blueRobots[x].getPosition().x()*1000.0)-(max_x_campo / 2.0))/((max_x_campo / 2.0)/(max_y/2.0)));
        newy = abs(((frame_received->_blueRobots[x].getPosition().y()*1000.0)-(max_y_campo / 2.0))/((max_y_campo / 2.0)/(max_x/2.0)));

        // setando dados para a sprite
        sprite.setPosition(newy, newx);
        sprite.setOrigin(256,256);
        sprite.setRotation(-0-(t*57.2958));

        if(frame_received->_blueRobots[x].getPosition().isValid()){ // se o frame for valido, desenha
            window->draw(sprite);
        }
    }

    for(int x = 0; x < frame_received->_yellowRobots.size(); x++){
        double t = frame_received->_yellowRobots[x].getOrientation().value(), newx, newy;

        // carregando imagem para sprite e setando a textura
        sprintf(direct, "../textures/y%d.png\0", frame_received->_blueRobots[x].robotId());
        if(!texture.loadFromFile(direct)){
            printf("Error loading texture.\n");
            exit(-1);
        }
        sprite.setTexture(texture);
        sprite.setScale(0.43,0.43);

        // calculando novo x e y para representação do cliente grafico
        newx = abs(((frame_received->_yellowRobots[x].getPosition().x()*1000.0)-(max_x_campo / 2.0))/((max_x_campo / 2.0)/(max_y/2.0)));
        newy = abs(((frame_received->_yellowRobots[x].getPosition().y()*1000.0)-(max_y_campo / 2.0))/((max_y_campo / 2.0)/(max_x/2.0)));

        // setando dados para a sprite
        sprite.setPosition(newy, newx);
        sprite.setOrigin(256,256);
        sprite.setRotation(-0-(t*57.2958));

        if(frame_received->_yellowRobots[x].getPosition().isValid()){ // se o frame for valido, desenha
            window->draw(sprite);
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

        // desenho das bolas e dos robos
        drawBall();
        drawRobots();

        window->display();
    }

}

void Samico::setFrame(Frame *newFrame){
    frame_received = newFrame;
}