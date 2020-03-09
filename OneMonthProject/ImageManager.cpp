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

	//�߰��Ϸ��� Ű������ �̹����� �����ϴ��� Ȯ��
	Image* img = FindImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� ������  ����
	if (img) return img;

	img = new Image;
	//�̹����� �ʱ�ȭ ���� ������ 
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
	//������ �̹����� ������ ���� �̹��� ��Ͽ� �߰��Ѵ�.
	_mImageList.insert(make_pair(strKey, img));

	return img;

}

Image* ImageManager::AddFrameImage(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	//�߰� �Ϸ��� Ű������ �̹����� �����ϴ��� Ȯ��
	Image* img = FindImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� ������ ����
	if (img) return img;

	img = new Image;
	//�̹����� ����� �ʱ�ȭ ���� ������
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
	//�ش� Ű �˻�
	mapImageListIter key = _mImageList.find(strKey);

	//Ű�� ã����
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

	//����ü�� ���鼭 ����
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
	//�̹����� ã�� �� ����
	Image* img = FindImage(strKey);
	if (img) img->Render(hdc);
}

void ImageManager::Render(string strKey, HDC hdc, int destX, int destY)
{
	//�̹����� ã�� �� ����
	Image* img = FindImage(strKey);
	if (img) img->Render(hdc, destX, destY);
}

void ImageManager::Render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	//�̹����� ã�� �� ����
	Image* img = FindImage(strKey);
	if (img) img->Render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void ImageManager::FrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	//�̹����� ã�� �� ����
	Image* img = FindImage(strKey);

	if (img)img->FrameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}
