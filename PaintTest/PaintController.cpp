#include "PaintController.h"

#include <QtWidgets/QGraphicsLineItem>
PaintController::PaintController(QObject *parent, PaintView* view)
	: QObject(parent),
	_view(view)
{
}

PaintController::~PaintController()
{
}

void PaintController::onMousePress(const QPoint& pos, const Qt::MouseButtons& buttons)
{
	if (selection == 1) {
		_line = _view->createLine(QLineF(pos, pos));
	}
	else if (selection == 2) {
		_rect = _view->createRect(QRectF(pos, pos));
		_point = pos; /// salvez punctul in care incepe dreptunghiul pt update

	}
}

void PaintController::onMouseMove(const QPoint& pos, const Qt::MouseButtons& buttons)
{
	if (buttons != Qt::MouseButton::LeftButton)
		return;
	if (selection == 1) {
		QLineF line = _line->line();
		line.setP2(pos);
		_line->setLine(line);
	}
	else if (selection == 2) {
		QRectF rect = _rect->rect();
		QPoint topLeft = QPoint(std::min(_point.x(), pos.x()), std::min(_point.y(), pos.y()));
		QPoint bottomRight = QPoint(std::max(_point.x(), pos.x()), std::max(_point.y(), pos.y()));
		rect.setTopLeft(topLeft);
		rect.setBottomRight(bottomRight);
		_rect->setRect(rect);
	}
}

void PaintController::onMouseRelease(const QPoint& pos, const Qt::MouseButtons& buttons)
{
}

