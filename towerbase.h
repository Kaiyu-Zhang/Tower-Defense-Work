#ifndef TOWERPOSITION_H
#define TOWERBASE_H

#include <QPoint>
#include <QSize>
#include <QPixmap>

class QPainter;

class TowerBase
{
public:
    TowerBase(QPoint pos, const QPixmap &sprite = QPixmap(":/image/open_spot.png"));

	void setHasTower(bool hasTower = true);
	bool hasTower() const;
    const QPoint pointTower() const;
	const QPoint centerPos() const;
	bool containPoint(const QPoint &pos) const;

	void draw(QPainter *painter) const;

public:
	bool		m_hasTower;
	QPoint		m_pos;
	QPixmap		m_sprite;

	static const QSize ms_fixedSize;
};

#endif // TOWERBASE_H
