#pragma once
#define IMAGESIZECONTROL 2
class ResourceCollection
{
public:
	ResourceCollection();
	~ResourceCollection();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
};

