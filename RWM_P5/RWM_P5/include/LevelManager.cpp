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
		l->setCastShadows(false);
	}

	// Room 1 to Room 2 corridor
	{
		Ogre::Light* lq = mSceneMgr->createLight("MainLightq");
		lq->setPosition(20.0f, 8.0f ,-50.0f);
		lq->setCastShadows(false);

		// Corridor floor
		buildingBlocks.push_back(new BuildingBlock(Vector3(3.6f, 3.4f, -20.3f), Vector3(4.0f, 1.04f, 10.0f), "Examples/FloorSafe", mWorld, mSceneMgr));
		buildingBlocks.push_back(new BuildingBlock(Vector3(10.4f, 3.4f, -23.3f), Vector3(10.0f, 1.04f, 4.0f), "Examples/FloorSafe", mWorld, mSceneMgr));
		// Corridor roof
		buildingBlocks.push_back(new BuildingBlock(Vector3(3.6f, 8.3f, -20.3f), Vector3(4.0f, 1.04f, 10.0f), "Examples/FloorSafe", mWorld, mSceneMgr));
		buildingBlocks.push_back(new BuildingBlock(Vector3(10.4f, 8.3f, -23.3f), Vector3(10.0f, 1.04f, 4.0f), "Examples/FloorSafe", mWorld, mSceneMgr));

		// Left wall
		buildingBlocks.push_back(new BuildingBlock(Vector3(1.16f, 6.1f, -20.3f), Vector3(1.0f, 4.54f, 10.0f), "Examples/Wall", mWorld, mSceneMgr));
		buildingBlocks.push_back(new BuildingBlock(Vector3(6.01f, 6.1f, -18.4f), Vector3(1.0f, 4.54f, 6.0f), "Examples/Wall", mWorld, mSceneMgr));
		buildingBlocks.push_back(new BuildingBlock(Vector3(8.15f, 6.1f, -25.3f), Vector3(14.65f, 4.54f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));
		buildingBlocks.push_back(new BuildingBlock(Vector3(10.9f, 6.1f, -20.85f), Vector3(9.0f, 4.54f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));
	}

	// Room 2
	{
		// floor
		buildingBlocks.push_back(new BuildingBlock(Vector3(25.0f, 3.4f, -23.0f), Vector3(20.0f, 1.0f, 15.0f), "Examples/FloorSafe", mWorld, mSceneMgr));
		// left wall
		buildingBlocks.push_back(new BuildingBlock(Vector3(25.0f, 8.4f, -30.0f), Vector3(20.0f, 10.0f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));
		// right wall
		buildingBlocks.push_back(new BuildingBlock(Vector3(25.0f, 8.4f, -15.2f), Vector3(20.0f, 10.0f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));
		// left of entrance
		buildingBlocks.push_back(new BuildingBlock(Vector3(15.0f, 8.4f, -18.0f), Vector3(1.0f, 10.0f, 6.82f), "Examples/Wall", mWorld, mSceneMgr));
		// right of entrance
		buildingBlocks.push_back(new BuildingBlock(Vector3(15.0f, 8.4f, -28.15f), Vector3(1.0f, 10.0f, 6.82f), "Examples/Wall", mWorld, mSceneMgr));
		// above entrance
		buildingBlocks.push_back(new BuildingBlock(Vector3(15.0f, 10.57f, -23.15f), Vector3(1.0f, 5.7f, 4.0f), "Examples/Wall", mWorld, mSceneMgr));
		// exit
		buildingBlocks.push_back(new BuildingBlock(Vector3(35.0f, 8.4f, -18.0f), Vector3(1.0f, 10.0f, 6.82f), "Examples/Wall", mWorld, mSceneMgr));
		buildingBlocks.push_back(new BuildingBlock(Vector3(35.0f, 8.4f, -28.15f), Vector3(1.0f, 10.0f, 6.82f), "Examples/Wall", mWorld, mSceneMgr));
		buildingBlocks.push_back(new BuildingBlock(Vector3(35.0f, 5.57f, -23.15f), Vector3(1.0f, 4.0f, 4.0f), "Examples/Wall", mWorld, mSceneMgr));

		seeSaws.push_back(new SeeSaw(Vector3(27.0f, 5.0f, -23.15f), Vector3(10.0f, 0.2f, 2.0f), Vector3(0, 0, 1), Vector3(-1,0,0), mWorld, mSceneMgr));
	}
}

void LevelManager::update() {
	std::vector<SeeSaw *>::iterator seeSawIter = seeSaws.begin();
	for ( ; seeSawIter != seeSaws.end(); seeSawIter++ ) {
		(*seeSawIter)->update();
	}
}