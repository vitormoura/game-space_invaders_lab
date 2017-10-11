#pragma once 

#include "InputCommand.h"

namespace my {

	//Representa��o de uma fila de comandos
	class CommandQueue
	{
	
	public:

		//Verifica se a fila de comandos possui novas entradas
		virtual bool has_commands() = 0;

		//Recupera pr�ximo comando da fila
		virtual InputCommand::Actions next() = 0;
	};

}