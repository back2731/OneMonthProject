#include "stdafx.h"
#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

HRESULT CollisionManager::Init()
{
	return S_OK;
}

void CollisionManager::CollisionSameVector(vector<UnitBase*>& unitVector, int knockBack, bool isCheck)
{
	if (isCheck)
	{
		if (!unitVector.empty())
		{
			for (int i = 0; i < unitVector.size(); i++)
			{
				for (int j = 0; j < unitVector.size(); j++)
				{
					if (unitVector[i]->GetUnitKind() != LARVA && unitVector[j]->GetUnitKind() != LARVA)
					{
						if (IntersectRect(&temp, &unitVector[i]->GetUnitRect(), &unitVector[j]->GetUnitRect()))
						{
							if (i == j) continue;

							// temp의 Width와 Height 선언
							int tempW = temp.right - temp.left;
							int tempH = temp.bottom - temp.top;

							if (tempH < tempW)
							{
								// 위쪽 충돌시 아래쪽으로 밀어줌
								if (temp.top == unitVector[i]->GetUnitRectTop())
								{
									unitVector[i]->SetUnitRectTop(unitVector[i]->GetUnitRectTop() + tempH / knockBack);
									unitVector[i]->SetUnitRectBottom(unitVector[i]->GetUnitRectBottom() + tempH / knockBack);
									unitVector[i]->SetUnitRectY(unitVector[i]->GetUnitRectY() + tempH / knockBack);
								}
								// 아래쪽 충돌시 위쪽으로 밀어줌
								else if (temp.bottom == unitVector[i]->GetUnitRectBottom())
								{
									unitVector[i]->SetUnitRectTop(unitVector[i]->GetUnitRectTop() - tempH / knockBack);
									unitVector[i]->SetUnitRectBottom(unitVector[i]->GetUnitRectBottom() - tempH / knockBack);
									unitVector[i]->SetUnitRectY(unitVector[i]->GetUnitRectY() - tempH / knockBack);
								}
							}
							else
							{
								// 왼쪽 충돌시 오른쪽으로 밀어줌
								if (temp.left == unitVector[i]->GetUnitRectLeft())
								{
									unitVector[i]->SetUnitRectLeft(unitVector[i]->GetUnitRectLeft() + tempW / knockBack);
									unitVector[i]->SetUnitRectRight(unitVector[i]->GetUnitRectRight() + tempW / knockBack);
									unitVector[i]->SetUnitRectX(unitVector[i]->GetUnitRectX() + tempW / knockBack);
								}
								// 오른쪽 충돌시 왼쪽으로 밀어줌
								else if (temp.right == unitVector[i]->GetUnitRectRight())
								{
									unitVector[i]->SetUnitRectLeft(unitVector[i]->GetUnitRectLeft() - tempW / knockBack);
									unitVector[i]->SetUnitRectRight(unitVector[i]->GetUnitRectRight() - tempW / knockBack);
									unitVector[i]->SetUnitRectX(unitVector[i]->GetUnitRectX() - tempW / knockBack);

								}
							}
						}
					}
				}
			}
		}
	}
	else
	{

	}
}

