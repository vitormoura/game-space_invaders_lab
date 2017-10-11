#pragma once

#include "Types.h"
#include "Invader.h"
#include "GameElement.h"

namespace my {

	namespace gelements {

		using namespace std;
		using namespace sf;

		//Conjunto ordenado de inimigos 
		class Horde :
			public GameElement
		{

		private:
			static const int DEFAULT_MARGIN = 10;


			std::default_random_engine						m_random_generator;
			unique_ptr<std::uniform_int_distribution<int>>	m_random_dist;

			float											m_reload_time;
			float											m_leader_attack_wait;
			EnemyLeaderPtr									m_leader;
			vector<InvaderPtr>								m_enemies;
			shared_ptr<vector<unique_ptr<list<InvaderPtr>>>>	m_squads;
			FloatRect										m_boundaries;
			float											m_horde_vert_pos;
			float											m_distance_to_drop;

			void						initEnemyHorde(GameWorldPtr world, Vector2f initial_pos, int largura, int altura);

		public:
			Horde(GameWorldPtr world, FloatRect boundaries, int largura, int altura);
			~Horde();

			virtual bool hit(GameElement* other);

			//Atualiza todo o conjunto de inimigos
			void update(Time t);

			//Desenha todo o conjunto de inimigos
			void draw(RenderTarget& target, RenderStates states) const;

			//Pede para remover o inimigo 
			void destroy(InvaderPtr e);

			Vector2f position() const {
				return Vector2f( m_boundaries.left, m_boundaries.top );
			}
		};

	};
}