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
#include <SFML/System/Vector2.hpp>
#include "Animation.h"

namespace sf
{
	class Sprite;
	class Text;
}



void									centerOrigin(sf::Sprite& sprite);	//center sprite origin
void									centerOrigin(sf::Text& text);		//center text origin
void									centerOrigin(GEX::Animation& animation); //center animation origin

//Degree/radian conversion
float									toDegree(float radian);
float									toRadian(float degree);

//random number generation
int										randomInt(int exclusiveMax);


//vector operations
float									length(sf::Vector2f vector);
sf::Vector2f							unitVector(sf::Vector2f vector);


