#pragma once
#include "GameElement.h"
#include "Destroyable.h"


#define DEFAULT_QTD_BLOCKS 6

namespace my {

	namespace gelements {

		class Shield :
			public GameElement
		{

		private:

			class ShieldBlock :
				public RectangleElement, public Destroyable {


			public:
				ShieldBlock() {
					m_me->setSize(Vector2f(10,10));
					m_me->setFillColor(Color::White);

					m_visible = true;
					m_hittable = true;
				}

				~ShieldBlock() {
					cout << "ShieldBlock::~ShieldBlock" << endl;
				}

				virtual void update(Time t) {

				}

				virtual void destroy( Destroyable* destroyer ) {
					
					m_visible = false;
					m_hittable = false;

					//m_world->element_factory()->remove(this);
				}
			};

			ShieldBlock*	m_blocks[DEFAULT_QTD_BLOCKS];
			Vector2f		m_dimensions;

		public:
			Shield(GameWorldPtr world, Vector2f dimensions, Vector2f initial_pos);
			~Shield(void);
									
			virtual void update(Time t);

			virtual bool hit(GameElement* other);

			Vector2f position() const { 
				return m_blocks[0]->position();
			}

		protected:
			
			void draw(RenderTarget& target, RenderStates states) const;
			void configBlocks( Vector2f initial_pos );
		};

	};
}

