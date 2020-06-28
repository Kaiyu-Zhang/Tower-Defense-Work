#include "towerbase.h"
#include <QPainter>

const QSize TowerBase::ms_fixedSize(44, 44);

TowerBase::TowerBase(QPoint pos, const QPixmap &sprite/* = QPixmap(":/image/open_spot.png")*/)
	: m_hasTower(false)
	, m_pos(pos)
	, m_sprite(sprite)
{
}

const QPoint TowerBase::centerPos() const
{
	QPoint offsetPoint(ms_fixedSize.width() / 2, ms_fixedSize.height() / 2);
	return m_pos + offsetPoint;
}

bool TowerBase::containPoint(const QPoint &pos) const
{
	bool isXInHere = m_pos.x() < pos.x() && pos.x() < (m_pos.x() + ms_fixedSize.width());
	bool isYInHere = m_pos.y() < pos.y() && pos.y() < (m_pos.y() + ms_fixedSize.height());
	return isXInHere && isYInHere;
}

bool TowerBase::hasTower() const
{
    return m_hasTower;
}

const QPoint TowerBase::pointTower() const
{
    return m_pos;
}

void TowerBase::setHasTower(bool hasTower/* = true*/)
{
	m_hasTower = hasTower;
}

void TowerBase::draw(QPainter *painter) const
{
	painter->drawPixmap(m_pos.x(), m_pos.y(), m_sprite);
}
