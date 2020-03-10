#pragma once
class PointManager
{
public:
	PointManager();
	~PointManager();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

