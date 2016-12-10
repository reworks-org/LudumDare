//
//  B2DCallbacks.hpp
//  LD37
//
//  Created by reworks on 10/12/2016.
//  Copyright (c) 2016 reworks. All rights reserved.
//

#ifndef LD37_B2DCALLBACKS_HPP_
#define LD37_B2DCALLBACKS_HPP_

#include <string>

#include <re/entity/Entity.hpp>
#include <re/physics/Box2D/Box2d.h>

class SandboxContact : public b2ContactListener
{
public:
	/*
	* IMPORTS: none
	* EXPORTS: none
	* PURPOSE: virtual destructor
	*/
	~SandboxContact() override;

	/*
	* IMPORTS: SEE BOX2D COLLISION DOCS
	* EXPORTS: 
	* PURPOSE: Override the box2d contact functions on collision start.
	*/
	void BeginContact(b2Contact* contact) override;

	/*
	* IMPORTS: SEE BOX2D COLLISION DOCS
	* EXPORTS:
	* PURPOSE: Override the box2d contact functions on collision end.
	*/
	void EndContact(b2Contact* contact) override;
};

#endif