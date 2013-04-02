#include "stdafx.h"
#include "Pulley.h"

Pulley::Pulley(hkpWorld * world, SceneManager * sceneMgr) : mWorld(world), mSceneMgr(sceneMgr)
{
	hkVector4 halfSize(0.5f, 0.5f, 0.5f);
	hkpBoxShape* boxShape = new hkpBoxShape( halfSize , 0 );

	hkpRigidBodyCinfo info;
	info.m_shape = boxShape;
	info.m_mass = 200.0f;
	hkpInertiaTensorComputer::setShapeVolumeMassProperties(boxShape, info.m_mass, info);
	info.m_motionType = hkpMotion::MOTION_BOX_INERTIA;

	info.m_position.set(-2.0f, 1.0f, -1.0f);
	mMoveableBody0 = new hkpRigidBody(info);

	info.m_position.set(-2.0f, 1.0f, 1.0f);
	mMoveableBody1 = new hkpRigidBody(info);

	mWorld->addEntity(mMoveableBody0);
	mWorld->addEntity(mMoveableBody1);

	boxShape->removeReference();

	// Create pulley constraint
	hkVector4 worldPivots[2];
	worldPivots[0] = hkVector4(-2.0f, 3.0f, -1.0f);
	worldPivots[1] = hkVector4(-2.0f, 3.0f, 1.0f);

	hkpPulleyConstraintData * pulley = new hkpPulleyConstraintData();

	hkVector4 bodyPivots[2];
	bodyPivots[0] = halfSize;
	bodyPivots[1] = halfSize;
	hkReal leverageOnBodyB = 1.0f;

	pulley->setInBodySpace(mMoveableBody1->getTransform(), mMoveableBody0->getTransform(),
							bodyPivots[1], bodyPivots[0],
							worldPivots[1], worldPivots[0],
							leverageOnBodyB);

	pulley->setRopeLength(10.0f);

	hkpConstraintInstance * constraint = new hkpConstraintInstance(mMoveableBody1, mMoveableBody0, pulley);

	mWorld->addConstraint(constraint);
	constraint->removeReference();
	pulley->removeReference();

	// Add two helper bodies to prevent constrained bodies getting too close to the pulleys
	hkpRigidBodyCinfo helperInfo;
	helperInfo.m_motionType = hkpMotion::MOTION_FIXED;
	helperInfo.m_position = worldPivots[0];
	helperInfo.m_shape = new hkpSphereShape(0.3f);
	hkpRigidBody * body = new hkpRigidBody(info);
	mWorld->addEntity(body);
	body->removeReference();

	info.m_position = worldPivots[1];
	body = new hkpRigidBody(info);
	mWorld->addEntity(body);

	body->removeReference();
	info.m_shape->removeReference();

	{
		mMesh0 = mSceneMgr->createEntity("pulley0", "cube.mesh");
		AxisAlignedBox aab = mMesh0->getBoundingBox();
		mMesh0->setCastShadows(true);
		mMesh0->setMaterialName("Examples/CubeDefault");

		Vector3 meshSize = aab.getSize();
		Vector3 scaling = Vector3(1.0f, 1.0f, 1.0f) / meshSize;

		mNode0 = mSceneMgr->getRootSceneNode()->createChildSceneNode("pulleyNode0");
		mNode0->setPosition(mMoveableBody0->getPosition()(0), mMoveableBody0->getPosition()(1), mMoveableBody0->getPosition()(2));
		mNode0->setScale(scaling);
		mNode0->attachObject(mMesh0);
	}

	// P. II
	{
		mMesh1 = mSceneMgr->createEntity("pulley1", "cube.mesh");
		AxisAlignedBox aab = mMesh1->getBoundingBox();
		mMesh1->setCastShadows(true);
		mMesh1->setMaterialName("Examples/Wall");

		Vector3 meshSize = aab.getSize();
		Vector3 scaling = Vector3(1.0f, 1.0f, 1.0f) / meshSize;

		mNode1 = mSceneMgr->getRootSceneNode()->createChildSceneNode("pulleyNode1");
		mNode1->setPosition(mMoveableBody1->getPosition()(0), mMoveableBody1->getPosition()(1), mMoveableBody1->getPosition()(2));
		mNode1->setScale(scaling);
		mNode1->attachObject(mMesh1);
	}
}

void Pulley::update() {
	mNode0->setPosition(mMoveableBody0->getPosition()(0), mMoveableBody0->getPosition()(1), mMoveableBody0->getPosition()(2));
	mNode1->setPosition(mMoveableBody1->getPosition()(0), mMoveableBody1->getPosition()(1), mMoveableBody1->getPosition()(2));
}