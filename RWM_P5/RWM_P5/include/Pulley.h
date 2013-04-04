#include "stdafx.h"
#include "Physics/Dynamics/Constraint/Pulley/hkpPulleyConstraintData.h"

using namespace Ogre;

class Pulley {
private:
	hkpWorld * mWorld;
	hkpRigidBody * mMoveableBody0;
	hkpRigidBody * mMoveableBody1;
	hkVector4 worldPivots[2];

	SceneManager * mSceneMgr;
	Entity * mMesh0;
	Entity * mMesh1;
	SceneNode * mNode0;
	SceneNode * mNode1;
	ManualObject * rope;
public:
	Pulley(Vector3 pivotPos1, Vector3 pivotPos2, hkpWorld * world, SceneManager * sceneMgr);
	~Pulley();

	void update();
};