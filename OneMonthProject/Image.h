#pragma once
#include"Animation.h"
class Image
{
public:

	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,	//리소스 로딩
		LOAD_FILE,			//파일 로딩
		LOAD_EMPTY,			//빈 비트맵 파일
		LOAD_END
	};


	typedef struct tagImage
	{
		DWORD	resID;		//리소스 ID
		HDC		hMemDC;		//메모리 DC
		HBITMAP hBit;				//비트맵(새로운 비트맵 핸들)
		HBITMAP hOBit;				//올드 비트맵(기존 비트맵 핸들)
		int		width;				//이미지 가로크기
		int		height;				//이미지 세로크기
		BYTE	loadType;			//로드 타입
		float	x;					//이미지 x좌표
		float   y;					//이미지 Y좌표
		int		currentFrameX;		//현재프레임X
		int		currentFrameY;		//현재프레임Y
		int		maxFrameX;			//최대 X프레임 갯수
		int		maxFrameY;			//최대 Y프레임 갯수
		int		frameWidth;			//1프레임 가로길이
		int		frameHeight;		//1프레임 세로길이


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

	LPIMAGE_INFO	_imageInfo;		//이미지 정보
	char*			_fileName;		//이미지 이름
	bool			_isTrans;		//배경색 날릴꺼니?
	COLORREF		_transColor;	//배경색 없앨 RGB

	BLENDFUNCTION	_blendFunc;		//알파블렌드 위한정보
	LPIMAGE_INFO	_blendImage;	//알파 블렌드를 사용하기 위한 이미지 정보

public:
	//빈 비트맵 이미지 초기화
	HRESULT Init(int width, int height);

	HRESULT Init(const char* fileName, int width, int height,
		bool isTrans, COLORREF transColor);

	HRESULT Init(const char* fileName, float x, float y, int width, int height,
		bool isTrans, COLORREF transColor);
	//프레임 이미지 파일로 초기화

	HRESULT Init(const char* fileName, int width, int height,
		int frameX, int frameY, bool isTrans, COLORREF transColor);

	HRESULT Init(const char* fileName, float x, float y, int width, int height,
		int frameX, int frameY, bool isTrans, COLORREF transColor);

	//투명값 셋팅
	void setTransColor(bool isTrans, COLORREF transColor);

	//삭제
	void Release();

	//렌더(내가 지정한 위치에 이미지 출력)
	void Render(HDC hdc);
	void Render(HDC hdc, int destX, int destY);
	void Render(HDC hdc, int destX, int destY, int width, int height);
	void Render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);


	//프레임렌더
	void FrameRender(HDC hdc, int destX, int destY);
	void FrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void FrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, int width, int height);
	//루프렌더(hdc, 루프시킬영역, x오프셋, y오프셋)
	void LoopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);
	void LoopAlphaRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY, BYTE alpha);
	//알파렌더
	void AlphaRender(HDC hdc, BYTE alpha);
	void AlphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void AlphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	void AniRender(HDC hdc, int destX, int destY, Animation* ani);

	//DC가져와라
	inline HDC GetMemDC() { return _imageInfo->hMemDC; }


	//이미지 좌표x 얻기
	inline float GetX() { return _imageInfo->x; }
	inline void SetX(float x) { _imageInfo->x = x; }

	//이미지 좌표y 얻기
	inline float GetY() { return _imageInfo->y; }
	inline void SetY(float y) { _imageInfo->y = y; }

	//이미지 센터 좌표 셋팅
	inline void SetCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	//가로,세로크기 얻기
	inline int GetWidth() { return _imageInfo->width; }
	inline int GetHeight() { return _imageInfo->height; }
		
	//바운딩 박스(충돌용)
	inline RECT GetBoundingBox()
	{
		RECT rc = RectMakeCenter(_imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height);
		return rc;
	}

	//프레임 x 셋팅
	inline int GetFrameX() { return _imageInfo->currentFrameX; }
	inline void SetFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	//프레임 y 셋팅
	inline int GetFrameY() { return _imageInfo->currentFrameY; }
	inline void SetFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	//1프레임 가로세로 크기
	inline int GetFrameWidth() { return _imageInfo->frameWidth; }
	inline int GetFrameHeight() { return _imageInfo->frameHeight; }

	//맥스프레임 x,y
	inline int GetMaxFrameX() { return _imageInfo->maxFrameX; }
	inline int GetMaxFrameY() { return _imageInfo->maxFrameY; }


};
