#pragma once

namespace my {

	//Representa��o abstrata de um comando disparado pelo usu�rio
	class InputCommand
	{

	public:

		//A��es dispon�veis 
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