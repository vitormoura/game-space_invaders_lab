#include "AnimatedSprite.h"

namespace my {

	namespace gelements {
				
		using namespace sf;

		AnimatedSprite::AnimatedSprite(const TextureAtlas& atlas, bool repeatable, int anim_speed_x) :
			m_repeatable(repeatable),
			m_running(false),
			m_cur_frame(0),
			m_wait_time(20),
			m_frame_def(atlas),
			m_animation_speed(my::DEFAULT_GAME_SPEED * anim_speed_x)
		{
		}

		FloatRect AnimatedSprite::bounds() {
			auto pos = m_me->getPosition();

			return FloatRect(pos.x, pos.y, m_frame_def.frame_size.x, m_frame_def.frame_size.y);
		}

		void AnimatedSprite::start_animation() {

			if (!m_running) {

				m_me->setTexture(*m_frame_def.texture);
				m_me->setTextureRect(IntRect(0, 0, m_frame_def.frame_size.x, m_frame_def.frame_size.y));

				m_running = true;
				m_cur_frame = 0;
			}
		}

		void AnimatedSprite::stop_animation() {

			if (m_running) {
				m_running = false;
			}
		}

		void AnimatedSprite::update(Time t) {

			if (m_running) {

				//Atualiza tempo de espera até exibição do próximo frame
				m_wait_time -= m_animation_speed * t.asSeconds();

				//Devemos atualizar ?
				if (m_wait_time <= 0) {

					//Redefinindo trecho do atlas que será exibido no sprite
					m_cur_frame++;

					if (m_cur_frame >= m_frame_def.qtd_frames) {

						if (m_repeatable)
						{
							m_cur_frame = 0;
						}
						else {
							stop_animation();
							return;
						}
					}

					m_me->setTextureRect(IntRect(m_cur_frame *  m_frame_def.frame_size.x, 0, m_frame_def.frame_size.x, m_frame_def.frame_size.y));
					m_wait_time = 20;
				}
			}
		}

		AnimatedSprite::~AnimatedSprite(void) {
		}

	}

}