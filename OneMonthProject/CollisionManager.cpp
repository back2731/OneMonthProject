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

void CollisionManager::CollisionSameVector(vector<UnitBase*>& unitVector)
{
	if (!unitVector.empty())
	{
		for (int i = 0; i < unitVector.size(); i++)
		{
			for (int j = 0; j < unitVector.size(); j++)
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
						if (IntersectRect(&temp, &unitVector[i]->GetUnitRect(), &buildingVector[j]->GetBuildingRect()))
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
		}
	}
}