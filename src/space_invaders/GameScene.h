#pragma once
#include "Types.h"
#include "GameElement.h"

namespace my {

	using namespace sf;
	using namespace gelements;

	class GameScene :
		public Drawable
	{		

	public:

		enum Layers {
			Background,
			Foreground,
			Size
		};

		GameScene( GamePtr game, ResourceFactoryPtr res_factory);
		
		~GameScene(void);

		//Carrega elementos da cena
		virtual void load() = 0;

		//Atualiza globalmente todos os elementos dessa cena
		virtual void update(Time time);
						
		//Dispara um evento para a cena
		virtual void do_events() = 0;

		//Limpa elementos que não fazem mais parte da lógica do jogo dentro da cena
		virtual void cleanUp() = 0;
		
		//Retorna a fábrica de recursos padrão
		inline ResourceFactoryPtr resource_factory() { return m_res_factory; }

	protected:
		
		GamePtr					m_game;

		ResourceFactoryPtr		m_res_factory;
		
		list<GameElementPtr>	m_trash;
		list<GameElementPtr>	m_elements[Layers::Size];

		//Desenha globalmente todos os elementos desse mundo
		virtual void draw(RenderTarget& target, RenderStates states) const;
	};

}