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

	createRoom1(Vector3(0.0f, 0.0f, 0.0f));
	createCorridor(Vector3(5.0f, 4.0f, -17.0f));
	createRoom2(Vector3(7.0f, 4.0f, -32.0f));
	createCorridor(Vector3(9.0f, 8.0f, -47.0f));
	createRoom3(Vector3(11.0f, 8.0f, -64.0f));
	createCorridor(Vector3(13.0f, 8.0f, -81.0f));
	createRoom4(Vector3(15.0f, 8.0f, -93.0f));
}

void LevelManager::update() {
	std::vector<SeeSaw *>::iterator seeSawIter = seeSaws.begin();
	for ( ; seeSawIter != seeSaws.end(); seeSawIter++ ) {
		(*seeSawIter)->update();
	}

	std::vector<Qube *>::iterator qIter = qubes.begin();
	for ( ; qIter != qubes.end(); qIter++ ) {
		(*qIter)->update();
	}
	std::vector<Extrusion *>::iterator extrusionsIter = extrusions.begin();
	for ( ; extrusionsIter != extrusions.end(); extrusionsIter++) {
		(*extrusionsIter)->update();
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
	buildingBlocks.push_back(new BuildingBlock(Vector3(0.0f, 0.5f, 2.0f)+pos, Vector3(12.0f, 1.0f, 12.0f), "Examples/Wall", mWorld, mSceneMgr));
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
	// Qube
	qubes.push_back(new Qube(Vector3(2.0f, 2.0f, 0.0f)+pos, Vector3(1.0f, 1.0f, 1.0f), mWorld, mSceneMgr));
	// SeeSaw
	seeSaws.push_back(new SeeSaw(Vector3(0.0f, 2.0f, -2.0f)+pos, Vector3(2.0f, 0.1f, 8.0f), Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.5f), mWorld, mSceneMgr));
}

