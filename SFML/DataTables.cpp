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


#include "DataTables.h"

namespace GEX {
	std::map<Pickup::Type, PickupData> initializePickupData()
	{
		std::map<Pickup::Type, PickupData> data;
		
		data[Pickup::Type::HealthRefill].texture = TextureID::Entities;
		data[Pickup::Type::HealthRefill].action = [](Aircraft& a) {a.repair(25); };
		data[Pickup::Type::HealthRefill].textureRect = sf::IntRect(0, 64, 40, 40);

		data[Pickup::Type::MissileRefill].texture = TextureID::Entities;
		data[Pickup::Type::MissileRefill].action = [](Aircraft& a) {a.collectMissiles(3); };
		data[Pickup::Type::MissileRefill].textureRect = sf::IntRect(40, 64, 40, 40);

		data[Pickup::Type::FireSpread].texture = TextureID::Entities;
		data[Pickup::Type::FireSpread].action = [](Aircraft& a) {a.increaseFireSpread(); };
		data[Pickup::Type::FireSpread].textureRect = sf::IntRect(80, 64, 40, 40);

		data[Pickup::Type::FireRate].texture = TextureID::Entities;
		data[Pickup::Type::FireRate].action = [](Aircraft& a) {a.increaseFireRate(); };
		data[Pickup::Type::FireRate].textureRect = sf::IntRect(120, 64, 40, 40);



		return data;
	}

	std::map<AircraftType, AircraftData> initializeAircraftData()
	{
		std::map<AircraftType, AircraftData> data;

		data[AircraftType::Eagle].hitPoints = 100;
		data[AircraftType::Eagle].speed = 200.f;
		data[AircraftType::Eagle].texture = TextureID::Entities;
		data[AircraftType::Eagle].fireInterval = sf::seconds(1);
		data[AircraftType::Eagle].textureRect = sf::IntRect(0, 0, 48, 64);
		data[AircraftType::Eagle].hasRollAnimation = true;

		data[AircraftType::Raptor].hitPoints = 20;
		data[AircraftType::Raptor].speed = 80.f;
		data[AircraftType::Raptor].texture = TextureID::Entities;
		data[AircraftType::Raptor].fireInterval = sf::Time::Zero; //doesn't fire bullets
		data[AircraftType::Raptor].textureRect = sf::IntRect(144, 0, 84, 64);
		data[AircraftType::Raptor].hasRollAnimation = false;

		data[AircraftType::Raptor].directions.emplace_back(Direction(45.f, 80.f));
		data[AircraftType::Raptor].directions.emplace_back(Direction(-45.f, 160.f));
		data[AircraftType::Raptor].directions.emplace_back(Direction(45.f, 80.f));

		data[AircraftType::Avenger].hitPoints = 40;
		data[AircraftType::Avenger].speed = 50.f;
		data[AircraftType::Avenger].texture = TextureID::Entities;
		data[AircraftType::Avenger].fireInterval = sf::seconds(2);
		data[AircraftType::Avenger].textureRect = sf::IntRect(228, 0, 60, 59);
		data[AircraftType::Avenger].hasRollAnimation = false;

		data[AircraftType::Avenger].directions.emplace_back(Direction(45.f, 50.f));
		data[AircraftType::Avenger].directions.emplace_back(Direction(0.f, 50.f));
		data[AircraftType::Avenger].directions.emplace_back(Direction(-45.f, 100.f));
		data[AircraftType::Avenger].directions.emplace_back(Direction(0.f, 50.f));
		data[AircraftType::Avenger].directions.emplace_back(Direction(45.f, 50.f));

		return data;
	}

	std::map<Projectile::Type, ProjectileData> initializeProjectileData()
	{
		std::map<Projectile::Type, ProjectileData> data;

		data[Projectile::Type::AlliedBullet].damage = 10;
		data[Projectile::Type::AlliedBullet].speed = 300.f;
		data[Projectile::Type::AlliedBullet].texture = TextureID::Entities;
		data[Projectile::Type::AlliedBullet].textureRect = sf::IntRect(175, 64, 3, 14);

		data[Projectile::Type::EnemyBullet].damage = 10;
		data[Projectile::Type::EnemyBullet].speed = 300.f;
		data[Projectile::Type::EnemyBullet].texture = TextureID::Entities;
		data[Projectile::Type::EnemyBullet].textureRect = sf::IntRect(175, 64, 3, 14);

		data[Projectile::Type::Missile].damage = 200;
		data[Projectile::Type::Missile].speed = 200.f;
		data[Projectile::Type::Missile].texture = TextureID::Entities;
		data[Projectile::Type::Missile].textureRect = sf::IntRect(160, 64, 15, 24);



		return data;
	}

	std::map<Particle::Type, ParticleData> initializeParticleData()
	{
		std::map<Particle::Type, ParticleData> data;

		data[Particle::Type::Propellant].color = sf::Color(255, 255, 50);
		data[Particle::Type::Propellant].lifetime = sf::seconds(0.6f);

		data[Particle::Type::Smoke].color = sf::Color(50, 50, 50);
		data[Particle::Type::Smoke].lifetime = sf::seconds(4.f);


		return data;
	}
}