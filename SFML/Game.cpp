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

#include "Game.h"
#include <stdexcept>
#include <string>


namespace {
	const sf::IntRect NO_ROLL(0, 0, 48, 64);
	const sf::IntRect ROLL_LEFT(48, 0, 48, 64);
	const sf::IntRect ROLL_RIGHT(96, 0, 48, 64);
}

namespace GEX {
	Game::Game()
		: window_(sf::VideoMode(600, 400), "PEW PEW PEW")
		, world_(window_)
		, statisticsText_()
		, statisticsUpdateTime_(sf::Time::Zero)
		, statisticsNumFrames_(0)
	{

		if (!font_.loadFromFile("Media/Sansation.ttf"))
		{
			throw std::exception("File not found");
		}

		statisticsText_.setFont(font_);
		statisticsText_.setPosition(0.0f, 0.0f);
		statisticsText_.setCharacterSize(15.f);
		statisticsText_.setString("Frames / Second = \nTime / Update =");
	}


	Game::~Game()
	{
	}

	//variable step with fixed max (Steps in time) never call update if greater than SPF 

	void Game::run()
	{
		const sf::Time SPF = sf::seconds(1.0f / 60.0f);	//seconds per frame for 60 fps
		sf::Clock clock;
		sf::Time timeSinceLastUpdate = sf::Time::Zero;
		//window_.setFramerateLimit(60);

		while (window_.isOpen())
		{

			processInput();
			timeSinceLastUpdate = clock.restart(); //not adding, now reseting


			while (timeSinceLastUpdate > SPF)
			{
				updateStatistics(SPF);
				//update(SPF);
				timeSinceLastUpdate -= SPF;
			}

			//updateStatistics(timeSinceLastUpdate);
			//update(timeSinceLastUpdate);

			render();
		}
	}

	void Game::processInput()
	{

		CommandQueue& commands = world_.getCommandQueue();
		sf::Event event;
		while (window_.pollEvent(event))
		{
			player_.handleEvent(event, commands);

			if (event.type = sf::Event::Closed)
			{
				window_.close();
			}
		}

		player_.handleRealtimeInput(commands);
	}

	void Game::update(sf::Time deltaTime, CommandQueue& commands)
	{
		world_.update(deltaTime, commands);
	}

	void Game::render()
	{
		window_.clear();
		world_.draw();

		window_.setView(window_.getDefaultView());
		window_.draw(statisticsText_);
		window_.display();

	}

	void Game::updateStatistics(sf::Time deltaTime)
	{
		statisticsUpdateTime_ += deltaTime;
		statisticsNumFrames_++;

		if (statisticsUpdateTime_ > sf::seconds(1))
		{
			statisticsText_.setString("Frames / Second = " + std::to_string(statisticsNumFrames_) + "\n" +
				"Time / Update   = " + std::to_string(statisticsUpdateTime_.asMicroseconds() / statisticsNumFrames_) + " us");

			statisticsUpdateTime_ -= sf::seconds(1);
			statisticsNumFrames_ = 0;
		}
	}

}


