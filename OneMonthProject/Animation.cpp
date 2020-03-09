#include "stdafx.h"
#include "Animation.h"


Animation::Animation()
	:_frameNum(0), _frameWidth(0), _frameHeight(0), _loop(false),
	_elapsedSec(0), _nowPlayIndex(0), _play(false)
{
}


Animation::~Animation()
{
}

HRESULT Animation::Init(int totalW, int totalH, int frameW, int frameH)
{
	//���� ������ ����
	_frameWidth = frameW;
	int frameWidthNum = totalW / _frameWidth;

	//���� ������ ����
	_frameHeight = frameH;
	int frameHeightNum = totalH / _frameHeight;

	//�� ������ ��
	_frameNum = frameWidthNum * frameHeightNum;


	//������ ��ġ ��� ���� ����.
	_frameList.clear();

	for (int i = 0; i < frameHeightNum; i++)
	{
		for (int j = 0; j < frameWidthNum; j++)
		{
			POINT framePos;
			framePos.x = j * _frameWidth;
			framePos.y = i * _frameHeight;

			//������ ��ġ ��� �߰��ϱ�
			_frameList.push_back(framePos);
		}
	}

	//�⺻ ���������� ��������.
	SetDefPlayFrame();
	return S_OK;
}

void Animation::SetDefPlayFrame(bool reverse, bool loop)
{
	//��������
	_loop = loop;
	//��� �ʱ�ȭ
	_playList.clear();

	if (reverse)
	{
		//������ �� 1�� �ε��� ����
		if (_loop)
		{
			//������
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}
			//������
			for (int i = _frameNum - 1; i > 0; i--)
			{
				_playList.push_back(i);
			}

		}
		//������ �� 0������
		else
		{
			//��
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}
			//��
			for (int i = _frameNum - 1; i >= 0; i--)
			{
				_playList.push_back(i);
			}
		}
	}
	else
	{
		//������
		for (int i = 0; i < _frameNum; i++)
		{
			_playList.push_back(i);
		}
	}

}

void Animation::SetPlayFrame(int * playArr, int arrLen, bool loop)
{
	_loop = loop;
	_playList.clear();

	for (int i = 0; i < arrLen; i++)
	{
		_playList.push_back(playArr[i]);
	}

}

//���۰� ��
void Animation::SetPlayFrame(int start, int end, bool reverse, bool loop)
{
	_loop = loop;
	_playList.clear();

	//���۰� ���� �������(�����ӱ���) ��� ���� ����
	if (start == end)
	{
		_playList.clear();
		Stop();
		return;
	}
	//���� �������� �� �����Ӻ��� ũ��
	else if (start > end)
	{
		//������ �� 1��������
		if (reverse)
		{
			if (_loop)
			{
				//��
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}
				//��
				for (int i = end + 1; i < start; i++)
				{
					_playList.push_back(i);
				}
			}
			//������ �� 0������
			else
			{
				//��
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}
				//��
				for (int i = end + 1; i <= start; i++)
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			for (int i = start; i <= end; i--)
			{
				_playList.push_back(i);
			}
		}
	}
	//���������� ���������� �� �����Ӻ��� �۴ٸ�
	else
	{
		if (reverse)
		{
			//������ �� 1��
			if (_loop)
			{
				for (int i = start; i <= end; i++)
				{
					_playList.push_back(i);
				}
				for (int i = end - 1; i > start; i--)
				{
					_playList.push_back(i);
				}
			}
			//������ �� 0�� ����
			else
			{	//��
				for (int i = start; i <= end; i++)
				{
					_playList.push_back(i);
				}
				//��
				for (int i = end - 1; i <= start; i--)
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			//��
			for (int i = start; i <= end; i++)
			{
				_playList.push_back(i);
			}
		}
	}
}

void Animation::SetFPS(int framePerSec)
{
	_FrameUpdateSec = 1.0f / framePerSec;
}

void Animation::FrameUpdate(float elapsedTime)
{
	//�÷��� ����?
	if (_play)
	{
		_elapsedSec += elapsedTime;

		//������ ������Ʈ �ð��� �Ǿ��ٸ�
		if (_elapsedSec >= _FrameUpdateSec)
		{
			_elapsedSec -= _FrameUpdateSec;
			_nowPlayIndex++;

			if (_nowPlayIndex == _playList.size())
			{
				if (_loop)
				{
					_nowPlayIndex = 0;
				}
				else
				{
					_nowPlayIndex--;
					_play = false;
				}
			}
		}
	}
}

void Animation::Start()
{
	_play = true;
	_nowPlayIndex = 0;
}

void Animation::Stop()
{
	_play = false;
	_nowPlayIndex = 0;
}

void Animation::Pause()
{
	_play = false;
}

void Animation::Resume()
{
	_play = true;
}
