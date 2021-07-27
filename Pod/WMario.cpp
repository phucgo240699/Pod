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
		if (time_t(this->row) >= this->movingMatrix.size() - 1
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
		if (time_t(this->col) >= this->movingMatrix[this->row].size() - 1
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
	

	//animation->Update(_dt);

	if (this->isFlyingMode) {
		if (this->isFireMode) {
			this->flyingFireAnimation->Update(_dt);
		}
		else {
			this->flyingAnimation->Update(_dt);
		}
	}
	else if (this->isSuperMode) {
		if (this->isFireMode) {
			this->superFireAniamtion->Update(_dt);
		}
		else {
			this->superAnimation->Update(_dt);
		}
	}
	else {
		if (this->isFireMode) {
			this->fireAnimation->Update(_dt);
		}
		else {
			this->animation->Update(_dt);
		}
	}
}

void WMario::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	/*D3DXVECTOR3 pos = D3DXVECTOR3(this->getX() - Camera::getInstance()->getX(), this->getY() - Camera::getInstance()->getY(), 0);
	this->animation->DrawWithoutCamera(_texture, this->animation->getCurrentFrame(), pos);*/

	if (this->isFlyingMode) {
		if (this->isFireMode) {
			Drawing::getInstance()->draw(_texture, this->flyingFireAnimation->getCurrentFrame(), this->getPosition(), D3DXVECTOR2(float(0), float(-4)));
		}
		else {
			Drawing::getInstance()->draw(_texture, this->flyingAnimation->getCurrentFrame(), this->getPosition(), D3DXVECTOR2(float(0), float(-4)));
		}
	}
	else if (this->isSuperMode) {
		if (this->isFireMode) {
			Drawing::getInstance()->draw(_texture, this->superFireAniamtion->getCurrentFrame(), this->getPosition(), D3DXVECTOR2(float(0), float(-3)));
		}
		else {
			Drawing::getInstance()->draw(_texture, this->superAnimation->getCurrentFrame(), this->getPosition(), D3DXVECTOR2(float(0), float(-3)));
		}
	}
	else {
		if (this->isFireMode) {
			Drawing::getInstance()->draw(_texture, this->fireAnimation->getCurrentFrame(), this->getPosition());
		}
		else {
			Drawing::getInstance()->draw(_texture, this->animation->getCurrentFrame(), this->getPosition());
		}
	}
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

void WMario::loadModeFromGlobalMarioFile()
{
	fstream fs;
	fs.open(FilePath::getInstance()->mario, ios::in);

	vector<string> v;
	string line;

	while (!fs.eof())
	{
		getline(fs, line);
		if (line[0] == '#') continue; // Comment
		if (line == "") continue; // Empty
		v = Tool::splitToVectorStringFrom(line, ',');

		this->setIsFireMode(stoi(v[18]) == 1);
		this->setIsSuperMode(stoi(v[19]) == 1);
		this->setIsFlyingMode(stoi(v[20]) == 1);
	}

	fs.close();
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

void WMario::setFireAnimation(Animation* _animation)
{
	this->fireAnimation = _animation;
}

void WMario::setSuperAnimation(Animation* _animation)
{
	this->superAnimation = _animation;
}

void WMario::setSuperFireAnimation(Animation* _animation)
{
	this->superFireAniamtion = _animation;
}

void WMario::setFlyingAnimation(Animation* _animation)
{
	this->flyingAnimation = _animation;
}

void WMario::setFlyingFireAnimation(Animation* _animation)
{
	this->flyingFireAnimation = _animation;
}

void WMario::setIsFireMode(bool _value)
{
	this->isFireMode = _value;
}

void WMario::setIsSuperMode(bool _value)
{
	this->isSuperMode = _value;
}

void WMario::setIsFlyingMode(bool _value)
{
	this->isFlyingMode = _value;
}

void WMario::loadMovingMatrix(vector<string> data, char seperator)
{
	this->movingMatrix = Tool::getCharMatrixFrom(data, seperator);
}

bool WMario::canMoveRight()
{
	if (time_t(this->col) >= this->movingMatrix[this->row].size() - 1
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
	if (time_t(this->row) >= this->movingMatrix.size() - 1
	|| this->movingMatrix[this->row + 1][this->col] == 'X') {
		return false;
	}

	return true;
}
