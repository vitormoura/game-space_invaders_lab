#include "Score.h"
#include <iostream>

namespace my {

	Score::Score() :
		m_score(0),
		m_max_score(0)
	{
	}

	Score::~Score()
	{
		std::cout << "Score::~Score" << std::endl;
	}

	void Score::add_points(int pts) {

		m_score += pts;

		if (m_score > m_max_score) {
			m_max_score = m_score;
		}
	}

	void Score::reset(int current, int max) {
		
		if (current > max) {
			max = current;
		}

		m_score = current;
		m_max_score = max;
	}
}


