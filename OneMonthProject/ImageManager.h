#pragma once
#include "SingletonBase.h"
#include "Image.h"
class ImageManager : public SingletonBase<ImageManager>
{

private:
	//맵으로 만든 이미지 목록
	typedef map<string, Image*> mapImageList;
	//맵으로 만든 이미지 목록의 반복자
	typedef map<string, Image*>::iterator mapImageListIter;

	mapImageList _mImageList;

public:
	ImageManager();
	~ImageManager();


	HRESULT Init();
	void Release();
	//키 값으로 빈 비트맵 초기화
	Image* AddImage(string strKey, int width, int height);
	//키값으로 이미지 파일 초기화
	Image* AddImage(string strKey, const char* fileName, int width, int height, bool trans, COLORREF transColor);
	Image* AddImage(string strKey, const char* fileName, float x, float y, int width, int height, bool trans, COLORREF transColor);
	//키값으로 프레임 이미지 파일 초기화
	Image* AddFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);
	Image* AddFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);

	//이미지 키값으로 찾기
	Image* FindImage(string strKey);
	//이미지 키값으로 삭제
	bool DeleteImage(string strKey);
	//이미지 전체삭제
	bool DeleteAll();


	void Render(string strKey, HDC hdc);
	void Render(string strKey, HDC hdc, int destX, int destY);
	void Render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	void FrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

};

