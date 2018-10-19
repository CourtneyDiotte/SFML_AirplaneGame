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
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "World.h"
#include "PlayerControl.h"
#include "Command.h"

//not using this class at the moment

namespace GEX {
	class Game
	{
	public:
		Game();
		~Game();

		void run();


	private:
		void				processInput();
		void				update(sf::Time deltaTime, CommandQueue& commands);
		void				render();
		void				updateStatistics(sf::Time deltaTime);

		

	private:
		sf::RenderWindow	window_;
		World				world_;
		PlayerControl		player_;
		sf::Text			statisticsText_;
		sf::Time			statisticsUpdateTime_;
		sf::Font			font_;
		unsigned int		statisticsNumFrames_;

		
	};
}