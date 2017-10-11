#include "Invader.h"
#include "GameWorld.h"
#include "Horde.h"

namespace my {

	namespace gelements {

		Invader::Invader(GameWorldPtr world, HordePtr h, Vector2f initial_pos) :
			AnimatedSprite(world->resource_factory()->enemy_tp_1(), true),
			m_horde(h),
			m_my_squad(nullptr)
		{
			m_visible = true;
			m_hittable = true;
			m_world = world;

			m_me->setPosition(initial_pos);

			start_animation();

#if DEBUG_MODE
			init_debug_info(res_factory);
#endif
		}

		void Invader::update(Time t) {
			AnimatedSprite::update(t);


#if DEBUG_MODE
			pos.x += m_me->getTextureRect().width / 4;

			m_debug_msg = to_string((int)pos.y);

			m_debug.setPosition(pos);
			m_debug.setString(m_debug_msg);
#endif
		}

		void Invader::shot() {
			auto pos = m_me->getPosition();
			pos.y += m_me->getLocalBounds().height;
			
			//TODO
			m_world->element_factory()->createBullet( this, pos, my::dir::DOWN, 1);
		}

		void Invader::destroy(Destroyable* destroyer) {
			
			m_visible = false;
			m_hittable = false;
						
			m_world->element_factory()->createNewExplosion(m_me->getPosition());
			m_horde->destroy(this);
		}

		Invader::~Invader()
		{
			std::cout << "Enemy::~Enemy" << std::endl;
		}

	}
}
