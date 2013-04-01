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

	// The player size
	hkVector4 vertexA(0, 0.4f, 0);
	hkVector4 vertexB(0, -0.4f, 0);
	mStandShape = new hkpCapsuleShape(vertexA, vertexB, 0.6f);

	vertexA.setZero4();
	mCrouchShape = new hkpCapsuleShape(vertexA, vertexB, 0.6f);

	// Construct character rigid body
	hkpCharacterRigidBodyCinfo info;
	info.m_mass = 60.0f;
	info.m_shape = mStandShape;

	info.m_maxForce = 50.0f;
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
	//mPreviousGround = new hkpSurfaceInfo();
	mCurrentAngle = HK_REAL_PI;

	mGravityGun = new hkpGravityGun();
	mGravityGun->m_throwVelocity = 5.0f;
	mGravityGun->m_maxMassOfObjectPicked = 101.0f;

	mWorld->unlock();
}

void Player::update(int UD, int LR, bool lmb, bool rmb, bool mmb, bool jump, Camera * cam, float dt) {
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
		input.m_forward.set(0, 0, 1);
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

	//mCurrentOrientation.setAxisAngle(hkVector4(0, 1, 0), mCurrentAngle+(HK_REAL_PI / 2));
	float yaw = cam->getOrientation().getYaw().valueRadians() + (HK_REAL_PI / 2);
	float pitch = cam->getOrientation().getPitch().valueRadians();
	hkQuaternion qY(hkVector4(0, 1, 0), yaw);
	hkQuaternion qX(hkVector4(1, 0, 0), pitch);
	qX.mul(qY);
	mTransform = hkTransform(qX, pos);

	// Hack to simulate dropping an object. Set throw velovity and 
	// impulse applied to zero so whatever you're holding drops at
	// your feet
	if (mmb && !mGravityGun->m_grabbedBodies.isEmpty()) {
		mGravityGun->m_throwVelocity = 0.0f;
		mGravityGun->m_impulseAppliedWhenObjectNotPicked = 0.0f;
		lmb = true;
	}

	mGravityGun->stepGun(dt, mWorld, mCharacterBody->getRigidBody(), mTransform, lmb, rmb);

	mGravityGun->m_throwVelocity = 5.0f;
	mGravityGun->m_impulseAppliedWhenObjectNotPicked = 100.0f;

	//Update the camera
	cam->setPosition(pos(0), pos(1) + 1.0, pos(2));
}