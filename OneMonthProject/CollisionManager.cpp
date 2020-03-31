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
									unitVector[i]->SetUnitRectTop(unitVector[i]->GetUnitRectTop());
									unitVector[i]->SetUnitRectBottom(unitVector[i]->GetUnitRectBottom());
									unitVector[i]->SetUnitRectY(unitVector[i]->GetUnitRectY());
								}
								// 아래쪽 충돌시 위쪽으로 밀어줌
								else if (temp.bottom == unitVector[i]->GetUnitRectBottom())
								{
									unitVector[i]->SetUnitRectTop(unitVector[i]->GetUnitRectTop());
									unitVector[i]->SetUnitRectBottom(unitVector[i]->GetUnitRectBottom());
									unitVector[i]->SetUnitRectY(unitVector[i]->GetUnitRectY());
								}
							}
							else
							{
								// 왼쪽 충돌시 오른쪽으로 밀어줌
								if (temp.left == unitVector[i]->GetUnitRectLeft())
								{
									unitVector[i]->SetUnitRectLeft(unitVector[i]->GetUnitRectLeft());
									unitVector[i]->SetUnitRectRight(unitVector[i]->GetUnitRectRight());
									unitVector[i]->SetUnitRectX(unitVector[i]->GetUnitRectX());
								}
								// 오른쪽 충돌시 왼쪽으로 밀어줌
								else if (temp.right == unitVector[i]->GetUnitRectRight())
								{
									unitVector[i]->SetUnitRectLeft(unitVector[i]->GetUnitRectLeft());
									unitVector[i]->SetUnitRectRight(unitVector[i]->GetUnitRectRight());
									unitVector[i]->SetUnitRectX(unitVector[i]->GetUnitRectX());

								}
							}
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
									unitVector[i]->SetUnitRectTop(unitVector[i]->GetUnitRectTop() + tempH / KNOCKBACK * 0.2);
									unitVector[i]->SetUnitRectBottom(unitVector[i]->GetUnitRectBottom() + tempH / KNOCKBACK * 0.2);
									unitVector[i]->SetUnitRectY(unitVector[i]->GetUnitRectY() + tempH / KNOCKBACK * 0.2);
								}
								// 아래쪽 충돌시 위쪽으로 밀어줌
								else if (temp.bottom == unitVector[i]->GetUnitRectBottom())
								{
									unitVector[i]->SetUnitRectTop(unitVector[i]->GetUnitRectTop() - tempH / KNOCKBACK * 0.2);
									unitVector[i]->SetUnitRectBottom(unitVector[i]->GetUnitRectBottom() - tempH / KNOCKBACK * 0.2);
									unitVector[i]->SetUnitRectY(unitVector[i]->GetUnitRectY() - tempH / KNOCKBACK * 0.2);
								}
							}
							else
							{
								// 왼쪽 충돌시 오른쪽으로 밀어줌
								if (temp.left == unitVector[i]->GetUnitRectLeft())
								{
									unitVector[i]->SetUnitRectLeft(unitVector[i]->GetUnitRectLeft() + tempW / KNOCKBACK * 0.2);
									unitVector[i]->SetUnitRectRight(unitVector[i]->GetUnitRectRight() + tempW / KNOCKBACK * 0.2);
									unitVector[i]->SetUnitRectX(unitVector[i]->GetUnitRectX() + tempW / KNOCKBACK * 0.2);
								}
								// 오른쪽 충돌시 왼쪽으로 밀어줌
								else if (temp.right == unitVector[i]->GetUnitRectRight())
								{
									unitVector[i]->SetUnitRectLeft(unitVector[i]->GetUnitRectLeft() - tempW / KNOCKBACK * 0.2);
									unitVector[i]->SetUnitRectRight(unitVector[i]->GetUnitRectRight() - tempW / KNOCKBACK * 0.2);
									unitVector[i]->SetUnitRectX(unitVector[i]->GetUnitRectX() - tempW / KNOCKBACK * 0.2);

								}
							}
						}
					}
				}
			}
		}
	}

}
