#pragma once
#include "Types.h"

namespace my {

	//Estabelece que um elemento pode ser destruído
	class Destroyable
	{

	public:
				
		virtual void destroy(Destroyable* destroyer = nullptr) = 0;
	};

}

