#include "stdafx.h"
#include "SeeSaw.h"

SeeSaw::SeeSaw (Vector3 pos, Vector3 size, Vector3 axis, Vector3 pivotOffset, hkpWorld * world, SceneManager * sceneMgr) :
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
	info.m_mass = 10.0f;
	hkpInertiaTensorComputer::computeBoxVolumeMassProperties(halfSize, info.m_mass, massProperties);
	info.m_inertiaTensor = massProperties.m_inertiaTensor;
	info.m_centerOfMass = massProperties.m_centerOfMass;
	info.m_motionType = hkpMotion::MOTION_BOX_INERTIA;
	info.m_enableDeactivation = false;

	mMoveablebody = new hkpRigidBody(info);
	mWorld->addEntity(mMoveablebody);

	boxShape->removeReference();

	// Create limited hinge constraint
	hkpLimitedHingeConstraintData * lhc = new hkpLimitedHingeConstraintData();

	//hkVector4 pivot(position(0) + pivotOffset.x, position(1) + pivotOffset.y, position(2) + pivotOffset.z);
	hkVector4 pivot(position);
	pivot(0) += pivotOffset.x;
	pivot(2) += pivotOffset.z;
	hkVector4 pivotAxis(axis.x, axis.y, axis.z);
	hkTransform t(mFixedBody->getTransform());
	//t.setTranslation(pivot);
	lhc->setInWorldSpace(mMoveablebody->getTransform(), t, pivot, pivotAxis);
	lhc->setMinAngularLimit(-HK_REAL_PI / 2.0f);
	lhc->setMaxAngularLimit(HK_REAL_PI / 2.0f);

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
	mMesh->setMaterialName("Examples/Wall");

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

	hkVector4 pos(mMoveablebody->getPosition());
	mNode->setPosition(pos(0), pos(1), pos(2));
}