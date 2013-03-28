#pragma once
#include "stdafx.h"
#include "Physics/Utilities/Weapons/hkpGravityGun.h"

using namespace Ogre;

class Player {
private:

	// Havok stuff
	hkpWorld * mWorld;
	
	hkReal mCurrentAngle;
	hkQuaternion mCurrentOrientation;


	hkpShape * mStandShape;
	hkpShape * mCrouchShape;
	hkpShape * mNewShape;

	hkpCharacterRigidBody * mCharacterBody;

	hkpCharacterContext * mCharacterContext;

	hkpSurfaceInfo * mPreviousGround;

	// Ogre stuff
	SceneManager * mSceneMgr;
	Entity		* mMesh;
	SceneNode	* mNode;
	Vector3		mSpawnLocation;
public:
	Player();
	Player(Vector3 spawnLocation, hkpWorld * world, SceneManager * sceneMgr);
	~Player();

	void update(int UD, int LR, bool lmb, bool rmb, bool mmb, bool jump, Camera * cam, float dt);

	// Accessors
	hkpCharacterContext * getCharacterContext() { return mCharacterContext; };
	hkpCharacterRigidBody * getCharacterRigidBody() { return mCharacterBody; };

	void setCurrrentAngle(hkReal angle) { mCurrentAngle = angle; };

	hkTransform mTransform;
	hkpGravityGun * mGravityGun;
};