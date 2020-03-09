#include "stdafx.h"
#include "ImageManager.h"


ImageManager::ImageManager()
{
}


ImageManager::~ImageManager()
{
}

HRESULT ImageManager::Init()
{
	return S_OK;
}

void ImageManager::Release()
{
	DeleteAll();
}

Image* ImageManager::AddImage(string strKey, int width, int height)
{

	//추가하려는 키값으로 이미지가 존재하는지 확인
	Image* img = FindImage(strKey);

	//추가하려는 이미지가 이미 있으면  리턴
	if (img) return img;

	img = new Image;
	//이미지가 초기화 되지 않으면 
	if (FAILED(img->Init(width, height)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

Image* ImageManager::AddImage(string strKey, const char * fileName, int width, int height, bool trans, COLORREF transColor)
{
	Image* img = FindImage(strKey);

	if (img) return img;

	img = new Image;

	if (FAILED(img->Init(fileName, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

Image* ImageManager::AddImage(string strKey, const char * fileName, float x, float y, int width, int height, bool trans, COLORREF transColor)
{
	Image* img = FindImage(strKey);

	if (img) return img;

	img = new Image;

	if (FAILED(img->Init(fileName, x, y, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);

		return NULL;
	}


	_mImageList.insert(make_pair(strKey, img));

	return img;
}

Image* ImageManager::AddFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	Image* img = FindImage(strKey);

	if (img) return img;

	img = new Image;

	if (FAILED(img->Init(fileName, x, y, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);

		return NULL;
	}
	//생성된 이미지를 맵으로 만든 이미지 목록에 추가한다.
	_mImageList.insert(make_pair(strKey, img));

	return img;

}

Image* ImageManager::AddFrameImage(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	//추가 하려는 키값으로 이미지가 존재하는지 확인
	Image* img = FindImage(strKey);

	//추가하려는 이미지가 이미 있으면 리턴
	if (img) return img;

	img = new Image;
	//이미지가 제대로 초기화 되지 않으면
	if (FAILED(img->Init(fileName, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

Image* ImageManager::FindImage(string strKey)
{
	mapImageListIter key = _mImageList.find(strKey);

	if (key != _mImageList.end())
	{
		return key->second;
	}

	return NULL;
}

bool ImageManager::DeleteImage(string strKey)
{
	//해당 키 검색
	mapImageListIter key = _mImageList.find(strKey);

	//키를 찾으면
	if (key != _mImageList.end())
	{
		key->second->Release();
		SAFE_DELETE(key->second);
		_mImageList.erase(key);

		return true;
	}

	return false;
}

bool ImageManager::DeleteAll()
{

	//맵전체를 돌면서 삭제
	mapImageListIter iter = _mImageList.begin();

	for (iter; iter != _mImageList.end();)
	{
		if (iter->second != NULL)
		{
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else ++iter;
	}

	_mImageList.clear();

	return true;
}

void ImageManager::Render(string strKey, HDC hdc)
{
	//이미지를 찾은 후 렌더
	Image* img = FindImage(strKey);
	if (img) img->Render(hdc);
}

void ImageManager::Render(string strKey, HDC hdc, int destX, int destY)
{
	//이미지를 찾은 후 렌더
	Image* img = FindImage(strKey);
	if (img) img->Render(hdc, destX, destY);
}

void ImageManager::Render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	//이미지를 찾은 후 렌더
	Image* img = FindImage(strKey);
	if (img) img->Render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void ImageManager::FrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	//이미지를 찾은 후 렌더
	Image* img = FindImage(strKey);

	if (img)img->FrameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}
