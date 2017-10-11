#include "PowerUp.h"
#include "GameWorld.h"
#include "AnimatedSprite.h"
#include "Turret.h"

namespace my {

	namespace gelements {

		PowerUp::PowerUp(GameWorldPtr world, Vector2f initial_pos) :
			AnimatedSprite(world->resource_factory()->powerup(), true)
		{
			m_world = world;
			m_me->setPosition(initial_pos);
			m_speed.y = 1;
			m_hittable = true;

			start_animation();
		}

		PowerUp::~PowerUp(void)
		{
			std::cout << __FUNCTION__ << std::endl;
		}

		void PowerUp::update(Time t) {
			AnimatedSprite::update(t);

			//Realizando de descida
			m_me->move(0.0f, (m_speed.x * m_speed.y) * t.asSeconds());

			auto my_bounds = this->bounds();
			auto world_bounds = m_world->boundaries();

			if (!world_bounds.contains(my_bounds.left, my_bounds.top)) {
				destroy();
			}
		}

		bool PowerUp::hit(GameElementPtr other) {

			//Verificamos se o outro elemento é do tipo Turret
			TurretPtr p = dynamic_cast<TurretPtr>( other );

			if( p != nullptr ) {
								
				if(my::gelements::hit_test<PowerUp,GameElement>(this, other)) {

					//Aplicamos o efeito do PowerUp ao Turret atingido
					BulletType t;
					t.resistance = 3;

					p->set_bullet_type(t);

					destroy();
					return true;
				}
			}

			return false;
		}

			void PowerUp::destroy(Destroyable* destroyer) {
				m_visible = false;
				m_hittable = false;

				stop_animation();
				m_world->element_factory()->remove(this);
			}

		}
	}
