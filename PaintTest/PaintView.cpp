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
	_drawButton = new QPushButton("desen", this);
	_rectButton->move(QPoint(70, 0));
	_drawButton->move(QPoint(140, 0));
	connect(_lineButton, &QPushButton::clicked, this,&PaintView::clickLineButton);
	connect(_rectButton, &QPushButton::clicked, this,&PaintView::clickRectButton);
	connect(_drawButton, &QPushButton::clicked, this, &PaintView::clickDrawButton);
}

PaintView::~PaintView()
{
}
QGraphicsEllipseItem* PaintView::createPoint(const QPointF& pt)
{
	double rad = 1;
	return _scene->addEllipse(pt.x() - rad, pt.y() - rad, rad * 2.0, rad * 2.0,
		QPen(), QBrush(Qt::SolidPattern)) ;
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

void PaintView::clickLineButton() {
	emit buttonSelect(1);
}
void PaintView::clickRectButton() {
	emit buttonSelect(2);
}

void PaintView::clickDrawButton()
{
	emit buttonSelect(0);
}
