#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "snowflake.h"

sf::VertexArray createFlake();
sf::VertexArray setPosition(sf::VertexArray array, sf::Vector2f pos);

int main()
{
    // cr�ation de la fen�tre
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    int currentX = 100;
    int currentDir = +1;
    // on fait tourner le programme tant que la fen�tre n'a pas �t� ferm�e
    int i = 1;
    SnowFlake* shape = new SnowFlake(i, sf::Vector2f(100,100)); 
    
    while (window.isOpen())
    {
        // on traite tous les �v�nements de la fen�tre qui ont �t� g�n�r�s depuis la derni�re it�ration de la boucle
        sf::Event event;
        while (window.pollEvent(event))
        {
            // fermeture de la fen�tre lorsque l'utilisateur le souhaite
            if (event.type == sf::Event::Closed || 
                    (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
        }

        // effacement de la fen�tre en noir
        window.clear(sf::Color::Black);

        // c'est ici qu'on dessine tout
        shape = new SnowFlake(i, sf::Vector2f(100,100)); 
        window.draw(*shape);
        sf::sleep(sf::milliseconds(2000));
        currentX += currentDir;
        if (currentX >= 600)
        {
            currentDir = -1;
        }
        else if (currentX <= 100)
        {
            currentDir = +1;
        }
        // fin de la frame courante, affichage de tout ce qu'on a dessin�
        window.display();
        i++;
        if(i > 10) {
            break;
        }
    }

    return 0;
}

sf::VertexArray setPosition(sf::VertexArray array, sf::Vector2f pos){
    for(unsigned int i = 0; i < array.getVertexCount() ; i++) {
        array[i].position.x = array[i].position.x + pos.x;
        array[i].position.y = array[i].position.y + pos.y;
    }
    return array;
}

