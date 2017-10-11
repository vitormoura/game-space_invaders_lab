#include "SimpleText.h"
#include "GameWorld.h"

namespace my {

	namespace gelements {

		SimpleText::SimpleText(ResourceFactoryPtr res_factory, Vector2f pos, int char_size) :
			TextElement(res_factory->default_font())
		{
			m_visible = true;
			m_hittable = false;

			//m_me->setColor(Color::White);
			m_me->setPosition(pos);
			m_me->setCharacterSize(char_size);
		}

		SimpleText::~SimpleText()
		{
			cout << "SimpleText::~SimpleText" << endl;
		}

	}
}
