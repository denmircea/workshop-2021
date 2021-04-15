#include "PaintView.h"

#include <QtGui/QMouseEvent>
static const int	kWindowWidth	= 800;
static const int	kWindowHeight	= 600;

static const QColor kInitialColor = QColor(0, 0, 0);
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
	_colorButton = new QPushButton("schimbare culoare", this);
	_rectButton->move(QPoint(0, 70));
	_drawButton->move(QPoint(0, 140));
	_colorButton->move(QPoint(0, 210));
	connect(_lineButton, &QPushButton::clicked, this,&PaintView::clickLineButton);
	connect(_rectButton, &QPushButton::clicked, this,&PaintView::clickRectButton);
	connect(_drawButton, &QPushButton::clicked, this, &PaintView::clickDrawButton);
	connect(_colorButton, &QPushButton::clicked, this, &PaintView::clickColorButton);
	_colorDialog = new QColorDialog(kInitialColor, this);
	_colorDialog->move(QPoint(150, 105));
	_pen = new QPen(kInitialColor,3);
}

PaintView::~PaintView()
{
}
QGraphicsEllipseItem* PaintView::createPoint(const QPointF& pt)
{
	double rad = 1;
	return _scene->addEllipse(pt.x() - rad, pt.y() - rad, rad * 2.0, rad * 2.0,
		getPen(), QBrush(Qt::SolidPattern)) ;
}
QGraphicsLineItem* PaintView::createLine(const QLineF& line)
{
	return _scene->addLine(line,getPen());
}
QGraphicsRectItem* PaintView::createRect(const QRectF& rect)
{
	return _scene->addRect(rect, getPen());
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

void PaintView::keyPressEvent(QKeyEvent* event)
{
	Qt::KeyboardModifiers modifiers = event->modifiers();
	emit keyPress(modifiers);
}

void PaintView::keyReleaseEvent(QKeyEvent* event)
{
	Qt::KeyboardModifiers modifiers = event->modifiers();
	emit keyPress(modifiers);
}

QPen PaintView::getPen()
{
	return *_pen;
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

void PaintView::clickColorButton()
{
	_pen->setColor(_colorDialog->getColor());
}

