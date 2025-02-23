#pragma once

#include <QtCore/QObject>

#include "PaintView.h"

class PaintController : public QObject
{
	Q_OBJECT

public:
					PaintController(QObject *parent, PaintView* view);
					~PaintController();

public slots:
	void			onActionSelect();
	void			onActionLine();
	void			onActionRectangle();
	void			onActionEllipse();

protected slots:
	void			onMousePress(const QPointF& pos, const Qt::MouseButtons& buttons);
	void			onMouseMove(const QPointF& pos, const Qt::MouseButtons& buttons);
	void			onMouseRelease(const QPointF& pos, const Qt::MouseButtons& buttons);

private:
	PaintView*			_view;

	QGraphicsLineItem*	_line;
	QGraphicsRectItem*  _rectangle;
	QGraphicsEllipseItem* _ellipse;
	QPointF			    _point;

	QString				_selectedTool;
};
