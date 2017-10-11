#pragma once
#include "Types.h"
#include "AnimatedSprite.h"
#include "Enemy.h"

namespace my {

	namespace gelements {

		class EnemyLeader :
			public AnimatedSprite, public Enemy
		{
		
		public:
			EnemyLeader(GameWorldPtr world, FloatRect boundaries);
			~EnemyLeader(void);

			void update(Time t);
						
			void shot();

			void hide();

			void go();

			virtual int value() { 
				return BONUS_ENEMY_POINTS; 
			}

			virtual void destroy(Destroyable* destroyer = nullptr);

		private:
			FloatRect	m_boundaries;
			Sound		m_sound;
			bool		m_attacking;

		};
	}
}

