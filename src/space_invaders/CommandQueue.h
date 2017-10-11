#pragma once 

#include "InputCommand.h"

namespace my {

	//Representação de uma fila de comandos
	class CommandQueue
	{
	
	public:

		//Verifica se a fila de comandos possui novas entradas
		virtual bool has_commands() = 0;

		//Recupera próximo comando da fila
		virtual InputCommand::Actions next() = 0;
	};

}