#include "StdAfx.h"
#include "Enemy.h"
#include "resource.h"

CImageList CEnemy::m_Images;

CEnemy::CEnemy(void)
{
	//随机确定X位置
	m_ptPos.x = rand()%(GAME_WIDTH-ENEMY_HEIGHT);

	//随机确定图像索引
	m_nImgIndex = rand()%2;

	//根据图像索引确定方向
	m_nMotion=1;
	m_ptPos.y=-ENEMY_HEIGHT;
	if (m_nImgIndex%2!=0)//如果是图像索引是偶数
	{
		m_ptPos.y = GAME_HEIGHT+ENEMY_HEIGHT;
	}
	//随机确定速度
	m_V = rand()%6+2;

	m_nWait=10;
}

CEnemy::~CEnemy(void)
{
}
BOOL CEnemy::LoadImage()
{
	return CGameObject::LoadImage(m_Images,IDB_BITMAP13,RGB(255,255,255),38,49,2);
}
BOOL CEnemy::Draw(CDC* pDC,BOOL bPause)
{
	m_nWait++;
	if(m_nWait>20)
		m_nWait=10;

	if(!bPause)//调整飞机飞行方向
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
		if(m_V<1)
			m_ptPos.x = m_ptPos.x + rand()%3+3;
		else if(m_V>=1&&m_V<2)
			m_ptPos.x = m_ptPos.x + rand()%2-2;
		else if(m_V>=2&&m_V<3)
			m_ptPos.x = m_ptPos.x + rand()%1-1;
		else if(m_V>=3&&m_V<4)
			m_ptPos.x = m_ptPos.x + rand()%3+4;
		else if(m_V>=4&&m_V<5)
			m_ptPos.x = m_ptPos.x + rand()%2+1;
		else
			m_ptPos.x = m_ptPos.x;
	}

	if(m_ptPos.y > GAME_HEIGHT+ENEMY_HEIGHT )
		return FALSE;
	if(m_ptPos.y < -ENEMY_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC,m_nImgIndex,m_ptPos,ILD_TRANSPARENT);

	return TRUE;
}
BOOL CEnemy::Fired()
{
	if(m_nWait==10)
		return TRUE;
	else
		return FALSE;
}