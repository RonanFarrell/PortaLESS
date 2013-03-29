#pragma once
#include "stdafx.h"
#include "Physics/Dynamics/Constraint/Bilateral/LimitedHinge/hkpLimitedHingeConstraintData.h"
#include "Physics/Dynamics/Constraint/Bilateral/Hinge/hkpHingeConstraintData.h"

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
	SeeSaw(Vector3 position, Vector3 size, Vector3 axis, Vector3 pivotOffset, hkpWorld * world, SceneManager * sceneMgr);
	~SeeSaw();

	void update();
};