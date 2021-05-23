#include "MainCharacter.h"

MainCharacter::MainCharacter(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY) : Component(_x, _y, _vx, _vy, _limitX, _limitY)
{
    Component::Component(_x, _y, _vx, _vy, _limitX, _limitY);
}

MainCharacter::MainCharacter(D3DXVECTOR3* _position, float _vx, float _vy, float _limitX, float _limitY) : Component(_position, _vx, _vy, _limitX, _limitY)
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
