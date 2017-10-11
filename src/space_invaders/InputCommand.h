#pragma once

namespace my {

	//Representação abstrata de um comando disparado pelo usuário
	class InputCommand
	{

	public:

		//Ações disponíveis 
		enum Actions {

			move_left,
			move_right,
			shot,
			pause,
			
			start,
			close,
			
			unsuported,
			size
		};


	};

}