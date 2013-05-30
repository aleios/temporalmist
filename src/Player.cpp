#include <Player.hpp>
#include <Matrix.hpp>
#include <LevelManager.hpp>

#include <SFML/Window/Event.hpp>

Player::Player(const std::string& inTexFilename, const std::string& inAnimFilename)
	: GameObject(inTexFilename, inAnimFilename)
{
	state = PlayerState::FALLING;
	sprite.Play(120);
	sprite.SetAnimation("walkRight");
}

Player::~Player()
{
}

void Player::Draw()
{
	sprite.Draw();
}

void Player::Update(unsigned int timestep)
{
	velocity.x = 0;
	//velocity.y = 0;

	// Update player logic, sounds, etc.
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if(state != PlayerState::WALKRIGHT)
		{
			//state = PlayerState::WALKRIGHT;
			sprite.SetAnimation("walkRight");
		}
		velocity.x = 10;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if(state != PlayerState::WALKLEFT)
		{
			//state = PlayerState::WALKLEFT;
			sprite.SetAnimation("walkLeft");
		}
		velocity.x = -10;
	}
	else if(state != PlayerState::JUMP && state != PlayerState::FALLING)
	{
		state = PlayerState::IDLE;
		sprite.SetAnimation("idle");
	}


	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && state != PlayerState::JUMP && state != PlayerState::FALLING)
	{
		state = PlayerState::JUMP;
		velocity.y = -20;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		velocity.y = 10;
	}

	// Test for collision
	LevelManager* levelManager = LevelManager::GetInstance();
	Map& map = levelManager->GetCurrentMap();

	auto cit = map.collisionTiles.begin(), cite = map.collisionTiles.end();
	bool foundCollision = false;
	for(; cit != cite; ++cit)
	{
		Rect collider = GetAABB();
		if(CheckCollision(*cit) && (state != PlayerState::JUMP || state == PlayerState::FALLING))
		{
			SetVelocity(velocity.x, 0);
			//SetPosition(0, -1, true);
			state = PlayerState::IDLE;
			foundCollision = true;
			break;
		}
	}

	if(!foundCollision)
	{
		velocity.y += 1.0f;

		if(velocity.y < 0.0f)
			state = PlayerState::JUMP;
		else if(velocity.y > 0.0f)
			state = PlayerState::FALLING;
	}

	std::cout << "Player velocity: " << velocity.x << ", " << velocity.y << "\n";

	// Set the velocity and position.
	SetPosition(velocity, true);

	SetAABB(position.x, position.y, position.x + sprite.frameWidth, position.y + sprite.frameHeight);

	sprite.Update();
}
