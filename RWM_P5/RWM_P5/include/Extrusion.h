#include "stdafx.h"
#include "Physics/Dynamics/Constraint/Bilateral/Prismatic/hkpPrismaticConstraintData.h"

using namespace Ogre;
static int numExtrusions = 0;

class Extrusion {
private:
	hkpWorld * mWorld;
	hkpRigidBody * mBody;

	SceneManager * mSceneMgr;
	Entity * mMesh;
	SceneNode * mNode;

public:
	Extrusion(Vector3 pos, Vector3 size, Vector3 axis, float extrusionTravel, hkpWorld * world, SceneManager * sceneMgr);
	void update();
};