#include "Game.h"
#include <cassert>
#include <cmath>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Keyboard.hpp>

static const float P_PLAYER_ACCELERATION = 2000.0f;
static const float P_PLAYER_DECELERATION = 1500.0f;
static const float P_PLAYER_MAX_SPEED = 8000.0f;
static const float P_ENEMY_ACCELERATION = 1700.0f;
static const float P_ENEMY_DECELERATION = 1000.0f;
static const float P_ENEMY_MAX_SPEED = 5000.0f;
Game::Game(const sf::Vector2u& renderDimensions)
	: P_render_Dimensions(renderDimensions)

{
	const bool result = P_texture.loadFromFile("content/texture.png");
	bool explosion = P_explosion.loadFromFile("content/Explosion1.png");


	assert(result);
	loadTextures();
	loadAnimations();
	M_create_Player();
	M_create_Enemy(Enemy);
	M_create_World();
	
	view1.setSize(sf::Vector2f(1980,1200));
	//view1.setCenter(sf::Vector2f(350, 300));
	

}

Game::~Game()
{
}
void Game::M_update(const sf::Time& elapsedTime, const sf::RenderWindow& window)
{

	view1.setCenter(P_player.M_get_position());
	P_elapsedSeconds = elapsedTime.asSeconds();
	M_update_Player_Velocity(P_elapsedSeconds);
	M_update_Player_Movement(P_elapsedSeconds);
	M_update_Player_Rotation(window);
	animH.update(P_elapsedSeconds);
	P_player.M_set_Texture_Rectangle(animH.bounds);
	if (hitting == false && P_player_Velocity == P_stop_Velocity)
	{
		std::cout << "standing still" << std::endl;
		animH.changeAnim(0);
		
	}
	
	if (is_Enemy_Active){
		M_update_Enemy_Velocity(P_elapsedSeconds, Enemy);
		M_update_Enemy_Movement(P_elapsedSeconds, Enemy);
		M_checkCollision(P_player, Enemy);
		M_update_Hit_Confirmation(Enemy);


	}
	
	if (is_Enemy_Active == false)
		M_spawn_Enemy(0.4f, 0.5f);
	if (is_Explosion_Active == true)
	{
		P_explosionTimer += P_elapsedSeconds;
		if (P_explosionTimer >= explosiontime)
			M_destroy_Explosion(explosion);
	}

}
void Game::M_draw(sf::RenderWindow& window)
{	
	
	window.clear(sf::Color(50, 50, 50, 255));
	window.draw(map);
	window.setView(view1);
	P_player.M_draw(window);
	if (is_Enemy_Active)
	{
		Enemy->M_draw(window);
	}
	if (is_Explosion_Active)
	{
		explosion->M_draw(window);
	}

	
}
void Game::M_update_Player_Velocity(const float elapsedTime)
{
	const float P_acceleration = P_PLAYER_ACCELERATION * elapsedTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		P_player_Velocity.x -= P_acceleration;
		animH.changeAnim(4);
		moving = true;
	}
		

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		P_player_Velocity.x += P_acceleration;
		animH.changeAnim(1);
		moving = true;
	}
		

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		P_player_Velocity.y -= P_acceleration;
		animH.changeAnim(1);
		moving = true;
	}
		

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		P_player_Velocity.y += P_acceleration;
		animH.changeAnim(1);
		moving = true;
		
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (hitting == false)
		{
			moving = false;
			animH.changeAnim(0);
		}
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))


	P_player_Velocity.x = M_clamp(P_player_Velocity.x, -P_PLAYER_MAX_SPEED, P_PLAYER_MAX_SPEED);
	P_player_Velocity.y = M_clamp(P_player_Velocity.y, -P_PLAYER_MAX_SPEED, P_PLAYER_MAX_SPEED);
}
void Game::M_update_Player_Movement(const float elapsedTime)
{
	sf::Vector2f position = P_player.M_get_position();
	position += P_player_Velocity * elapsedTime;
	if (position.x < 0.0f || position.x > P_render_Dimensions.x)
		position.x = P_player.M_get_position().x;

	if (position.y < 0.0f || position.y > P_render_Dimensions.y)
		position.y = P_player.M_get_position().y;

	P_player.M_set_Position(position);

	if (P_player_Velocity.x != 0.0f)
		P_player_Velocity.x += -M_sign(P_player_Velocity.x) * P_PLAYER_DECELERATION * elapsedTime;
	if (P_player_Velocity.y != 0.0f)
		P_player_Velocity.y += -M_sign(P_player_Velocity.y) * P_PLAYER_DECELERATION * elapsedTime;
}
void Game::M_update_Player_Rotation(const sf::RenderWindow& window)
{
	sf::Vector2f player_Position = P_player.M_get_position();
	sf::Vector2i mouse_Position = sf::Mouse::getPosition(/*window*/);
	float x_distance = player_Position.x - (float)mouse_Position.x;
	float y_distance = player_Position.y - (float)mouse_Position.y;
	float angle = (atan2(((float)mouse_Position.y - player_Position.y), ((float)mouse_Position.x - player_Position.x)) * 180 / M_PI);
	if (angle < 0)	angle += 360;
	P_player.M_set_Rotation(angle);
}
void Game::M_update_Hit_Confirmation(GameObject *Target) // Want hit range as variable?
{
	if (is_Enemy_Active == true)
	{
		bool mouse_Pressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			mouse_Pressed = false;
		float player_Rotation = P_player.M_get_Rotation();
		float enemy_Rotation = Target->M_get_Rotation();

		sf::Vector2f player_Position = P_player.M_get_position();
		sf::Vector2f enemy_Position = Target->M_get_position();

		float x_distance = player_Position.x - enemy_Position.x;
		float y_distance = player_Position.y - enemy_Position.y;

		float x_enemydistance = enemy_Position.x - player_Position.x;
		float y_enemydistance = enemy_Position.x - player_Position.x;

		float angle = (atan2((enemy_Position.y), enemy_Position.x) * 180 / M_PI);
		float enemyAngle = (atan2((y_distance), x_distance) * 180 / M_PI);

		if (angle < 0)	angle += 360;
		if (is_Enemy_Active)
			{
			if (mouse_Pressed == true)
			{
				animH.changeAnim(2);
				
				hitting = true;

				if ((player_Rotation - angle < 35 && player_Rotation - angle > -35) && M_checkCollision(P_player, Target) == true && mouse_Pressed == true)
				{
					std::cout << "Player hit Enemy " << std::endl;
					Target->M_hit(P_player.M_get_Damage());
					if (Target->M_get_Hit_Points() <= 0.0f)
						M_destroy_Enemy(Target);
				}
			}
			else 
				hitting = false;
			/*if (M_checkCollision(P_player, Target) == true)
			{
				animH.changeAnim(3);
				std::cout << "Enemy hit Player " << std::endl;
				P_player.M_hit(Target->M_get_Damage());
				if (P_player.M_get_Hit_Points() < 0)
				{
					P_player.M_set_lives(P_player.M_get_Lives()-1);
					if (P_player.M_get_Lives() < 0)
					Game::Over();*/
				
					
			}
			
		
		
	}
}
void Game::M_update_Enemy_Velocity(const float elapsedTime, GameObject *Target)
{
	if (is_Enemy_Active == true)
	{
		sf::Vector2f current_Position = Target->M_get_position();
		sf::Vector2f target_Position = P_player.M_get_position();
		float x_distance = current_Position.x - target_Position.x;
		float y_distance = current_Position.y - target_Position.y;
		float angle = (atan2((target_Position.y - current_Position.y), (target_Position.x - current_Position.x)) * 180 / M_PI);
		if (angle < 0)	angle += 360;
		Target->M_set_Rotation(angle);
		const float P_acceleration = P_ENEMY_ACCELERATION * elapsedTime;

		if (x_distance > 70)
			P_enemy_Velocity.x -= P_acceleration;

		if (x_distance < 70)
			P_enemy_Velocity.x += P_acceleration;

		if (y_distance < 70)
			P_enemy_Velocity.y += P_acceleration;

		if (y_distance > 70)
			P_enemy_Velocity.y -= P_acceleration;

		P_player_Velocity.x = M_clamp(P_player_Velocity.x, -P_ENEMY_MAX_SPEED, P_ENEMY_MAX_SPEED);
		P_player_Velocity.y = M_clamp(P_player_Velocity.y, -P_ENEMY_MAX_SPEED, P_ENEMY_MAX_SPEED);
	}
}
void Game::M_update_Enemy_Movement(const float elapsedTime, GameObject *Target)
{
	if (is_Enemy_Active == true)
	{
		sf::Vector2f position = Target->M_get_position();
		position += P_enemy_Velocity * elapsedTime;
		if (position.x < 0.0f || position.x > P_render_Dimensions.x)
			position.x = Target->M_get_position().x;

		if (position.y < 0.0f || position.y > P_render_Dimensions.y)
			position.y = Target->M_get_position().y;

		Target->M_set_Position(position);

		if (P_enemy_Velocity.x != 0.0f)
			P_enemy_Velocity.x += -M_sign(P_enemy_Velocity.x) * P_PLAYER_DECELERATION * elapsedTime;
		if (P_enemy_Velocity.y != 0.0f)
			P_enemy_Velocity.y += -M_sign(P_enemy_Velocity.y) * P_PLAYER_DECELERATION * elapsedTime;
	}
}
bool Game::M_checkCollision(GameObject P_player, GameObject *Target)
{
	sf::FloatRect PlayerBoundingBox = P_player.M_get_Bounding_Box();
	sf::FloatRect TargetBoundingBox = Target->M_get_Bounding_Box();
	if (PlayerBoundingBox.intersects(TargetBoundingBox))
	{ 
		//std::cout << "Collision!" << std::endl;
		return true;
	}
	return false;
}

