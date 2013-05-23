#include "stdafx.h"
#include "Extrusion.h"

Extrusion::Extrusion(Vector3 pos, Vector3 size, Vector3 axis, float extrusionTravel, hkpWorld * world, SceneManager * sceneMgr):
	mWorld(world), mSceneMgr(sceneMgr)
{
	hkVector4 halfSize(size.x * 0.5f, size.y * 0.5, size.z * 0.5);
	hkpBoxShape * shape = new hkpBoxShape(halfSize, 0);

	hkpRigidBodyCinfo info;
	info.m_shape = shape;
	info.m_mass = 800.0f;
	hkpInertiaTensorComputer::setShapeVolumeMassProperties(shape, info.m_mass, info);
	info.m_motionType = hkpMotion::MOTION_BOX_INERTIA;
	info.m_position.set(pos.x, pos.y, pos.z);
	mBody = new hkpRigidBody(info);
	mWorld->addEntity(mBody);
	shape->removeReference();


	hkpRigidBodyCinfo anchorInfo;
	anchorInfo.m_motionType = hkpMotion::MOTION_FIXED;
	anchorInfo.m_position = hkVector4(pos.x + (20.0f * axis.x), pos.y, pos.z + (20.0f * axis.z));
	anchorInfo.m_shape = new hkpSphereShape(0.1f);
	hkpRigidBody * anchor = new hkpRigidBody(anchorInfo);
	mWorld->addEntity(anchor);

	// Setup prismatic constraint
	hkVector4 a(axis.x, axis.y, axis.z);
	hkpPrismaticConstraintData * prismatic = new hkpPrismaticConstraintData();
	prismatic->setMaxLinearLimit(extrusionTravel);
	prismatic->setMinLinearLimit(0.0f);
	prismatic->setInWorldSpace(mBody->getTransform(), anchor->getTransform(), hkVector4(pos.x, pos.y, pos.z), a);
	hkpConstraintInstance * prismaticConstraint = new hkpConstraintInstance(mBody, anchor, prismatic);
	mWorld->addConstraint(prismaticConstraint);
	prismaticConstraint->removeReference();
	prismatic->removeReference();

	// Ogre
	char entityName[] = "000ExtrusionEntity";
	entityName[0] += numExtrusions;
	mMesh = mSceneMgr->createEntity(entityName, "cube.mesh");
	AxisAlignedBox aab = mMesh->getBoundingBox();
	mMesh->setMaterialName("Examples/Wall");

	Vector3 meshSize = aab.getSize();
	Vector3 scaling = size / meshSize;

	char nodeName[] = "000ExtrusionNode";
	nodeName[0] += numExtrusions;
	mNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(nodeName);
	mNode->setPosition(pos.x, pos.y, pos.z);
	mNode->setScale(scaling);
	mNode->attachObject(mMesh);

	numExtrusions++;
}

void Extrusion::update() {
	mNode->setPosition(mBody->getPosition()(0), mBody->getPosition()(1), mBody->getPosition()(2));
}