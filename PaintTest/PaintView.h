#pragma once

#include <QtWidgets/QGraphicsView>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qcolordialog.h>
class PaintView : public QGraphicsView
{
	Q_OBJECT
public:
						PaintView(QWidget *parent);
						~PaintView();

	QGraphicsLineItem*	createLine(const QLineF& line);
	QGraphicsRectItem* createRect(const QRectF& rect);
	QGraphicsEllipseItem* createPoint(const QPointF& point);

	

signals:
	void				mousePress(const QPoint& pos, const Qt::MouseButtons& buttons);
	void				mouseMove(const QPoint& pos, const Qt::MouseButtons& buttons);
	void				mouseRelease(const QPoint& pos, const Qt::MouseButtons& buttons);
	void				keyPress(const Qt::KeyboardModifiers& buttons);
	void				buttonSelect(int id);
	void				colorChange(const QColor& color);
private:
	void				mousePressEvent(QMouseEvent* event) override;
	void				mouseMoveEvent(QMouseEvent* event) override;
	void				mouseReleaseEvent(QMouseEvent* event) override;
	void				keyPressEvent(QKeyEvent* event) override;
	void				keyReleaseEvent(QKeyEvent* event) override;
	QPen 				getPen();
public slots:
	void  clickLineButton();
	void  clickRectButton();
	void  clickDrawButton();
	void  clickColorButton();
private:
	QGraphicsScene*	_scene;
	QPushButton* _lineButton;
	QPushButton* _rectButton;
	QPushButton* _drawButton;
	QPushButton* _colorButton;
	QColorDialog* _colorDialog;
	QPen* _pen;
};				
