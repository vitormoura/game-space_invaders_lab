#include "NetworkCommandQueue.h"

namespace my {

	NetworkCommandQueue::NetworkCommandQueue(unsigned short port) : 
		m_listener(),
		m_consumer(nullptr)
	{
		m_listener.setBlocking(true);
		m_listener.listen(9595);

		m_consumer = new std::thread(std::bind( &NetworkCommandQueue::get_commands, this ));
	}

	NetworkCommandQueue::~NetworkCommandQueue(void)
	{
		delete m_consumer;

		std::cout << __FUNCTION__<< std::endl;
	}

	bool NetworkCommandQueue::has_commands() {
		return m_actions.size() > 0;
	}

	InputCommand::Actions NetworkCommandQueue::next() {

		if( m_actions.size() > 0 )
		{
			char cmd = toupper(m_actions[0]);
			m_actions.pop_front();

			switch (cmd)
			{

			case 'A':
				return InputCommand::Actions::move_left;

			case 'D':
				return InputCommand::Actions::move_right;

			case 'W':
				return InputCommand::Actions::shot;

			case 'P':
				return InputCommand::Actions::start;
			}
		}

		return InputCommand::Actions::unsuported;
	}

	void NetworkCommandQueue::get_commands() {

		const size_t max_bytes = 1;

		char cmd[max_bytes];
		size_t bytes_readed = 0;

		while(true) {

			sf::TcpSocket client;

			if (m_listener.accept(client) == sf::Socket::Done)
			{
				while(true) {

					sf::Socket::Status status = client.receive(cmd, max_bytes, bytes_readed);

					if( status == sf::Socket::Status::Done ) {
						m_actions.push_back(*cmd);
					}
				}
			}

		}
	}
}