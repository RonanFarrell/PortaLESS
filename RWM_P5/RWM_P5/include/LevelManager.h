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
	std::vector<ManualObject *> mLevelOutline;
	ManualObject * createOutline(Vector3 pos, Vector3 size, String name);

	void createRoom1(Vector3 pos);
public:
	LevelManager();
	LevelManager(hkpWorld * world, Ogre::SceneManager * sceneMgr);
	~LevelManager();

	void loadLevel1();

	void update();
};