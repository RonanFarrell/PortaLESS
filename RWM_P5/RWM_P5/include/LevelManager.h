#pragma once
#include "stdafx.h"
#include "BuildingBlock.h"

class LevelManager {
private:
	std::vector<BuildingBlock *> buildingBlocks;
	hkpWorld * mWorld;
	Ogre::SceneManager * mSceneMgr;

public:
	LevelManager();
	LevelManager(hkpWorld * world, Ogre::SceneManager * sceneMgr);
	~LevelManager();

	void loadLevel1();
};