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
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "PlayerControl.h"
#include "TextureManager.h"
#include "StateStack.h"
#include <SFML/Graphics/Font.hpp>
#include "CommandQueue.h"
#include "SoundPlayer.h"

class Application
{
public:
						Application();

						//game loop
	void				run();


private:
						//handle event
	void				processInput();
						//update statestack
	void				update(sf::Time deltaTime);
						//render world
	void				render();
						//update stats
	void				updateStatistics(sf::Time deltaTime);
						//register state IDs
	void				registerStates();

private:
	static const sf::Time timePerFrame;
	sf::RenderWindow	  window_;

	GEX::PlayerControl    player_;
	GEX::TextureManager   textures_;
	GEX::StateStack		  stateStack_;
	GEX::MusicPlayer      music_;
	GEX::SoundPlayer      sound_;


	sf::Text			  statisticsText_;
	sf::Time			  statisticsUpdateTime_;
	unsigned int		  statisticsNumFrames_;


};

