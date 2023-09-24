#include "MessageQueue.h"

MessageQueue::MessageQueue()
{
	;
}

MessageQueue* MessageQueue::getInstance()
{
	if (!m_instance)
	{
		m_instance = new MessageQueue();
	}

	return m_instance;
}

MessageQueue::Message MessageQueue::getMessage()
{
	if (m_messages.size() == 0)
	{
		Payload p;
		Message m;
		m.type = MessageQueue::MessageType::EMPTY;
		m.payload = p;
		return m;
	}

	Message m = m_messages.back();
	m_messages.pop_back();
	return m;
}

void MessageQueue::pushMessage(MessageQueue::Message m)
{
	m_messages.push_back(m);
}

MessageQueue* MessageQueue::m_instance = nullptr;
std::vector<MessageQueue::Message> MessageQueue::m_messages;