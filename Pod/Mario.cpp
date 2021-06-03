#include "Mario.h"

void Mario::setUpAnimations()
{
	this->animations = new vector<Animation*>();

	this->animations->push_back(new Animation(0, 0, 2, FilePath::getInstance()->mario_standing));
	this->animations->push_back(new Animation(0, 0, 2, FilePath::getInstance()->mario_running));
	this->animations->push_back(new Animation(0, 0, 2, FilePath::getInstance()->mario_jumping_dropping));
}

Mario::Mario(float _x, float _y, float _vx, float _vy, float _limitX, float _limitY, LPCWSTR _imagePath, LPCWSTR _debugBoxPath, D3DCOLOR _transcolor, MarioState _state) : MainCharacter(_x, _y, _vx, _vy, _limitX, _limitY)
{
	MainCharacter::MainCharacter(_x, _y, _vx, _vy, _limitX, _limitY);

	this->texture = LoadTextureFromImage(_imagePath, _transcolor);
	this->debugTexture = LoadTextureFromImage(_debugBoxPath, _transcolor);
	/*this->state = _state;
	this->setState(_state);*/
}

Mario::Mario(D3DXVECTOR3* _position, float _vx, float _vy, float _limitX, float _limitY, LPCWSTR _imagePath, LPCWSTR _debugBoxPath, D3DCOLOR _transcolor, MarioState _state) : MainCharacter(_position, _vx, _vy, _limitX, _limitY)
{
	MainCharacter::MainCharacter(_position, _vx, _vy, _limitX, _limitY);

	this->texture = LoadTextureFromImage(_imagePath, _transcolor);
	this->debugTexture = LoadTextureFromImage(_debugBoxPath, _transcolor);
	/*this->state = _state;
	this->setState(_state);*/
}

Mario::~Mario()
{
	MainCharacter::~MainCharacter();
	delete& texture;
	delete& state;
	delete& isFlip;

	for (int i = 0; i < this->animations->size(); ++i) {
		delete this->animations->at(i);
	}
	delete currentAnimation;
}

Animation* Mario::getCurrentAnimation()
{
	return this->currentAnimation;
}

MarioSubState Mario::getSubState()
{
	return this->subState;
}

MarioState Mario::getState()
{
	return this->state;
}

RECT* Mario::getBounds()
{
	if (currentAnimation == NULL) {
		return NULL;
	}

	RECT* r = new RECT();
	r->top = this->getY();
	r->bottom = r->top + this->currentAnimation->getCurrentFrameHeight();
	r->left = this->getX();
	r->right = r->left + this->currentAnimation->getCurrentFrameWidth();

	return r;
}

bool Mario::getIsFlip()
{
	return this->isFlip;
}

float Mario::getWidth()
{
	return this->currentAnimation->getCurrentFrameWidth();
}

float Mario::getHeight()
{
	return this->currentAnimation->getCurrentFrameHeight();
}

void Mario::Update(float _dt)
{
	if (currentAnimation == NULL) {
		return;
	}


	this->currentAnimation->Update(_dt);
	this->updateVelocity();
	this->plusX(round(this->getVx() * _dt));
	this->plusY(round(this->getVy() * _dt));
}

void Mario::Draw()
{
	if (currentAnimation == NULL) {
		return;
	}
	Camera* camera = Camera::getInstance();
	float translateX = 0;
	if (this->getX() > camera->getWidth() / 2) {
		translateX = -camera->getX();
	}

	float translateY = 0;
	if (this->getY() > camera->getHeight() / 2) {
		translateY = -(camera->getY());
	}

	this->currentAnimation->Draw(this->texture, this->getPosition(), D3DXVECTOR2(translateX, translateY), this->getIsFlip(), D3DCOLOR_XRGB(255, 255, 255));
	if (debugMode == Setting::getInstance()->getDebugMode()) {
		Drawing::getInstance()->draw(this->debugTexture, this->getBounds(), NULL, this->getPosition(), D3DXVECTOR2(translateX, translateY), false, D3DCOLOR_ARGB(128, 255, 255, 255));
	}
}

