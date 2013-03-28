#include "stdafx.h"
#include "SeeSaw.h"

SeeSaw::SeeSaw (Vector3 pos, Vector3 size, Vector3 axis, hkpWorld * world, SceneManager * sceneMgr) :
	mWorld(world), mSceneMgr(sceneMgr)
{
	numSeeSaw++;

	mFixedBody = mWorld->getFixedRigidBody();

	hkVector4 halfSize(size.x * 0.5, size.y * 0.5, size.z * 0.5);
	hkpBoxShape * boxShape = new hkpBoxShape(halfSize, 0);
	hkVector4 position(pos.x, pos.y, pos.z);
	
	hkpRigidBodyCinfo info;
	info.m_position = position;
	info.m_shape = boxShape;

	hkMassProperties massProperties;
	info.m_mass = 200.0f;
	hkpInertiaTensorComputer::computeBoxVolumeMassProperties(halfSize, info.m_mass, massProperties);
	info.m_inertiaTensor = massProperties.m_inertiaTensor;
	info.m_centerOfMass = massProperties.m_centerOfMass;
	info.m_motionType = hkpMotion::MOTION_BOX_INERTIA;

	mMoveablebody = new hkpRigidBody(info);
	mWorld->addEntity(mMoveablebody);

	boxShape->removeReference();

	// Create limited hinge constraint
	hkpLimitedHingeConstraintData * lhc = new hkpLimitedHingeConstraintData();

	hkVector4 pivot(position);
	hkVector4 pivotAxis(axis.x, axis.y, axis.z);
	lhc->setInWorldSpace(mMoveablebody->getTransform(), mFixedBody->getTransform(), pivot, pivotAxis);
	lhc->setMinAngularLimit(-HK_REAL_PI / 3.0f);
	lhc->setMaxAngularLimit(HK_REAL_PI / 4.0f);

	hkpConstraintInstance * constraint = new hkpConstraintInstance(mMoveablebody, mFixedBody, lhc);
	mWorld->addConstraint(constraint);
	
	constraint->removeReference();
	lhc->removeReference();

	// Setup Ogre stuff
	char entityName[] = "000SeeSawEntity";
	entityName[0] += numSeeSaw;
	mMesh = mSceneMgr->createEntity(entityName, "cube.mesh");
	AxisAlignedBox aab = mMesh->getBoundingBox();
	mMesh->setCastShadows(true);
	mMesh->setMaterialName("Examples/CubeDefault");

	Vector3 meshSize = aab.getSize();
	Vector3 scaling = size / meshSize;

	char nodeName[] = "000SeeSawNode";
	nodeName[0] += numSeeSaw;
	mNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(nodeName);
	mNode->setPosition(pos);
	mNode->setScale(scaling);
	mNode->attachObject(mMesh);
}


void SeeSaw::update() {
	hkVector4 hkAxis(0, 0, 0);
	hkQuaternion mOrientation = mMoveablebody->getRotation();
	Radian angle(mOrientation.getAngle());
	if (mOrientation.hasValidAxis()) {
		mOrientation.getAxis(hkAxis);
	}
	Vector3 oAxis(hkAxis(0), hkAxis(1), hkAxis(2));
	Quaternion oOrientation(angle, oAxis);
	mNode->setOrientation(oOrientation);
}