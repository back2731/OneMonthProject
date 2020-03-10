#pragma once
class UIManager
{
public:
	UIManager();
	~UIManager();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

