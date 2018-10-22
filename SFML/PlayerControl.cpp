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

#include "PlayerControl.h"
#include "Aircraft.h"
#include "Command.h"
#include <functional>

namespace GEX {

	struct AircraftMover
	{
		AircraftMover(float vx, float vy)
			: velocity(vx, vy)
		{}

		void operator()(Aircraft& aircraft, sf::Time dt) const
		{
			aircraft.accelerate(velocity);
		}

		sf::Vector2f velocity;
	};
	struct AircraftRotator
	{
		AircraftRotator(float value)
		{}

		void operator()(Aircraft& aircraft, sf::Time dt) const
		{
			aircraft.rotate(value);
		}

		float value;
	};


	PlayerControl::PlayerControl()
		: currentMissionStatus_(MissionStatus::MissionRunning)
	{
		//set up bindings
		keyBindings_[sf::Keyboard::Right] = Action::MoveRight;
		keyBindings_[sf::Keyboard::Left] = Action::MoveLeft;
		keyBindings_[sf::Keyboard::Up] = Action::MoveUp;
		keyBindings_[sf::Keyboard::Down] = Action::MoveDown;

		keyBindings_[sf::Keyboard::R] = Action::RotateRight;
		keyBindings_[sf::Keyboard::L] = Action::RotateLeft;

		keyBindings_[sf::Keyboard::Space] = Action::FireBullet;
		keyBindings_[sf::Keyboard::M] = Action::LaunchMissile;



		//set up action bindings
		initializeActions();

		/*actionBindings_[Action::MoveLeft].category = Category::PlayerAircraft;
		actionBindings_[Action::MoveRight].category = Category::PlayerAircraft;
		actionBindings_[Action::MoveUp].category = Category::PlayerAircraft;
		actionBindings_[Action::MoveDown].category = Category::PlayerAircraft;
		actionBindings_[Action::RotateLeft].category = Category::EnemyAircraft;
		actionBindings_[Action::RotateRight].category = Category::EnemyAircraft;*/

		for(auto& pair : actionBindings_)
		{
			pair.second.category = Category::PlayerAircraft;
		}
	}
	void PlayerControl::handleEvent(const sf::Event& event, CommandQueue& commands)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			auto found = keyBindings_.find(event.key.code);
			if(found != keyBindings_.end())
			{
				commands.push(actionBindings_[found->second]);
			}
		}
	}
	void PlayerControl::handleRealtimeInput(CommandQueue& commands)
	{
		//traverse all assigned keys, look up the action, generate the command
		for (auto pair : keyBindings_)
		{
			if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
			{
				commands.push(actionBindings_[pair.second]);
			}
			
		}
	}
	void PlayerControl::setMissionStatus(MissionStatus status)
	{
		currentMissionStatus_ = status;
	}

	MissionStatus PlayerControl::getMissionStatus() const
	{
		return currentMissionStatus_;
	}

	void PlayerControl::initializeActions()
	{
		const float playerSpeed = 200.f;

		actionBindings_[Action::MoveLeft].action = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f));
		actionBindings_[Action::MoveRight].action = derivedAction<Aircraft>(AircraftMover(+playerSpeed, 0.f));
		actionBindings_[Action::MoveUp].action = derivedAction<Aircraft>(AircraftMover(0.f, -playerSpeed));
		actionBindings_[Action::MoveDown].action = derivedAction<Aircraft>(AircraftMover(0.f, +playerSpeed));

		actionBindings_[Action::FireBullet].action = derivedAction<Aircraft>(std::bind(&Aircraft::fireBullet, std::placeholders::_1));
		actionBindings_[Action::LaunchMissile].action = derivedAction<Aircraft>(std::bind(&Aircraft::launchMissile, std::placeholders::_1));
		

		/*actionBindings_[Action::RotateRight].action = derivedAction<Aircraft>(AircraftRotator(+1.f));
		actionBindings_[Action::RotateLeft].action = derivedAction<Aircraft>(AircraftRotator(-1.f));*/

	}

	bool PlayerControl::isRealtimeAction(Action action)
	{
		switch (action)
		{//if any are being used, return true
		case Action::MoveLeft:
		case Action::MoveRight:
		case Action::MoveUp:
		case Action::MoveDown:
		case Action::RotateRight:
		case Action::RotateLeft:
		case Action::FireBullet:
			return true;
			break;
		default:
			return false;
			break;
		}
	}
}
