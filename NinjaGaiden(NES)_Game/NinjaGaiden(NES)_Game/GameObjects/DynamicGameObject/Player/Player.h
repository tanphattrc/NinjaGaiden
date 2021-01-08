#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "../../../GameComponents/Animation.h"
#include "../../../GameComponents/GameGlobal.h"
#include "../../Entity.h"
#include "PlayerData.h"
#include "PlayerState.h"
#include "PlayerRunningState.h"
#include "../Player/PlayerStandingBeatState.h"
#include "../Player/PlayerSittingState.h"
#include "../../../GameComponents/Camera.h"
#include "PlayerFallingState.h"
#include "PlayerClimbingState.h"
#include "../../ExplosionEffect/ExplosionHit.h"
#include "PlayerJumpingState.h"
#include "../../../GameDefine/GameDefine.h"
#include "PlayerUseWeaponState.h"
#include "../../Weapon/FireWeapon.h"
#include "../../Weapon/ThrowingStarWeapon.h"
#include "../../Weapon/WindmillStarWeapon.h"
#include "../Player/PlayerClingingState.h"
#include "../../../GameComponents/Sound.h"

class Player : public Entity
{
public:
	
	
    Player();
    ~Player();
	
    enum MoveDirection
    {
        MoveToLeft, //chay tu phai sang trai
        MoveToRight, //chay tu trai sang phai
        None //dung im
    };
	void SetCamera(Camera *camera);
    void Update(float dt);

    void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

	void OnNoCollisionWithBottom();
    void SetState(PlayerState *newState);

    MoveDirection getMoveDirection();

    RECT GetBound();     

    PlayerState::StateName getState();

    //xu ly input
    //gom 256 key tuong ung true = dang dc nhan, false = khong dc nhan
    void HandleKeyboard();

    void OnKeyPressed(int key);

    void OnKeyUp(int key);

    //true thi se lat nguoc anh theo truc y
    void SetReverse(bool flag);
	bool GetReserse();


	bool allowMoveLeft;
	bool allowMoveRight;
	bool invincible;
	bool isJummping;
	bool isOnStair;
	
	ExplosionHit *e_Hit;

	PlayerData *mPlayerData;
	Weapon *mWeapon;
	void setPlayerMana(int mana);
	int getPlayerMana();
	void setPlayerHP(int HP);
	int getPlayerHP();
	int getIndex();
	void setIndex(int _index);
	void setAllowHit(bool allow);
	bool getAllowHit();
protected:
	Camera *mCamera;

	//EffectHit  *e_Hit;

	
	Animation   *mCurrentAnimation,
		*mAnimationStanding,
		*mAnimationRunning,
		*mAnimationJumping,
		*mAnimationStandingBeat,
		*mAnimationSitting,
		*mAnimationSittingBeat,
		*mAnimationDying,
		*mAnimationClimbing,
		*mAnimationClinging,
		*mAnimationUsingWeapon;

    void changeAnimation(PlayerState::StateName state);

    PlayerState::StateName mCurrentState;

    //chi cho phep jump khi nhan nhim space, muon nhay lai phai tha phim space roi nhan lai
	bool allowJump, mCurrentReverse;
	//chi cho phep danh khi nhan Z, muon danh lai phai tha phim Z roi nhan lai
	bool allowHit;
	// cho phep invincible khi bị quái đánh
	float timeStopUpdateAni;
	

	int InvincibleTime;
	int playerHP;
	int playerMana;
	int index;

};

