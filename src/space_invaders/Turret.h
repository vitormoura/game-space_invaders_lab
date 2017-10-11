#pragma once

#include "Types.h"
#include "GameElement.h"
#include "Destroyable.h"
#include "BulletType.h"


namespace my {

	namespace gelements {

		using namespace sf;

		//Torre de tiro sob controle do jogador
		class Turret :
			public SpriteElement, public Destroyable
		{

		private:

			//Representa os estados que o canhão pode assumir
			enum States {
				moving_left,
				moving_right,
				firing,
				reloading,
				respawn,
				size
			};

			static const float DEFAULT_RELOAD_TIME;

			FloatRect	m_boundaries;
			float		m_reload_time;
			float		m_respawn_time;
			bool		m_states[States::size];
			int			m_tries;
			BulletType	m_default_bullet_type;

			Sound		m_shot_sound;

			//Recupera posição do ponto de disparo do canhão
			Vector2f	pointerPosition();

			//Remove todos os estados da última atualização
			void clearStates();

		public:
			Turret(GameWorldPtr w, FloatRect boundaries);
			~Turret();

			//Atualiza estado e animações de acordo com o estado atual
			void update(Time t);

			virtual void destroy(Destroyable* destroyer = nullptr);

			//Recupera quantidade de tentativas 
			inline int tries() const { return m_tries; }

			//Redefine o tipo de munição utilizada
			void set_bullet_type( BulletType t );

			//Dispara o canhão
			void fire();

			//Dispara rotina de recarga do canhão
			void reload();

			//Move o canhão para esquerda na velocidade padrão
			void move_left();

			//Move o canhão para direita na velocidade padrão
			void move_right();

			//Inicializa estados
			void init_states();

		};

	};

}