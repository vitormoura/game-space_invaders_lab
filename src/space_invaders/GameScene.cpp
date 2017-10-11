#include "GameScene.h"
#include "ResourceFactory.h"


namespace my {

	GameScene::GameScene(GamePtr game, ResourceFactoryPtr res_factory) :
		m_game(game),
		m_res_factory(res_factory)
	{
	}

	GameScene::~GameScene(void)
	{
		for (int i = 0; i < Layers::Size; i++) {
			for (auto e : m_elements[i]) {
				delete e;
			}
		}

		cout << "GameScene::~GameScene" << endl;
	}

	void GameScene::draw(RenderTarget& target, RenderStates states) const {
				
		for (int i = 0; i < Layers::Size; i++) {
			for (auto e : m_elements[i]) {
				target.draw(*e, states);
			}
		}
	}

	void GameScene::update(Time time) {
		
		for (int i = 0; i < Layers::Size; i++) {
			for (auto e : m_elements[i]) {
				e->update(time);
			}
		}
	}

}