#include "GameWorld.h"
#include "Score.h"
#include "Game.h"

#include "Player.h"
#include "SimpleText.h"
#include "Enemy.h"
#include "Horde.h"
#include "Turret.h"
#include "Explosion.h"
#include "Bullet.h"
#include "Shield.h"

namespace my {

	GameWorld::GameWorld(GamePtr game, ResourceFactoryPtr res_factory) :
		GameScene(game,res_factory),
		m_elem_factory(new ElementFactory(GameWorldPtr(this)))
	{
		this->configRegions();

		m_background.setTexture(m_res_factory->background());
		m_background.setTextureRect(IntRect(0,0,400,400));
	}
	
	GameWorld::~GameWorld() {
		std::cout << "GameWorld::~GameWorld" << std::endl;
	}

	void GameWorld::do_events() {
		m_player->play();
	}

	void GameWorld::load() {
		
		for (int i = 0; i < Layers::Size; i++) {
			m_elements[i].clear();
		}

		TurretPtr t1 = element_factory()->createTurret();
		m_player = new Player<Turret>(t1, m_game->get_player_cmds());
		m_player->m_actions[ InputCommand::Actions::move_left ] = std::bind( &Turret::move_left, t1 );
		m_player->m_actions[ InputCommand::Actions::move_right ] = std::bind( &Turret::move_right, t1 );
		m_player->m_actions[ InputCommand::Actions::shot ] = std::bind( &Turret::fire, t1 );
		m_player->m_actions[InputCommand::Actions::close] = std::bind(&Game::end, m_game);
		

		element_factory()->createHorde(8, 4);

		auto s1 = element_factory()->createShield(Vector2f(m_regions[Regions::Shields].left + 80, m_regions[Regions::Shields].top), 3, 2);
		auto s2 = element_factory()->createShield(Vector2f(m_regions[Regions::Shields].left + 180, m_regions[Regions::Shields].top), 3, 2);
		auto s3 = element_factory()->createShield(Vector2f(m_regions[Regions::Shields].left + 280, m_regions[Regions::Shields].top), 3, 2);
		
		configMessages();
	}

	void GameWorld::add(GameElementPtr e, Layers layer) {
		m_elements[layer].push_back(e);
	}

	void GameWorld::remove(GameElementPtr e) {
		m_trash.push_back(e);
	}
		
	void GameWorld::destroy(EnemyPtr e) {
		
		if (m_current_score != nullptr) {

			m_current_score->add_points( e->value() );

			m_score_msg->message(to_string(m_current_score->current()));
			m_max_score_msg->message(to_string(m_current_score->max()));
		}
		
		auto ge = dynamic_cast<GameElementPtr>(e);

		if( ge != nullptr ) {
			

			m_elem_factory->createPowerup(ge->position());

			element_factory()->remove(ge);
		}
	}
	
	void GameWorld::update(Time time) {

		//Atualizando exibição da quantidade de vidas
		m_tries_msg->message(to_string( m_player->element()->tries()).c_str());

		GameScene::update(time);

		handleColisions();
	}
		
	void GameWorld::draw(RenderTarget& target, RenderStates states) const {

		#if DEBUG_MODE
		highlightRegions(target);
		#endif
				
		target.draw( m_background, states);

		GameScene::draw(target, states);
	}

	void GameWorld::handleColisions() {
		
		for( auto me : m_elements[Layers::Foreground] ) {
			for (auto other : m_elements[Layers::Foreground]) {
				me->hit(other);
			}
		}
	}
	
	void GameWorld::cleanUp() {
		
		for(auto t : m_trash ) {
						
			for( auto e = m_elements[Layers::Foreground].begin(); e != m_elements[Layers::Foreground].end(); e++ ) {
				
				if( *e == t ) {
					m_elements[Layers::Foreground].remove(t);

					delete t;
					break;
				}
			}
		}
				
		m_trash.clear();
	}
	
	void GameWorld::configRegions() {

		const int DEFAULT_WIDTH = 400;

		m_regions[Regions::Top].top = 0;
		m_regions[Regions::Top].left = 0;
		m_regions[Regions::Top].height = 50;
		m_regions[Regions::Top].width = DEFAULT_WIDTH;

		m_regions[Regions::Battlefield].top = m_regions[Regions::Top].height;
		m_regions[Regions::Battlefield].left = 0;
		m_regions[Regions::Battlefield].height = 260;
		m_regions[Regions::Battlefield].width = DEFAULT_WIDTH;

		m_regions[Regions::Shields].top = m_regions[Regions::Battlefield].height + m_regions[Regions::Battlefield].top;
		m_regions[Regions::Shields].left = 0;
		m_regions[Regions::Shields].height = 25;
		m_regions[Regions::Shields].width = DEFAULT_WIDTH;

		m_regions[Regions::Earth].top = (m_regions[Regions::Shields].height * 2) + m_regions[Regions::Shields].top;
		m_regions[Regions::Earth].left = 0;
		m_regions[Regions::Earth].height = 100;
		m_regions[Regions::Earth].width = DEFAULT_WIDTH;
	}

	void GameWorld::configMessages() {

		auto i_region = m_regions[Regions::Top];
		auto default_font_size = 12;
		auto default_padding = 10;

		int cur_score = 0;
		int max_score = 0;

		if( m_current_score != nullptr ) {
			cur_score = m_current_score->current();
			max_score = m_current_score->max();
		}

		element_factory()->createText("SCORE", default_font_size, Vector2f(i_region.left + default_padding, i_region.top + default_padding));
		element_factory()->createText("HI-SCORE", default_font_size, Vector2f(i_region.left + default_padding + (i_region.width / 2) - 50, i_region.top + default_padding));
		element_factory()->createText("TRIES", default_font_size, Vector2f(i_region.left + default_padding + (i_region.width ) - 50, i_region.top + default_padding));

		m_score_msg = element_factory()->createText( std::to_string(cur_score).c_str(), default_font_size, Vector2f(i_region.left + default_padding, i_region.top + default_font_size + default_padding));
		m_max_score_msg = element_factory()->createText( std::to_string(max_score).c_str(), default_font_size, Vector2f(i_region.left + default_padding + (i_region.width / 2) - 50, i_region.top + default_font_size + default_padding));
		m_tries_msg = element_factory()->createText( std::to_string( m_player->element()->tries() ).c_str(), default_font_size, Vector2f(i_region.left + default_padding + (i_region.width ) - 50, i_region.top + default_font_size + default_padding));
	}

	FloatRect GameWorld::boundaries() {
		return FloatRect(m_regions[Regions::Battlefield].left, m_regions[Regions::Battlefield].top, m_regions[Regions::Battlefield].width, (m_regions[Regions::Earth].top + m_regions[Regions::Earth].height));
	}

	void GameWorld::highlightRegions(RenderTarget& target) const {
		
		for ( auto p : m_regions) 
		{
			RectangleShape r;
			
			r.setPosition(p.second.left, p.second.top);
			r.setOutlineColor(Color::White);
			r.setOutlineThickness(1.0f);
			r.setFillColor(Color::Black);
			r.setSize(Vector2f(p.second.width, p.second.height));
						
			target.draw(r);
		}
	}

	
}