void Mario::setIsFlip(bool _isFlip)
{
	this->isFlip = _isFlip;
}

void Mario::setState(MarioState _state)
{
	switch (_state)
	{
	case STANDING:
		if (this->getState() != STANDING || this->currentAnimation == NULL) {
			this->currentAnimation = this->animations->at(0);
			this->setTargetVx(0);
			this->setTargetVy(0);
			this->setAccelerationY(0);
			this->setVy(0);

			if (this->getVx() > this->getTargetVx()) {
				this->setAccelerationX(-0.6);
			}
			else if (this->getVx() < this->getTargetVx()) {
				this->setAccelerationX(0.6);
			}
			else {
				this->setAccelerationX(0);
			}
		}
		
		break;
	case WALKING:
		if (this->getState() != WALKING || this->currentAnimation == NULL) {
			this->currentAnimation = this->animations->at(1);
		}
		
		break;
	case JUMPING:
		if (this->getState() != JUMPING || this->currentAnimation == NULL) {
			this->currentAnimation = this->animations->at(2);
			this->setTargetVy(0);
			this->setVy(-5);
			this->setAccelerationY(0.2);
		}

		break;
	case DROPPING:
		if (this->getState() != DROPPING || this->currentAnimation == NULL) {
			this->currentAnimation = this->animations->at(2);
			this->setTargetVy(8);
			this->setAccelerationY(0.4);
		}
		break;
	default:
		break;
	}

	this->state = _state;
}
void Mario::setSubState(MarioSubState _subState)
{
	switch (_subState)
	{
	case NONE:
		break;
	case PUSHING:
		this->setVx(0);
		this->setAccelerationX(0);
		break;
	default:
		break;
	}
	this->subState = _subState;
}
// 2760 1066
// 028 5409 6666
void Mario::updateVelocity()
{
	if (this->getTargetVx() > 0) {
		if (this->getVx() + this->getAccelerationX() <= this->getTargetVx()) {
			this->plusVx(this->getAccelerationX());
		}
	}
	else if (this->getTargetVx() < 0) {
		if (this->getVx() + this->getAccelerationX() >= this->getTargetVx()) {
			this->plusVx(this->getAccelerationX());
		}
	}
	else { // = 0
		if (this->getIsFlip() == false) { // -->
			if (this->getVx() + this->getAccelerationX() > 0) {
				this->plusVx(this->getAccelerationX());
			}
			else {
				this->setVx(0);
			}
		}
		else { // <--
			if (this->getVx() + this->getAccelerationX() < 0) {
				this->plusVx(this->getAccelerationX());
			}
			else {
				this->setVx(0);
			}
		}
	}

	if (this->getTargetVy() > 0) {
		if (this->getVy() + this->getAccelerationY() <= this->getTargetVy()) {
			this->plusVy(this->getAccelerationY());
		}
	}
	else if (this->getTargetVy() == 0) {
		if (this->getState() == JUMPING) {
			if (this->getVy() + this->getAccelerationY() < 0) {
				this->plusVy(this->getAccelerationY());
			}
			else {
				this->setState(MarioState::DROPPING);
			}
		}
	}
}

void Mario::onKeyUp()
{
	if (this->getState() == WALKING) {
		this->setState(MarioState::STANDING);
	}
	else if (this->getState() == DROPPING) {
		if (this->getVx() < 0) {
			this->setAccelerationX(0.6);
		}
		else if (this->getVx() > 0) {
			this->setAccelerationX(-0.6);
		}
		if (this->getTargetVx() != 0) {
			this->setTargetVx(0);
		}
	}
}

