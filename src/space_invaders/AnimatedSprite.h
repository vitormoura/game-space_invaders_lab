#pragma once

#include "Types.h"
#include "GameElement.h"
#include "ResourceFactory.h"

namespace my {

	namespace gelements {

		using namespace sf;
		
		//Representa uma animação de sprite
		class AnimatedSprite :
			public VisualGameElement < Sprite >
		{

		public:
			AnimatedSprite(const TextureAtlas& atlas, bool repeatable, int anim_speed_x = 1 );
			~AnimatedSprite(void);

			virtual void update(Time t);

			virtual FloatRect bounds();

		protected:

			//Inicia a animação
			virtual void start_animation();

			//Interrompe a animação
			virtual void stop_animation();


		private:
			const TextureAtlas&		m_frame_def;

			bool					m_repeatable;
			bool					m_running;

			int						m_cur_frame;
			float					m_wait_time;
			float					m_animation_speed;
		};
	};
}