#include "Turret.h"
#include "GameWorld.h"

namespace my {

	namespace gelements {

		const float Turret::DEFAULT_RELOAD_TIME = 1.0;

		Turret::Turret(GameWorldPtr w, FloatRect boundaries) :
			m_boundaries(boundaries),
			m_reload_time(0.0f),
			m_respawn_time(0.0f),
			m_tries(my::DEFAULT_TRIES),
			m_default_bullet_type()
		{
			m_speed.x = DEFAULT_GAME_SPEED;

			m_default_bullet_type.resistance = 1;
			m_hittable = true;
			m_world = w;

			m_me->setTexture(w->resource_factory()->turret());
			m_me->setPosition(Vector2f(m_boundaries.left, m_boundaries.top));
			
			m_shot_sound.setBuffer( w->resource_factory()->shot());

			clearStates();
		}

		void Turret::update(Time t) {

			auto cur_pos = m_me->getPosition();
			auto movement = (m_speed.x * t.asSeconds());

			if (m_states[moving_left]) {

				if ((cur_pos.x - movement) > m_boundaries.left) {
					m_me->move(movement * -1, 0);
				}

			}
			else if (m_states[moving_right]) {

				if ((cur_pos.x + movement + m_me->getLocalBounds().width) < m_boundaries.width) {
					m_me->move(movement, 0);
				}
			}

			if (m_states[firing]) {
				m_world->element_factory()->createBullet(this, pointerPosition(), my::dir::UP, m_default_bullet_type.resistance );
				m_shot_sound.play();

				reload();
			}

			if (m_states[reloading]) {
				m_reload_time -= t.asSeconds();

				if (m_reload_time <= 0.0f) {
					m_states[reloading] = false;
				}
			}

			if (m_states[respawn]) {
				m_respawn_time -= t.asSeconds();

				if (m_respawn_time <= 0.0f) {
					m_states[respawn] = false;
					m_hittable = true;
					m_visible = true;
				}
			}
		}

		void Turret::move_left() {
			m_states[moving_right] = false;
			m_states[moving_left] = true;
		}

		void Turret::move_right() {
			m_states[moving_left] = false;
			m_states[moving_right] = true;
		}

		void Turret::fire() {
			if (!m_states[reloading]) {
				m_states[firing] = true;
			}
		}

		void Turret::reload() {
			m_states[reloading] = true;
			m_states[firing] = false;
			m_reload_time = DEFAULT_RELOAD_TIME;
		}

		void Turret::set_bullet_type( BulletType t ) {
			m_default_bullet_type = t;
		}

		void Turret::destroy(Destroyable* destroyer) {

			m_hittable = false;
			m_visible = false;

			m_tries--;

			m_world->element_factory()->createNewExplosion(m_me->getPosition());

			clearStates();

			if (m_tries > 0) {

				//m_me->setFillColor(Color(255, 255, 255, 20));
				m_states[States::respawn] = true;
				m_respawn_time = DEFAULT_RELOAD_TIME * 2;
			}
			
		}

		Vector2f Turret::pointerPosition() {
			auto bounds = m_me->getLocalBounds();
			auto pos = m_me->getPosition();

			return Vector2f(pos.x + (bounds.width / 2), pos.y);
		}

		void Turret::clearStates() {
			for (size_t i = 0; i < States::size; i++) {
				m_states[i] = false;
			}
		}

		//Inicializa estados
		void Turret::init_states() {

		}

		Turret::~Turret()
		{
			std::cout << "Turret::~Turret" << std::endl;
		}
	}
}