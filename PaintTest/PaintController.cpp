#include "PaintController.h"

#include <QtWidgets/QGraphicsLineItem>
#include <QtCore/qdebug.h>

const QString kLineTool = "lineTool";
const QString kSelectTool = "selectTool";
const QString kRectangleTool = "rectangleTool";
const QString kEllipseTool = "ellipseTool";


PaintController::PaintController(QObject *parent, PaintView* view)
	: QObject(parent),
	_view(view),
	_selectedTool("")
{
}

PaintController::~PaintController()
{
}

void PaintController::onActionSelect()
{
	qDebug() << "Action select triggered";
	_selectedTool = kSelectTool;
}

void PaintController::onActionLine()
{
	qDebug() << "Action line triggered";
	_selectedTool = kLineTool;
}

void PaintController::onActionRectangle()
{
	qDebug() << "Action rectangle triggered";
	_selectedTool = kRectangleTool;
}

void PaintController::onActionEllipse()
{
	qDebug() << "Action ellipse triggered";
	_selectedTool = kEllipseTool;
}

void PaintController::onMousePress(const QPointF& pos, const Qt::MouseButtons& buttons)
{
	if (_selectedTool == kLineTool)
	{
		_line = _view->createLine(QLineF(pos, pos));
	}
	else if (_selectedTool == kRectangleTool)
	{
		_rectangle = _view->createRectangle(QRectF(pos, pos));
		_point = pos; /// salvez punctul in care incepe dreptunghiul pt update
	}
	else if (_selectedTool == kEllipseTool)
	{
		_ellipse = _view->createEllipse(QRectF(pos, pos));
		_point = pos;
	}
}

void PaintController::onMouseMove(const QPointF& pos, const Qt::MouseButtons& buttons)
{
	if (buttons != Qt::MouseButton::LeftButton)
		return;

	if (_selectedTool == kLineTool)
	{
		QLineF line = _line->line();
		line.setP2(pos);
		_line->setLine(line);
	}
	else if (_selectedTool == kRectangleTool)
	{
		QRectF rect = _rectangle->rect();
		QPointF topLeft = QPointF(std::min(_point.x(), pos.x()), std::min(_point.y(), pos.y()));
		QPointF bottomRight = QPointF(std::max(_point.x(), pos.x()), std::max(_point.y(), pos.y()));
		rect.setTopLeft(topLeft);
		rect.setBottomRight(bottomRight);
		_rectangle->setRect(rect);
	}
	else if (_selectedTool == kEllipseTool)
	{
		QRectF rect = _ellipse->rect();
		QPointF topLeft = QPointF(std::min(_point.x(), pos.x()), std::min(_point.y(), pos.y()));
		QPointF bottomRight = QPointF(std::max(_point.x(), pos.x()), std::max(_point.y(), pos.y()));
		rect.setTopLeft(topLeft);
		rect.setBottomRight(bottomRight);
		_ellipse->setRect(rect);
	}
}

void PaintController::onMouseRelease(const QPointF& pos, const Qt::MouseButtons& buttons)
{
}
