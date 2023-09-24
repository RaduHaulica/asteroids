#pragma once


#include <stdlib.h>
#include <time.h>

#include "Config.h"
#include "Utility.h"

#include "PlayerShip.h"
#include "Boulder.h"

#include "ObjectFactory.h"

#include "ParticleManager.h"
#include "ParticleFactory.h"

#include "MessageQueue.h"

class Game
{
public:
    // containers
    sf::RenderWindow* window;

    std::shared_ptr<PlayerShip> ship;
    std::vector<std::shared_ptr<GameObject>> boulders;
    std::vector<std::shared_ptr<GameObject>> bullets;

    std::vector<std::shared_ptr<GameObject>> collisions;
    std::vector<sf::VertexArray> collisionHelpers;

    ObjectFactory objectSpawner;
    ParticleFactory particleSpawner;

    ParticleManager particles;

    GameParameters config;
    float dt{ 0.f };
    sf::Clock clock;
    sf::Vector2f lastMousePosition;
    sf::Vector2f mousePosition;

    // misc game flags
    bool isQuitGameRequested;

    // update related
    float fixedTimeUpdateInterval = 1.f / 60.f;
    float fixedTimeUpdateAccumulator{ 0.f };

    Game(GameParameters gameConfiguration);
    ~Game();

    void initialize();

	void update(float dt);

    void draw();

    void run();

    void reset();
};