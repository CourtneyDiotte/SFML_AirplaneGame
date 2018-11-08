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

#include "TextureManager.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include "StateIdentifiers.h"
#include "CommandQueue.h"
#include "MusicPlayer.h"

namespace GEX {

	//forward declaration
	class StateStack;
	class PlayerControl;
	class SoundPlayer;

	class State
	{
	public:

		typedef std::unique_ptr<State> Ptr;

		struct Context 
		{
			Context(
				sf::RenderWindow& window,
				TextureManager& textures,
				PlayerControl& player,
				MusicPlayer& music,
				SoundPlayer& sound);


			sf::RenderWindow*   window;
			TextureManager*		textures;
			PlayerControl*		player;
			MusicPlayer*		music;
			SoundPlayer*		sound;
		};

	public:
								State(StateStack& stack, Context context);
		virtual					~State();

		//abstract functions
		virtual void			draw() = 0;
		virtual bool			update(sf::Time) = 0;
		virtual bool			handleEvent(const sf::Event& event) = 0;

	protected:
		void					requestStackPush(StateID stateID); //push StateID
		void					requestStackPop();	//pop StateID
		void					requestStackClear();	//clear StateID

		Context					getContext() const;	//returns context_



	private:
		StateStack*				stack_;
		Context					context_;
	};
}
