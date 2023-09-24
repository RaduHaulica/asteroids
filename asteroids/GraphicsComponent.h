#pragma once

#include <SFML/Graphics.hpp>

#include "Utility.h"
#include "Interfaces.h"
class GameObject;

class GraphicsComponent: public sf::Drawable, public Updatable
{
public:
	sf::Sprite m_sprite;
	std::vector<std::vector<sf::Vector2f>> m_polygons;
	std::vector<sf::VertexArray> m_vertices;
	sf::Color m_color { sf::Color::White};
	GameObject* m_parent;
	sf::Vector2f m_position;

	GraphicsComponent(GameObject* parent);

	void update( float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void rotate(float angle);
};