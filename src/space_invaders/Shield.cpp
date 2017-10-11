#include "Shield.h"
#include "GameWorld.h"

namespace my {

	namespace gelements {

		Shield::Shield(GameWorldPtr world, Vector2f dimensions, Vector2f initial_pos)
		{
			m_world = world;
			m_hittable = true;

			m_dimensions = dimensions;
			configBlocks(initial_pos);
		}

		Shield::~Shield(void) {
			
			/*
			for( auto b : m_blocks ) {
				delete b;
			}
			*/
			cout << "Shield::~Shield" << endl;
		}

		void Shield::update(Time t) {
			for( auto b : m_blocks ) {
				b->update(t);
			}
		}

		bool Shield::hit(GameElement* other) {
			return false;
		}

		void Shield::draw(RenderTarget& target, RenderStates states) const {
			for( auto b : m_blocks ) {
				target.draw(*b, states);
			}
		}

		void Shield::configBlocks(Vector2f initial_pos) {

			int index = 0;

			for (int i = 0; i < m_dimensions.y; i++)
			{
				for (int j = 0; j < m_dimensions.x; j++)
				{
					m_blocks[index] = new ShieldBlock();
					
					m_blocks[index]->get()->setPosition( initial_pos.x + ( 10 * j ), initial_pos.y + ( 10 * i ) );	
					m_world->add(m_blocks[index], GameWorld::Layers::Foreground);
										
					index++;
				}	
			}
		}
	}
}