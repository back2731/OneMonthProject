#pragma once
#include "SingletonBase.h"
class PlayerManager : public SingletonBase<PlayerManager>
{
private:
	int saveX;
	int saveY;
	
	bool selectLarva;

public:
	PlayerManager();
	~PlayerManager();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void SetSelectLarva(bool _isPush) { selectLarva = _isPush; }
	bool GetSelectLarvaValue() { return selectLarva; }

	void SetXY(int x, int y);
	int GetSaveX() { return saveX; }
	int GetSaveY() { return saveY; }
};

