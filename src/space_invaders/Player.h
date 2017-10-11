#pragma once

#include "Types.h"
#include "InputCommand.h"
#include "CommandQueue.h"

namespace my {

	//Representa um jogador, remoto ou local
	template<typename T>
	class Player
	{
	
	public:
		std::function<void(void)>	m_actions[InputCommand::Actions::size];
		
		Player(T* element, CommandQueuePtr cmd_queue) :
			m_cmd_queue(cmd_queue),
			m_element(element)  {
		}

		virtual ~Player(void) {

		}
	
		T* element() { return m_element; }

		void play() {

			while(m_cmd_queue->has_commands()) {
				
				InputCommand::Actions cmd = m_cmd_queue->next();
				
				if(m_actions[cmd]) {
					m_actions[cmd]();
				}
			}
		}

	protected:
		CommandQueuePtr				m_cmd_queue;
		T*							m_element;


		
	};

}