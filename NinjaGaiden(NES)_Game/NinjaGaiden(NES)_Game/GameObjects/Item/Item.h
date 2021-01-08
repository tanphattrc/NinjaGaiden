#pragma once
#include "../StaticGameObject/GameObject.h"
class Item : public GameObject
{
public:
	Item();
	void Init(D3DXVECTOR3 position, float posStop,string itemName);
	void OnCollision( ); // Test 8/5


	~Item();

	virtual const char* FileName();
	int TotalFrame();
	int Row();
	int Column();
	float SecondPerFrame();
	void Update(float dt);
	string _itemName;

protected:


};