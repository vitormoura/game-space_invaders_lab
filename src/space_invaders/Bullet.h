#pragma once

#include "Types.h"
#include "GameElement.h"
#include "Destroyable.h"

namespace my {

	namespace gelements {

		//Representa um projétil disparado por inimigos ou pelo canhão
		class Bullet :
			public RectangleElement, public Destroyable
		{
					
		public:
						
			Bullet(Vector2f initial_pos, GameElementPtr source, int dir = my::dir::UP, int resistance = 1);
			virtual ~Bullet();

			void update(Time t);
			virtual bool hit(GameElementPtr other);
			virtual void destroy(Destroyable* destroyer = nullptr);

		private:
			GameElementPtr	m_source;
			int				m_resistance;
		};
	};
}

