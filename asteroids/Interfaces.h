#pragma once

#include <memory>

class Body
{
public:
	virtual void collide() = 0;
};

class Updatable
{
public:
	virtual void update(float dt) = 0;
};