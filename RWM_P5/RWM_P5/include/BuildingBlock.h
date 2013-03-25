#pragma once
#include "stdafx.h"
#include <string>

using namespace Ogre;

static int numBlocks = 0;

class BuildingBlock {
private:

	// Havok stuff
	hkpWorld * mWorld;
	hkpRigidBody * blockBody;

	// Ogre Stuff
	SceneManager * mSceneMgr;
	SceneNode * mNode;
	Entity * mMesh;

public:
	BuildingBlock(Vector3 pos, Vector3 size, std::string materialName, hkpWorld * world, SceneManager * sceneMgr) :
		mWorld(world), mSceneMgr(sceneMgr)
	{
		numBlocks++;

		// Create physics box shape
		hkVector4 blockDimensions(size.x * 0.5, size.y * 0.5, size.z * 0.5);
		hkVector4 blockPosition(pos.x, pos.y, pos.z);
		hkpConvexShape * blockShape = new hkpBoxShape(blockDimensions, 0);

		// Set physical properties
		hkpRigidBodyCinfo blockInfo;
		blockInfo.m_motionType	= hkpMotion::MOTION_FIXED;
		blockInfo.m_qualityType = HK_COLLIDABLE_QUALITY_FIXED;
		blockInfo.m_restitution = 0.4;
		blockInfo.m_friction	= 0.8;
		blockInfo.m_position	= blockPosition;
		blockInfo.m_shape		= blockShape;

		blockBody = new hkpRigidBody(blockInfo);
		mWorld->addEntity(blockBody);
		blockShape->removeReference();

		char entityName[] = "000BuildingBlockEntity";
		entityName[0] += numBlocks;
		mMesh = mSceneMgr->createEntity(entityName, "cube.mesh");
		AxisAlignedBox aab = mMesh->getBoundingBox();
		mMesh->setCastShadows(true);
		mMesh->setMaterialName(materialName);

		Vector3 meshSize = aab.getSize();
		Vector3 scaling = size / meshSize;

		char nodeName[] = "000BuildingBlockNode";
		nodeName[0] += numBlocks;
		mNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(nodeName);
		mNode->setPosition(pos);
		mNode->setScale(scaling);
		mNode->attachObject(mMesh);
	};

	~BuildingBlock();
};