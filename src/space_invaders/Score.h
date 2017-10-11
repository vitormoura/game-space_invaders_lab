#pragma once

namespace my {

	//Representa um placar de pontua��o de jogo
	class Score
	{
		
	public:
		Score();
		~Score();

		//Recupera pontua��o atual do score
		inline int current() { return m_score; }

		//Recupera quantidade m�xima de pontos j� obtidos por usu�rios
		inline int max() { return m_max_score; }

		//Soma a quantidade de pontos informada ao total do score (atualizando a pontua��o m�xima se necess�rio)
		void add_points(int pts);

		//Redefine valores atuais de pontua��o e o m�ximo j� atingido por outros jogadores
		void reset(int current, int max);

	private:
		int	m_score;
		int	m_max_score;
	};
	
}
