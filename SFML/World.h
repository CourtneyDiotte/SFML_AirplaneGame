/**
*
* @author Courtney Diotte
*
* @version 1.0
* *
* @section DESCRIPTION
* Aircraft shooter game
*
* @section LICENSE
* *
* Copyright 2018
* Permission to use, copy, modify, and/or distribute this software for
* any purpose with or without fee is hereby granted, provided that the
* above copyright notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
* WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
* ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
* ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
* OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*
* @section Academic Integrity
* I certify that this work is solely my own and complies with
* NBCC Academic Integrity Policy (policy 1111)
*/

#pragma once

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "SceneNode.h"
#include "SpriteNode.h"
#include "TextureManager.h"
#include "Aircraft.h"
#include "CommandQueue.h"

namespace sf {
	class RenderWindow;
}

namespace GEX 
{
	class World
	{
	public:

		explicit					World(sf::RenderWindow& window);
		void						update(sf::Time dt, CommandQueue& commands);  //update world
		void						adaptPlayerVelocity(); //adapt player's velocity to be same 
		void						adaptPlayerPosition();	//adapt player's position to within the screen bounds
		void						draw();


		CommandQueue&				getCommandQueue();	//returns command queue

	private:
		void						loadTextures();  //load textures 
		void						buildScene();	//init layers, background and players
			
						//Adds spawn points where enemies will spawn (contains aircraft type and locations)
		void						addEnemies();   
		void						addEnemy(AircraftType type, float x, float y);
		void						spawnEnemies();

		sf::FloatRect				getViewBounds() const;
		sf::FloatRect				getBattlefieldBounds() const;

		void						guideMissiles();
		void						handleCollisions();

	private:
		enum Layer
		{
			Background = 0,
			Air,
			LayerCount
		};

		struct SpawnPoint
		{
			SpawnPoint(AircraftType _type, float _relX, float _relY)
				: type(_type)
				, x(_relX)
				, y(_relY)
			{}

			AircraftType			type;
			float					x;
			float					y;
		};


	private:
		sf::RenderWindow&			window_;
		sf::View					worldView_;
		TextureManager				textures_;
		SceneNode					sceneGraph_;
		std::vector<SceneNode*>		sceneLayers_;
		sf::FloatRect				worldBounds_;
		sf::Vector2f				spawnPosition_;
		float						scrollSpeed_;
		Aircraft*					playerAircraft_;
		CommandQueue				commandQueue_;
		std::vector<SpawnPoint>		enemySpawnPoints_;
		std::vector<Aircraft*>		activeEnemies_;
	};

}

