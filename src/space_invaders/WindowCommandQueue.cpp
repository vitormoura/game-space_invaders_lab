#include "WindowCommandQueue.h"

namespace my {

	WindowCommandQueue::WindowCommandQueue(sf::Window& window) :
		m_window(window)
	{
	}

	WindowCommandQueue::~WindowCommandQueue(void)
	{
		std::cout << __FUNCTION__<< std::endl;
	}

	bool WindowCommandQueue::has_commands() {
		m_has_event = m_window.pollEvent(m_event);

		return m_has_event;
	}

	InputCommand::Actions WindowCommandQueue::next() {

		if( m_has_event )
		{
			switch ( m_event.type )
			{

				//Teclas acionadas:
			case sf::Event::KeyPressed:

				if( sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ) {
					return InputCommand::Actions::move_left;
				}

				if( sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ) {
					return InputCommand::Actions::move_right;
				}

				if( sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ) {
					return InputCommand::Actions::shot;
				}

				if( sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
					return InputCommand::Actions::start;
				}

				//Fechamento da janela:
			case sf::Event::Closed:
				return InputCommand::Actions::close;
			}
		}

		return InputCommand::Actions::unsuported;

	}

}