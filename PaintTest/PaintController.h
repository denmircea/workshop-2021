#pragma once

#include <QtCore/QObject>

#include "PaintView.h"

class PaintController : public QObject
{
	Q_OBJECT

public:
					PaintController(QObject *parent, PaintView* view);
					~PaintController();

protected slots:
	void			onMousePress(const QPoint& pos, const Qt::MouseButtons& buttons);
	void			onMouseMove(const QPoint& pos, const Qt::MouseButtons& buttons);
	void			onMouseRelease(const QPoint& pos, const Qt::MouseButtons& buttons);
	void			onButtonSelect(int id);
	void			onKeyPress(const Qt::KeyboardModifiers& buttons);
private:
	PaintView*			_view;

	QGraphicsLineItem*	_line;
	QGraphicsRectItem*  _rect;
	QPoint _point;
	bool _shiftPressed;
	int _selection;
};
