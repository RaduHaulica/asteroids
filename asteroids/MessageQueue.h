#pragma once

#include <SFML/Graphics.hpp>



class MessageQueue
{
	static MessageQueue* m_instance;

	MessageQueue();
public:
	static enum MessageType
	{
		EMPTY,
		SHOTS_FIRED,
		MAKE_ROCK,
		MAKE_RUBBLE,
		EXPLOSION,
	};

	static struct Payload
	{
		sf::Vector2f position;
		sf::Vector2f direction;
	};

	static struct Message
	{
		MessageType type;
		Payload payload;
	};

	static std::vector<Message> m_messages;

	static MessageQueue* getInstance();

	static Message getMessage();
	static void pushMessage(Message m);
};