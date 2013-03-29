#pragma once
#include "stdafx.h"
#include "BuildingBlock.h"
#include "SeeSaw.h"

class LevelManager {
private:
	std::vector<BuildingBlock *> buildingBlocks;
	std::vector<SeeSaw *> seeSaws;
	hkpWorld * mWorld;
	Ogre::SceneManager * mSceneMgr;

public:
	LevelManager();
	LevelManager(hkpWorld * world, Ogre::SceneManager * sceneMgr);
	~LevelManager();

	void loadLevel1();

	void update();
};