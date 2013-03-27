#pragma once
#include "stdafx.h"

using namespace Ogre;
static int numQubes = 0;

class Qube {
private:
	// Havok stuff
	hkpRigidBody * mBody;
	hkpWorld * mWorld;
	hkVector4 mPosition;
	hkQuaternion mOrientation;

	// Ogre stuff
	Entity * mMesh;
	SceneNode * mNode;
	SceneManager * mSceneMgr;

public:
	Qube(Vector3 pos, Vector3 size, hkpWorld * world, SceneManager * sceneMgr);
	~Qube();

	void update();

	void convertToHeavy();
	void convertToFloaty();
};