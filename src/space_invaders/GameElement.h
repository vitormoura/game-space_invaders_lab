 #pragma once

#include "Constants.h"
#include "Types.h"

namespace my {
		
	class GameWorld;
	
	namespace gelements {
	
		using namespace sf;
		using namespace std;

		template<typename T, typename K>
		bool hit_test(T* me, K* other) {
						
			if (me->hittable() && other->hittable() && (me != other)) {
								
				auto myBounds = me->bounds();
				auto otherBounds = other->bounds();

				return myBounds.intersects(otherBounds);
			}
			else
				return false;
		};
		
				
		//Representa um elemento de jogo, capaz de ser desenhado (draw) e atualizado (update)
		class GameElement :
			public Drawable
		{
										
		protected:

			//Referência do mundo a qual esse elemento está vinculado diretamente
			GameWorldPtr	m_world;

			//Velocidade de movimentação do elemento de jogo
			Vector2f	m_speed;

			//Define se o elemento de jogo pode ser alvo de colisões
			bool		m_hittable;

		public:
									
			//Recupera se o elemento é alvo de colisões
			bool hittable() const { return m_hittable; }
						
			//Limites do elemento
			virtual FloatRect bounds() {
				return FloatRect();
			}

			//Verifica se esse elemento atingiu o outro elemento informado
			virtual bool hit(GameElementPtr other) {
				return hit_test(this, other);
			}

			//Atualiza situação atual do elemento de jogo
			virtual void update(Time t) = 0;

			virtual Vector2f position() const = 0;

			//Define o mundo desse elemento de jogo
			void set(GameWorldPtr w) {
				m_world = w;
			}

			GameElement() :
				m_world(),
				m_speed(Vector2f(DEFAULT_GAME_SPEED, -1)),
				m_hittable(false)
			{
			}

			virtual ~GameElement() {

			}
		};


		//Elemento de jogo visual padrão
		template<typename T>
		class VisualGameElement :
			public GameElement
		{

		public:
			typedef VisualGameElement<T> base_type;
			
		public:
			T*		m_me;
			bool	m_visible;
			int		m_cur_state;

			VisualGameElement() :
				m_me(new T()),
				m_visible(true)
			{
			}

			//Retorna a referência para o elemento visual 
			T* get() {
				return m_me;
			}

			Vector2f position() const {
				return m_me->getPosition();
			}

			virtual FloatRect bounds() {
				return m_me->getGlobalBounds();
			}

			virtual ~VisualGameElement() {
				std::cout << "VisualGameElement::~VisualGameElement " << std::endl;
				delete m_me;
			}

		protected:

#if DEBUG_MODE
			Text	m_debug;
			string	m_debug_msg;

			void init_debug_info(ResourceFactory& res_factory) {
				m_debug.setFont(res_factory.default_font());
				m_debug.setColor(Color::White);
				m_debug.setCharacterSize(9);
			}
#endif

			//Desenha o elemento visual
			virtual void draw(RenderTarget& target, RenderStates states) const {

				if (m_visible) {
					target.draw(*m_me, states);

#if DEBUG_MODE
					target.draw(m_debug, states);
#endif	
				}
			}

		};


		//Elemento de jogo abstrato do tipo retangulo gráfico
		class RectangleElement :
			public VisualGameElement < RectangleShape >
		{
					
		};


		//Elemento de jogo abstrato do tipo Sprite (Imagem)
		class SpriteElement :
			public VisualGameElement < Sprite >
		{
			
		};

		//Elemento de jogo abstrato do tipo Texto
		class TextElement :
			public VisualGameElement < Text >
		{

		public:

			TextElement(const Font& font) {
				m_me->setFont(font);
			}
			
			void message(const string& msg) {
				m_me->setString(msg);
			}

			void update( Time t ) {
			}

		protected:
			bool	m_require_update;
			string	m_msg;
		};

	};
}