#pragma once
#include "Types.h"

namespace my {

	//Estabelece que um elemento pode ser destru�do
	class Destroyable
	{

	public:
				
		virtual void destroy(Destroyable* destroyer = nullptr) = 0;
	};

}

