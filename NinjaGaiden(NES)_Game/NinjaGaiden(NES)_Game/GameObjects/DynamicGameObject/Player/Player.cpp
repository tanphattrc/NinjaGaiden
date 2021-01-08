#include "Player.h"
#include "PlayerStandingState.h"
#include "PlayerJumpingState.h"
#include "PlayerStandingBeatState.h"
#include "../../..//GameDefine/GameDefine.h"



Player::Player()
{

	
	//e_Hit = nullptr;
	mAnimationStanding = new Animation("Resources/Ninja/standing.png", 1, 1, 1, 0, D3DCOLOR_XRGB(255, 163, 177));
    mAnimationJumping = new Animation("Resources/Ninja/jumping.png", 4, 1, 4, 0.25f, D3DCOLOR_XRGB(255, 163, 177));
    mAnimationRunning = new Animation("Resources/Ninja/running.png", 3, 1, 3, 0.15f, D3DCOLOR_XRGB(255, 163, 177));
	mAnimationStandingBeat = new Animation("Resources/Ninja/standingbeat.png", 2, 1, 2, 0.3f, D3DCOLOR_XRGB(255, 163, 177));
    mAnimationSitting= new Animation ("Resources/Ninja/sitting.png", 1, 1, 1, 0, D3DCOLOR_XRGB(255, 163, 177));
	mAnimationSittingBeat = new Animation("Resources/Ninja/sittingbeat.png", 2, 1, 2, 0.3f, D3DCOLOR_XRGB(255, 163, 177));
	mAnimationDying = new Animation("Resources/Ninja/dying.png", 1, 1, 1, 0, D3DCOLOR_XRGB(255, 163, 177));
	mAnimationClimbing = new Animation("Resources/Ninja/Climbing.png", 2, 1, 2, 0.25f, D3DCOLOR_XRGB(255, 163, 177));
	mAnimationClinging = new Animation("Resources/Ninja/Clinging.png", 1, 1, 1, 0, D3DCOLOR_XRGB(255, 163, 177));
	mAnimationUsingWeapon = new Animation("Resources/Ninja/usingweapon.png", 3, 1, 3, 0.1f, D3DCOLOR_XRGB(255, 163, 177));

	this->mPlayerData = new PlayerData();
    this->mPlayerData->player = this;
    this->vx = 0;
    this->vy = 0;
    this->SetState(new PlayerStandingState(this->mPlayerData));
	invincible = false;
    allowJump = false;
	allowHit = false;
	isJummping = false;
	index = 0;
	Tag = Ninja;
	InvincibleTime = 80;
	
	e_Hit = new ExplosionHit(this->GetPosition());
	e_Hit->_Active = false;
	isOnStair = false;
	timeStopUpdateAni = 0;
	isUpdate = true;
	//mWeapon = nullptr;
	playerMana = 0;
	playerHP = 16;
	
}

Player::~Player()
{
}

void Player::Update(float dt)
{
	// Effect Hit
	if (GameGlobal::Pause)
	{
		if (e_Hit->_Active)
		{
			e_Hit->Update(dt);
			if (e_Hit->_timeSpawn >= e_Hit->Column()* e_Hit->SecondPerFrame())
			{
				e_Hit->_Active = false;
				e_Hit->_timeSpawn = 0;
			}
			else
			{
				e_Hit->_timeSpawn += dt;
			}
		}
		//Weapon
		if (mWeapon)
		{

			mWeapon->Update(dt);
			mWeapon->GetPositionPlayer(mPlayerData->player->GetPosition());
			//mWeapon->SetPosLimitAtMap(mCamera->GetPosition() + D3DXVECTOR3(mCamera->GetWidth() / 2, 0, 0));
			mWeapon->setBoundLimit(mCamera->GetBound());
			//mWeapon->SetDirection(mCurrentReverse);
			mWeapon->setBoundplayer(this->mPlayerData->player->GetBound());

		}

		if (timeStopUpdateAni < (mCurrentAnimation->getColums())*0.25 && this->isUpdate == true || this->mCurrentState != PlayerState::Climbing)
		{
			mCurrentAnimation->Update(dt);
			timeStopUpdateAni += dt;
		}
		else
		{
			mCurrentAnimation->ResetAnimation();
			timeStopUpdateAni = 0;
			isUpdate = false;
		}
		if (this->mPlayerData->state)
		{
			this->mPlayerData->state->Update(dt);
		}

		Entity::Update(dt);

	}
	else
	{

	}
}

