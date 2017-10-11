#pragma once

#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

#include <thread>
#include <functional>
#include <random>
#include <memory>
#include <iostream>
#include <string>
#include <map>
#include <list>
#include <deque>

namespace my {


	namespace gelements {

		class GameElement;

		template<typename T>
		class VisualGameElement;

		class RectangleElement;
		class SpriteElement;
		class TextElement;
		class Horde;
		class Shield;
		class SimpleText;
		class Turret;
		class StaticSprite;
		class AnimatedSprite;
		class Enemy;
		class Invader;
		class EnemyLeader;
		class Explosion;
		class PowerUp;
		struct BulletType;
		class Bullet;
		

		typedef StaticSprite*	StaticSpritePtr;
		typedef Turret*			TurretPtr;
		typedef Bullet*			BulletPtr;
		typedef PowerUp*		PowerUpPtr;
		typedef Shield*			ShieldPtr;
		typedef Enemy*			EnemyPtr;
		typedef Invader*		InvaderPtr;
		typedef EnemyLeader*	EnemyLeaderPtr;
		typedef Horde*			HordePtr;
		typedef Explosion*		ExplosionPtr;
		typedef SimpleText*		SimpleTextPtr;
		typedef GameElement*	GameElementPtr;
	}

	class Score;
	class StateManager;
	class ResourceFactory;
	class Destroyable;
	class GameScene;
	class MainScreen;
	class GameWorld;
	class Game;
	
	class CommandQueue;
	class InputCommand;
	class WindowCommandQueue;
	class NetworkCommandQueue;

	template<typename T>
	class Player;

	typedef Destroyable*						DestroyablePtr;
	typedef CommandQueue*						CommandQueuePtr;
	typedef WindowCommandQueue*					WindowCommandQueuePtr;
	typedef NetworkCommandQueue*				NetworkCommandQueuePtr;
	typedef Player<my::gelements::Turret>*		PlayerPtr;
	typedef Game*								GamePtr;
	typedef GameScene*							GameScenePtr;
	typedef GameWorld*							GameWorldPtr;
	typedef MainScreen*							MainScreenPtr;
	typedef ResourceFactory*					ResourceFactoryPtr;
}
