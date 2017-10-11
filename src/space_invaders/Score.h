#pragma once

namespace my {

	//Representa um placar de pontuação de jogo
	class Score
	{
		
	public:
		Score();
		~Score();

		//Recupera pontuação atual do score
		inline int current() { return m_score; }

		//Recupera quantidade máxima de pontos já obtidos por usuários
		inline int max() { return m_max_score; }

		//Soma a quantidade de pontos informada ao total do score (atualizando a pontuação máxima se necessário)
		void add_points(int pts);

		//Redefine valores atuais de pontuação e o máximo já atingido por outros jogadores
		void reset(int current, int max);

	private:
		int	m_score;
		int	m_max_score;
	};
	
}
