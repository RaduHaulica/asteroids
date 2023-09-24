#pragma once

#include <SFML/Graphics.hpp>

#include "Utility.h"
#include "Interfaces.h"

class GameObject;

class ColliderComponent: public sf::Drawable, public Updatable
{
public:
	sf::Vector2f m_position;
	std::vector<std::vector<sf::Vector2f>> m_polygons;
	std::vector<sf::VertexArray> m_vertices;
	sf::Color m_color{ sf::Color::Green };
	GameObject* m_parent;

	ColliderComponent(GameObject* parent);

	void update(float dt);
	void collide();
	void render();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void rotate(float angle);
};