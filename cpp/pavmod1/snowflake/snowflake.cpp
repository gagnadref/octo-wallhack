#include "snowflake.h"
#include <iostream>
#include <math.h>

SnowFlake::SnowFlake(int degree, sf::Vector2f initialPos): vertexArray(NULL) {
    vertexArray = new sf::VertexArray(sf::LinesStrip, 3);
    (*vertexArray)[0].position = initialPos + sf::Vector2f(0, 0);
    (*vertexArray)[1].position = initialPos + sf::Vector2f(100,0);
    (*vertexArray)[2].position = initialPos + sf::Vector2f(50,100*sqrt(3.0)/2.0);
    vertexArray->append((*vertexArray)[0].position);
    for(int i = 0; i < degree; i++) {
        this->expandFlake();
        //std::cout << (*vertexArray)[0].position.x << "  " << (*vertexArray)[0].position.y << std::endl;  
    }
}

void SnowFlake::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(*vertexArray, states);
}

void SnowFlake::move(sf::Vector2f deltaPos) {
}

void SnowFlake::expandFlake() {
    int vertexCount(vertexArray->getVertexCount());
    sf::VertexArray oldVertexArray = *vertexArray;
    vertexArray = new sf::VertexArray(sf::LinesStrip, 4*vertexCount);
    for (unsigned int i = 0; i < vertexCount; i++){
        sf::Vector2f pointA = oldVertexArray[i].position;
        int j = i + 1;
        if (i == vertexCount - 1) {
            j = 0;
        }
        sf::Vector2f pointB = oldVertexArray[j].position;
        sf::Vector2f diff = pointB - pointA;
        float length = sqrt(diff.x*diff.x + diff.y*diff.y); 
        sf::Vector2f unitaryDiff(diff.x/length, diff.y/length);
        sf::Vector2f ortDiff(unitaryDiff.y, -unitaryDiff.x);
        (*vertexArray)[i*4].position = pointA;
        (*vertexArray)[i*4+1].position = pointA + sf::Vector2f(unitaryDiff.x * length/3.0, unitaryDiff.y * length/3.0); 
        (*vertexArray)[i*4+2].position = pointA + sf::Vector2f(ortDiff.x * length/(2.0*sqrt(3.0)) + unitaryDiff.x * length/2.0, ortDiff.y * length/(2.0*sqrt(3.0)) + unitaryDiff.y * length/2.0);
        (*vertexArray)[i*4+3].position = pointA + sf::Vector2f(unitaryDiff.x * 2.0*length/3.0, unitaryDiff.y * 2.0*length/3.0); 
    }
}
