#pragma once

#include "Types.h"
#include "CommandQueue.h"
#include "WindowCommandQueue.h"
#include "NetworkCommandQueue.h"
#include "GameWorld.h"
#include "Score.h"
#include "StateManager.h"
#include <thread>

namespace my {
		
	using namespace sf;
	using namespace std;
		
	//Representa uma instância de jogo com uma janela própria
	class Game
	{

	private:
		RenderWindow			m_window;
		Time					m_timePerFrame;
		vector<GameScenePtr>	m_scenes;
		GameScenePtr			m_cur_scene;
		ResourceFactoryPtr		m_global_res_factory;
		Score					m_score;
		StateManager			m_state;
		CommandQueuePtr			m_win_commands;
				
		int						m_tries;
		
	public:
		
		Game( const char* title, size_t winSize );
		~Game();
		
		inline CommandQueuePtr get_player_cmds() { return dynamic_cast<CommandQueuePtr>(m_win_commands); }

		void start();

		void reset();

		//Inicia execução do jogo, aguardando fechamento da janela principal
		void run();

		void end();

		
	protected:

		
	private:
				
		void handleAll();
		void handleEvents();
		void handleRendering();
		void handleUpdate();

		void configScenes();
	};

	

}