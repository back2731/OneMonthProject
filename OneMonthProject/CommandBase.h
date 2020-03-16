#pragma once
#define COMMANDMAX 9
enum SLOTNUMBER
{
	SLOT1,
	SLOT2,
	SLOT3,
	SLOT4,
	SLOT5,
	SLOT6,
	SLOT7,
	SLOT8,
	SLOT9,
};

class CommandBase
{
private:

public:
	CommandBase();
	~CommandBase();

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual	void GetBirthXY(int X, int Y);


};

