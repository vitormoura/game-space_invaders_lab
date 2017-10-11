#include "Bullet.h"
#include "GameWorld.h"

namespace my  {

	namespace gelements {

		Bullet::Bullet(Vector2f initial_pos, GameElementPtr source, int direction, int resistance) :
			m_source(source),
			m_resistance(resistance)
		{
			m_hittable = true;
			m_visible = true;

			m_speed.x = my::DEFAULT_GAME_SPEED * 2;
			m_speed.y = direction;

			m_me->setSize(Vector2f(2, 2));
			m_me->setPosition(initial_pos);
			m_me->setFillColor(Color::White);
		}

		void Bullet::update(Time t) {

			//Realizando movimento padrão
			m_me->move(0.0f, (m_speed.x * m_speed.y) * t.asSeconds());

			auto my_bounds = this->bounds();
			auto world_bounds = m_world->boundaries();

			if (!world_bounds.contains(my_bounds.left, my_bounds.top)) {
				destroy();
			}

		}

		bool Bullet::hit(GameElementPtr other) {

			//Não atinge a própria origem
			if (m_hittable &&  m_source != other) {

				auto el = dynamic_cast<DestroyablePtr>(other);
								
				//E só atinge objetos capazes de serem avariados
				if (el != nullptr) {

					if (hit_test<Bullet,GameElement>(this, other)) {
												
						el->destroy(this);

						m_resistance--;

						if(m_resistance <= 0 ) {
							destroy();
						}

						return true;
					}
				}
			}

			return false;
		}

		void Bullet::destroy(Destroyable* destroyer) {

			m_visible = false;
			m_hittable = false;

			m_world->element_factory()->remove(this);
		}

		Bullet::~Bullet()
		{
			std::cout << "Bullet::~Bullet" << std::endl;
		}

	}
}