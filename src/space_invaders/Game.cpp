#include "Game.h"
#include "GameWorld.h"
#include "MainScreen.h"

namespace my {

	Game::Game(const char* title, size_t winSize) :
		m_window(sf::VideoMode(winSize, winSize), title),
		m_global_res_factory( new ResourceFactory() ),
		m_timePerFrame(sf::seconds(1.f / DEFAULT_GAME_SPEED)),
		m_win_commands( new WindowCommandQueue(m_window))
		//m_win_commands(new NetworkCommandQueue(9595))
	{
		configScenes();
	}

	void Game::configScenes() {
				
		auto ms = MainScreenPtr(new MainScreen(this, m_global_res_factory));
		
		auto c1 = GameWorldPtr(new GameWorld(this, m_global_res_factory));
		c1->score(&m_score);
						
		m_scenes.push_back(ms);
		m_scenes.push_back(c1);		
	}

	Game::~Game()
	{
		delete m_scenes[0];		
		delete m_scenes[1];
		delete m_global_res_factory;
						
		cout << "Game::~Game" << endl;
	}
		
	void Game::run()
	{
		reset();

		m_score.reset(0, m_state.loadMaxScore());
		
		sf::Clock clock;
		sf::Time timeSinceLastUpdate = sf::Time::Zero;

		while (m_window.isOpen())
		{
			handleEvents();

			timeSinceLastUpdate += clock.restart();

			while (timeSinceLastUpdate > m_timePerFrame) {
				timeSinceLastUpdate -= m_timePerFrame;

				//handleEvents();
				handleUpdate();
			}

			handleRendering();
		}

		m_state.saveMaxScore(m_score.max());
	}

	void Game::start() {
		m_cur_scene = m_scenes[1];
		m_cur_scene->load();
	}

	void Game::reset() {
		m_cur_scene = m_scenes[0];
		m_cur_scene->load();
	}


	void Game::handleAll() {
		handleEvents();
	}

	void Game::handleUpdate() {
		m_cur_scene->update(m_timePerFrame);
	}

	void Game::handleRendering() {
		m_window.clear(sf::Color::Black);

		m_window.draw(*m_cur_scene);

		m_window.display();

		m_cur_scene->cleanUp();
	}

	void Game::end() {
		m_window.close();
	}

	void Game::handleEvents() {

		m_cur_scene->do_events();

		/*
		sf::Event event;

		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window.close();

			m_cur_scene->trigger(event);
		}
		*/
	}

}