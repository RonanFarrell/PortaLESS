#include "stdafx.h"
#include "Player.h"

Player::Player() {

}

Player::~Player() {

}

Player::Player(Vector3 spawnLocation, hkpWorld * world, SceneManager * sceneMgr):
	mWorld(world), mSceneMgr(sceneMgr)
{
	mWorld->lock();

	// Setup Havok stuff
	hkVector4 vertexA(0, 0, 0.4f);
	hkVector4 vertexB(0, 0, -0.4f);

	mStandShape = new hkpCapsuleShape(vertexA, vertexB, 0.6f);

	vertexA.setZero4();
	mCrouchShape = new hkpCapsuleShape(vertexA, vertexB, 0.6f);

	// Construct character rigid body
	hkpCharacterRigidBodyCinfo info;
	info.m_mass = 60.0f;
	info.m_shape = mStandShape;

	info.m_maxForce = 6000.0f;
	info.m_up = hkVector4(0.0, 1.0, 0.0);
	info.m_position.set(spawnLocation.x, spawnLocation.y, spawnLocation.z);
	info.m_maxSlope = 60.0f * HK_REAL_DEG_TO_RAD;

	mCharacterBody = new hkpCharacterRigidBody( info );
	hkpCharacterRigidBodyListener * listener = new hkpCharacterRigidBodyListener();
	mCharacterBody->setListener( listener );
	listener->removeReference();

	mWorld->addEntity( mCharacterBody->getRigidBody() );

	// Create character state machine and context
	hkpCharacterState * state;
	hkpCharacterStateManager * manager = new hkpCharacterStateManager();

	state = new hkpCharacterStateOnGround();
	manager->registerState( state,	HK_CHARACTER_ON_GROUND);
	state->removeReference();

	state = new hkpCharacterStateInAir();
	manager->registerState( state,	HK_CHARACTER_IN_AIR);
	state->removeReference();

	state = new hkpCharacterStateJumping();
	manager->registerState( state,	HK_CHARACTER_JUMPING);
	state->removeReference();

	state = new hkpCharacterStateClimbing();
	manager->registerState( state,	HK_CHARACTER_CLIMBING);
	state->removeReference();

	mCharacterContext = new hkpCharacterContext( manager, HK_CHARACTER_ON_GROUND );
	manager->removeReference();

	// Set character type
	mCharacterContext->setCharacterType(hkpCharacterContext::HK_CHARACTER_RIGIDBODY);
	mPreviousGround = new hkpSurfaceInfo();
	mCurrentAngle = HK_REAL_PI;

	mWorld->unlock();

	//Setup Ogre stuff
	mMesh = mSceneMgr->createEntity("PlayerMesh", "ogrehead.mesh");

    mNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("PlayerNode");
    mNode->attachObject(mMesh);

	float r = mMesh->getBoundingRadius();
	float scalefactor=1.5*1.0/r;

	mNode->setPosition(spawnLocation);
	mNode->setScale(scalefactor,scalefactor,scalefactor);
}

void Player::update(int UD, int LR, bool jump, Camera * cam, float dt) {
	if (dt <= 0)
		return;

	mWorld->lock();

	hkVector4 pos = mCharacterBody->getRigidBody()->getPosition();

	mCurrentOrientation.setAxisAngle(hkVector4(0, 1, 0), mCurrentAngle);

	hkpCharacterInput input;
	hkpCharacterOutput output;
	{
		input.m_inputLR = LR;
		input.m_inputUD = UD;

		input.m_wantJump = jump;
		input.m_atLadder = false;

		input.m_up.set(0, 1, 0);
		input.m_forward.set(0, 0, -1);
		input.m_forward.setRotatedDir( mCurrentOrientation, input.m_forward );

		hkStepInfo stepInfo;
		stepInfo.m_deltaTime = dt;
		stepInfo.m_invDeltaTime = 1.0f / dt;

		input.m_stepInfo = stepInfo;

		input.m_characterGravity.set(0, -16, 0);
		input.m_velocity = mCharacterBody->getRigidBody()->getLinearVelocity();
		input.m_position = pos;

		mCharacterBody->checkSupport(stepInfo, input.m_surfaceInfo);
	}

	mCharacterContext->update( input, output );
	mCharacterBody->setLinearVelocity(output.m_velocity, dt);

	mWorld->unlock();

	//Update the camera
	cam->setPosition(pos(0), pos(1) + 2, pos(2));

	// Update the scene node
	mNode->setPosition(mCharacterBody->getRigidBody()->getPosition()(0),
						mCharacterBody->getRigidBody()->getPosition()(1),
						mCharacterBody->getRigidBody()->getPosition()(2));
}