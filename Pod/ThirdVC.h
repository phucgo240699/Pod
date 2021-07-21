#pragma once
#include "ViewController.h"
#include "Mario.h"
#include "SectionFile.h"
#include "AnimationBundle.h"
#include "AnimationCDPlayer.h"

class ThirdVC : public ViewController
{
private:
	//int componentIdStanded = 0; // this is the component that mario is standing on
	Mario* mario;
	Map* map;
	LPDIRECT3DTEXTURE9 sunnyMapTexture;

	int beginGroundId, endGroundId;
	vector<Ground*>* grounds;


public:
	// Getter
	Mario* getMario();



	// Setter
	void setMario(Mario* _mario);

	// De init


	void viewDidLoad();
	void viewReceiveKeyUp();
	void viewReceiveKeyUp(vector<KeyType> _keyTypes);
	void viewReceiveKeyDown(vector<KeyType> _keyTypes);
	void viewWillUpdate(float _dt);
	void viewDidUpdate(float _dt);
	void viewWillRender();
	void viewDidRender();
	void viewWillRelease();

	void adaptRangeID(vector<string> data, char seperator);
	void adaptData();
	void adaptAnimation();
	void adaptToGrid();
};