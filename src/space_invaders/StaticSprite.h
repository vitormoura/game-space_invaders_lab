#pragma once

#include "Types.h"
#include "GameElement.h"
#include "ResourceFactory.h"

namespace my {

	namespace gelements {

		class StaticSprite :
			public SpriteElement
		{

		public:
			StaticSprite(void);
			virtual ~StaticSprite(void);
			
			void update(Time t);
		};

	}
}
