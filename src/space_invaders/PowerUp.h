#pragma once
#include "Types.h"
#include "AnimatedSprite.h"
#include "Destroyable.h"


namespace my {

	namespace gelements {

		//Representa um power up para melhorar a efetividade dos disparos do jogador
		class PowerUp :
			public AnimatedSprite, public Destroyable
		{

		public:
			PowerUp(GameWorldPtr world, Vector2f initial_pos);
			~PowerUp(void);

			void update(Time t);

			void destroy(Destroyable* destroyer = nullptr);

			bool hit(GameElementPtr other);
		};

	}
}