#include <SFML/Graphics.hpp>

class SnowFlake: public sf::Drawable {
    private:
        sf::VertexArray* vertexArray;
        void expandFlake();
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    public:
        SnowFlake(int degree, sf::Vector2f initialPos);
        void move(sf::Vector2f deltaPos);
};
