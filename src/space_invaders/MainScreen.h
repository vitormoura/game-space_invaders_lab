#pragma once

#include "Types.h"
#include "GameScene.h"
#include "StaticSprite.h"

namespace my {

	using namespace gelements;

	class MainScreen :
		public GameScene
	{
	
	public:
		MainScreen(GamePtr game, ResourceFactoryPtr res_factory);
		~MainScreen(void);
		
		void load();
				
		void update(Time time);
								
		void do_events();
				
		void cleanUp();


	private:
		int a;

		StaticSpritePtr	m_logo;
		StaticSpritePtr	m_background;
		SimpleTextPtr	m_pressstart_msg;

		float			m_blink_refresh;
	};

}