void Mario::onKeyUp(vector<KeyType> _keyTypes)
{
	for (int i = 0; i < _keyTypes.size(); ++i) {
		if (_keyTypes[i] == KeyType::space) {
			if (this->getState() == JUMPING) {
				startdrop = this->getY();
				this->setState(MarioState::DROPPING);
			}
		}
		else if (_keyTypes[i] == KeyType::right) {
			if (this->getSubState() == PUSHING) {
				this->setSubState(MarioSubState::NONE);
			}
		}
		else if (_keyTypes[i] == KeyType::left) {
			if (this->getSubState() == PUSHING) {
				this->setSubState(MarioSubState::NONE);
			}
		}
	}
}

void Mario::onKeyDown(vector<KeyType> _keyTypes)
{
	bool hasKeyRight = false;
	bool hasKeyLeft = false;

	for (int i = 0; i < _keyTypes.size(); ++i) {
		if (_keyTypes[i] == KeyType::right) {
			if (this->getSubState() == PUSHING) {
				continue;
			}
			hasKeyRight = true;

			if (!hasKeyLeft) {
				this->setIsFlip(false);
				if (this->getState() == DROPPING) {
					this->setTargetVx(1.6);
				}
				else {
					this->setTargetVx(2.4);
				}
				this->setAccelerationX(0.4);
			}
			else {
				this->setTargetVx(0);
				if (this->getVx() > this->getTargetVx()) {
					this->setAccelerationX(-0.6);
				}
				else if (this->getVx() < this->getTargetVx()) {
					this->setAccelerationX(0.6);
				}
				else {
					this->setAccelerationX(0);
				}
			}
		}
		else if (_keyTypes[i] == KeyType::left) {
			if (this->getSubState() == PUSHING) {
				continue;
			}
			hasKeyLeft = true;

			if (!hasKeyRight) {
				this->setIsFlip(true);
				if (this->getState() == DROPPING) {
					this->setTargetVx(-1.6);
				}
				else {
					this->setTargetVx(-2.4);
				}
				this->setAccelerationX(-0.4);
			}
			else {
				this->setTargetVx(0);
				if (this->getVx() > this->getTargetVx()) {
					this->setAccelerationX(-0.6);
				}
				else if (this->getVx() < this->getTargetVx()) {
					this->setAccelerationX(0.6);
				}
				else {
					this->setAccelerationX(0);
				}
			}
		}
		else if (_keyTypes[i] == KeyType::space) {
			if (this->getState() == DROPPING) {
				return;
			}
			if (this->getState() == STANDING || this->getState() == WALKING) {
				this->setState(MarioState::JUMPING);
			}
		}
	}

	if (this->getTargetVx() == 0 && this->getState() == WALKING) {
		this->setState(MarioState::STANDING);
	}
	if (this->getTargetVx() != 0 && this->getState() == STANDING) {
		this->setState(MarioState::WALKING);
	}
}

void Mario::loadInfo(string line, char seperator)
{
	vector<string> v = Tool::splitToVectorStringFrom(line, seperator);
	this->setX(stof(v[0]));
	this->setY(stof(v[1]));
	this->setLimitX(stof(v[2]));
	this->setLimitY(stof(v[3]));
	this->setState(Tool::getMarioStateFromString(v[4]));
}

void Mario::loadAnimations(vector<string> data, char seperatorRow, char seperatorCol)
{
	this->animations = new vector<Animation*>();
	vector<RECT*>* frames = new vector<RECT*>();
	vector<int> frame;
	RECT* r;
	int id = 0;

	for (int i = 0; i < data.size(); ++i) {
		if (data[i].at(0) == seperatorRow) {
			this->animations->push_back(new Animation(0, 0, stoi(data[i].substr(2,1)), frames));
			++id;
			frame.clear();
			frames = new vector<RECT*>();
			continue;
		};

		frame = Tool::splitToVectorIntegerFrom(data[i], seperatorCol);
		r = new RECT();
		r->left = frame[0];
		r->top = frame[1];
		r->right = r->left + frame[2];
		r->bottom = r->top + frame[3];
		frames->push_back(r);
	}
	int a = 0;
}