void CollisionManager::CollisionUnitToBuilding(vector<UnitBase*>& unitVector, vector<BuildBase*>& buildingVector)
{
	if (!unitVector.empty())
	{
		if (!buildingVector.empty())
		{
			for (int i = 0; i < unitVector.size(); i++)
			{
				if (unitVector[i]->GetUnitKind() != LARVA)
				{
					for (int j = 0; j < buildingVector.size(); j++)
					{
						if (IntersectRect(&temp, &unitVector[i]->GetUnitRect(), &buildingVector[j]->GetBuildingCollisionRect()))
						{

							// temp의 Width와 Height 선언
							int tempW = temp.right - temp.left;
							int tempH = temp.bottom - temp.top;

							if (tempH < tempW)
							{
								// 위쪽 충돌시 아래쪽으로 밀어줌
								if (temp.top == unitVector[i]->GetUnitRectTop())
								{
									unitVector[i]->SetUnitRectTop(unitVector[i]->GetUnitRectTop() + tempH / BUILDKNOCKBACK);
									unitVector[i]->SetUnitRectBottom(unitVector[i]->GetUnitRectBottom() + tempH / BUILDKNOCKBACK);
									unitVector[i]->SetUnitRectY(unitVector[i]->GetUnitRectY() + tempH / BUILDKNOCKBACK);
								}
								// 아래쪽 충돌시 위쪽으로 밀어줌
								else if (temp.bottom == unitVector[i]->GetUnitRectBottom())
								{
									unitVector[i]->SetUnitRectTop(unitVector[i]->GetUnitRectTop() - tempH / BUILDKNOCKBACK);
									unitVector[i]->SetUnitRectBottom(unitVector[i]->GetUnitRectBottom() - tempH / BUILDKNOCKBACK);
									unitVector[i]->SetUnitRectY(unitVector[i]->GetUnitRectY() - tempH / BUILDKNOCKBACK);
								}
							}
							else
							{
								// 왼쪽 충돌시 오른쪽으로 밀어줌
								if (temp.left == unitVector[i]->GetUnitRectLeft())
								{
									unitVector[i]->SetUnitRectLeft(unitVector[i]->GetUnitRectLeft() + tempW / BUILDKNOCKBACK);
									unitVector[i]->SetUnitRectRight(unitVector[i]->GetUnitRectRight() + tempW / BUILDKNOCKBACK);
									unitVector[i]->SetUnitRectX(unitVector[i]->GetUnitRectX() + tempW / BUILDKNOCKBACK);
								}
								// 오른쪽 충돌시 왼쪽으로 밀어줌
								else if (temp.right == unitVector[i]->GetUnitRectRight())
								{
									unitVector[i]->SetUnitRectLeft(unitVector[i]->GetUnitRectLeft() - tempW / BUILDKNOCKBACK);
									unitVector[i]->SetUnitRectRight(unitVector[i]->GetUnitRectRight() - tempW / BUILDKNOCKBACK);
									unitVector[i]->SetUnitRectX(unitVector[i]->GetUnitRectX() - tempW / BUILDKNOCKBACK);

								}
							}
						}
					}
				}
			}
		}
	}
}

