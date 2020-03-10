#pragma once
class UpgradeManager
{
public:
	UpgradeManager();
	~UpgradeManager();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

