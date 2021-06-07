#include "WMario.h"

WMario::WMario(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY) : MainCharacter(_x, _y, _vx, _vy, _limitX, _limitY)
{
	
}

WMario::WMario(D3DXVECTOR3* _position, float _vx, float _vy, float _limitX, float _limitY) : MainCharacter(_position, _vx, _vy, _limitX, _limitY)
{
}

float WMario::getWidth()
{
	return this->animation->getCurrentFrameWidth();
}

float WMario::getHeight()
{
	return this->animation->getCurrentFrameHeight();
}

WMarioState WMario::getState()
{
	return this->state;
}

void WMario::setState(WMarioState _state)
{
	switch (_state)
	{
	case STAND:
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
	
	if (this->getState() != STAND) {
		r = (this->getY() + (this->getVy() * _dt)) / tileSize;
		c = (this->getX() + (this->getVx() * _dt)) / tileSize;

		if (this->getState() == MOVING_UP) {
			if (this->getY() + (this->getVy() * _dt) >= 0 && this->movingMatrix[r][c] != 'X') {
				this->plusY(round(this->getVy() * _dt));
			}
			else {
				this->setY(round(r * tileSize));
				this->setState(WMarioState::STAND);
			}
		}
		else if (this->getState() == MOVING_DOWN) {
			if (this->getY() + (this->getVy() * _dt) + this->animation->getCurrentFrameHeight() <= this->movingMatrix.size() * tileSize && this->movingMatrix[r + 1][c] != 'X') {
				this->plusY(round(this->getVy() * _dt));
			}
			else {
				this->setY(round(r * tileSize));
				this->setState(WMarioState::STAND);
			}
		}
		else if (this->getState() == MOVING_LEFT) {
			if (this->getX() + (this->getVx() * _dt) >= 0 && this->movingMatrix[r][c] != 'X') {
				this->plusX(round(this->getVx() * _dt));
			}
			else {
				this->setX(round((c + 1) * tileSize));
				this->setState(WMarioState::STAND);
			}
		}
		else if (this->getState() == MOVING_RIGHT) {
			if (this->getX() + (this->getVx() * _dt) + this->animation->getCurrentFrameWidth() <= this->movingMatrix[r].size() * tileSize && this->movingMatrix[r][c + 1] != 'X') {
				this->plusX(round(this->getVx() * _dt));
			}
			else {
				this->setX(round(c * tileSize));
				this->setState(WMarioState::STAND);
			}
		}
	}

	if (this->getState() == STAND) {
		animation->setCurrentIndexFrame(0);
	}
	else {
		animation->Update(_dt);
	}
}

void WMario::Draw(LPDIRECT3DTEXTURE9 _texture)
{
	this->animation->Draw(_texture, this->animation->getCurrentFrame() , this->getPosition());
}

void WMario::onKeyDown(vector<KeyType> _keyTypes)
{
	for (int i = 0; i < _keyTypes.size(); ++i) {
		if (this->getState() == STAND) {
			r = this->getY() / tileSize;
			c = this->getX() / tileSize;
			if (_keyTypes[i] == KeyType::up) {
				if (r > 0 && this->movingMatrix[r - 1][c] != 'X') {
					if (this->movingMatrix[r-1][c] <= limitScenceId) {
						this->setState(WMarioState::MOVING_UP);
					}
				}
			}
			else if (_keyTypes[i] == KeyType::down) {
				int q1 = r - 1;
				int q2 = this->movingMatrix.size();
				if (q1 < q2 && this->movingMatrix[r + 1][c] != 'X') {
					int qwe = int(this->movingMatrix[r + 1][c]);
					int asd = int(limitScenceId);
;					if (this->movingMatrix[r+1][c] <= limitScenceId) {
						this->setState(WMarioState::MOVING_DOWN);
					}
				}
			}
			else if (_keyTypes[i] == KeyType::left) {
				if (c > 0 && this->movingMatrix[r][c - 1] != 'X') {
					if (this->movingMatrix[r][c - 1] <= limitScenceId) {
						this->setState(WMarioState::MOVING_LEFT);
					}
				}
			}
			else if (_keyTypes[i] == KeyType::right) {
				if (c - 1 < this->movingMatrix[r].size() && this->movingMatrix[r][c + 1] != 'X') {
					if (this->movingMatrix[r][c + 1] <= limitScenceId) {
						this->setState(WMarioState::MOVING_RIGHT);
					}
				}
			}
		}
	}
}

void WMario::onKeyUp()
{
	
}

void WMario::loadInfo(string line, char seperator)
{
	vector<int> v = Tool::splitToVectorIntegerFrom(line, seperator);

	this->setX(v[0]);
	this->setY(v[1]);
	this->setVx(v[2]);
	this->setVx(v[3]);
	this->setLimitX(v[4]);
	this->setLimitX(v[5]);
	this->tileSize = v[6];
}

void WMario::loadAnimations(vector<string> data, char seperatorRow, char seperatorCol)
{
	vector<RECT>* frames = new vector<RECT>();

	for (int i = 0; i < data.size(); ++i) {
		if (data[i][0] == seperatorRow) {
			this->animation = new Animation(0, 0, stoi(data[i].substr(2, 1)), frames);
			return;
		}
		else {
			frames->push_back(Tool::getRECT(data[i], seperatorCol));
		}
	}
}

void WMario::loadMovingMatrix(vector<string> data, char seperator)
{
	this->movingMatrix = Tool::getCharMatrixFrom(data, seperator);
}
