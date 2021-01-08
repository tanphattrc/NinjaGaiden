#pragma once
#include "./../../GameComponents/Animation.h"
#include "../Entity.h"
#include "GameObject.h"
//#include "../DynamicGameObject/Player/Player.h"

//vien gach
class GameObject: public Entity
{
public:
    ~GameObject();

	void Update(float dt);
	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255,255, 255, 255));
	void Draw(D3DXVECTOR2 transform);

	void Hidden();
	//int OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);
	void OnCollision();
	float _timeSpawn;
	float _posStop;
	//Add
	virtual vector<GameObject*> GetBullet();
	virtual void SetActive(bool variable);
	void GetPLayer(Entity* player);
	void SetRange(float min, float max);
	void SetOriginalTurn(int turn);
	bool mCurrentServe;
	//add
	GameObject(D3DXVECTOR3 position, const char* filename, int totalFrame, int row, int colum, int seconeFrame);

protected:

	GameObject();
	int originalTurn;
	//Add
	float minX;
	float maxX;
	Entity* mPlayer;
	D3DXVECTOR3 originalPos;
	int turnLeft;
	//add
	bool init(D3DXVECTOR3 position);

	void OnSetPosition(D3DXVECTOR3 poks);

	virtual const char* FileName() ; 
	virtual int TotalFrame() ; //so frame cua animation
	virtual int Row() ; // so row cua resource hinh anh animation
	virtual int Column() ; // so cot cua resource hinh anh animation
	virtual float SecondPerFrame() ; //so giay de chuyen frame cua animation
	

	Animation *mAnimation;
};      
