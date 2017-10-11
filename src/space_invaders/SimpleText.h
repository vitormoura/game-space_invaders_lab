#pragma once

#include "Types.h"
#include "GameElement.h"

namespace my {

	namespace gelements {

		using namespace sf;

		class SimpleText :
			public TextElement
		{

		public:
			SimpleText(ResourceFactoryPtr res_factory, Vector2f pos, int char_size = 10);
			~SimpleText();
		};

	};

}