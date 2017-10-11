#include "Explosion.h"
#include "GameWorld.h"
#include "AnimatedSprite.h"

namespace my {

	namespace gelements {

		using namespace sf;

		Explosion::Explosion(GameWorldPtr world, Vector2f initial_pos) :
			AnimatedSprite(world->resource_factory()->explosion(), false, 3)
		{
			m_me->setPosition(initial_pos);

			m_hittable = false;
			m_visible = true;
			

			m_sound.setBuffer(world->resource_factory()->enemy_explosion());

			start_animation();
			m_sound.play();
		}

		void Explosion::stop_animation() {

			AnimatedSprite::stop_animation();
			m_visible = false;
		}

		Explosion::~Explosion()
		{
			cout << "Explosion::~Explosion" << endl;
		}
	}
}
