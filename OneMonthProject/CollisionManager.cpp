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

					// temp�� Width�� Height ����
					int tempW = temp.right - temp.left;
					int tempH = temp.bottom - temp.top;

					if (tempH < tempW)
					{
						// ���� �浹�� �Ʒ������� �о���
						if (temp.top == unitVector[i]->GetUnitRectTop())
						{
							unitVector[i]->SetUnitRectTop(unitVector[i]->GetUnitRectTop() + tempH / KNOCKBACK);
							unitVector[i]->SetUnitRectBottom(unitVector[i]->GetUnitRectBottom() + tempH / KNOCKBACK);
							unitVector[i]->SetUnitRectY(unitVector[i]->GetUnitRectY() + tempH / KNOCKBACK);
						}
						// �Ʒ��� �浹�� �������� �о���
						else if (temp.bottom == unitVector[i]->GetUnitRectBottom())
						{
							unitVector[i]->SetUnitRectTop(unitVector[i]->GetUnitRectTop() - tempH / KNOCKBACK);
							unitVector[i]->SetUnitRectBottom(unitVector[i]->GetUnitRectBottom() - tempH / KNOCKBACK);
							unitVector[i]->SetUnitRectY(unitVector[i]->GetUnitRectY() - tempH / KNOCKBACK);
						}
					}
					else
					{
						// ���� �浹�� ���������� �о���
						if (temp.left == unitVector[i]->GetUnitRectLeft())
						{
							unitVector[i]->SetUnitRectLeft(unitVector[i]->GetUnitRectLeft() + tempW / KNOCKBACK);
							unitVector[i]->SetUnitRectRight(unitVector[i]->GetUnitRectRight() + tempW / KNOCKBACK);
							unitVector[i]->SetUnitRectX(unitVector[i]->GetUnitRectX() + tempW / KNOCKBACK);
						}
						// ������ �浹�� �������� �о���
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

							// temp�� Width�� Height ����
							int tempW = temp.right - temp.left;
							int tempH = temp.bottom - temp.top;

							if (tempH < tempW)
							{
								// ���� �浹�� �Ʒ������� �о���
								if (temp.top == unitVector[i]->GetUnitRectTop())
								{
									unitVector[i]->SetUnitRectTop(unitVector[i]->GetUnitRectTop() + tempH / KNOCKBACK);
									unitVector[i]->SetUnitRectBottom(unitVector[i]->GetUnitRectBottom() + tempH / KNOCKBACK);
									unitVector[i]->SetUnitRectY(unitVector[i]->GetUnitRectY() + tempH / KNOCKBACK);
								}
								// �Ʒ��� �浹�� �������� �о���
								else if (temp.bottom == unitVector[i]->GetUnitRectBottom())
								{
									unitVector[i]->SetUnitRectTop(unitVector[i]->GetUnitRectTop() - tempH / KNOCKBACK);
									unitVector[i]->SetUnitRectBottom(unitVector[i]->GetUnitRectBottom() - tempH / KNOCKBACK);
									unitVector[i]->SetUnitRectY(unitVector[i]->GetUnitRectY() - tempH / KNOCKBACK);
								}
							}
							else
							{
								// ���� �浹�� ���������� �о���
								if (temp.left == unitVector[i]->GetUnitRectLeft())
								{
									unitVector[i]->SetUnitRectLeft(unitVector[i]->GetUnitRectLeft() + tempW / KNOCKBACK);
									unitVector[i]->SetUnitRectRight(unitVector[i]->GetUnitRectRight() + tempW / KNOCKBACK);
									unitVector[i]->SetUnitRectX(unitVector[i]->GetUnitRectX() + tempW / KNOCKBACK);
								}
								// ������ �浹�� �������� �о���
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