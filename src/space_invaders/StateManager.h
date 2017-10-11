#pragma once

namespace my {

	class StateManager
	{
	
	public:
		StateManager(void);
		~StateManager(void);

		bool	saveMaxScore( int score );
		int		loadMaxScore();
	};

}