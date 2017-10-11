#include <list>

#include "Horde.h"
#include "Invader.h"
#include "EnemyLeader.h"
#include "GameWorld.h"

namespace my {

	namespace gelements {

		Horde::Horde(GameWorldPtr world, FloatRect boundaries, int largura, int altura) :
			m_boundaries(boundaries),
			m_enemies(largura * altura),
			m_distance_to_drop(0.0f),
			m_horde_vert_pos(0.0f),
			m_squads(new vector<unique_ptr<list<InvaderPtr>>>()),
			m_reload_time(1.0),
			m_leader_attack_wait(20.0),
			m_random_dist(nullptr)
		{
			m_speed.x = DEFAULT_GAME_SPEED / 2;
			m_speed.y = dir::RIGHT;
			m_world = world;

			initEnemyHorde(world, Vector2f(m_boundaries.left, m_boundaries.top), largura, altura);
		}

		void Horde::update(Time t) {

			auto last_direction = m_speed.y;
			auto offsetY = (m_speed.x * t.asSeconds());
			auto max_height = m_horde_vert_pos;

			for (auto e : m_enemies) {

				if (!e->m_visible)
					continue;

				auto el = e->get();
				auto el_bounds = el->getLocalBounds();
				auto el_pos = el->getPosition();

				//O movimento é do tipo horizontal ?
				if (m_distance_to_drop <= 0) {

					//O primeiro inimigo que superar a borda direita...
					if (last_direction == dir::RIGHT && (el_pos.x + el_bounds.width) > m_boundaries.width) {
						m_speed.y = dir::LEFT;
					}
					//O primeiro inimigo que superar a borda esquerda, coloca a horda em modo vertical e reverte a direção do movimento horizontal
					else if (last_direction == dir::LEFT && (el_pos.x < 0)) {
						m_speed.y = dir::RIGHT;
					}

					el->move((m_speed.x * last_direction) * t.asSeconds(), 0);
				}
				//Temos um movimento vertical em curso ?
				else if (m_distance_to_drop > 0) {

					//Ainda dentro dos limites que nos permite descer
					if (m_horde_vert_pos <= m_boundaries.height) {

						//O movimento vertical é aplicado a cada um dos inimigos vão realizar o mesmo movimento 
						//de forma agrupada
						el->move(0, offsetY);
					}
					else {
						m_distance_to_drop = -1;
					}
				}

				//Atualizando 
				max_height = max(max_height, el->getPosition().y);

				e->update(t);
			}

			//Após desenhar todos os membros da horda, se a direção corrente mudou, significa que devemos iniciar um movimento vertical
			if (m_speed.y != last_direction) {
				m_distance_to_drop = 20 + Horde::DEFAULT_MARGIN;
			}
			//Em outro caso, vamos verificar se precisamos atualizar informações de deslocamento vertical
			else if (m_distance_to_drop > 0) {
				m_distance_to_drop -= offsetY;
			}

			m_horde_vert_pos = max_height;


			///*
			if (m_reload_time <= 0)
			{
				int n = (*m_random_dist)(m_random_generator);

				if (m_squads->at(n)->size() > 0)
				{
					InvaderPtr e = m_squads->at(n)->back();

					if (e->hittable()) {
						e->shot();
					}
				}

				m_reload_time = 1;
			}
			else
			{
				m_reload_time -= t.asSeconds();
			}
			//*/


			if( m_leader_attack_wait <= 0 ) {
				
				m_leader->go();
				m_leader_attack_wait = 20.0;

			} else {
				m_leader_attack_wait -= t.asSeconds();
			}
		}

		void Horde::draw(RenderTarget& target, RenderStates states) const {

		}

		bool Horde::hit(GameElement* other) {
			return false;
		}

		void Horde::destroy(InvaderPtr e) {
			
			e->get_squad()->remove(e);
			
			auto it = std::find(m_enemies.begin(), m_enemies.end(), e);

			if(it != m_enemies.end()) {
				m_enemies.erase(it);
			}

			m_world->destroy(e);
		}

		void Horde::initEnemyHorde(GameWorldPtr world, Vector2f initial_pos, int largura, int altura) {

			auto index = 0;
			auto ultPos = initial_pos;
			auto size = FloatRect();
			auto res_factory = world->resource_factory();

			//Líder da horda
			m_leader = world->element_factory()->createLeader(m_boundaries);

			//Inicializando lista de inimigos:
			for (int l = 0; l < largura; l++)
			{
				ultPos.y = initial_pos.y;

				//TODO
				m_squads->push_back(unique_ptr<list<InvaderPtr>>(new list<InvaderPtr>()));

				for (int a = 0; a < altura; a++)
				{
					auto e = world->element_factory()->createEnemy(this,ultPos);
					auto v = e->get();
					size = e->bounds();

					e->set_squad(m_squads->at(l).get());

					m_enemies[index] = e;
					m_squads->at(l)->push_back(e);

					index++;

					ultPos.y = (ultPos.y + size.height + Horde::DEFAULT_MARGIN);
				}

				ultPos.x = (ultPos.x + size.width + Horde::DEFAULT_MARGIN);
			}

			m_horde_vert_pos = ultPos.y;
			m_random_dist.reset(new std::uniform_int_distribution<int>(0, m_squads->size() - 1));

		}
				
		Horde::~Horde()
		{
			std::cout << "Horde::~Horde" << std::endl;
		}
	}
}