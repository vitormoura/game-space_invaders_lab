#pragma once
#include "GameElement.h"
#include "AnimatedSprite.h"
#include "Enemy.h"
#include "Destroyable.h"

namespace my {
		
	namespace gelements {

		using namespace std;
		using namespace sf;

		//Representa um invasor, o tipo de inimigo clássico
		class Invader :
			public AnimatedSprite, public Enemy 
		{

		public:
						
			Invader(GameWorldPtr world, HordePtr h, Vector2f initial_pos);
			~Invader();

			void update(Time t);

			inline list<InvaderPtr>* get_squad() const { return m_my_squad; }

			inline void set_squad(list<InvaderPtr>* squad) { m_my_squad = squad; }

			void shot();
			
			int value() { return ENEMY_POINTS; }

			virtual void destroy(Destroyable* destroyer = nullptr);

		protected:

			list<InvaderPtr>* m_my_squad;

			enum states {
				attacking,
				destroing,
				destroyed,
				size
			};

		private:
			FloatRect	m_bounds;
			HordePtr	m_horde;
		};
	}

}