void Player::HandleKeyboard()
{
	if (GameGlobal::Pause)
	{
		if (this->mPlayerData->state)
		{
			this->mPlayerData->state->HandleKeyboard();
		}
	}
}

void Player::OnKeyPressed(int key)
{
    if (key ==DIK_SPACE )
    {
        if (allowJump)
        {
            if (mCurrentState == PlayerState::Running || mCurrentState == PlayerState::Standing || mCurrentState==PlayerState::Sitting)
            {
                this->SetState(new PlayerJumpingState(this->mPlayerData));
            }

            allowJump = false;
        }
		
    }
	if (key == DIK_Z)
	{
		if (allowHit)
		{
			if (mCurrentState == PlayerState::Running || mCurrentState == PlayerState::Standing)// || mCurrentState == PlayerState::Falling || mCurrentState == PlayerState::Jumping)
			{
				this->SetState(new PlayerStandingBeatState(this->mPlayerData));


			}
		}
		//allowHit = false;
	}
	if (key == DIK_C)
	{
		this->SetState(new PlayerUseWeaponState(this->mPlayerData));
	}
	
}

void Player::OnKeyUp(int key)
{
    if (key == DIK_SPACE)
        allowJump = true;

	if (key == DIK_Z)
		allowHit = true;
	if (key == DIK_C)
	{
		
		if (mWeapon && mWeapon->_Active==false)
		{
			if (mWeapon->TagWeapon == Entity::WeaponType::ThrowingStarWeapon && playerMana >= 3||
				mWeapon->TagWeapon == Entity::WeaponType::WindmillStarWeapon && playerMana >=5 ||
				mWeapon->TagWeapon == Entity::WeaponType::FireWeapon && playerMana >=5 )
			{
				mWeapon->_Active = true;
				for (int i = 0; i < mWeapon->GetWeapon().size(); i++)
				{
					mWeapon->GetWeapon()[i]->_Active = true;
				}
				if (mWeapon->TagWeapon == Entity::WeaponType::ThrowingStarWeapon)
				{
					playerMana -= 3;
					Sound::getInstance()->play("ThrowingStarWeapon", true, 0);
				}
				else
				{
					if (mWeapon->TagWeapon == Entity::WeaponType::ThrowingStarWeapon)
					{
						Sound::getInstance()->play("WindmillStarWeapon", true, 0);
					}
					else
					{
						Sound::getInstance()->play("FireWeapon", true, 0);
					}
					playerMana -= 5;
				}
			}
			mWeapon->SetDirection2(mCurrentReverse);

		}
		else
		{
			if (mWeapon)
			{
				mWeapon->_Active = true;
				for (int i = 0; i < mWeapon->GetWeapon().size(); i++)
				{
					mWeapon->GetWeapon()[i]->_Active = true;
				}
				mWeapon->SetDirection2(mCurrentReverse);
				
			}
		}
		
	}

}

void Player::SetReverse(bool flag)
{
    mCurrentReverse = flag;
}

bool Player::GetReserse()
{
	return mCurrentReverse;
}

void Player::setPlayerMana(int mana)
{
	playerMana = mana;
}

int Player::getPlayerMana()
{
	return playerMana;
}

void Player::setPlayerHP(int HP)
{
	playerHP = HP;
}

int Player::getPlayerHP()
{
	return playerHP;
}

int Player::getIndex()
{
	return index;
}

void Player::setIndex(int _index)
{
	index = _index;
}

void Player::setAllowHit(bool allow)
{
	allowHit = allow;
}

bool Player::getAllowHit()
{
	return allowHit;
}

void Player::SetCamera(Camera *camera)
{
	this->mCamera = camera;
}

