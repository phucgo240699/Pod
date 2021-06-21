#include "MainCharacter.h"

MainCharacter::MainCharacter(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY) : Component(_x, _y, _vx, _vy, _limitX, _limitY)
{
    Component::Component(_x, _y, _vx, _vy, _limitX, _limitY);
}

MainCharacter::MainCharacter(D3DXVECTOR3 _position, float _vx, float _vy, float _limitX, float _limitY) : Component(_position, _vx, _vy, _limitX, _limitY)
{
    Component(_position, _vx, _vy, _limitX, _limitY);
}

MainCharacter::~MainCharacter()
{
    Component::~Component();
}

void MainCharacter::setState(MarioState _state)
{
}

Animation* MainCharacter::getCurrentAnimation()
{
    return nullptr;
}

float MainCharacter::getAccelerationX()
{
    return this->accelerationX;
}

float MainCharacter::getAccelerationY()
{
    return this->accelerationY;
}

float MainCharacter::getTargetVx()
{
    return this->targetVx;
}

float MainCharacter::getTargetVy()
{
    return this->targetVy;
}

void MainCharacter::setAccelerationX(float _accelerationX)
{
    this->accelerationX = _accelerationX;
}

void MainCharacter::setAccelerationY(float _accelerationY)
{
    this->accelerationY = _accelerationY;
}

void MainCharacter::setTargetVx(float _targetVx)
{
    this->targetVx = _targetVx;
}

void MainCharacter::setTargetVy(float _targetVy)
{
    this->targetVy = _targetVy;
}
