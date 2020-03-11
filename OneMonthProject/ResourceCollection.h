#pragma once
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

