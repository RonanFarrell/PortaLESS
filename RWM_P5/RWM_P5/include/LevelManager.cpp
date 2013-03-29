#include "stdafx.h"
#include "LevelManager.h"

LevelManager::LevelManager(hkpWorld * world, Ogre::SceneManager * sceneMgr) :
	mWorld(world), mSceneMgr(sceneMgr)
{}

void LevelManager::loadLevel1() {
	// Room 1
	{
		// Floor
		buildingBlocks.push_back(new BuildingBlock(Vector3(0.0f, -0.5f, -5.0f), Vector3(15.0f, 1.0f, 20.0f), "Examples/FloorSafe", mWorld, mSceneMgr));
		buildingBlocks.push_back(new BuildingBlock(Vector3(-3.7f, 0.70f, -13.5f), Vector3(7.6f, 1.5f, 5.0f), "Examples/FloorSafe", mWorld, mSceneMgr));
		buildingBlocks.push_back(new BuildingBlock(Vector3(3.7f, 1.95f, -13.5f), Vector3(7.6f, 4.0f, 5.0f), "Examples/FloorSafe", mWorld, mSceneMgr));

		// Walls
		buildingBlocks.push_back(new BuildingBlock(Vector3(0.0f, 5.0f, 5.0f), Vector3(15.0f, 10.2f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));
		// Wall right of exit
		buildingBlocks.push_back(new BuildingBlock(Vector3(-3.0f, 5.0f, -15.0f), Vector3(9.5f, 10.2f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));
		// Wall right of exit
		buildingBlocks.push_back(new BuildingBlock(Vector3(6.5f, 5.0f, -15.0f), Vector3(2.0f, 10.2f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));
		// Wall above exit
		buildingBlocks.push_back(new BuildingBlock(Vector3(3.6f, 9.0f, -15.0f), Vector3(4.0f, 2.5f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));

		buildingBlocks.push_back(new BuildingBlock(Vector3(-7.5f, 5.0f, -5.0f), Vector3(1.0f, 10.2f, 20.0f), "Examples/Wall", mWorld, mSceneMgr));
		buildingBlocks.push_back(new BuildingBlock(Vector3(7.5f, 5.0f, -5.0f), Vector3(1.0f, 10.2f, 20.0f), "Examples/Wall", mWorld, mSceneMgr));

		// Roof
		buildingBlocks.push_back(new BuildingBlock(Vector3(0.0f, 10.0f, -5.0f), Vector3(15.0f, 1.0f, 20.0f), "Examples/Wall", mWorld, mSceneMgr));

		Ogre::Light* l = mSceneMgr->createLight("MainLight");
		l->setPosition(0.0f, 8.0f ,0.0f);
		l->setCastShadows(true);
	}

	// Room 1 to Room 2 corridor
	{
		buildingBlocks.push_back(new BuildingBlock(Vector3(3.6f, 3.4f, -18.0f), Vector3(4.0f, 1.04f, 5.0f), "Examples/FloorSafe", mWorld, mSceneMgr));
	}
}