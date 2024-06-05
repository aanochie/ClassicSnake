#include "snake.hpp"

Snake::Snake() : m_body(std::list<sf::Sprite>(4))
{
    // .end() returns last body + 1 therefore -- is used to get to the last position
    // [0][1][3][4][] <- end() where as head is at [4] and tail is at [0]
    m_head = --m_body.end();
    m_tail = m_body.begin();
}


Snake::~Snake()
{
}

void Snake::Init(const sf::Texture& texture)
{
    float x = 16.f;
    for(auto& piece: m_body)
    {
        piece.setTexture(texture);
        // Playable area starts at 16, 16 where first sprite will be placed
        // Next will be at 32,16 and so on
        // Ensuring snake appears as continous body at top left corner oriented
        // horizontally
        piece.setPosition({x, 16.f});
        // x increased by 16 because all of the sprites(.png) are 16x16
        x += 16.f;
    }

}

void Snake::Move(const sf::Vector2f& direction)
{
    // tail is going to be moved to position next to head 
    m_tail->setPosition(m_head->getPosition() + direction);
    // After moving m_tail it becomes the new head of the body
    m_head = m_tail;
    // m_tail changes as it becomes the element next to old tail
    ++m_tail;

    // Reset the m_tail to begin when it reaches the end of body
    if(m_tail == m_body.end())
    {
        m_tail = m_body.begin();
    }
}

bool Snake::IsOn(const sf::Sprite& other) const
{
    // Returns if head of snake in on other sprite
    // in order to detect collision and food eating
    return other.getGlobalBounds().intersects(m_head->getGlobalBounds());
}

void Snake::Grow(const sf::Vector2f& direction)
{
    sf::Sprite newPiece;
    // To get the texture of new piece we going to get it 
    // by derefrencing the m_body
    newPiece.setTexture(*(m_body.begin()->getTexture()));
    // Allows the new piece to appear next to the position
    // of the head in the given direction
    newPiece.setPosition(m_head->getPosition() + direction);

    // Insert new sprite in the m_body
    // After add a new piece the new piece will be the head
    // therefore set the new piece as the head
    m_head = m_body.insert(++m_head, newPiece);
}

void Snake::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for(auto& piece : m_body)
    {
        target.draw(piece);
    }
}
