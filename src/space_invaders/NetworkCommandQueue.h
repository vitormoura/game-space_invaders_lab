#pragma once
#include "Types.h"
#include "SFML\Network.hpp"
#include "CommandQueue.h"

namespace my {

	class NetworkCommandQueue : 
		public CommandQueue
	{

	public:
		NetworkCommandQueue(unsigned short port);
		~NetworkCommandQueue(void);

		bool has_commands();
				
		InputCommand::Actions next();

	private:
		sf::TcpListener		m_listener;
		std::deque<char>	m_actions; 
		std::thread*		m_consumer;

		void get_commands();
	};

}