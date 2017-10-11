#include "EnemyLeader.h"
#include "GameWorld.h"

namespace my {

	namespace gelements {

		EnemyLeader::EnemyLeader(GameWorldPtr world, FloatRect boundaries) :
			AnimatedSprite(world->resource_factory()->leader(), false),
			m_attacking(false),
			m_sound(),
			m_boundaries(boundaries)
		{
			m_sound.setBuffer(world->resource_factory()->mistery());
			m_sound.setLoop(true);

			set(world);
			hide();			
		}

		EnemyLeader::~EnemyLeader(void)
		{
		}

		void EnemyLeader::update(Time t) {

			if(m_attacking) 
			{
				auto my_bounds = bounds();

				if( my_bounds.left > m_boundaries.width ) {
					hide();
				}
				else {
					m_me->move( m_speed.x * t.asSeconds(), 0);
				}
			}
		}

		void EnemyLeader::shot() {

		}

		void EnemyLeader::go() {
			
			m_visible = true;
			m_hittable = true;
			m_attacking = true;

			start_animation();
			m_sound.play();
		}

		void EnemyLeader::hide() {
			
			stop_animation();
			m_sound.pause();

			m_visible = false;
			m_hittable = false;
			m_attacking = false;

			m_me->setPosition(m_boundaries.left - bounds().width, m_boundaries.top);
		}

		void EnemyLeader::destroy(Destroyable* destroyer) {

			if( destroyer != nullptr ) {
				m_world->element_factory()->createNewExplosion(m_me->getPosition());

				hide();
			}
		}
	}
}