#include "Game.h"

Game::Game(GameParameters gameConfiguration)
{
    config = gameConfiguration;
}

void Game::initialize()
{
    // initialize random seed
    std::srand(std::time(NULL));

    defaultFont.loadFromFile("./assets/Roboto-Bold.ttf");

    menuText.setFont(defaultFont);
    menuText.setFillColor(sf::Color::Yellow);
    menuText.setString("ASTEROIDS!\n\nPRESS ENTER TO START\n\n\nArrow keys - steer ship\nSpace - shoot lasers\nPress ESC to restart\nHold ESC to quit\n\nPress F1 for debug mode\n(shows colliders)");
    menuText.setPosition(300.f, 500.f);

    scoreText.setFont(defaultFont);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(0.f, 0.f);
    scoreText.setString("Score text string");

    gameOverText.setFont(defaultFont);
    gameOverText.setFillColor(sf::Color::Yellow);
    gameOverText.setPosition(200.f, 500.f);
    gameOverText.setString("CONGRATULATIONS!\nAll the rocks are dead, now you can rest\n\nPress ESC to restart\nShow those rocks who's boss again!");

    std::fstream scoreFile;
    scoreFile.open("score.txt", std::fstream::in);
    std::string line;
    std::getline(scoreFile, line);
    std::cout << "Reading from file... " << line << "\n";
    scoreFile.close();
    previousScore = std::stof(line);

    highScoreText.setFont(defaultFont);
    highScoreText.setFillColor(sf::Color::White);
    highScoreText.setPosition(700.f, 0.f);
    highScoreText.setString("Low score: " + std::to_string(previousScore));


    if (window != nullptr)
    {
        delete window;
    }
	window = new sf::RenderWindow(sf::VideoMode(1000, 1000), "Polygons!");

    timePassed = 0.f;

    dt = 0.f;
    clock.restart();

    mousePosition = { 0.f, 0.f };
    lastMousePosition = { 0.f, 0.f };

    isQuitGameRequested = false;
    isGameStarted = false;
    isGameCompleted = false;

    fixedTimeUpdateInterval = 1.f / 60.f;
    fixedTimeUpdateAccumulator = 0.f;

    ship = std::make_shared<PlayerShip>();
    ship->m_position = { 500.f, 500.f };
    ship->m_orientation = { 0.f, -1.f };
    ship->m_velocity = { 0.f, 0.f };
    ship->m_acceleration = { 0.f, 0.f };

    collisionHelpers.clear();

    // create boulders distributed around the player ship
    int quadrantBase = 5;
    for (int i = 0; i < quadrantBase; i++)
    {
        for (int j = 0; j < quadrantBase; j++)
        {
            if ((i == j) && (quadrantBase % 2 == 1) && (i == quadrantBase / 2))
            {
                // skip center quadrant
                continue;
            }

            sf::Vector2f origin;
            origin.x = (GlobalConfig::BOUNDARY_MAX_X / quadrantBase) * i + (GlobalConfig::BOUNDARY_MAX_X / quadrantBase) / 2;
            origin.y = (GlobalConfig::BOUNDARY_MAX_Y / quadrantBase) * j + (GlobalConfig::BOUNDARY_MAX_Y / quadrantBase) / 2;

            // add a bit of offset
            float randomAngle = degToRad(rand() % 360 + 1);
            float randomDistance = rand() % 100 + 1;
            sf::Vector2f offset = randomDistance * normalize(rotateVectorByAngle({ 1.f, 0.f }, randomAngle));

			boulders.push_back(std::move(objectSpawner.createObject(GlobalConfig::OBJECTS::BOULDER, origin + offset)));
        }
    }
}

void Game::draw()
{
    // draw stuff
    window->clear();

    for (int i = 0; i < boulders.size(); i++)
    {
        window->draw(*boulders[i]);
    }

    for (int i = 0; i < bullets.size(); i++)
    {
        window->draw(*bullets[i]);
    }

    if (GlobalConfig::DEBUG_MODE)
    {
        //std::cout << "Collision helpers: " << collisionHelpers.size() << "\n";
		for (int i = 0; i < collisionHelpers.size(); i++)
		{
			window->draw(collisionHelpers[i]);
		}
    }

    window->draw(particles);

    window->draw(*ship);
    
    if (isGameStarted)
    {
        window->draw(scoreText);
        window->draw(highScoreText);
    }

    if (!isGameStarted)
    {
        window->draw(menuText);
    }
    if (isGameCompleted)
    {
        window->draw(gameOverText);
    }

    window->display();
}

