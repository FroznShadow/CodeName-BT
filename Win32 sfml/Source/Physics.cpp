#include "Physics.h"

Physics::Physics(float x, float y, float width, float height)
{
	m_mass = 0.001;
	m_xvelocity = 0;
	m_yvelocity = 0;
	m_jumped = false;
	m_getlastlocation = 0;
	m_falling = false;
	m_floor = false;

	m_xposition = x;
	m_yposition = y;
	m_width = width;
	m_height = height;

	m_tophitbox_width = width;
	m_bothitbox_width = width;
	m_lefthitbox_height = height;
	m_righthitbox_height = height;

	m_lefthitbox_xposition = x;
	m_lefthitbox_yposition = y;
	m_righthitbox_xposition = x + width - m_righthitbox_width;
	m_righthitbox_yposition = y;

	m_tophitbox_xposition = x;
	m_tophitbox_yposition = y;
	m_bothitbox_xposition = x;
	m_bothitbox_yposition = y + height - m_bothitbox_height;
}

Physics::Physics()
{}

Physics::~Physics()
{
}

//------------//
//Calculations//
//------------//

void Physics::force()
{
	m_force = m_mass * m_xacceleration;
}

void Physics::momentum()
{
	m_momentum = m_mass * sqrtf(powf(m_xvelocity,2)+powf(m_yvelocity,2));
}

void Physics::impulse()
{
}

void Physics::gravity()
{
	m_yvelocity += m_mass * g;
}

void Physics::jumpForce()
{
	m_yvelocity -= 2;
	m_jumped = true;
	m_floor = false;
}

void Physics::setXVelocity(float movespeed)
{
	if (movespeed == 0) { m_xvelocity = 0; }
	if (m_xvelocity < 0.5 && m_xvelocity > -0.5) { m_xvelocity += movespeed; }
	else if (m_xvelocity > 0.5) { m_xvelocity = 0.45; }
	else if (m_xvelocity < -0.5) { m_xvelocity = -0.45; }
}

void Physics::setXVelocity()
{
	if (m_getlastlocation == m_xposition) { m_xvelocity = 0; }
	if (m_xvelocity > 0) { m_xvelocity = m_xvelocity - 0.001; }
	else if (m_xvelocity < 0) { m_xvelocity = m_xvelocity + 0.001; }
	m_getlastlocation = m_xposition;
}

void Physics::setYVelocity(float jumpspeed)
{
	if (jumpspeed == 0 && !m_floor) { if (m_falling && m_yvelocity > 0) {} else { m_yvelocity = 0; } }
	else { m_yvelocity = jumpspeed; }
}

float Physics::getXPosition()
{
	m_tophitbox_xposition += m_xvelocity;
	m_bothitbox_xposition += m_xvelocity;
	m_lefthitbox_xposition += m_xvelocity;
	m_righthitbox_xposition += m_xvelocity;

	return m_xposition += m_xvelocity;
}

float Physics::getYPosition()
{
	m_tophitbox_yposition += m_yvelocity;
	m_bothitbox_yposition += m_yvelocity;
	m_lefthitbox_yposition += m_yvelocity;
	m_righthitbox_yposition += m_yvelocity;

	return m_yposition += m_yvelocity;
}

////////////////////////////////////////////////////////////
/// Checks for collision and returns an appropriate value
/// depending on which side the collision was detected.
///
/// Top and bot hitboxes take priority over left and right.
////////////////////////////////////////////////////////////
int Physics::checkForCollision(Physics Rectangle)
{
	if (m_layer != Rectangle.m_layer) return false;

	//---------//
	//---BOT---//
	//---------//
	if (m_bothitbox_xposition < Rectangle.m_tophitbox_xposition + Rectangle.m_tophitbox_width &&
		m_bothitbox_yposition < Rectangle.m_tophitbox_yposition + Rectangle.m_tophitbox_height &&
		m_bothitbox_xposition + m_bothitbox_width > Rectangle.m_tophitbox_xposition &&
		m_bothitbox_yposition + m_bothitbox_height > Rectangle.m_tophitbox_yposition) return bot;

	//---------//
	//---TOP---//
	//---------//
	if (m_tophitbox_xposition < Rectangle.m_bothitbox_xposition + Rectangle.m_bothitbox_width &&
		m_tophitbox_yposition < Rectangle.m_bothitbox_yposition + Rectangle.m_bothitbox_height &&
		m_tophitbox_xposition + m_tophitbox_width > Rectangle.m_bothitbox_xposition &&
		m_tophitbox_yposition + m_tophitbox_height > Rectangle.m_bothitbox_yposition) return top;

	//----------//
	//---LEFT---//
	//----------//
	if (m_lefthitbox_xposition < Rectangle.m_righthitbox_xposition + Rectangle.m_righthitbox_width &&
		m_lefthitbox_yposition < Rectangle.m_righthitbox_yposition + Rectangle.m_righthitbox_height &&
		m_lefthitbox_xposition + m_lefthitbox_width > Rectangle.m_righthitbox_xposition &&
		m_lefthitbox_yposition + m_lefthitbox_height > Rectangle.m_righthitbox_yposition) return left;

	//---------//
	//--RIGHT--//
	//---------//
	if (m_righthitbox_xposition < Rectangle.m_lefthitbox_xposition + Rectangle.m_lefthitbox_width &&
		m_righthitbox_yposition < Rectangle.m_lefthitbox_yposition + Rectangle.m_lefthitbox_height &&
		m_righthitbox_xposition + m_righthitbox_width > Rectangle.m_lefthitbox_xposition &&
		m_righthitbox_yposition + m_righthitbox_height > Rectangle.m_lefthitbox_yposition) return right;
	

	//if (m_xposition < Rectangle.m_xposition + Rectangle.m_width &&
	//	m_yposition < Rectangle.m_yposition + Rectangle.m_height &&
	//	m_xposition + m_width > Rectangle.m_xposition &&
	//	m_yposition + m_height > Rectangle.m_yposition) return true;
	else { return 0; }
}