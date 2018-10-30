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

#include "Aircraft.h"
#include "DataTables.h"
#include "TextNode.h"
#include <string>
#include "Utility.h"
#include "CommandQueue.h"

namespace GEX {

	namespace
	{
		const std::map<AircraftType, AircraftData>	TABLE = initializeAircraftData();
	}

	Aircraft::Aircraft(AircraftType type, const TextureManager & textures)
		: Entity(TABLE.at(type).hitPoints)
		, type_(type)
		, sprite_(textures.get(TABLE.at(type).texture), TABLE.at(type).textureRect)
		, explosion_(textures.get(TextureID::Explosion))
		, showExplosion_(true)
		, healthDisplay_(nullptr)
		, missileDisplay_(nullptr)
		, travelDistance_(0.f)
		, directionIndex_(0)
		, isFiring_(false)
		, fireRateLevel_(1)
		, fireSpreadLevel_(1)
		, fireCountdown_(sf::Time::Zero)
		, fireCommand_()
		, launchMissileCommand_()
		, isLaunchingMissile_(false)
		, isMarkedForRemoval_(false)
		, spawnPickup_(false)
		, isRollAnimation_(false)
	{
		explosion_.setFrameSize(sf::Vector2f(256, 256));
		explosion_.setNumFrames(16);
		explosion_.setDuration(sf::seconds(1));

		centerOrigin(explosion_);

		// Set up commands
		fireCommand_.category = Category::AirSceneLayer;
		fireCommand_.action = [this, &textures](SceneNode& node, sf::Time dt) 
		{
			createBullets(node, textures);
		};

		launchMissileCommand_.category = Category::AirSceneLayer;
		launchMissileCommand_.action = [this, &textures](SceneNode& node, sf::Time dt)
		{
			createProjectile(node, Projectile::Type::Missile, 0.f, 0.5f, textures);
		};

		dropPickupCommand_.category = Category::AirSceneLayer;
		dropPickupCommand_.action = [this, &textures](SceneNode& node, sf::Time dt)
		{
			createPickup(node, textures);
		};


		centerOrigin(sprite_);

		std::unique_ptr<TextNode> health(new TextNode(""));

		healthDisplay_ = health.get();
		attachChild(std::move(health));
	}

	void Aircraft::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
	{
		if (isDestroyed() && showExplosion_)
			target.draw(explosion_, states);
		else
			target.draw(sprite_, states);
	}

	unsigned int Aircraft::getCategory() const
	{
		switch (type_)
		{
		case AircraftType::Eagle:
			return Category::Type::PlayerAircraft;
				break;
		default:
			return Category::Type::EnemyAircraft;
			break;

		}
	}
	void Aircraft::updateText()
	{
		healthDisplay_->setText(std::to_string(getHitPoints()) + "HP");
		healthDisplay_->setPosition(0.f, 50.f);

		healthDisplay_->setRotation(-getRotation());
	}
	void Aircraft::fireBullet()
	{
		if (TABLE.at(type_).fireInterval != sf::Time::Zero)
			isFiring_ = true;
	}
	void Aircraft::launchMissile()
	{
		isLaunchingMissile_ = true;
	}
	bool Aircraft::isAllied() const
	{
		return (type_ == AircraftType::Eagle);
	}
	void Aircraft::increaseFireRate()
	{
		if (fireRateLevel_ < 10)
			++fireRateLevel_;
	}
	void Aircraft::increaseFireSpread()
	{
		if (fireSpreadLevel_ < 3)
			++fireSpreadLevel_;
	}
	void Aircraft::collectMissiles(unsigned int count)
	{
		missileAmmo_ += count;
	}
	sf::FloatRect Aircraft::getBoundingBox() const
	{
		return getWorldTransform().transformRect(sprite_.getGlobalBounds());
	}
	bool Aircraft::isMarkedForRemoval() const
	{
		return (isDestroyed() && (explosion_.isFinished() || !showExplosion_));
	}
	void Aircraft::remove()
	{
		Entity::remove();
		showExplosion_ = false;
	}
	void Aircraft::updateRollAnimation()
	{
		if (TABLE.at(type_).hasRollAnimation)
		{
			sf::IntRect textureRect = TABLE.at(type_).textureRect;

			//Roll left
			if (getVelocity().x < 0.f)
			{
				textureRect.left += textureRect.width;
			}
			//Roll right
			else if (getVelocity().x > 0.f)
			{
				textureRect.left += (2 * textureRect.width);
			}

			sprite_.setTextureRect(textureRect);
		}
	}
	void Aircraft::updateCurrent(sf::Time dt, CommandQueue& commands)
	{
		checkProjectileLaunch(dt, commands);
		
		
		if (isDestroyed())
		{
			checkPickupDrop(commands);
			explosion_.update(dt);
			return;
		}
		updateMovementPattern(dt);
		Entity::updateCurrent(dt, commands);
		updateRollAnimation();
		updateText();
		
	}
	void Aircraft::updateMovementPattern(sf::Time dt)
	{
		//movement pattern
		const std::vector<Direction>& directions = TABLE.at(type_).directions;

		if (!directions.empty())
		{
			if (travelDistance_ > (directions[directionIndex_].distance))
			{
				directionIndex_ = (++directionIndex_) % directions.size();
				travelDistance_ = 0;
			}
			float radians = toRadian(directions[directionIndex_].angle + 90.f);
			float vx = getMaxSpeed() * std::cos(radians);
			float vy = getMaxSpeed() * std::sin(radians);

			setVelocity(vx, vy);
			travelDistance_ += getMaxSpeed() * dt.asSeconds();

		}
	}
	void Aircraft::checkPickupDrop(CommandQueue & commands)
	{
		if (!isAllied() && randomInt(1) == 0 && !spawnPickup_)
			commands.push(dropPickupCommand_);


		spawnPickup_ = true;
	}

