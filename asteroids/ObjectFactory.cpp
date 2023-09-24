#include "ObjectFactory.h"

std::unique_ptr<GameObject> ObjectFactory::createObject(GlobalConfig::OBJECTS objectType, sf::Vector2f origin, sf::Vector2f orientation)
{
	if (objectType == GlobalConfig::OBJECTS::BOULDER)
	{
		auto object = std::make_unique<Boulder>(origin);

		object->m_type = GlobalConfig::OBJECTS::BOULDER;

		object->m_position = origin;
		object->m_graphicsComponent.m_position = origin;
		object->m_colliderComponent.m_position = origin;

		float randomOrientation = degToRad(rand() % 360 + 1);
		object->m_orientation = rotateVectorByAngle({ 1.f, 0.f }, randomOrientation);
		object->m_velocity = 10.f * object->m_orientation;

		sf::Vector2f brush = { 10.f, 0.f };
		std::vector<sf::Vector2f> polygon;

		for (int i = 0; i < 8; i++)
		{
			float randomDistance = rand() % 25 + 25;
			float randomAngle = rand() % 10 - 5;

			brush = rotateVectorByAngle(brush, PI / 4.f + randomAngle);
			brush = randomDistance * normalize(brush);

			polygon.push_back(origin + brush);
		}

		polygon = computeConvexHull(polygon);
		object->m_graphicsComponent.m_polygons.push_back(polygon);
		object->m_colliderComponent.m_polygons.push_back(polygon);

		float rotationSpeed = rand() % 4 - 1.5f;
		object->m_rotationSpeed = rotationSpeed;
		
		//for (int i = 0; i < object->m_graphicsComponent.m_polygons.size(); i++)
		//{
		//	sf::VertexArray boulderVA;
		//	boulderVA.setPrimitiveType(sf::PrimitiveType::LineStrip);
		//	for (int j = 0; j < object->m_graphicsComponent.m_polygons[i].size(); j++)
		//	{
		//		boulderVA.append(sf::Vertex(object->m_graphicsComponent.m_polygons[i][j], sf::Color::White));
		//	}
		//	boulderVA.append(sf::Vertex(object->m_graphicsComponent.m_polygons[i][0], sf::Color::White));
		//	object->m_graphicsComponent.m_vertices.push_back(boulderVA);
		//	object->m_colliderComponent.m_vertices.push_back(boulderVA);
		//}

		return std::move(object);
	}

	if (objectType == GlobalConfig::OBJECTS::ROCK)
	{
		std::unique_ptr<Boulder> object = std::make_unique<Boulder>(origin);

		object->m_type = GlobalConfig::OBJECTS::ROCK;

		object->m_position = origin;
		object->m_graphicsComponent.m_position = origin;
		object->m_colliderComponent.m_position = origin;

		float randomOrientation = degToRad(rand() % 360 + 1);
		object->m_orientation = rotateVectorByAngle({ 1.f, 0.f }, randomOrientation);
		object->m_velocity = 20.f * object->m_orientation;

		sf::Vector2f brush = { 10.f, 0.f };
		std::vector<sf::Vector2f> polygon;

		for (int i = 0; i < 4; i++)
		{
			float randomDistance = rand() % 15 + 15;
			float randomAngle = rand() % 15 - 8;

			brush = rotateVectorByAngle(brush, PI / 2.f + randomAngle);
			brush = randomDistance * normalize(brush);

			polygon.push_back(origin + brush);
		}

		polygon = computeConvexHull(polygon);
		object->m_graphicsComponent.m_polygons.push_back(polygon);
		object->m_colliderComponent.m_polygons.push_back(polygon);

		float rotationSpeed = rand() % 4 - 1.5f;
		object->m_rotationSpeed = rotationSpeed;

		//for (int i = 0; i < object->m_graphicsComponent.m_polygons.size(); i++)
		//{
		//	sf::VertexArray boulderVA;
		//	boulderVA.setPrimitiveType(sf::PrimitiveType::LineStrip);
		//	for (int j = 0; j < object->m_graphicsComponent.m_polygons[i].size(); j++)
		//	{
		//		boulderVA.append(sf::Vertex(object->m_graphicsComponent.m_polygons[i][j], sf::Color::White));
		//	}
		//	boulderVA.append(sf::Vertex(object->m_graphicsComponent.m_polygons[i][0], sf::Color::White));
		//	object->m_graphicsComponent.m_vertices.push_back(boulderVA);
		//	object->m_colliderComponent.m_vertices.push_back(boulderVA);
		//}

		return std::move(object);
	}

	if (objectType == GlobalConfig::OBJECTS::BULLET)
	{
		std::unique_ptr<GameObject> object = std::make_unique<GameObject>(origin);

		object->m_type = GlobalConfig::OBJECTS::BULLET;

		object->m_maxVelocity = 500.f;

		object->m_position = origin;
		object->m_graphicsComponent.m_position = origin;
		object->m_colliderComponent.m_position = origin;

		object->m_orientation = orientation;
		object->m_velocity = 500.f * normalize(orientation);
		object->m_acceleration = { 0.f, 0.f };

		std::vector<sf::Vector2f> triangle;
		triangle.push_back({ object->m_position.x + 5.f, object->m_position.y });
		triangle.push_back({ object->m_position.x - 3.f, object->m_position.y - 3.f });
		triangle.push_back({ object->m_position.x - 3.f, object->m_position.y + 3.f });
		object->m_graphicsComponent.m_polygons.push_back(triangle);
		object->m_graphicsComponent.rotate(computeAngleBetweenVectorAndOXAxis(object->m_orientation));
		object->m_colliderComponent.m_polygons.push_back(triangle);
		object->m_colliderComponent.rotate(computeAngleBetweenVectorAndOXAxis(object->m_orientation));

		return std::move(object);
	}
}