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

#include "GexState.h"
#include "TextureManager.h"
#include "Utility.h"

#include "FontManager.h"
GexState::GexState(GEX::StateStack & stack, State::Context context)
	: State(stack, context)
	, backgroundSprite_()
	, pausedText_()
	, returnToMenu_()
	, returnToGame_()
	, gexState_()
{

	gexState_.setFont(GEX::FontManager::getInstance().get(GEX::FontID::Main));
	gexState_.setString("GEX State");
	gexState_.setCharacterSize(70);
	centerOrigin(gexState_);

	pausedText_.setFont(GEX::FontManager::getInstance().get(GEX::FontID::Main));
	pausedText_.setString("Game Paused");
	pausedText_.setCharacterSize(50);
	centerOrigin(pausedText_);

	returnToMenu_.setFont(GEX::FontManager::getInstance().get(GEX::FontID::Main));
	returnToMenu_.setString("Press Backspace to return to the main menu");
	centerOrigin(returnToMenu_);

	returnToGame_.setFont(GEX::FontManager::getInstance().get(GEX::FontID::Main));
	returnToGame_.setString("Press G to return to game");
	centerOrigin(returnToGame_);

	
	sf::Vector2f viewSize = context.window->getView().getSize();
	backgroundSprite_.setTexture(context.textures->get(GEX::TextureID::Face));
	centerOrigin(backgroundSprite_);
	backgroundSprite_.setPosition(viewSize.x / 2.f, viewSize.y / 2.f);
	backgroundSprite_.setColor(sf::Color(255, 255, 255, 128));

	gexState_.setPosition(0.5f * viewSize.x, 0.2f * viewSize.y);
	pausedText_.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);
	returnToMenu_.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
	returnToGame_.setPosition(0.5f * viewSize.x, 0.7f * viewSize.y);
	
}


void GexState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(100, 0, 0, 100));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundSprite_);
	window.draw(backgroundShape);
	window.draw(gexState_);
	window.draw(pausedText_);
	window.draw(returnToMenu_);
	window.draw(returnToGame_);
	
}

bool GexState::update(sf::Time dt)
{
	return false;
}

bool GexState::handleEvent(const sf::Event & event)
{
	if (event.type != sf::Event::KeyPressed)
		return false;
	else if (event.key.code == sf::Keyboard::Escape)
		requestStackPop();
	else if (event.key.code == sf::Keyboard::G)
		requestStackPop();
	else if (event.key.code == sf::Keyboard::BackSpace)
	{
		requestStackClear();
		requestStackPush(GEX::StateID::Menu);
	}

	return false;
}
