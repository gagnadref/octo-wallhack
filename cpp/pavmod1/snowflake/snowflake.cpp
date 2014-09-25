#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

sf::VertexArray createFlake();
sf::VertexArray setPosition(sf::VertexArray array, sf::Vector2f pos);

int main()
{
    // création de la fenêtre
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    int currentX = 100;
    int currentDir = +1;
    // on fait tourner le programme tant que la fenêtre n'a pas été fermée
    while (window.isOpen())
    {
        // on traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
        sf::Event event;
        while (window.pollEvent(event))
        {
            // fermeture de la fenêtre lorsque l'utilisateur le souhaite
            if (event.type == sf::Event::Closed || 
                    (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
        }

        // effacement de la fenêtre en noir
        window.clear(sf::Color::Black);

        // c'est ici qu'on dessine tout
        sf::VertexArray newShape = createFlake();
        sf::VertexArray shape = setPosition(newShape, sf::Vector2f(currentX, 100));
        //shape.setFillColor(sf::Color::Red);
        std::cout << shape[0].position.x << std::endl;
        window.draw(shape);
        sf::sleep(sf::milliseconds(3));
        currentX += currentDir;
        if (currentX >= 600)
        {
            currentDir = -1;
        }
        else if (currentX <= 100)
        {
            currentDir = +1;
        }
        // fin de la frame courante, affichage de tout ce qu'on a dessiné
        window.display();
    }

    return 0;
}

sf::VertexArray setPosition(sf::VertexArray array, sf::Vector2f pos){
    for(unsigned int i = 0; i < array.getVertexCount() ; i++) {
        array[i].position.x = array[i].position.x + pos.x;
        array[i].position.y = array[i].position.y + pos.y;
    }
    std::cout << array[0].position.x << std::endl;
    return array;
}

sf::VertexArray flakify(sf::VertexArray convex) {
    sf::VertexArray newConvex(sf::LinesStrip, 4*convex.getVertexCount());
    for (unsigned int i = 0; i < convex.getVertexCount(); i++){
        sf::Vector2f pointA = convex[i].position;
        int j = i + 1;
        if (i == convex.getVertexCount()) {
            j = 0;
        }
        sf::Vector2f pointB = convex[j].position;
        sf::Vector2f middle = pointB-pointA;
        middle.x = middle.x/2.0;
        middle.y = middle.y/2.0;
        sf::Vector2f quarter(middle.x/3.0*2.0, middle.y/3.0*2.0);
        sf::Vector2f ortMiddle(middle.y/sqrt(2.0), -middle.x/sqrt(2.0));
        newConvex[i*4].position = pointA;
        newConvex[i*4+1].position = pointA + quarter; 
        newConvex[i*4+2].position = pointA + ortMiddle + middle; 
        newConvex[i*4+3].position = pointA + quarter + quarter;
    }
    return newConvex;
}

sf::VertexArray createFlake(){ 
    sf::VertexArray convex(sf::LinesStrip, 3);
    convex[0].position = sf::Vector2f(0, 0);
    convex[1].position = sf::Vector2f(100,0);
    convex[2].position = sf::Vector2f(50,100/sqrt(2));
    
    convex = flakify(convex);
    convex = flakify(convex);
    convex.append(convex[0].position);
    return convex;
}

