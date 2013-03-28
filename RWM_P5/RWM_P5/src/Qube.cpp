#include "stdafx.h"
#include "Qube.h"

Qube::Qube(Vector3 pos, Vector3 size, hkpWorld * world, SceneManager * sceneMgr) :
	mWorld(world), mSceneMgr(sceneMgr)
{
	numQubes++;

	// Create physics box shape
	hkVector4 qubeDimensions(size.x * 0.5, size.y * 0.5, size.z * 0.5);
	hkVector4 qubePosition(pos.x, pos.y, pos.z);
	hkpConvexShape * qubeShape = new hkpBoxShape(qubeDimensions, 0);

	// Set physical properties
	hkpRigidBodyCinfo qubeInfo;
	qubeInfo.m_motionType	= hkpMotion::MOTION_BOX_INERTIA;
	qubeInfo.m_qualityType = HK_COLLIDABLE_QUALITY_CRITICAL;
	qubeInfo.m_restitution = 0.0;
	qubeInfo.m_friction	= 0.5;
	qubeInfo.m_mass = 100.0f;
	qubeInfo.m_position	= qubePosition;
	qubeInfo.m_shape = qubeShape;

	mBody = new hkpRigidBody(qubeInfo);
	mWorld->addEntity(mBody);
	qubeShape->removeReference();

	char entityName[] = "000QubeEntity";
	entityName[0] += numQubes;
	mMesh = mSceneMgr->createEntity(entityName, "cube.mesh");
	AxisAlignedBox aab = mMesh->getBoundingBox();
	mMesh->setCastShadows(true);
	mMesh->setMaterialName("Examples/CubeDefault");

	Vector3 meshSize = aab.getSize();
	Vector3 scaling = size / meshSize;

	char nodeName[] = "000QubeNode";
	nodeName[0] += numQubes;
	mNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(nodeName);
	mNode->setPosition(pos);
	mNode->setScale(scaling);
	mNode->attachObject(mMesh);
}

void Qube::update() {
	mPosition = mBody->getPosition();
	mNode->setPosition(mPosition(0), mPosition(1), mPosition(2));

	hkVector4 hkAxis(0, 0, 0);
	mOrientation = mBody->getRotation();
	Radian angle(mOrientation.getAngle());
	if (mOrientation.hasValidAxis()) {
		mOrientation.getAxis(hkAxis);
	}
	Vector3 oAxis(hkAxis(0), hkAxis(1), hkAxis(2));
	Quaternion oOrientation(angle, oAxis);
	mNode->setOrientation(oOrientation);
}

void Qube::convertToDefault() {
	mMesh->setMaterialName("Examples/CubeDefault");
	mBody->setGravityFactor(1);
	mBody->setMass(100.0f);
	mBody->setRestitution(0.1f);
}

void Qube::convertToHeavy() {
	mMesh->setMaterialName("Examples/CubeHeavy");
	mBody->setGravityFactor(1);
	mBody->setMass(200.0f);
	mBody->setRestitution(0.0f);
}

void Qube::convertToFloaty() {
	mMesh->setMaterialName("Examples/CubeFloaty");
	mBody->setGravityFactor(0);
	mBody->setMass(100.0f);
}

void Qube::convertToBouncy() {
	mMesh->setMaterialName("Examples/CubeBouncy");
	mBody->setGravityFactor(1);
	mBody->setMass(200.0f);
	mBody->setRestitution(1.1f);
}