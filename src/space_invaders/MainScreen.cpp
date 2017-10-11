#include "MainScreen.h"
#include "ResourceFactory.h"
#include "SimpleText.h"
#include "Game.h"

namespace my {

	MainScreen::MainScreen(GamePtr game, ResourceFactoryPtr res_factory) : 
		GameScene(game, res_factory),
		m_blink_refresh(0.3f), 
		m_logo( new StaticSprite() ),
		m_background( new StaticSprite() ),
		m_pressstart_msg(nullptr)
	{
	}

	MainScreen::~MainScreen(void)
	{
		cout << "MainScreen::~MainScreen" << endl;
	}

	void MainScreen::load() {

		m_pressstart_msg = SimpleTextPtr( new SimpleText(m_res_factory, Vector2f(120,300), 15 ));
		m_pressstart_msg->message("PRESS START TO PLAY");

		Text* t = m_pressstart_msg->get();
		Sprite* s = m_logo->get();

		s->setPosition(30,100); 
		s->setTexture(m_res_factory->logo());

		Sprite* b = m_background->get();
		b->setPosition(0,0); 
		b->setTexture(m_res_factory->background());
		b->setTextureRect(IntRect(0,0,400,400));

		m_elements[Layers::Background].push_back(m_background);
		m_elements[Layers::Background].push_back(m_logo);
		m_elements[Layers::Background].push_back(m_pressstart_msg);
	}

	void MainScreen::update(Time time) {

		m_blink_refresh -= time.asSeconds();

		if( m_blink_refresh <= 0 ) {
			m_pressstart_msg->m_visible = !m_pressstart_msg->m_visible;
			m_blink_refresh = 0.3f;
		}
	}

	void MainScreen::do_events() {

		if(m_game->get_player_cmds()->has_commands()) {
			
			InputCommand::Actions act = m_game->get_player_cmds()->next();

			if( act == InputCommand::Actions::start ) {
				m_game->start();
			}
			else if ( act == InputCommand::Actions::close ) {
				m_game->end();
			}
		}
	}

	void MainScreen::cleanUp() {

	}

}