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


#include "EmitterNode.h"
#include "Command.h"
#include "CommandQueue.h"
#include "ParticleNode.h"

namespace GEX {
	EmitterNode::EmitterNode(Particle::Type type)
		: SceneNode()
		, accumulatedTime_(sf::Time::Zero)
	    , type_(type)
	    , particleSystem_(nullptr)
	{}

	void EmitterNode::updateCurrent(sf::Time dt, CommandQueue & commands)
	{
		if (particleSystem_)
		{
			emitParticle(dt);
		}
		else
		{
			auto finder = [this](ParticleNode& container, sf::Time dt) {
				if (container.getParticleType() == type_)
				{
					particleSystem_ = &container;
				}
			};
			Command command;
			command.category = Category::Type::ParticleSystem;
			command.action = derivedAction<ParticleNode>(finder);

			commands.push(command);
		}
	}

	void EmitterNode::emitParticle(sf::Time dt)
	{
		const float EMISSION_RATE = 30.f;
		const sf::Time INTERVAL = sf::seconds(1.f) / EMISSION_RATE;

		accumulatedTime_ += dt;

		while (accumulatedTime_ > INTERVAL)
		{
			accumulatedTime_ -= INTERVAL;
			particleSystem_->addParticle(getWorldPosition());
		}

	}
}