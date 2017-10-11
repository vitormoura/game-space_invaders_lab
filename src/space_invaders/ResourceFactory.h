#pragma once

#include "Types.h"

namespace my {

	using namespace sf;
	using namespace std;
		
	//Informações sobre um atlas de sprites presentes em uma textura
	struct TextureAtlas {
				
		unique_ptr<Texture>	texture;
		Vector2f			frame_size;
		size_t				qtd_frames;

		TextureAtlas( const char* file, int w, int h, size_t qtd ) :
			texture( unique_ptr<Texture>(new Texture())),
			qtd_frames(qtd),
			frame_size( Vector2f( float( w / qtd), float(h) )) 
		{
			if(!texture->loadFromFile(file, IntRect(0,0, w,h))) {
				throw new runtime_error("Erro ao carregar atlas");
			}
		}

		TextureAtlas::~TextureAtlas() {
			cout << "TextureAtlas::~TextureAtlas" << endl;
		}
	};

	//Fabrica de recursos 
	class ResourceFactory
	{
	public:
		typedef unique_ptr<TextureAtlas> Ptr;
		
	private:
		vector<Ptr> m_textures;

		unique_ptr<SoundBuffer>		m_enemy_explosion;
		unique_ptr<SoundBuffer>		m_mistery;
		unique_ptr<SoundBuffer>		m_shot;

	public:
		
		unique_ptr<Font>			m_default_font;
		unique_ptr<Image>			m_enemies_atlas;
		unique_ptr<Texture>			m_background;
		unique_ptr<Texture>			m_turret;
		unique_ptr<Texture>			m_logo;
					
		ResourceFactory();
		~ResourceFactory();

		//Recupera fonte padrão para escrita de texto na tela de jogo
		const Font& default_font();

		//Recupera textura do player
		const Texture& turret();

		//Recupera logo do jogo
		const Texture& logo();

		//Recupera atlas de inimigos
		const TextureAtlas& enemy_tp_1();

		//Recupera atlas de um power up
		const TextureAtlas& powerup();

		//Recupera atlas de inimigos
		const TextureAtlas& explosion();

		//Recupera atlas que presenta o líder de esquadrão inimigo
		const TextureAtlas& leader();

		//Recupera buffer para um som de explosão de amigo
		const SoundBuffer& enemy_explosion();
		
		const SoundBuffer& mistery();

		//Recupera som do tiro
		const SoundBuffer& shot();

		//Recupera Textura do background
		const Texture& background();

	};

}