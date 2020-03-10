#pragma once

class UnitBase
{
public:
	UnitBase();
	~UnitBase();

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
};

