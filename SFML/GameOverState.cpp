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

#include "GameOverState.h"
#include "FontManager.h"
#include "Utility.h"
#include "GameState.h"

namespace GEX {
	GameOverState::GameOverState(GEX::StateStack & stack, Context context)
		: State(stack, context)
		, gameOvertext_()
		, elapsedTime_(sf::Time::Zero)
	{
		sf::Font& font = GEX::FontManager::getInstance().get(GEX::FontID::Main);
		
		sf::Vector2f windowSize(context.window->getSize());

		gameOvertext_.setFont(font);
		if (context.player->getMissionStatus() == GEX::MissionStatus::MissionFailure)
		{
			gameOvertext_.setString("Mission Failed");
		}
		else
		{
			gameOvertext_.setString("Mission Successful");
		}
		gameOvertext_.setCharacterSize(70);
		centerOrigin(gameOvertext_);
		gameOvertext_.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);
	}

	void GameOverState::draw()
	{
		sf::RenderWindow& window = *getContext().window;
		window.setView(window.getDefaultView());

		sf::RectangleShape backgroundShape;
		backgroundShape.setFillColor(sf::Color(0, 0, 0, 10));
		backgroundShape.setSize(window.getView().getSize());

		window.draw(backgroundShape);
		window.draw(gameOvertext_);
	}

	bool GameOverState::update(sf::Time dt)
	{
		const float YOU_LOST_TEXT_TIMER = 3.f;
		elapsedTime_ += dt;
		if (elapsedTime_ > sf::seconds(YOU_LOST_TEXT_TIMER))
		{
			requestStackClear();
			requestStackPush(GEX::StateID::Menu);
		}
		return false;
	}

	bool GameOverState::handleEvent(const sf::Event & event)
	{
		return false;
	}
}