#pragma once
struct BuildStatus
{
	int playerNumber;		// �÷��̾� �ѹ�
	int buildingHp;			// �ǹ� ü��
	float buildTime;		// ���� �ð�
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

