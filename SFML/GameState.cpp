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

#include "GameState.h"



GameState::GameState(GEX::StateStack& stack, State::Context context)
	: State(stack, context)
	, world_(*context.window)
	, player_(*context.player)
{}


void GameState::draw()
{
	world_.draw();
}

bool GameState::update(sf::Time dt)
{
	auto& commands = world_.getCommandQueue();
	world_.update(dt, commands);

	if (!world_.hasAlivePlayer())
	{
		player_.setMissionStatus(GEX::MissionStatus::MissionFailure);
		requestStackPush(GEX::StateID::GameOver);
	}
	else if (world_.hasPlayerReachedEnd())
	{
		player_.setMissionStatus(GEX::MissionStatus::MissionSuccess);
		requestStackPush(GEX::StateID::GameOver);
	}

	player_.handleRealtimeInput(commands);
	return true;
}

bool GameState::handleEvent(const sf::Event & event)
{
	GEX::CommandQueue& commands = world_.getCommandQueue();
	player_.handleEvent(event, commands);

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)
	{
		requestStackPop();
		requestStackPush(GEX::StateID::Menu);
	}
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::G)
	{
		requestStackPush(GEX::StateID::Gex);
	}
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		requestStackPush(GEX::StateID::Pause);
	}
	return true;
}
