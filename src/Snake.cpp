#include "Snake.h"

Snake::Snake() : body(std::list<sf::Sprite>(4))
{
    // Tete = fin de la liste, queue = debut de la liste
    head = --body.end();
    tail = body.begin();
}

Snake::~Snake()
{
}

void Snake::Init(const sf::Texture &texture)
{
    // Generation du serpent
    float x = 32.f;
    for (auto &piece : body)
    {
        piece.setTexture(texture);
        piece.setPosition({x, 32.f});
        x += 32.f;
    }
}

void Snake::Move(const sf::Vector2f &direction)
{
    // Maj de la position de la queue en fonction de la position de la tête
    tail->setPosition(head->getPosition() + direction);
    // Faire l'ancienne tête faire partie de la queue
    head = tail;
    // Bouge l'itérateur "tail" à l'élément suivant de la liste
    ++tail;

    // Si itérateur "tail" à la fin de "body" => reset de "tail" au début de "body"
    if (tail == body.end())
    {
        tail = body.begin();
    }
}

// Détection d'éléments
bool Snake::IsOn(const sf::Sprite &other) const
{
    return other.getGlobalBounds().intersects(head->getGlobalBounds());
}

// Allonger serpent
void Snake::Grow(const sf::Vector2f &direction)
{
    sf::Sprite newPiece;
    newPiece.setTexture(*(body.begin()->getTexture()));
    newPiece.setPosition(head->getPosition() + direction);

    head = body.insert(++head, newPiece);
}

// Detection de si le serpent intersecte avec lui-même
bool Snake::IsSelfIntersecting() const
{
    bool flag = false;

    for (auto piece = body.begin(); piece != body.end(); ++piece)
    {
        if (head != piece)
        {
            flag = IsOn(*piece);

            if (flag)
            {
                break;
            }
        }
    }

    return flag;
}

void Snake::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (auto &piece : body)
    {
        target.draw(piece);
    }
}