void Game::M_create_Player()
{
	
	P_player.M_set_Texture(this->texmgr.getRef("Character"));
	sf::IntRect texrect(animH.bounds);
	const sf::IntRect textureRectangle(0, 0, 100, 118);
	P_player.M_set_Texture_Rectangle(texrect);
	const sf::Vector2f position(0.5f * P_render_Dimensions.x, 0.5f * P_render_Dimensions.y);
	P_player.M_set_Position(position);
	P_player.M_set_Damage(10);
}
void Game::M_create_Enemy(GameObject *Target)
{
	const sf::IntRect texture_Rectangle(0, 0, 100, 118);
	const sf::Vector2f position(0.2f * P_render_Dimensions.x, 0.6f * P_render_Dimensions.y);
	Target->M_set_Texture(P_texture);
	Target->M_set_Texture_Rectangle(texture_Rectangle);
	Target->M_set_Position(position);
	Target->M_set_Damage(3);
	is_Enemy_Active = true;
}
void Game::M_create_Explosion(Explosion *explosion, GameObject *Target)
{
	const sf::IntRect texture_Rectangle(0, 0, 100, 118);
	const sf::Vector2f position(Target->M_get_position());
	explosion->M_set_Position(position);
	explosion->M_set_Texture(P_explosion);
	explosion->M_set_Texture_Rectangle(texture_Rectangle);
	is_Explosion_Active = true;
}
void Game::M_create_World()
{
	const int level[] =
	{
		0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 2, 2, 2,
		1, 1, 1, 3, 3, 3, 2, 2, 3, 3, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,

	};
	map.m_load("Tileset.png", sf::Vector2u(200, 200), level, 10, 6);
}
void Game::M_spawn_Enemy(float x_position, float y_position)
{
	is_Enemy_Active = true;
	GameObject *Enemy = new GameObject();
	const sf::IntRect texture_Rectangle(0, 0, 100, 118);
	const sf::Vector2f position(x_position * P_render_Dimensions.x, y_position * P_render_Dimensions.y);
	Enemy->M_set_Texture(P_texture);
	Enemy->M_set_Texture_Rectangle(texture_Rectangle);
	Enemy->M_set_Position(position);
	Enemy->M_set_Damage(10);
	
}
void Game::M_spawn_explosion(float x_position, float y_position)
{
	Explosion *explosion = new Explosion();
	const sf::IntRect texture_Rectangle(0, 0, 100, 118);
	const sf::Vector2f position(x_position,y_position);
	explosion->M_set_Position(position);
	explosion->M_set_Texture(P_explosion);
	explosion->M_set_Texture_Rectangle(texture_Rectangle);
	is_Explosion_Active = true;
}
void Game::loadTextures()
{
	texmgr.loadTexture("Character", "content/Character.png");

}
void Game::loadAnimations()
{
	
	Animation idle("idle", 1, 2, 0.2,sf::IntRect(0,0,33,33) );
	Animation runright("run", 3, 9, 0.2, sf::IntRect(0, 0, 31.5, 33));
	Animation hit("hit", 1, 7, 0.2, sf::IntRect(0, 0, 50, 41));
	Animation get_Hit("get_hit", 17, 21, 0.2, sf::IntRect(0, 0, 33, 33));
	Animation runleft("runleft", 1, 7, 0.2, sf::IntRect(0, 0, 35, 39));


	animH.addAnim(idle);
	animH.addAnim(runright);
	animH.addAnim(hit);
	animH.addAnim(get_Hit);
	animH.addAnim(runleft);

}

void Game::M_destroy_Enemy(GameObject *Target)
{
	
	sf::Vector2f position = Target->M_get_position();
	Game::M_spawn_explosion(position.x,position.y);
	is_Enemy_Active = false;
	Target->M_Destroy();
	
}
void Game::M_destroy_Explosion(Explosion *Target)
{
	is_Explosion_Active = false;
	P_explosionTimer = 0;
	Target->M_Destroy();
}

float Game::M_clamp(const float value, const float min, const float max)
{
	if (value < min)
		return min;
	else if (value > max)
		return max;
	else
		return value;
}
float Game::M_sign(const float value)
{
	return value / abs(value);
}