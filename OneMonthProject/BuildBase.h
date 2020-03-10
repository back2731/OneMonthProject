#pragma once
struct BuildStatus
{
	int playerNumber;		// 플레이어 넘버
	int buildingHp;			// 건물 체력
	float buildTime;		// 빌드 시간
};

class BuildBase
{
protected:
	BuildStatus buildStatus;

public:
	BuildBase();
	~BuildBase();

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
};

