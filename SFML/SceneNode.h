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
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>
#include <vector>
#include <memory>
#include "Category.h"
#include "Utility.h"
#include <set>


namespace GEX
{
	//forward declaration
	class CommandQueue;
	struct Command;

	class SceneNode : public sf::Transformable, public sf::Drawable
	{
	public:
		using Ptr = std::unique_ptr<SceneNode>;
		using Pair = std::pair<SceneNode*, SceneNode*>;  //pair of pointers to SceneNodes

	public:
									SceneNode(Category::Type category = Category::Type::None);
		virtual						~SceneNode() = default;
									SceneNode(const SceneNode&) = delete;
		SceneNode&					operator=(SceneNode&) = delete;

		void						attachChild(Ptr child); //add child
		Ptr							detachChild(const SceneNode& ptr);  //remove child
		void						update(sf::Time dt, CommandQueue& comands);	//update nodes
		sf::Vector2f				getWorldPosition() const;
		sf::Transform				getWorldTransform() const;

		virtual sf::FloatRect		getBoundingBox() const;
		void						drawBoundingBox(sf::RenderTarget& target, sf::RenderStates states) const;

		void						onCommand(const Command& command, sf::Time dt);//Command current node, if category matches, and command children
		virtual unsigned int		getCategory() const;	//return category

		void						checkSceneCollision(SceneNode& rootNode, std::set<Pair>& collisionPair);
		void						checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPair); //See if nodes are colliding

		virtual bool			    isDestroyed() const;
		virtual bool				isMarkedForRemoval() const;

		void						removeWrecks();

	protected:
		//update the tree
		virtual void				updateCurrent(sf::Time dt, CommandQueue& comands);
		void						updateChildren(sf::Time dt, CommandQueue& commands);

	private:
		//draw the tree
		virtual void				draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		virtual void				drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		void						drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;


	private:
		SceneNode *					parent_;
		std::vector<Ptr>			children_;  //vector of unique pointers to SceneNodes 
		Category::Type				category_;
	};

	float distance(const SceneNode& lhs, const SceneNode& rhs);

	bool collision(const SceneNode& lhs, const SceneNode& rhs); //check if bounding box of rects are intersecting 
}

