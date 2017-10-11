#pragma once

#include "Types.h"
#include "AnimatedSprite.h"

namespace my {

	namespace gelements {

		//Representa um explosão de um inimigo
		class Explosion :
			public AnimatedSprite
		{

		public:
			
			Explosion(GameWorldPtr world, Vector2f initial_pos);
			~Explosion();

			void stop_animation();

		private:
			Sound m_sound;
		};

	};

}