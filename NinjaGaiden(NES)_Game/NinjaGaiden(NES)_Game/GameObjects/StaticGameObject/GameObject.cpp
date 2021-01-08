#include "GameObject.h"
#include "../../GameComponents/GameGlobal.h"


GameObject::GameObject()
{
	
}

GameObject::GameObject(D3DXVECTOR3 position, const char* filename, int totalFrame, int row, int colum, int seconeFrame )
{
	_Active = true;
	mAnimation = new Animation(filename, totalFrame, row, colum, seconeFrame);
	SetPosition(position);
	Entity::SetWidth(mAnimation->GetWidth());
	Entity::SetHeight(mAnimation->GetHeight());
	
	
}

GameObject::~GameObject()
{

}

bool GameObject::init(D3DXVECTOR3 position)
{
	_Active = true;
	_allowPlayerpick = false;
	mAnimation = new Animation(FileName(), TotalFrame(), Row(), Column(), SecondPerFrame());

	SetPosition(position);
	mAnimation->SetPosition(position);
	Entity::SetWidth(mAnimation->GetWidth());
	Entity::SetHeight(mAnimation->GetHeight());

	originalPos = position;
	isUpdate = true;
	return true;
}

void GameObject::OnSetPosition(D3DXVECTOR3 pos)
{
	mAnimation->SetPosition(pos);
}

const char * GameObject::FileName()
{
	return nullptr;
}

int GameObject::TotalFrame()
{
	return 0;
}

int GameObject::Row()
{
	return 0;
}

int GameObject::Column()
{
	return 0;
}

float GameObject::SecondPerFrame()
{
	return 0.0f;
}



void GameObject::Update(float dt)
{
	if (GameGlobal::Pause)
	if (_Active)
	{
		mAnimation->Update(dt);
	}
	else
	{
		//respawnTime += dt;
		//respawnTime >= 5 &&
		if (mPlayer != NULL)
			if (((originalPos.x <= mPlayer->GetPosition().x - 130) && (originalPos.x >= mPlayer->GetPosition().x - 132) && mPlayer->GetVx() > 0 && originalTurn == -1) ||
				(originalPos.x >= mPlayer->GetPosition().x + 130 && originalPos.x <= mPlayer->GetPosition().x + 132 && mPlayer->GetVx() > 0 && originalTurn == 1))
			{
				if (this -> TagEnemy == Entity::Eagle)
				{
					
					if (abs (mPlayer->GetPosition().y - originalPos.y) > 20)
					{
						_Active = true;
						posX = originalPos.x;
						posY = originalPos.y;
					}
				}
				else
				{
					_Active = true;
					posX = originalPos.x;
					posY = originalPos.y;
				}
				//respawnTime = 0;
				
			}
	}
	Entity::Update(dt);
//	Entity::Update(dt);
	Entity::Update(dt);
}

void GameObject::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	if (this->_Active)
	{
		mAnimation->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
	}
}

 



void GameObject::Draw(D3DXVECTOR2 transform)
{
	if (this->_Active)
	{
		mAnimation->Draw(D3DXVECTOR3(transform.x, transform.y, 0));
	}
}

void GameObject::Hidden()
{
	this->_Active = false;
	vx = 0;
	vy = 0;
	this->SetPosition(-100, 0);
}

void GameObject::OnCollision()
{
	_Active = false;
	vx = 0;
	vy = 0;
	this->SetPosition(-100, 0);
}

//Add
vector<GameObject*> GameObject::GetBullet()
{
	return vector<GameObject*>();
}

void GameObject::SetActive(bool variable)
{
	if (_Active == true && variable == false)
	{
		/*active = false;
		posX = originalPos.x;
		posY = originalPos.y;*/
		Hidden();
	}
	/*if (variable == true && respawnTime >= 1)

	{
		respawnTime = 0;
		_Active = true;
		posX = originalPos.x;
		posY = originalPos.y;
	}*/
}

void GameObject::GetPLayer(Entity * player)
{
	mPlayer = player;
}

void GameObject::SetRange(float min, float max)
{
	minX = min;
	maxX = max;
}

void GameObject::SetOriginalTurn(int turn)
{
	originalTurn = turn;
}
//ADD