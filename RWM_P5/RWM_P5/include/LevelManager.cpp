#include "stdafx.h"
#include "LevelManager.h"

LevelManager::LevelManager(hkpWorld * world, Ogre::SceneManager * sceneMgr) :
mWorld(world), mSceneMgr(sceneMgr)
{
	
}

void LevelManager::loadLevel1() {
	Ogre::Light* l = mSceneMgr->createLight("MainLight");
	l->setPosition(0.0f, 8.0f ,0.0f);
	l->setCastShadows(false);

	p = new Pulley(mWorld, mSceneMgr);

	createRoom1(Vector3(0.0f, 0.0f, 0.0f));
	createCorridor(Vector3(5.0f, 4.0f, -17.0f));
	createRoom2(Vector3(7.0f, 4.0f, -32.0f));
}

void LevelManager::update() {
	std::vector<SeeSaw *>::iterator seeSawIter = seeSaws.begin();
	for ( ; seeSawIter != seeSaws.end(); seeSawIter++ ) {
		(*seeSawIter)->update();
	}

	p->update();
}

void LevelManager::createCorridor(Vector3 pos) {
	// Middle section floor & roof
	buildingBlocks.push_back(new BuildingBlock(Vector3(0.0f, 0.5f, 0.0f)+pos, Vector3(6.0f, 1.0f, 2.0f), "Examples/Wall", mWorld, mSceneMgr));
	buildingBlocks.push_back(new BuildingBlock(Vector3(0.0f, 4.5f, 0.0f)+pos, Vector3(6.0f, 1.0f, 2.0f), "Examples/Wall", mWorld, mSceneMgr));
	// Middle section walls
	buildingBlocks.push_back(new BuildingBlock(Vector3(-1.0f, 2.5f, -1.5f)+pos, Vector3(4.0f, 3.0f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));
	buildingBlocks.push_back(new BuildingBlock(Vector3(1.0f, 2.5f, 1.5f)+pos, Vector3(4.0f, 3.0f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));
	// First section floor & roof
	buildingBlocks.push_back(new BuildingBlock(Vector3(-2.0f, 0.5f, 4.0f)+pos, Vector3(2.0f, 1.0f, 6.0f), "Examples/Wall", mWorld, mSceneMgr));
	buildingBlocks.push_back(new BuildingBlock(Vector3(-2.0f, 4.5f, 3.5f)+pos, Vector3(2.0f, 1.0f, 5.0f), "Examples/Wall", mWorld, mSceneMgr));
	// First section walls
	buildingBlocks.push_back(new BuildingBlock(Vector3(-3.5f, 2.5f, 2.5f)+pos, Vector3(1.0f, 3.0f, 7.0f), "Examples/Wall", mWorld, mSceneMgr));
	buildingBlocks.push_back(new BuildingBlock(Vector3(-0.5f, 2.5f, 4.0f)+pos, Vector3(1.0f, 3.0f, 4.0f), "Examples/Wall", mWorld, mSceneMgr));
	// End section floor & roof
	buildingBlocks.push_back(new BuildingBlock(Vector3(2.0f, 0.5f, -4.0f)+pos, Vector3(2.0f, 1.0f, 6.0f), "Examples/Wall", mWorld, mSceneMgr));
	buildingBlocks.push_back(new BuildingBlock(Vector3(2.0f, 4.5f, -3.5f)+pos, Vector3(2.0f, 1.0f, 5.0f), "Examples/Wall", mWorld, mSceneMgr));
	// End section walls
	buildingBlocks.push_back(new BuildingBlock(Vector3(3.5f, 2.5f, -2.5f)+pos, Vector3(1.0f, 3.0f, 7.0f), "Examples/Wall", mWorld, mSceneMgr));
	buildingBlocks.push_back(new BuildingBlock(Vector3(0.5f, 2.5f, -4.0f)+pos, Vector3(1.0f, 3.0f, 4.0f), "Examples/Wall", mWorld, mSceneMgr));
}

void LevelManager::createRoom1(Vector3 pos) {
	// Floor
	buildingBlocks.push_back(new BuildingBlock(Vector3(0.0f, -5.5f, 2.0f)+pos, Vector3(12.0f, 1.0f, 12.0f), "Examples/Wall", mWorld, mSceneMgr));
	// First Step
	buildingBlocks.push_back(new BuildingBlock(Vector3(-3.0f, 1.75f, -7.0f)+pos, Vector3(6.0f, 1.5f, 6.0f), "Examples/Wall", mWorld, mSceneMgr));
	// Second Step
	buildingBlocks.push_back(new BuildingBlock(Vector3(3.0f, 3.0f, -7.0f)+pos, Vector3(6.0f, 4.0f, 6.0f), "Examples/Wall", mWorld, mSceneMgr));
	// Wall left of exit
	buildingBlocks.push_back(new BuildingBlock(Vector3(-2.0f, 5.0f, -10.5f)+pos, Vector3(8.0f, 8.0f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));
	// Wall right of exit
	buildingBlocks.push_back(new BuildingBlock(Vector3(5.0f, 7.0f, -10.5f)+pos, Vector3(2.0f, 4.0f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));
	// Wall above exit
	buildingBlocks.push_back(new BuildingBlock(Vector3(3.0f, 8.5f, -10.5f)+pos, Vector3(2.0f, 1.0f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));
	// Left wall
	buildingBlocks.push_back(new BuildingBlock(Vector3(-6.5f, 5.0f, -1.0f)+pos, Vector3(1.0f, 8.0f, 18.0f), "Examples/Wall", mWorld, mSceneMgr));
	// Right wall
	buildingBlocks.push_back(new BuildingBlock(Vector3(6.5f, 5.0f, -1.0f)+pos, Vector3(1.0f, 8.0f, 18.0f), "Examples/Wall", mWorld, mSceneMgr));
	// Back wall
	buildingBlocks.push_back(new BuildingBlock(Vector3(0.0f, 5.0f, 8.5f)+pos, Vector3(12.0f, 8.0f, 1.0f), "Examples/Controls", mWorld, mSceneMgr));
	// Roof
	buildingBlocks.push_back(new BuildingBlock(Vector3(0.0f, 9.5f, -1.0f)+pos, Vector3(12.0f, 1.0f, 18.0f), "Examples/Wall", mWorld, mSceneMgr));
}

void LevelManager::createRoom2(Vector3 pos) {
	// Floor
	buildingBlocks.push_back(new BuildingBlock(Vector3(0.0f, 0.5f, 0.0f)+pos, Vector3(10.0f, 1.0f, 16.0f), "Examples/Wall", mWorld, mSceneMgr));
	// Left wall
	buildingBlocks.push_back(new BuildingBlock(Vector3(-5.5f, 5.0f, 0.0f)+pos, Vector3(1.0f, 8.0f, 16.0f), "Examples/Wall", mWorld, mSceneMgr));
	// Right wall
	buildingBlocks.push_back(new BuildingBlock(Vector3(5.5f, 5.0f, 0.0f)+pos, Vector3(1.0f, 8.0f, 16.0f), "Examples/Wall", mWorld, mSceneMgr));
	// Back wall left
	buildingBlocks.push_back(new BuildingBlock(Vector3(3.0f, 5.0f, 8.5f)+pos, Vector3(4.0f, 8.0f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));
	// Back wall right
	buildingBlocks.push_back(new BuildingBlock(Vector3(-3.0f, 5.0f, 8.5f)+pos, Vector3(4.0f, 8.0f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));
	// Wall above entrance
	buildingBlocks.push_back(new BuildingBlock(Vector3(0.0f, 6.5f, 8.5f)+pos, Vector3(2.0f, 5.0f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));
	// Wall exit right
	buildingBlocks.push_back(new BuildingBlock(Vector3(3.0f, 5.0f, -8.5f)+pos, Vector3(4.0f, 8.0f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));
	// Wall exit left
	buildingBlocks.push_back(new BuildingBlock(Vector3(-3.0f, 5.0f, -8.5f)+pos, Vector3(4.0f, 8.0f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));
	// Wall below exit
	buildingBlocks.push_back(new BuildingBlock(Vector3(0.0f, 3.0f, -8.5f)+pos, Vector3(2.0f, 4.0f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));
	// Wall above exit
	buildingBlocks.push_back(new BuildingBlock(Vector3(0.0f, 8.5f, -8.5f)+pos, Vector3(2.0f, 1.0f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));
	// Roof
	buildingBlocks.push_back(new BuildingBlock(Vector3(0.0f, 9.5f, 0.0f)+pos, Vector3(10.0f, 1.0f, 16.0f), "Examples/Wall", mWorld, mSceneMgr));

	// SeeSaw
	seeSaws.push_back(new SeeSaw(Vector3(0.0f, 2.0f, -2.0f)+pos, Vector3(2.0f, 0.1f, 8.0f), Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.5f), mWorld, mSceneMgr));
}