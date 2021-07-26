#include "WMario.h"

WMario::WMario(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY) : MainCharacter(_x, _y, _vx, _vy, _limitX, _limitY)
{
	
}

WMario::WMario(D3DXVECTOR3 _position, float _vx, float _vy, float _limitX, float _limitY) : MainCharacter(_position, _vx, _vy, _limitX, _limitY)
{
}

int WMario::getWidth()
{
	return this->animation->getCurrentFrameWidth();
}

int WMario::getHeight()
{
	return this->animation->getCurrentFrameHeight();
}

WMarioState WMario::getState()
{
	return this->state;
}

char WMario::getCurrentSceneId()
{
	return this->movingMatrix[row][col];
}

void WMario::setState(WMarioState _state)
{
	switch (_state)
	{
	case WMARIO_STANDING:
		this->setVx(0);
		this->setVy(0);
		break;
	case MOVING_UP:
		this->setVy(-2);
		break;
	case MOVING_DOWN:
		this->setVy(2);
		break;
	case MOVING_LEFT:
		this->setVx(-2);
		break;
	case MOVING_RIGHT:
		this->setVx(2);
		break;
	default:
		break;
	}
	this->state = _state;
}

void WMario::Update(float _dt)
{
	

	switch (this->getState())
	{
	case WMARIO_STANDING:
		break;
	case MOVING_UP:
		if (this->row <= 0
		|| this->movingMatrix[this->row - 1][this->col] == 'X'
		|| (this->startRowMove != this->row && this->movingMatrix[this->row][this->col] != '-')) {
			this->setY(float(this->row * tileSize));
			this->setState(WMarioState::WMARIO_STANDING);
		}
		else {
			this->plusY(this->getVy() * _dt);
			this->row = int((this->getY() + this->getHeight()) / this->tileSize);
		}
		break;
	case MOVING_DOWN:
		if (this->row >= this->movingMatrix.size() - 1
		|| this->movingMatrix[this->row + 1][this->col] == 'X'
		|| (this->startRowMove != this->row && this->movingMatrix[this->row][this->col] != '-')) {
			this->setY(float(this->row * tileSize));
			this->setState(WMarioState::WMARIO_STANDING);
		}
		else {
			this->plusY(this->getVy() * _dt);
			this->row = int(this->getY() / this->tileSize);
		}
		break;
	case MOVING_LEFT:
		if (this->col <= 0
		|| this->movingMatrix[this->row][this->col - 1] == 'X'
		|| (this->startColMove != this->col && this->movingMatrix[this->row][this->col] != '-')) {
			this->setX(float(this->col * tileSize));
			this->setState(WMarioState::WMARIO_STANDING);
		}
		else {
			this->plusX(this->getVx() * _dt);
			this->col = int((this->getX() + this->getWidth()) / this->tileSize);
		}
		break;
	case MOVING_RIGHT:
		if (this->col >= this->movingMatrix[this->row].size() - 1
		|| this->movingMatrix[this->row][this->col + 1] == 'X'
		|| (this->startColMove != this->col && this->movingMatrix[this->row][this->col] != '-')) {
			this->setX(float(this->col * tileSize));
			this->setState(WMarioState::WMARIO_STANDING);
		}
		else {
			this->plusX(this->getVx() * _dt);
			this->col = int(this->getX() / this->tileSize);
		}
		break;
	default:
		break;
	}
	

	animation->Update(_dt);
}

void WMario::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(this->getX() - Camera::getInstance()->getX(), this->getY() - Camera::getInstance()->getY(), 0);
	this->animation->DrawWithoutCamera(_texture, this->animation->getCurrentFrame(), pos);
}

void WMario::onKeyDown(vector<KeyType> _keyTypes)
{
	for (size_t i = 0; i < _keyTypes.size(); ++i) {
		if (this->getState() == WMARIO_STANDING) {
			if (_keyTypes[i] == KeyType::up) {
				if (canMoveTop()) {
					this->setState(WMarioState::MOVING_UP);
					this->startRowMove = this->row;
				}
			}
			else if (_keyTypes[i] == KeyType::down) {
				if (canMoveBottom()) {
					this->setState(WMarioState::MOVING_DOWN);
					this->startRowMove = this->row;
				}
			}
			else if (_keyTypes[i] == KeyType::left) {
				if (canMoveLeft()) {
					this->setState(WMarioState::MOVING_LEFT);
					this->startColMove = this->col;
				}
			}
			else if (_keyTypes[i] == KeyType::right) {
				if (canMoveRight()) {
					this->setState(WMarioState::MOVING_RIGHT);
					this->startColMove = this->col;
				}
			}
		}
	}
}

void WMario::loadInfo(string line, char seperator)
{
	vector<string> v = Tool::splitToVectorStringFrom(line, seperator);

	this->setVx(stof(v[0]));
	this->setVx(stof(v[1]));
	this->setLimitX(stof(v[2]));
	this->setLimitX(stof(v[3]));
	this->tileSize = stoi(v[4]);
	this->row = stoi(v[5]);
	this->col = stoi(v[6]);
	this->startRowMove = stoi(v[5]);
	this->startColMove = stoi(v[6]);

	this->setX(float(this->col * this->tileSize));
	this->setY(float(this->row * this->tileSize));
}

void WMario::setAnimation(Animation* _animation)
{
	this->animation = _animation;
}

void WMario::loadMovingMatrix(vector<string> data, char seperator)
{
	this->movingMatrix = Tool::getCharMatrixFrom(data, seperator);
}

bool WMario::canMoveRight()
{
	if (this->col >= this->movingMatrix[this->row].size() - 1
	|| this->movingMatrix[this->row][this->col + 1] == 'X') {
		return false;
	}
	return true;
}

bool WMario::canMoveLeft()
{
	if (this->col <= 0
	|| this->movingMatrix[this->row][this->col - 1] == 'X') {
		return false;
	}

	return true;
}

bool WMario::canMoveTop()
{
	if (this->row <= 0
	|| this->movingMatrix[this->row - 1][this->col] == 'X') {
		return false;
	}

	return true;
}

bool WMario::canMoveBottom()
{
	if (this->row >= this->movingMatrix.size() - 1
	|| this->movingMatrix[this->row + 1][this->col] == 'X') {
		return false;
	}

	return true;
}
