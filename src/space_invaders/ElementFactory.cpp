#include "GameWorld.h"

#include "SimpleText.h"
#include "Enemy.h"
#include "Invader.h"
#include "EnemyLeader.h"
#include "Horde.h"
#include "Turret.h"
#include "Explosion.h"
#include "Bullet.h"
#include "Shield.h"
#include "PowerUp.h"

namespace my {

namespace gelements {

		ElementFactory::ElementFactory(GameWorld* world) :
			m_world(world)
		{
		}

		SimpleTextPtr	ElementFactory::createText(const char* msg, int fontSize, Vector2f pos) {
			auto t = SimpleTextPtr(new SimpleText(m_world->resource_factory(), pos));
						
			t->get()->setCharacterSize(fontSize);
			t->message(msg);

			m_world->add(t, GameWorld::Background);

			return t;
		}

		EnemyLeaderPtr ElementFactory::createLeader( FloatRect boundaries ) {
		
			auto el = EnemyLeaderPtr(new EnemyLeader( m_world, boundaries));

			m_world->add(el, my::GameWorld::Foreground);

			return el;
		}

		HordePtr ElementFactory::createHorde(int largura, int altura) {
			auto e1 = HordePtr(new Horde(m_world, m_world->regions(my::GameWorld::Regions::Battlefield), 8, 4));

			e1->set(m_world);
			m_world->add(e1, my::GameWorld::Foreground);

			return e1;
		}

		InvaderPtr ElementFactory::createEnemy( HordePtr horde, Vector2f pos) {

			auto e =  InvaderPtr(new Invader(m_world, horde, pos));

			e->set(m_world);
			m_world->add(GameElementPtr(e), my::GameWorld::Foreground);

			return e;
		}

		TurretPtr ElementFactory::createTurret() {

			auto t = TurretPtr(new Turret(m_world, m_world->regions(GameWorld::Regions::Earth)));

			t->set(m_world);
			m_world->add(t, GameWorld::Foreground);

			return t;
		}

		ExplosionPtr ElementFactory::createNewExplosion(Vector2f pos) {

			auto e = ExplosionPtr(new Explosion(m_world, pos));

			e->set(m_world);
			m_world->add(e, GameWorld::Background);

			return e;
		}

		BulletPtr	ElementFactory::createBullet(GameElement* source, Vector2f pos, int direction, int resistance) {

			auto b = BulletPtr(new Bullet(pos, source, direction, resistance));

			b->set(m_world);
			m_world->add(b, GameWorld::Foreground);

			return b;
		}

		PowerUpPtr ElementFactory::createPowerup( Vector2f pos ) {
			auto p = PowerUpPtr( new PowerUp(m_world, pos));
			m_world->add(p, GameWorld::Foreground);

			return p;
		}
				
		///*
		ShieldPtr	ElementFactory::createShield(Vector2f pos, int largura, int altura) {
			auto s = ShieldPtr(new Shield(m_world, Vector2f(largura, altura), pos));

			s->set(m_world);
			m_world->add(s, GameWorld::Layers::Foreground);

			return s;
		}
		//*/

		void ElementFactory::remove(GameElementPtr el) {
			m_world->remove(el);
		}

		ElementFactory::~ElementFactory()
		{
		}
	}
}