#ifndef _PHYSICS_H
#define _PHYSICS_H

#include "Collision.h"

class Physics
{
public:
	Physics(float x, float y, float width, float height);
	Physics();
	~Physics();

	//------------//
	//Calculations//
	//------------//

	void force();
	void momentum();
	void impulse();
	void gravity();
	void jumpForce();
	int checkForCollision(Physics Rectangle);

	//----------//
	//Set-Values//
	//----------//

	void setXVelocity(float movespeed);
	void setXVelocity();
	void setYVelocity(float jumpspeed);
	void setPosition(float x, float y) { m_xposition = x; m_yposition = y; }
	void setSize(float x, float y) { m_width = x; m_height = y; }
	void setJump() { m_jumped = false; }
	void setFloor() { if (m_floor) { m_floor = false; } else { m_floor = true; m_falling = false; } }
	void setFloor(bool value) {	m_floor = value; if (value == true) { m_falling = false; }	}
	void setLayer(int layer) { m_layer = layer; }
	void setFalling() { m_falling = true; }

	//----------//
	//Get-Values//
	//----------//

	float getXPosition();
	float getYPosition();
	float getXVelocity() { return m_xvelocity; }
	float getYVelocity() { return m_yvelocity; }
	float getWidth() { return m_width; }
	float getHeight() { return m_height; }
	 bool getJumped() { return m_jumped; }
	 bool getFalling() { return m_falling; }
	 bool getFloor() { return m_floor; }

private:
	int m_layer;
	float m_xposition;
	float m_yposition;
	float m_width;
	float m_height;
	float m_force;
	float m_mass;
	float m_xacceleration;
	float m_yacceleration;
	float m_xvelocity;
	float m_yvelocity;
	float m_momentum;
	float m_getlastlocation;
	bool m_jumped;
	bool m_falling;
	bool m_floor;

	//--------//
	//HitBoxes//
	//--------//
	float m_tophitbox_xposition;
	float m_tophitbox_yposition;
	float m_tophitbox_width;
	float m_tophitbox_height = 5;

	float m_bothitbox_xposition;
	float m_bothitbox_yposition;
	float m_bothitbox_width;
	float m_bothitbox_height = 5;

	float m_lefthitbox_xposition;
	float m_lefthitbox_yposition;
	float m_lefthitbox_width = 5;
	float m_lefthitbox_height;

	float m_righthitbox_xposition;
	float m_righthitbox_yposition;
	float m_righthitbox_width = 5;
	float m_righthitbox_height;
};

#endif