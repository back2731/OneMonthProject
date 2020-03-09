#pragma once
#include "SingletonBase.h"
#include "Image.h"
class ImageManager : public SingletonBase<ImageManager>
{

private:
	//������ ���� �̹��� ���
	typedef map<string, Image*> mapImageList;
	//������ ���� �̹��� ����� �ݺ���
	typedef map<string, Image*>::iterator mapImageListIter;

	mapImageList _mImageList;

public:
	ImageManager();
	~ImageManager();


	HRESULT Init();
	void Release();
	//Ű ������ �� ��Ʈ�� �ʱ�ȭ
	Image* AddImage(string strKey, int width, int height);
	//Ű������ �̹��� ���� �ʱ�ȭ
	Image* AddImage(string strKey, const char* fileName, int width, int height, bool trans, COLORREF transColor);
	Image* AddImage(string strKey, const char* fileName, float x, float y, int width, int height, bool trans, COLORREF transColor);
	//Ű������ ������ �̹��� ���� �ʱ�ȭ
	Image* AddFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);
	Image* AddFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);

	//�̹��� Ű������ ã��
	Image* FindImage(string strKey);
	//�̹��� Ű������ ����
	bool DeleteImage(string strKey);
	//�̹��� ��ü����
	bool DeleteAll();


	void Render(string strKey, HDC hdc);
	void Render(string strKey, HDC hdc, int destX, int destY);
	void Render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	void FrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

};

