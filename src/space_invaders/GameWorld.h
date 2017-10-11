#pragma once

#include "Constants.h"
#include "Types.h"
#include "GameScene.h"
#include "ResourceFactory.h"

namespace my {

	using namespace std;
	using namespace sf;
	using namespace gelements;
	
	namespace gelements {

		//Representa uma fábrica de elementos de um mundo
		class ElementFactory
		{

		public:
			ElementFactory(GameWorldPtr world);
			~ElementFactory();

			InvaderPtr		createEnemy( HordePtr horde, Vector2f pos);
			HordePtr		createHorde(int largura, int altura);
			TurretPtr		createTurret();
			ExplosionPtr	createNewExplosion(Vector2f pos);
			BulletPtr		createBullet(GameElement* source, Vector2f pos, int direction, int resistance);
			SimpleTextPtr	createText(const char* msg, int fontSize, Vector2f pos);
			ShieldPtr		createShield(Vector2f pos, int largura, int altura);
			EnemyLeaderPtr	createLeader( FloatRect boundaries );
			PowerUpPtr		createPowerup( Vector2f pos );

			void			remove(GameElement* el);

		private:
			GameWorldPtr m_world;
		};
	}
	
	//Representa um mundo composto de elementos de jogo
	class GameWorld :
		public GameScene
	{

	public:
				
		enum class Regions {
			Top,
			Battlefield,
			Shields,
			Earth,
			Size
		};

	private:
		
		PlayerPtr						m_player;
						
		unique_ptr<ElementFactory>		m_elem_factory;
		map<Regions, FloatRect>			m_regions;
		Sprite							m_background;
		Score*							m_current_score;

		SimpleTextPtr					m_score_msg;
		SimpleTextPtr					m_max_score_msg;
		SimpleTextPtr					m_tries_msg;
		
	public:

		GameWorld(GamePtr game, ResourceFactoryPtr res_factory);
		~GameWorld();

				
		//Retorna uma referência para o jogador
		inline PlayerPtr player() { return m_player; }

		

		//Retorna uma fábrica capaz de criar e associar novos elementos ao mundo
		inline ElementFactory* element_factory() { return m_elem_factory.get(); }

		//Recupera limites da região desejada
		inline const FloatRect& regions(Regions r) { return m_regions[r]; }

		//Redefine o score do jogador
		inline void score(Score* score) { m_current_score = score;  }

		//Limites do mundo
		FloatRect boundaries();


		//Adiciona um novo elemento ao mundo de jogo
		void add(GameElementPtr e, Layers layer);

		//Remove o elemento do mundo
		void remove(GameElementPtr e);

		//Informa que um certo inimigo foi destruído
		void destroy(EnemyPtr e);

		//Atualiza globalmente todos os elementos desse mundo
		void update(Time time);

		//Desenha globalmente todos os elementos desse mundo
		void draw(RenderTarget& target, RenderStates states) const;
		
		//Limpa elementos que não fazem mais parte da lógica do jogo
		void cleanUp();
			
		//Inicializa elementos do mundo de jogo
		void load();

		void do_events();

	private:

		//Configura regiões padrão do mundo de jogo
		void configRegions();

		//Configura exibição dos elementos de informação do jogo
		void configMessages();

		//Verifica colisões entre elementos do jogo
		void handleColisions();
		
		//Desenha um delimitador para verificar localização das regiõoes do mundo
		void highlightRegions(RenderTarget& target) const;
	};

	

}