/*
-----------------------------------------------------------------------------
Filename:    RWM_P5.cpp
-----------------------------------------------------------------------------


This source file is generated by the
   ___                   _              __    __ _                  _ 
  /___\__ _ _ __ ___    /_\  _ __  _ __/ / /\ \ (_)______ _ _ __ __| |
 //  // _` | '__/ _ \  //_\\| '_ \| '_ \ \/  \/ / |_  / _` | '__/ _` |
/ \_// (_| | | |  __/ /  _  \ |_) | |_) \  /\  /| |/ / (_| | | | (_| |
\___/ \__, |_|  \___| \_/ \_/ .__/| .__/ \/  \/ |_/___\__,_|_|  \__,_|
      |___/                 |_|   |_|                                 
      Ogre 1.8.x Application Wizard for VC10 (May 2012)
      https://bitbucket.org/jacmoe/ogreappwizards
-----------------------------------------------------------------------------
*/

#include "stdafx.h"
#include "RWM_P5.h"

//-------------------------------------------------------------------------------------
RWM_P5::RWM_P5(void)
{
}
//-------------------------------------------------------------------------------------
RWM_P5::~RWM_P5(void)
{
}

//-------------------------------------------------------------------------------------
void RWM_P5::createScene(void)
{
	physics.SetUp();


    // Set ambient light
    mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0, 1.0, 1.0));
	//mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);

	// Create the player
	levelManager = new LevelManager(physics.GetPhysicsWorld(), mSceneMgr);
	levelManager->loadLevel1();
	player = new Player(Ogre::Vector3(13.0f, 12.0f, -81.0f), physics.GetPhysicsWorld(), mSceneMgr);
	qube = new Qube(Ogre::Vector3(3.0f, 2.0f, 0.0f), Ogre::Vector3(1.0f, 1.0f, 1.0f), physics.GetPhysicsWorld(), mSceneMgr);
}



#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        RWM_P5 app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
