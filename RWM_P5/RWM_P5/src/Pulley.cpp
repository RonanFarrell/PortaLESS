#include "stdafx.h"
#include "Pulley.h"

Pulley::Pulley(Vector3 pivotPos1, Vector3 pivotPos2, hkpWorld * world, SceneManager * sceneMgr) : mWorld(world), mSceneMgr(sceneMgr)
{

	// Door
	hkVector4 doorSize(1.0f, 1.5f, 0.5f);
	hkpBoxShape * doorShape = new hkpBoxShape( doorSize , 0 );

	hkpRigidBodyCinfo doorInfo;
	doorInfo.m_shape = doorShape;
	doorInfo.m_mass = 400.0f;
	hkpInertiaTensorComputer::setShapeVolumeMassProperties(doorShape, doorInfo.m_mass, doorInfo);
	doorInfo.m_motionType = hkpMotion::MOTION_BOX_INERTIA;

	doorInfo.m_position.set(pivotPos1.x, pivotPos1.y - 2.0f, pivotPos1.z);
	mMoveableBody0 = new hkpRigidBody(doorInfo);
	doorShape->removeReference();

	// Container

	hkVector4 containerSize(1.5f, 0.25f, 1.5f);
	hkpBoxShape * containerShape = new hkpBoxShape(containerSize, 0);

	hkpRigidBodyCinfo containerInfo;
	containerInfo.m_shape = containerShape;
	containerInfo.m_mass = 200.0f;
	containerInfo.m_friction = 1.0f;
	hkpInertiaTensorComputer::setShapeVolumeMassProperties(containerShape, containerInfo.m_mass, containerInfo);
	containerInfo.m_motionType = hkpMotion::MOTION_BOX_INERTIA;
	containerInfo.m_position.set(pivotPos2.x, pivotPos2.y - 2.0f, pivotPos2.z);
	mMoveableBody1 = new hkpRigidBody(containerInfo);
	containerShape->removeReference();

	mWorld->addEntity(mMoveableBody0);
	mWorld->addEntity(mMoveableBody1);


	// Create pulley constraint
	worldPivots[0] = hkVector4(pivotPos1.x, pivotPos1.y, pivotPos1.z);
	worldPivots[1] = hkVector4(pivotPos2.x, pivotPos2.y, pivotPos2.z);

	hkpPulleyConstraintData * pulley = new hkpPulleyConstraintData();

	hkVector4 bodyPivots[2];
	bodyPivots[0] = hkVector4(0, 0, 0);
	bodyPivots[1] = hkVector4(0, 0, 0);
	hkReal leverageOnBodyB = 1.0f;

	pulley->setInBodySpace(mMoveableBody1->getTransform(), mMoveableBody0->getTransform(),
							bodyPivots[1], bodyPivots[0],
							worldPivots[1], worldPivots[0],
							leverageOnBodyB);

	pulley->setRopeLength(8.0f);

	hkpConstraintInstance * constraint = new hkpConstraintInstance(mMoveableBody1, mMoveableBody0, pulley);

	mWorld->addConstraint(constraint);
	constraint->removeReference();
	pulley->removeReference();

	hkpRigidBody * anchor0;
	hkpRigidBody * anchor1;
	// Add two helper bodies to prevent constrained bodies getting too close to the pulleys
	hkpRigidBodyCinfo helperInfo;
	helperInfo.m_motionType = hkpMotion::MOTION_FIXED;
	helperInfo.m_position = worldPivots[0];
	helperInfo.m_shape = new hkpSphereShape(0.3f);
	anchor0 = new hkpRigidBody(helperInfo);
	mWorld->addEntity(anchor0);

	helperInfo.m_position = worldPivots[1];
	anchor1 = new hkpRigidBody(helperInfo);
	mWorld->addEntity(anchor1);

	helperInfo.m_shape->removeReference();

	// Lock the orientation of the body
	//mMoveableBody0->setMaxAngularVelocity(0.0f);
	//mMoveableBody1->setMaxAngularVelocity(0.0f);

	// Create prismatic constraint
	hkVector4 axis(0.0f, 1.0f, 0.0f);
	hkpPrismaticConstraintData * prismatic = new hkpPrismaticConstraintData();
	prismatic->setMaxLinearLimit(20.0f);
	prismatic->setMinLinearLimit(-20.0f);
	prismatic->setInWorldSpace(mMoveableBody1->getTransform(), anchor1->getTransform(), worldPivots[1], axis);
	hkpConstraintInstance * prismaticConstraint = new hkpConstraintInstance(mMoveableBody1, anchor1, prismatic);
	mWorld->addConstraint(prismaticConstraint);
	prismaticConstraint->removeReference();
	prismatic->removeReference();

	prismatic = new hkpPrismaticConstraintData();
	prismatic->setMaxLinearLimit(20.0f);
	prismatic->setMinLinearLimit(-20.0f);
	prismatic->setInWorldSpace(mMoveableBody1->getTransform(), anchor1->getTransform(), worldPivots[0], axis);
	prismaticConstraint = new hkpConstraintInstance(mMoveableBody0, anchor0, prismatic);
	mWorld->addConstraint(prismaticConstraint);
	prismaticConstraint->removeReference();
	prismatic->removeReference();

	{
		mMesh0 = mSceneMgr->createEntity("pulley0", "cube.mesh");
		AxisAlignedBox aab = mMesh0->getBoundingBox();
		mMesh0->setCastShadows(true);
		mMesh0->setMaterialName("Examples/Wall");

		Vector3 meshSize = aab.getSize();
		Vector3 scaling = Vector3(2.0f, 3.0f, 1.0f) / meshSize;

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
		Vector3 scaling = Vector3(3.0f, 0.5f, 3.0f) / meshSize;

		mNode1 = mSceneMgr->getRootSceneNode()->createChildSceneNode("pulleyNode1");
		mNode1->setPosition(mMoveableBody1->getPosition()(0), mMoveableBody1->getPosition()(1), mMoveableBody1->getPosition()(2));
		mNode1->setScale(scaling);
		mNode1->attachObject(mMesh1);
	}

	// Rope
	rope = mSceneMgr->createManualObject("rope");
	rope->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);
	rope->colour(ColourValue(0, 1, 0, 1));
	rope->position(mMoveableBody0->getPosition()(0), mMoveableBody0->getPosition()(1), mMoveableBody0->getPosition()(2));
	rope->position(worldPivots[0](0), worldPivots[0](1), worldPivots[0](2));
	rope->position(worldPivots[1](0), worldPivots[1](1), worldPivots[1](2));
	rope->position(mMoveableBody1->getPosition()(0), mMoveableBody1->getPosition()(1), mMoveableBody1->getPosition()(2));
	rope->end();
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(rope);
}

void Pulley::update() {
	mNode0->setPosition(mMoveableBody0->getPosition()(0), mMoveableBody0->getPosition()(1), mMoveableBody0->getPosition()(2));
	mNode1->setPosition(mMoveableBody1->getPosition()(0), mMoveableBody1->getPosition()(1), mMoveableBody1->getPosition()(2));

	mMoveableBody0->setLinearVelocity(hkVector4(0, mMoveableBody0->getLinearVelocity()(1), 0));
	mMoveableBody1->setLinearVelocity(hkVector4(0, mMoveableBody1->getLinearVelocity()(1), 0));

	rope->clear();
	rope->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);
	rope->colour(ColourValue(0, 1, 0, 1));
	rope->position(mMoveableBody0->getPosition()(0), mMoveableBody0->getPosition()(1), mMoveableBody0->getPosition()(2));
	rope->position(worldPivots[0](0), worldPivots[0](1), worldPivots[0](2));
	rope->position(worldPivots[1](0), worldPivots[1](1), worldPivots[1](2));
	rope->position(mMoveableBody1->getPosition()(0), mMoveableBody1->getPosition()(1), mMoveableBody1->getPosition()(2));
	rope->end();
}