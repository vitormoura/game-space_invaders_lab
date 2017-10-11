#pragma once
#include "Types.h"
#include "CommandQueue.h"

namespace my {

	//Fila de comandos obtidos a partir da janela
	class WindowCommandQueue :
		public CommandQueue
	{
	
	public:
		WindowCommandQueue(sf::Window& window);
		~WindowCommandQueue(void);

		bool has_commands();
				
		InputCommand::Actions next();

	private:
		sf::Event	m_event;
		sf::Window&	m_window;
		bool		m_has_event;
	};

};
