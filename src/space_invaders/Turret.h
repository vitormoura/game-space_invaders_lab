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

			//Representa os estados que o canh�o pode assumir
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

			//Recupera posi��o do ponto de disparo do canh�o
			Vector2f	pointerPosition();

			//Remove todos os estados da �ltima atualiza��o
			void clearStates();

		public:
			Turret(GameWorldPtr w, FloatRect boundaries);
			~Turret();

			//Atualiza estado e anima��es de acordo com o estado atual
			void update(Time t);

			virtual void destroy(Destroyable* destroyer = nullptr);

			//Recupera quantidade de tentativas 
			inline int tries() const { return m_tries; }

			//Redefine o tipo de muni��o utilizada
			void set_bullet_type( BulletType t );

			//Dispara o canh�o
			void fire();

			//Dispara rotina de recarga do canh�o
			void reload();

			//Move o canh�o para esquerda na velocidade padr�o
			void move_left();

			//Move o canh�o para direita na velocidade padr�o
			void move_right();

			//Inicializa estados
			void init_states();

		};

	};

}