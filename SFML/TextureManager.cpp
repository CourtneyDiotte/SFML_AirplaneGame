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

#include "TextureManager.h"
#include <stdexcept>
#include <cassert>

namespace GEX {
	TextureManager::TextureManager()
	{
	}


	TextureManager::~TextureManager()
	{
	}

	void GEX::TextureManager::load(TextureID id, const std::string & path)
	{
		//smrt pointer wrapping sf::texture object
		std::unique_ptr<sf::Texture> texture(new sf::Texture());

		if (!texture->loadFromFile(path))
		{
			throw std::runtime_error("Texture load failed " + path);
		}
		//unique pointer requires move, cant copy
		auto rc = textures_.insert(std::make_pair(id, std::move(texture)));
		assert(rc.second);  //when compiling for debug, asserting rc.second is true - if not, it crashes

	}

	sf::Texture& TextureManager::get(TextureID id) const
	{
		auto found = textures_.find(id);

		//assert(found != textures_.end());
		if (found == textures_.end())
		{
			throw std::exception("Didn't find texture");
		}

		return *(found->second); //dereferences pointer to give object its pointing to
	}
}