void LevelManager::createRoom3(Vector3 pos) {
	// Floor
	buildingBlocks.push_back(new BuildingBlock(Vector3(0.0f, 0.5f, 0.0f)+pos, Vector3(16.0f, 1.0f, 20.0f), "Examples/Wall", mWorld, mSceneMgr));
	// Wall left of entrance
	buildingBlocks.push_back(new BuildingBlock(Vector3(4.5f, 5.0f, 10.5f)+pos, Vector3(7.0f, 8.0f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));
	// Wall right of entrance
	buildingBlocks.push_back(new BuildingBlock(Vector3(-4.5f, 5.0f, 10.5f)+pos, Vector3(7.0f, 8.0f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));
	// Wall above entrance
	buildingBlocks.push_back(new BuildingBlock(Vector3(0.0f, 6.5f, 10.5f)+pos, Vector3(2.0f, 5.0f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));
	// Wall right of exit
	buildingBlocks.push_back(new BuildingBlock(Vector3(4.5f, 5.0f, -10.5f)+pos, Vector3(7.0f, 8.0f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));
	// Wall left of exit
	buildingBlocks.push_back(new BuildingBlock(Vector3(-4.5f, 5.0f, -10.5f)+pos, Vector3(7.0f, 8.0f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));
	// Wall above exit
	buildingBlocks.push_back(new BuildingBlock(Vector3(0.0f, 6.5f, -10.5f)+pos, Vector3(2.0f, 5.0f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));
	// Left wall
	buildingBlocks.push_back(new BuildingBlock(Vector3(8.5f, 5.0f, 0.0f)+pos, Vector3(1.0f, 8.0f, 20.0f), "Examples/Wall", mWorld, mSceneMgr));
	// Right wall
	buildingBlocks.push_back(new BuildingBlock(Vector3(-8.5f, 5.0f, 0.0f)+pos, Vector3(1.0f, 8.0f, 20.0f), "Examples/Wall", mWorld, mSceneMgr));
	// Roof
	buildingBlocks.push_back(new BuildingBlock(Vector3(0.0f, 9.5f, 0.0f)+pos, Vector3(16.0f, 1.0f, 20.0f), "Examples/Wall", mWorld, mSceneMgr));

	// Top platform
	buildingBlocks.push_back(new BuildingBlock(Vector3(5.0f, 3.0f, 5.0f)+pos, Vector3(6.0f, 4.0f, 10.0f), "Examples/Wall", mWorld, mSceneMgr));
	// Step
	buildingBlocks.push_back(new BuildingBlock(Vector3(5.0f, 2.0f, -1.0f)+pos, Vector3(6.0f, 2.0f, 2.0f), "Examples/Wall", mWorld, mSceneMgr));

	// Create pulley system
	p = new Pulley(Vector3(0.0f, 8.0f, -9.5f)+pos, Vector3(0.0f, 8.0f, 3.0f)+pos, mWorld, mSceneMgr);

	// Qubes
	qubes.push_back(new Qube(Vector3(-4.0f, 1.0f, 0.0f)+pos, Vector3(1.0f, 1.0f, 1.0f), mWorld, mSceneMgr));
	qubes.push_back(new Qube(Vector3(-4.0f, 1.0f, 3.0f)+pos, Vector3(1.0f, 1.0f, 1.0f), mWorld, mSceneMgr));
	qubes.push_back(new Qube(Vector3(-4.0f, 1.0f, 6.0f)+pos, Vector3(1.0f, 1.0f, 1.0f), mWorld, mSceneMgr));
	qubes.push_back(new Qube(Vector3(-4.0f, 1.0f, -3.0f)+pos, Vector3(1.0f, 1.0f, 1.0f), mWorld, mSceneMgr));
}

void LevelManager::createRoom4(Vector3 pos) {
	// Floor
	buildingBlocks.push_back(new BuildingBlock(Vector3(0.0f, 0.5f, 0.0f)+pos, Vector3(10.0f, 1.0f, 10.0f), "Examples/Wall", mWorld, mSceneMgr));
	// Roof
	buildingBlocks.push_back(new BuildingBlock(Vector3(0.0f, 17.5f, 0.0f)+pos, Vector3(10.0f, 1.0f, 10.0f), "Examples/Wall", mWorld, mSceneMgr));

	buildingBlocks.push_back(new BuildingBlock(Vector3(-3.05f, 9.0f, 5.5f)+pos, Vector3(4.1f, 16.0f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));//0
	buildingBlocks.push_back(new BuildingBlock(Vector3(0.0f, 10.5f, 5.5f)+pos, Vector3(2.0f, 13.0f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));//1
	buildingBlocks.push_back(new BuildingBlock(Vector3(2.0f, 15.0f, 5.5f)+pos, Vector3(2.0f, 4.0f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));//2
	buildingBlocks.push_back(new BuildingBlock(Vector3(4.0f, 14.5f, 5.5f)+pos, Vector3(2.0f, 5.0f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));//3
	buildingBlocks.push_back(new BuildingBlock(Vector3(2.0f, 11.5f, 5.5f)+pos, Vector3(2.0f, 1.0f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));//4
	buildingBlocks.push_back(new BuildingBlock(Vector3(3.0f, 6.0f, 5.5f)+pos, Vector3(4.0f, 10.0f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));//5

	buildingBlocks.push_back(new BuildingBlock(Vector3(-5.5f, 10.0f, -2.0f)+pos, Vector3(0.9f, 14.0f, 6.0f), "Examples/Wall", mWorld, mSceneMgr));//6
	buildingBlocks.push_back(new BuildingBlock(Vector3(-5.5f, 9.0f, 3.0f)+pos, Vector3(0.9f, 16.0f, 4.0f), "Examples/Wall", mWorld, mSceneMgr));//7
	buildingBlocks.push_back(new BuildingBlock(Vector3(-5.5f, 2.0f, -4.0f)+pos, Vector3(0.9f, 2.0f, 2.0f), "Examples/Wall", mWorld, mSceneMgr));//8
	buildingBlocks.push_back(new BuildingBlock(Vector3(-5.5f, 1.5f, -2.0f)+pos, Vector3(0.9f, 1.0f, 2.0f), "Examples/Wall", mWorld, mSceneMgr));//9
	buildingBlocks.push_back(new BuildingBlock(Vector3(-5.5f, 2.5f, 0.0f)+pos, Vector3(0.9f, 1.0f, 2.0f), "Examples/Wall", mWorld, mSceneMgr));//10

	buildingBlocks.push_back(new BuildingBlock(Vector3(4.0f, 9.0f, -5.5f)+pos, Vector3(2.0f, 16.0f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));//11
	buildingBlocks.push_back(new BuildingBlock(Vector3(2.0f, 12.0f, -5.5f)+pos, Vector3(2.0f, 10.0f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));//12
	buildingBlocks.push_back(new BuildingBlock(Vector3(0.0f, 10.0f, -5.5f)+pos, Vector3(2.0f, 8.0f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));//13
	buildingBlocks.push_back(new BuildingBlock(Vector3(-2.0f, 11.0f, -5.5f)+pos, Vector3(2.0f, 12.0f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));//14
	buildingBlocks.push_back(new BuildingBlock(Vector3(-4.0f, 10.5f, -5.5f)+pos, Vector3(2.0f, 13.0f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));//15
	buildingBlocks.push_back(new BuildingBlock(Vector3(-4.0f, 2.0f, -5.5f)+pos, Vector3(2.0f, 2.0f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));//16
	buildingBlocks.push_back(new BuildingBlock(Vector3(-2.0f, 2.5f, -5.5f)+pos, Vector3(2.0f, 3.0f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));//17
	buildingBlocks.push_back(new BuildingBlock(Vector3(0.0f, 3.0f, -5.5f)+pos, Vector3(2.0f, 4.0f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));//18
	buildingBlocks.push_back(new BuildingBlock(Vector3(2.0f, 3.5f, -5.5f)+pos, Vector3(2.0f, 5.0f, 1.0f), "Examples/Wall", mWorld, mSceneMgr));//19

	buildingBlocks.push_back(new BuildingBlock(Vector3(5.5f, 9.0f, 4.0f)+pos, Vector3(1.0f, 16.0f, 2.0f), "Examples/Wall", mWorld, mSceneMgr));//20
	buildingBlocks.push_back(new BuildingBlock(Vector3(5.5f, 14.0f, 2.0f)+pos, Vector3(1.0f, 6.0f, 2.0f), "Examples/Wall", mWorld, mSceneMgr));//21
	buildingBlocks.push_back(new BuildingBlock(Vector3(5.5f, 13.5f, 0.0f)+pos, Vector3(1.0f, 7.0f, 2.0f), "Examples/Wall", mWorld, mSceneMgr));//22
	buildingBlocks.push_back(new BuildingBlock(Vector3(5.5f, 13.0f, -2.0f)+pos, Vector3(1.0f, 8.0f, 2.0f), "Examples/Wall", mWorld, mSceneMgr));//23
	buildingBlocks.push_back(new BuildingBlock(Vector3(5.5f, 12.5f, -4.0f)+pos, Vector3(1.0f, 9.0f, 2.0f), "Examples/Wall", mWorld, mSceneMgr));//24
	buildingBlocks.push_back(new BuildingBlock(Vector3(5.5f, 4.0f, -4.0f)+pos, Vector3(1.0f, 6.0f, 2.0f), "Examples/Wall", mWorld, mSceneMgr));//25
	buildingBlocks.push_back(new BuildingBlock(Vector3(5.5f, 4.5f, -2.0f)+pos, Vector3(1.0f, 7.0f, 2.0f), "Examples/Wall", mWorld, mSceneMgr));//26
	buildingBlocks.push_back(new BuildingBlock(Vector3(5.5f, 5.0f, 0.0f)+pos, Vector3(1.0f, 8.0f, 2.0f), "Examples/Wall", mWorld, mSceneMgr));//27
	buildingBlocks.push_back(new BuildingBlock(Vector3(5.5f, 5.5f, 2.0f)+pos, Vector3(1.0f, 9.0f, 2.0f), "Examples/Wall", mWorld, mSceneMgr));//28

	// Extrusion
	extrusions.push_back(new Extrusion(Vector3(-6.0f, 1.5f, 0.0f)+pos, Vector3(2.0f, 1.0f, 2.0f), Vector3(1.0f, 0.0f, 0.0f), 2.0f, mWorld, mSceneMgr));
	extrusions.push_back(new Extrusion(Vector3(-6.0f, 2.5f, -2.0f)+pos, Vector3(2.0f, 1.0f, 2.0f), Vector3(1.0f, 0.0f, 0.0f), 2.0f, mWorld, mSceneMgr));
	extrusions.push_back(new Extrusion(Vector3(-4.0f, 3.5f, -6.0f)+pos, Vector3(2.0f, 1.0f, 2.0f), Vector3(0.0f, 0.0f, 1.0f), 2.0f, mWorld, mSceneMgr));
	extrusions.push_back(new Extrusion(Vector3(-2.0f, 4.5f, -6.0f)+pos, Vector3(2.0f, 1.0f, 2.0f), Vector3(0.0f, 0.0f, 1.0f), 2.0f, mWorld, mSceneMgr));
	extrusions.push_back(new Extrusion(Vector3(0.0f, 5.5f, -6.0f)+pos, Vector3(2.0f, 1.0f, 2.0f), Vector3(0.0f, 0.0f, 1.0f), 2.0f, mWorld, mSceneMgr));
	extrusions.push_back(new Extrusion(Vector3(2.0f, 6.5f, -6.0f)+pos, Vector3(2.0f, 1.0f, 2.0f), Vector3(0.0f, 0.0f, 1.0f), 2.0f, mWorld, mSceneMgr));
	extrusions.push_back(new Extrusion(Vector3(6.0f, 7.5f, -4.0f)+pos, Vector3(2.0f, 1.0f, 2.0f), Vector3(-1.0f, 0.0f, 0.0f), 2.0f, mWorld, mSceneMgr));
	extrusions.push_back(new Extrusion(Vector3(6.0f, 8.5f, -2.0f)+pos, Vector3(2.0f, 1.0f, 2.0f), Vector3(-1.0f, 0.0f, 0.0f), 2.0f, mWorld, mSceneMgr));
	extrusions.push_back(new Extrusion(Vector3(6.0f, 9.5f, 0.0f)+pos, Vector3(2.0f, 1.0f, 2.0f), Vector3(-1.0f, 0.0f, 0.0f), 2.0f, mWorld, mSceneMgr));
	extrusions.push_back(new Extrusion(Vector3(6.0f, 10.5f, 2.0f)+pos, Vector3(2.0f, 1.0f, 2.0f), Vector3(-1.0f, 0.0f, 0.0f), 2.0f, mWorld, mSceneMgr));
	extrusions.push_back(new Extrusion(Vector3(4.0f, 11.5f, 6.0f)+pos, Vector3(2.0f, 1.0f, 2.0f), Vector3(0.0f, 0.0f, -1.0f), 2.0f, mWorld, mSceneMgr));
	extrusions.push_back(new Extrusion(Vector3(2.0f, 12.5f, 6.0f)+pos, Vector3(2.0f, 1.0f, 2.0f), Vector3(0.0f, 0.0f, -1.0f), 2.0f, mWorld, mSceneMgr));
	 
	// Platform at top
	buildingBlocks.push_back(new BuildingBlock(Vector3(0.0f, 13.75f, 0.0f)+pos, Vector3(2.0f, 0.5f, 10.0f), "Examples/Wall", mWorld, mSceneMgr));
}
