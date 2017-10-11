#include <iostream>

#include "ResourceFactory.h"

namespace my {
		
	ResourceFactory::ResourceFactory() : 
		m_default_font(nullptr),
		m_enemies_atlas(nullptr),
		m_enemy_explosion(nullptr),
		m_background(nullptr),
		m_turret(nullptr),
		m_logo(nullptr)
	{
		auto t1 = new TextureAtlas("Resources\\Sprites\\enemy_1_small_2x2.png", 40, 11, 2);
		auto t2 = new TextureAtlas("Resources\\Sprites\\explosion_s.png", 93, 24, 3);
		auto t3 = new TextureAtlas("Resources\\Sprites\\leader.png", 38, 16, 1);
		auto t4 = new TextureAtlas("Resources\\Sprites\\powerup_p.png", 32, 16, 2);
	

		m_textures.push_back(Ptr(t1));
		m_textures.push_back(Ptr(t2));
		m_textures.push_back(Ptr(t3));
		m_textures.push_back(Ptr(t4));
	}
	
	ResourceFactory::~ResourceFactory()
	{
		cout << "ResourceFactory::~ResourceFactory" << endl;
	}

	const Texture& ResourceFactory::logo() {
				
		if (m_logo == nullptr) {

			auto logo = new Texture();
			
			if (logo->loadFromFile("Resources\\Sprites\\logo.png")) {
				m_logo.reset(logo);
				std::cout << "logo: ok" << std::endl;
			}

			//m_logo.reset(logo);
		}

		return *m_logo;
	}
		
	const Texture& ResourceFactory::turret() {

		if (m_turret == nullptr) {

			auto txtTU = new Texture();
			txtTU->setRepeated(true);

			if (txtTU->loadFromFile("Resources\\Sprites\\turret.png")) {
				std::cout << "turret: ok" << std::endl;
			}

			m_turret.reset(txtTU);
		}

		return *m_turret;
	}

	const Font& ResourceFactory::default_font() {
		
		if (m_default_font == nullptr) {
			m_default_font.reset(new Font());

			
			if (m_default_font->loadFromFile( "Resources\\Fonts\\consola.ttf")) {
				std::cout << "default_font: ok" << std::endl;
			}
		}

		return *m_default_font;
	}

	const SoundBuffer& ResourceFactory::enemy_explosion() {
		
		if(m_enemy_explosion == nullptr) {
			auto snd = new SoundBuffer();
			
			if(snd->loadFromFile("Resources\\Sounds\\explosion.wav")) {
				std::cout << "enemy_explosion: ok" << std::endl;
			}
			
			m_enemy_explosion.reset(snd);
		}

		return *m_enemy_explosion.get();
	}

	const SoundBuffer& ResourceFactory::mistery() {
		
		if(m_mistery == nullptr) {
			auto snd = new SoundBuffer();
			
			if(snd->loadFromFile("Resources\\Sounds\\ufo_lowpitch.wav")) {
				std::cout << "m_mistery: ok" << std::endl;
			}
			
			m_mistery.reset(snd);
		}

		return *m_mistery.get();
	}

	const SoundBuffer& ResourceFactory::shot() {

		if(m_shot == nullptr) {
			auto snd = new SoundBuffer();
			
			if(snd->loadFromFile("Resources\\Sounds\\shoot.wav")) {
				std::cout << "m_mistery: ok" << std::endl;
			}
			
			m_shot.reset(snd);
		}

		return *m_shot.get();
	}
		
	const TextureAtlas& ResourceFactory::enemy_tp_1() {
		return *m_textures[0];
	}

	const TextureAtlas& ResourceFactory::explosion() {
		return *m_textures[1];
	}

	const TextureAtlas&  ResourceFactory::leader() {
		return *m_textures[2];
	}

	const TextureAtlas& ResourceFactory::powerup() 
	{
		return *m_textures[3];
	}

	const Texture& ResourceFactory::background() {

		if(m_background == nullptr) {
			
			auto txtBG = new Texture();
			txtBG->setRepeated(true);
						
			if(txtBG->loadFromFile("Resources\\Sprites\\background.png")) {
				std::cout << "background: ok" << std::endl;
			}

			m_background.reset(txtBG);
		}

		return *m_background;
	}
}