void Player::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
    mCurrentAnimation->FlipVertical(mCurrentReverse);
    mCurrentAnimation->SetPosition(this->GetPosition());

   
	if (mCamera)
	{
		
		D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
			GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);
		if (e_Hit->_Active)
		{
			e_Hit->Draw(e_Hit->GetPosition(),RECT(),D3DXVECTOR2(),trans);
		}

	
		 
		// WEAPON
		if (mWeapon && mWeapon->_Active)
		{
			mWeapon->Draw(mWeapon->GetPosition(), RECT(), D3DXVECTOR2(), trans);
		}

		if (invincible)
		{
			InvincibleTime--;
			if (InvincibleTime % 2 == 0 && InvincibleTime >=0)
			{
				mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0), sourceRect, scale, trans, angle, rotationCenter, colorKey);
			}
			if (InvincibleTime <= 0)
			{
				invincible=false;
				InvincibleTime = 80;
			}
		}
		else mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0), sourceRect, scale, trans, angle, rotationCenter, colorKey);
	}
	else
	{
		if (e_Hit->_Active)
		{
			e_Hit->Draw(e_Hit->GetPosition());
		}
		 mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0));
		 if (mWeapon)
		 {
			 mWeapon->Draw(mWeapon->GetPosition());
		 }
	}
}

void Player::SetState(PlayerState *newState)
{
	allowMoveLeft = true;
	allowMoveRight = true;
    delete this->mPlayerData->state;

    this->mPlayerData->state = newState;

    this->changeAnimation(newState->GetState());

    mCurrentState = newState->GetState();
}

RECT Player::GetBound()
{
    RECT rect;
    rect.left = this->posX - mCurrentAnimation->GetWidth() / 2;
    rect.right = rect.left + mCurrentAnimation->GetWidth();
    rect.top = this->posY - mCurrentAnimation->GetHeight() / 2;
    rect.bottom = rect.top + mCurrentAnimation->GetHeight();

    return rect;
}

void Player::changeAnimation(PlayerState::StateName state)
{
    switch (state)
    {
        case PlayerState::Running:
            mCurrentAnimation = mAnimationRunning;
            break;

        case PlayerState::Standing:
            mCurrentAnimation = mAnimationStanding;
            break;

        case PlayerState::Falling:
            mCurrentAnimation = mAnimationJumping;
            break;

        case PlayerState::Jumping:
            mCurrentAnimation = mAnimationJumping;
            break;
		case PlayerState ::StandingBeat:
			mCurrentAnimation = mAnimationStandingBeat;
			break;
		case PlayerState ::Sitting:
			mCurrentAnimation = mAnimationSitting;
			break;
		case PlayerState::SittingBeat:
			mCurrentAnimation = mAnimationSittingBeat;
			break;
		case PlayerState::Die:
			mCurrentAnimation = mAnimationDying;
			break;
		case PlayerState::Climbing:
			mCurrentAnimation = mAnimationClimbing;
			break;
		case PlayerState::UseWeapon:
			mCurrentAnimation = mAnimationUsingWeapon;
			break;
		case PlayerState::Clinging:
			mCurrentAnimation = mAnimationClinging;
			break;
    }

    this->width = mCurrentAnimation->GetWidth();
    this->height = mCurrentAnimation->GetHeight();
}

Player::MoveDirection Player::getMoveDirection()
{
    if (this->vx > 0)
    {
        return MoveDirection::MoveToRight;
    }
    else if (this->vx < 0)
    {
        return MoveDirection::MoveToLeft;
    }

    return MoveDirection::None;
}
void Player::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	 this->mPlayerData->state->OnCollision(impactor, side, data);
}
void Player::OnNoCollisionWithBottom()
{
	if (mCurrentState != PlayerState::Jumping && mCurrentState != PlayerState::Falling && mCurrentState != PlayerState::StandingBeat && mCurrentState!=PlayerState::Climbing && mCurrentState!=PlayerState::UseWeapon
		&& mCurrentState != PlayerState::Clinging)
	{
		this->SetState(new PlayerFallingState(this->mPlayerData));
	}
}
PlayerState::StateName Player::getState()
{
    return mCurrentState;
}