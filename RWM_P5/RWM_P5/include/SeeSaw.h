#pragma once
#include "stdafx.h"
#include "Physics/Dynamics/Constraint/Bilateral/LimitedHinge/hkpLimitedHingeConstraintData.h"

using namespace Ogre;

static int numSeeSaw = 0;

class SeeSaw {
private:
	// Havok stuff
	hkpRigidBody * mFixedBody;
	hkpRigidBody * mMoveablebody;
	hkpWorld * mWorld;

	// Ogre stuff
	Entity * mMesh;
	SceneNode * mNode;
	SceneManager * mSceneMgr;

public:
	SeeSaw(Vector3 position, Vector3 size, Vector3 axis, hkpWorld * world, SceneManager * sceneMgr);
	~SeeSaw();

	void update();
};