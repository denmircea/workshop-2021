#include "PaintView.h"

#include <QtGui/QMouseEvent>
static const int	kWindowWidth	= 800;
static const int	kWindowHeight	= 600;

PaintView::PaintView(QWidget *parent)
	: QGraphicsView(parent)
{
	_scene = new QGraphicsScene(this);
	_scene->setSceneRect(QRectF(0, 0, kWindowWidth, kWindowHeight));

	this->setScene(_scene);
	this->centerOn(0, 0);
	_lineButton = new QPushButton("linie",this);
	_rectButton = new QPushButton("dreptunghi", this);
	_rectButton->move(QPoint(70, 0));
}

PaintView::~PaintView()
{
}

QGraphicsLineItem* PaintView::createLine(const QLineF& line)
{
	return _scene->addLine(line);
}
QGraphicsRectItem* PaintView::createRect(const QRectF& rect)
{
	return _scene->addRect(rect);
}

void PaintView::mousePressEvent(QMouseEvent* event)
{
	QPoint pos = event->pos();
	Qt::MouseButtons buttons = event->buttons();
	emit mousePress(pos, buttons);
}

void PaintView::mouseMoveEvent(QMouseEvent* event)
{
	QPoint pos = event->pos();
	Qt::MouseButtons buttons = event->buttons();
	emit mouseMove(pos, buttons);
}

void PaintView::mouseReleaseEvent(QMouseEvent* event)
{
	QPoint pos = event->pos();
	Qt::MouseButtons buttons = event->buttons();
	emit mouseRelease(pos, buttons);
}