	void Aircraft::createPickup(SceneNode & node, const TextureManager & textures) const
	{
		auto type = static_cast<Pickup::Type>(randomInt(static_cast<int>(Pickup::Type::Count)));

		std::unique_ptr<Pickup> pickup(new Pickup(type, textures));
		pickup->setPosition(getWorldPosition());
		pickup->setVelocity(0.f, 0.f);
		node.attachChild(std::move(pickup));
	}

	float Aircraft::getMaxSpeed() const
	{
		return TABLE.at(type_).speed;
	}

	void Aircraft::createBullets(SceneNode & node, const TextureManager & textures)
	{
		Projectile::Type type = isAllied() ? Projectile::Type::AlliedBullet : Projectile::Type::EnemyBullet;
		switch (fireSpreadLevel_)
		{
		case 1:
			createProjectile(node, type, 0.f, 0.5, textures);
			break;
		case 2:
			createProjectile(node, type, -0.33, 0.5, textures);
			createProjectile(node, type, +0.33, 0.5, textures);
			break;
		case 3:
			createProjectile(node, type, -0.5, 0.5, textures);
			createProjectile(node, type, 0.f, 0.5, textures);
			createProjectile(node, type, +0.5, 0.5, textures);
			break;
		}
	}

	void Aircraft::createProjectile(SceneNode & node, Projectile::Type type, float xOffset, float yOffset, 
									const TextureManager & texture)
	{
		std::unique_ptr<Projectile> projectile(new Projectile(type, texture));
		sf::Vector2f offset(xOffset * sprite_.getGlobalBounds().width, yOffset * sprite_.getGlobalBounds().height);
		sf::Vector2f velocity(0.f, projectile->getMaxSpeed());
		float sign = isAllied() ? -1.f : 1.f;

		projectile->setPosition(getWorldPosition() + offset * sign);
		projectile->setVelocity(velocity * sign);

		node.attachChild(std::move(projectile));

	}

	void Aircraft::checkProjectileLaunch(sf::Time dt, CommandQueue & commands)
	{
		//enemies are always firing
		if (!isAllied())
			fireBullet();

		if (isFiring_ && fireCountdown_ <= sf::Time::Zero)
		{
			commands.push(fireCommand_);
			fireCountdown_ += TABLE.at(type_).fireInterval / (fireRateLevel_ + 1.f);
			isFiring_ = false;
		}
		else if(fireCountdown_ > sf::Time::Zero)
		{
			fireCountdown_ -= dt;
		}

		//missile
		if (isLaunchingMissile_)
		{
			commands.push(launchMissileCommand_);
			isLaunchingMissile_ = false;
		}
	}
}
