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

#include "Application.h"
#include <stdexcept>
#include "GameState.h"
#include "TitleState.h"
#include "MenuState.h"
#include "PauseState.h"
#include "GexState.h"
#include "GameOverState.h"
#include "FontManager.h"

const sf::Time Application::timePerFrame = sf::seconds(1.0f / 60.0f);	//seconds per frame for 60 fps

Application::Application()
	: window_(sf::VideoMode(1024, 768), "Killer Planes")
	, player_()
	, textures_()
	, stateStack_(GEX::State::Context(window_, textures_, player_))
	, statisticsText_()
	, statisticsUpdateTime_()
	, statisticsNumFrames_(0)
	
{
	window_.setKeyRepeatEnabled(false); //so you can't just hold down button to shoot, have to push repeatedly
	GEX::FontManager::getInstance().load(GEX::FontID::Main, "Media/Sansation.ttf");


	textures_.load(GEX::TextureID::TitleScreen, "Media/Textures/TitleScreen.png");
	textures_.load(GEX::TextureID::Face, "Media/Textures/face.png");

	statisticsText_.setFont(GEX::FontManager::getInstance().get(GEX::FontID::Main));
	statisticsText_.setPosition(0.0f, 0.0f);
	statisticsText_.setCharacterSize(15.f);
	statisticsText_.setString("Frames / Second = \nTime / Update =");

	registerStates();
	stateStack_.pushState(GEX::StateID::Title);
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window_.isOpen())
	{
		timeSinceLastUpdate += clock.restart(); //not adding, now reseting

		while (timeSinceLastUpdate > timePerFrame)
		{
			processInput();
			update(timePerFrame);

			if (stateStack_.isEmpty())
			{
				window_.close();
			}
			timeSinceLastUpdate -= timePerFrame;
			
		}
		updateStatistics(timeSinceLastUpdate);
		render();
	}
}

void Application::processInput()
{
	sf::Event event;

	while (window_.pollEvent(event))
	{
		stateStack_.handleEvent(event);

		if (event.type == sf::Event::Closed)
		{
			window_.close();
		}
	}
}

void Application::update(sf::Time deltaTime)
{
	stateStack_.update(deltaTime);
}

void Application::render()
{
	window_.clear();
	stateStack_.draw();

	window_.setView(window_.getDefaultView());
	window_.draw(statisticsText_);
	window_.display();
}

void Application::updateStatistics(sf::Time deltaTime)
{
	statisticsUpdateTime_ += deltaTime;
	statisticsNumFrames_++;

	if (statisticsUpdateTime_ >= sf::seconds(1))
	{
		statisticsText_.setString("Frames / Second = " + std::to_string(statisticsNumFrames_) + "\n" +
			"Time / Update   = " + std::to_string(statisticsUpdateTime_.asMicroseconds() / statisticsNumFrames_) + " us");

		
		statisticsNumFrames_ = 0;
		statisticsUpdateTime_ -= sf::seconds(1);
	}
}

void Application::registerStates()
{
	stateStack_.registerState<TitleState>(GEX::StateID::Title);
	stateStack_.registerState<MenuState>(GEX::StateID::Menu);
	stateStack_.registerState<GameState>(GEX::StateID::Game);
	stateStack_.registerState<PauseState>(GEX::StateID::Pause);
	stateStack_.registerState<GexState>(GEX::StateID::Gex);
	stateStack_.registerState<GEX::GameOverState>(GEX::StateID::GameOver);
}

