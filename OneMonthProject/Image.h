#pragma once
#include"Animation.h"
class Image
{
public:

	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,	//���ҽ� �ε�
		LOAD_FILE,			//���� �ε�
		LOAD_EMPTY,			//�� ��Ʈ�� ����
		LOAD_END
	};


	typedef struct tagImage
	{
		DWORD	resID;		//���ҽ� ID
		HDC		hMemDC;		//�޸� DC
		HBITMAP hBit;				//��Ʈ��(���ο� ��Ʈ�� �ڵ�)
		HBITMAP hOBit;				//�õ� ��Ʈ��(���� ��Ʈ�� �ڵ�)
		int		width;				//�̹��� ����ũ��
		int		height;				//�̹��� ����ũ��
		BYTE	loadType;			//�ε� Ÿ��
		float	x;					//�̹��� x��ǥ
		float   y;					//�̹��� Y��ǥ
		int		currentFrameX;		//����������X
		int		currentFrameY;		//����������Y
		int		maxFrameX;			//�ִ� X������ ����
		int		maxFrameY;			//�ִ� Y������ ����
		int		frameWidth;			//1������ ���α���
		int		frameHeight;		//1������ ���α���


		tagImage()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			width = 0;
			height = 0;
			x = 0;
			y = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

	Image();
	~Image();

private:

	LPIMAGE_INFO	_imageInfo;		//�̹��� ����
	char*			_fileName;		//�̹��� �̸�
	bool			_isTrans;		//���� ��������?
	COLORREF		_transColor;	//���� ���� RGB

	BLENDFUNCTION	_blendFunc;		//���ĺ��� ��������
	LPIMAGE_INFO	_blendImage;	//���� ���带 ����ϱ� ���� �̹��� ����

public:
	//�� ��Ʈ�� �̹��� �ʱ�ȭ
	HRESULT Init(int width, int height);

	HRESULT Init(const char* fileName, int width, int height,
		bool isTrans, COLORREF transColor);

	HRESULT Init(const char* fileName, float x, float y, int width, int height,
		bool isTrans, COLORREF transColor);
	//������ �̹��� ���Ϸ� �ʱ�ȭ

	HRESULT Init(const char* fileName, int width, int height,
		int frameX, int frameY, bool isTrans, COLORREF transColor);

	HRESULT Init(const char* fileName, float x, float y, int width, int height,
		int frameX, int frameY, bool isTrans, COLORREF transColor);

	//���� ����
	void setTransColor(bool isTrans, COLORREF transColor);

	//����
	void Release();

	//����(���� ������ ��ġ�� �̹��� ���)
	void Render(HDC hdc);
	void Render(HDC hdc, int destX, int destY);
	void Render(HDC hdc, int destX, int destY, int width, int height);
	void Render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);


	//�����ӷ���
	void FrameRender(HDC hdc, int destX, int destY);
	void FrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void FrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, int width, int height);
	//��������(hdc, ������ų����, x������, y������)
	void LoopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);
	void LoopAlphaRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY, BYTE alpha);
	//���ķ���
	void AlphaRender(HDC hdc, BYTE alpha);
	void AlphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void AlphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	void AniRender(HDC hdc, int destX, int destY, Animation* ani);

	//DC�����Ͷ�
	inline HDC GetMemDC() { return _imageInfo->hMemDC; }


	//�̹��� ��ǥx ���
	inline float GetX() { return _imageInfo->x; }
	inline void SetX(float x) { _imageInfo->x = x; }

	//�̹��� ��ǥy ���
	inline float GetY() { return _imageInfo->y; }
	inline void SetY(float y) { _imageInfo->y = y; }

	//�̹��� ���� ��ǥ ����
	inline void SetCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	//����,����ũ�� ���
	inline int GetWidth() { return _imageInfo->width; }
	inline int GetHeight() { return _imageInfo->height; }
		
	//�ٿ�� �ڽ�(�浹��)
	inline RECT GetBoundingBox()
	{
		RECT rc = RectMakeCenter(_imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height);
		return rc;
	}

	//������ x ����
	inline int GetFrameX() { return _imageInfo->currentFrameX; }
	inline void SetFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	//������ y ����
	inline int GetFrameY() { return _imageInfo->currentFrameY; }
	inline void SetFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	//1������ ���μ��� ũ��
	inline int GetFrameWidth() { return _imageInfo->frameWidth; }
	inline int GetFrameHeight() { return _imageInfo->frameHeight; }

	//�ƽ������� x,y
	inline int GetMaxFrameX() { return _imageInfo->maxFrameX; }
	inline int GetMaxFrameY() { return _imageInfo->maxFrameY; }


};