void Game::run()
{
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed || isQuitGameRequested)
                window->close();
        }

        // get delta time, mouse coords
        dt = clock.restart().asSeconds();
        mousePosition = sf::Vector2f(sf::Mouse::getPosition(*window));

        // collect input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            isQuitGameRequested = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            isGameStarted = true;
        }

        if (isGameStarted)
        {
            if (!isGameCompleted)
            {
				timePassed += dt;
            }
            scoreText.setString("Score: " + std::to_string(timePassed));

            // update stuff
            GlobalConfig::update(dt);
            for (auto&& boulder : boulders)
            {
                boulder->update(dt);
            }
            for (auto&& bullet : bullets)
            {
                bullet->update(dt);
            }
            ship->update(dt);
            particles.update(dt);

            // ==========
            // collisions
            // ==========

            //std::cout << "CollisionHelpers size: " << collisionHelpers.size() << "\n";
            collisionHelpers.clear();
            std::vector<GameObject*> collisions;

            // ship and boulders
            for (int i = 0; i < boulders.size(); i++)
            {
                // broad phase test
                if (distanceBetweenPoints(ship->m_position, boulders[i]->m_position) < ship->m_radius + boulders[i]->m_radius)
                {
                    // if passed proceed with narrow phase test

                    // create minkowski difference
                    std::vector<sf::Vector2f> difference;
                    std::vector<sf::Vector2f> polygon1 = computeConvexHull(boulders[i]->m_colliderComponent.m_polygons[0]);
                    for (int it1 = 0; it1 < polygon1.size(); it1++)
                    {
                        std::vector<sf::Vector2f> polygon2 = computeConvexHull(ship->m_colliderComponent.m_polygons[0]);
                        for (int it2 = 0; it2 < polygon2.size(); it2++)
                        {
                            difference.push_back(polygon1[it1] - polygon2[it2]);
                        }
                    }
                    difference = computeConvexHull(difference);

                    if (isPointInsideConvexPolygon({ 0.f, 0.f }, difference))
                    {
                        collisions.push_back(ship.get());
                        collisions.push_back(boulders[i].get());

                        ship->collide();
                        boulders[i]->collide();
                    }
                }
            }

            // boulders

            if (boulders.size() > 1)
            {
                for (int i = 0; i < (boulders.size() - 1); i++)
                {
                    std::vector<sf::Vector2f> polygon1;
                    polygon1 = computeConvexHull(boulders[i]->m_colliderComponent.m_polygons[0]);

                    for (int j = i + 1; j < boulders.size(); j++)
                    {
                        // broad phase test
                        if (distanceBetweenPoints(boulders[i]->m_position, boulders[j]->m_position) < boulders[i]->m_radius + boulders[j]->m_radius)
                        {
                            // if passed proceed with narrow phase test

                            // create minkowski difference
                            std::vector<sf::Vector2f> difference;

                            std::vector<sf::Vector2f> polygon2;
                            polygon2 = computeConvexHull(boulders[j]->m_colliderComponent.m_polygons[0]);

                            for (int it1 = 0; it1 < polygon1.size(); it1++)
                            {
                                for (int it2 = 0; it2 < polygon2.size(); it2++)
                                {
                                    difference.push_back(polygon1[it1] - polygon2[it2]);
                                }
                            }

                            difference = computeConvexHull(difference);

                            if (isPointInsideConvexPolygon({ 0.f, 0.f }, difference))
                            {
                                collisions.push_back(boulders[i].get());
                                collisions.push_back(boulders[j].get());

                                boulders[i]->collide();
                                boulders[j]->collide();
                            }
                        }
                    }
                }
            }

            // lasers and boulders
            //std::cout << "Lasers: " << bullets.size() << "\n";
            for (int i = 0; i < bullets.size(); i++)
            {
                std::vector<sf::Vector2f> polygon1;
                polygon1 = computeConvexHull(bullets[i]->m_colliderComponent.m_polygons[0]);

                for (int j = 0; j < boulders.size(); j++)
                {
                    // broad phase test
                    if (distanceBetweenPoints(bullets[i]->m_position, boulders[j]->m_position) < bullets[i]->m_radius + boulders[j]->m_radius)
                    {
                        // if test passed proceed with narrow pahse

                        // create minkowski difference
                        std::vector<sf::Vector2f> difference;

                        std::vector<sf::Vector2f> polygon2;
                        polygon2 = computeConvexHull(boulders[j]->m_colliderComponent.m_polygons[0]);

                        for (int it1 = 0; it1 < polygon1.size(); it1++)
                        {
                            for (int it2 = 0; it2 < polygon2.size(); it2++)
                            {
                                difference.push_back(polygon1[it1] - polygon2[it2]);
                            }
                        }

                        difference = computeConvexHull(difference);

                        sf::VertexArray differenceVA = pointsToVertices(difference, sf::Color::Blue);
                        differenceVA.setPrimitiveType(sf::PrimitiveType::LineStrip);
                        collisionHelpers.push_back(differenceVA);

                        if (isPointInsideConvexPolygon({ 0.f, 0.f }, difference))
                        {
                            std::cout << "BANG BANG!\n";
                            collisions.push_back(bullets[i].get());
                            collisions.push_back(boulders[j].get());

                            bullets[i]->collide();
                            boulders[j]->collide();

                            MessageQueue::Message m;
                            m.type = MessageQueue::MessageType::EXPLOSION;
                            m.payload.position = boulders[j]->m_position;
                            m.payload.direction = boulders[j]->m_orientation;
                            MessageQueue::getInstance()->pushMessage(m);

                            if (boulders[j]->m_type == GlobalConfig::OBJECTS::BOULDER)
                            {
                                m.type = MessageQueue::MessageType::MAKE_ROCK;
                                m.payload.position = boulders[j]->m_position + 25.f * boulders[j]->m_orientation;
                                m.payload.direction = rotateVector90Left(boulders[j]->m_orientation);
                                MessageQueue::getInstance()->pushMessage(m);

                                m.payload.position = boulders[j]->m_position - 25.f * boulders[j]->m_orientation;
                                m.payload.direction = rotateVector90Right(boulders[j]->m_orientation);
                                MessageQueue::getInstance()->pushMessage(m);
                            }

                            if (boulders[j]->m_type == GlobalConfig::OBJECTS::ROCK)
                            {
                                m.type = MessageQueue::MessageType::MAKE_RUBBLE;
                                m.payload.position = boulders[j]->m_position;
                                m.payload.direction = boulders[j]->m_orientation;
                                MessageQueue::getInstance()->pushMessage(m);
                            }

                            bullets[i]->m_markedForDeath = true;
                            boulders[j]->m_markedForDeath = true;
                        }
                    }
                }
            }

            //std::cout << "Collisions: " << collisions.size() << "\n";
            for (int i = 0; i < collisions.size(); i++)
            {
                collisions[i]->m_colliderComponent.m_color = sf::Color::Red;
            }
            collisions.clear();

            // process messages
            bool empty{ false };
            while (!empty)
            {
                MessageQueue::Message currentMessage = MessageQueue::getInstance()->getMessage();
                switch (currentMessage.type)
                {
                case MessageQueue::MessageType::EMPTY:
                {
                    empty = true;
                    break;
                }
                case MessageQueue::MessageType::SHOTS_FIRED:
                {
                    bullets.push_back(objectSpawner.createObject(GlobalConfig::OBJECTS::BULLET, currentMessage.payload.position, currentMessage.payload.direction));
                    break;
                }
                case MessageQueue::MessageType::MAKE_ROCK:
                {
                    boulders.push_back(objectSpawner.createObject(GlobalConfig::OBJECTS::ROCK, currentMessage.payload.position, currentMessage.payload.direction));
                    break;
                }
                case MessageQueue::MessageType::EXPLOSION:
                {
                    for (int i = 0; i < 10; i++)
                    {
                        particles.addParticle(particleSpawner.createParticle(GlobalConfig::PARTICLES::EXPLOSION_PIXEL, currentMessage.payload.position, currentMessage.payload.direction));
                    }
                    break;
                }
                case MessageQueue::MessageType::MAKE_RUBBLE:
                {
                    for (int i = 0; i < 20; i++)
                    {
                        particles.addParticle(particleSpawner.createParticle(GlobalConfig::PARTICLES::DEBRIS_PIXEL, currentMessage.payload.position, currentMessage.payload.direction));
                    }
                    break;
                }
                }
            }

            // miscellaneous
            lastMousePosition = mousePosition;

            // cleanup
            for (int i = 0; i < boulders.size(); i++)
            {
                if (boulders[i]->m_markedForDeath)
                {
                    boulders.erase(boulders.begin() + i);
                    i--;
                }
            }

            for (int i = 0; i < bullets.size(); i++)
            {
                if (bullets[i]->m_markedForDeath)
                {
                    bullets.erase(bullets.begin() + i);
                    i--;
                }
            }

            if (boulders.size() <= 0)
            {
                isGameCompleted = true;
            }
        }

        // draw
        for (int i = 0; i < boulders.size(); i++)
        {
            boulders[i]->render();
        }
        for (int i = 0; i < bullets.size(); i++)
        {
            bullets[i]->render();
        }
        ship->render();

        draw();
    }
}

void Game::reset()
{
    initialize();
}

Game::~Game()
{
    if (isGameCompleted && timePassed < previousScore)
    {
		std::fstream scoreFile;
		scoreFile.open("score.txt", std::fstream::out);
		scoreFile << std::to_string(timePassed);
		scoreFile.close();
    }

    delete window;
}