void CollisionManager::CollisionUnitToUnit(vector<UnitBase*>& unitVector, vector<UnitBase*>& _unitVector)
{
	if (!unitVector.empty())
	{
		if (!_unitVector.empty())
		{
			for (int i = 0; i < unitVector.size(); i++)
			{
				if (unitVector[i]->GetUnitKind() != LARVA)
				{
					for (int j = 0; j < _unitVector.size(); j++)
					{
						if (IntersectRect(&temp, &unitVector[i]->GetUnitRect(), &_unitVector[j]->GetUnitRect()))
						{

							// temp의 Width와 Height 선언
							int tempW = temp.right - temp.left;
							int tempH = temp.bottom - temp.top;

							if (tempH < tempW)
							{
								// 위쪽 충돌시 아래쪽으로 밀어줌
								if (temp.top == unitVector[i]->GetUnitRectTop())
								{
									unitVector[i]->SetUnitRectTop(unitVector[i]->GetUnitRectTop() + tempH / KNOCKBACK);
									unitVector[i]->SetUnitRectBottom(unitVector[i]->GetUnitRectBottom() + tempH / KNOCKBACK);
									unitVector[i]->SetUnitRectY(unitVector[i]->GetUnitRectY() + tempH / KNOCKBACK);
								}
								// 아래쪽 충돌시 위쪽으로 밀어줌
								else if (temp.bottom == unitVector[i]->GetUnitRectBottom())
								{
									unitVector[i]->SetUnitRectTop(unitVector[i]->GetUnitRectTop() - tempH / KNOCKBACK);
									unitVector[i]->SetUnitRectBottom(unitVector[i]->GetUnitRectBottom() - tempH / KNOCKBACK);
									unitVector[i]->SetUnitRectY(unitVector[i]->GetUnitRectY() - tempH / KNOCKBACK);
								}
							}
							else
							{
								// 왼쪽 충돌시 오른쪽으로 밀어줌
								if (temp.left == unitVector[i]->GetUnitRectLeft())
								{
									unitVector[i]->SetUnitRectLeft(unitVector[i]->GetUnitRectLeft() + tempW / KNOCKBACK);
									unitVector[i]->SetUnitRectRight(unitVector[i]->GetUnitRectRight() + tempW / KNOCKBACK);
									unitVector[i]->SetUnitRectX(unitVector[i]->GetUnitRectX() + tempW / KNOCKBACK);
								}
								// 오른쪽 충돌시 왼쪽으로 밀어줌
								else if (temp.right == unitVector[i]->GetUnitRectRight())
								{
									unitVector[i]->SetUnitRectLeft(unitVector[i]->GetUnitRectLeft() - tempW / KNOCKBACK);
									unitVector[i]->SetUnitRectRight(unitVector[i]->GetUnitRectRight() - tempW / KNOCKBACK);
									unitVector[i]->SetUnitRectX(unitVector[i]->GetUnitRectX() - tempW / KNOCKBACK);

								}
							}
						}
					}
				}
			}
			for (int i = 0; i < _unitVector.size(); i++)
			{
				if (_unitVector[i]->GetUnitKind() != LARVA)
				{
					for (int j = 0; j < unitVector.size(); j++)
					{
						if (IntersectRect(&temp, &_unitVector[i]->GetUnitRect(), &unitVector[j]->GetUnitRect()))
						{

							// temp의 Width와 Height 선언
							int tempW = temp.right - temp.left;
							int tempH = temp.bottom - temp.top;

							if (tempH < tempW)
							{
								// 위쪽 충돌시 아래쪽으로 밀어줌
								if (temp.top == _unitVector[i]->GetUnitRectTop())
								{
									_unitVector[i]->SetUnitRectTop(_unitVector[i]->GetUnitRectTop() + tempH / KNOCKBACK);
									_unitVector[i]->SetUnitRectBottom(_unitVector[i]->GetUnitRectBottom() + tempH / KNOCKBACK);
									_unitVector[i]->SetUnitRectY(_unitVector[i]->GetUnitRectY() + tempH / KNOCKBACK);
								}
								// 아래쪽 충돌시 위쪽으로 밀어줌
								else if (temp.bottom == _unitVector[i]->GetUnitRectBottom())
								{
									_unitVector[i]->SetUnitRectTop(_unitVector[i]->GetUnitRectTop() - tempH / KNOCKBACK);
									_unitVector[i]->SetUnitRectBottom(_unitVector[i]->GetUnitRectBottom() - tempH / KNOCKBACK);
									_unitVector[i]->SetUnitRectY(_unitVector[i]->GetUnitRectY() - tempH / KNOCKBACK);
								}
							}
							else
							{
								// 왼쪽 충돌시 오른쪽으로 밀어줌
								if (temp.left == _unitVector[i]->GetUnitRectLeft())
								{
									_unitVector[i]->SetUnitRectLeft(_unitVector[i]->GetUnitRectLeft() + tempW / KNOCKBACK);
									_unitVector[i]->SetUnitRectRight(_unitVector[i]->GetUnitRectRight() + tempW / KNOCKBACK);
									_unitVector[i]->SetUnitRectX(_unitVector[i]->GetUnitRectX() + tempW / KNOCKBACK);
								}
								// 오른쪽 충돌시 왼쪽으로 밀어줌
								else if (temp.right == _unitVector[i]->GetUnitRectRight())
								{
									_unitVector[i]->SetUnitRectLeft(_unitVector[i]->GetUnitRectLeft() - tempW / KNOCKBACK);
									_unitVector[i]->SetUnitRectRight(_unitVector[i]->GetUnitRectRight() - tempW / KNOCKBACK);
									_unitVector[i]->SetUnitRectX(_unitVector[i]->GetUnitRectX() - tempW / KNOCKBACK);

								}
							}
						}
					}
				}
			}

		}
	}

}
