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
#include "Aircraft.h"
#include <map>
#include "Projectile.h"
#include "Pickup.h"
#include "Particle.h"

namespace GEX {
	//compilation unit 
	//declaring data structures 

	struct Direction
	{
		Direction(float a, float d)
			: angle(a)
			, distance(d)
		{}

		float								angle;
		float								distance;
	};

	struct AircraftData
	{
		int										hitPoints;
		float									speed;
		TextureID								texture;
		sf::Time								fireInterval; //how frequently bullets can fire
		sf::IntRect								textureRect;
		bool									hasRollAnimation;

		std::vector<Direction>					directions;
	};

	struct ProjectileData
	{
		int										damage;
		float									speed;
		TextureID								texture;
		sf::IntRect								textureRect;
	};

	struct PickupData
	{
		std::function<void(Aircraft&)>			action;
		TextureID								texture;
		sf::IntRect								textureRect;
	};

	struct ParticleData
	{
		sf::Color								color;
		sf::Time								lifetime;
	};

	std::map<Pickup::Type, PickupData>			initializePickupData();
	std::map<AircraftType, AircraftData>		initializeAircraftData();
	std::map<Projectile::Type, ProjectileData>	initializeProjectileData();
	std::map<Particle::Type, ParticleData>		initializeParticleData();
}