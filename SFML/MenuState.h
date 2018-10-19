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
#include "State.h"
#include "World.h"
#include "PlayerControl.h"
#include "CommandQueue.h"

class MenuState : public GEX::State
{
public:
	MenuState(GEX::StateStack& stack, State::Context context);
							//draw menu
	void					draw() override;
							//update
	bool					update(sf::Time dt) override;

							//handle key press events
	bool					handleEvent(const sf::Event& event) override;

							//change color of option text
	void					updateOptionText();

private:
	enum OptionNames {
		Play = 0,
		Exit
	};

	sf::Sprite				backgroundSprite_;
	std::vector<sf::Text>	options_;
	std::size_t				optionsIndex_;


	

};

