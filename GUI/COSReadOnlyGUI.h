#pragma once
#include "ui_GUI.h"
#include "Service.h"
#include "Observer.h"
#include <qpainter.h>
class COSReadOnlyGUI : public QWidget, public Observer
{
	Q_OBJECT
public:
	COSReadOnlyGUI(Service& service, QWidget *parent = Q_NULLPTR) : QWidget(parent), service(service)
	{
		setWindowTitle("COS DRAW");
		this->resize(500, 400);
		service.suntCurios(this);
	}
	void update()
	{
		repaint();
	}
private:
	Ui::GUIClass ui;
	Service& service;
protected:
	void paintEvent(QPaintEvent* ev) override
	{		for (int i = 0; i < service.getCos().size(); ++i)		{			QPainter p{ this };			//p.drawRect(i*10+4,i*30+100,i*9-10,i*6-20);
			int x = rand() % 500;
			int y = rand() % 400;
			int h = rand() % 10;
			int w = rand() % 10;
			p.drawRect(x, y, h * 10, w * 8);
		}
	}
};