#pragma once
#include <qlabel.h>
#include <qwidget.h>
#include <qformlayout.h>
#include <qboxlayout.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qtablewidget.h>
#include <qlineedit.h>
#include <qmessagebox.h>
#include <qpainter.h>
#include "ui_Lab_10_11.h"
#include "Service.h"
#include "Observer.h"
class CosReadOnlyGUI: public QWidget, public Observer
{
private:
	Service& service;
	Cos& cos;
protected:
	void paintEvent(QPaintEvent*) override
	{
		QPainter g{ this };
		for (int i=0;i<cos.cos_lungime();i++)
		{
			int x = rand() % 400 + 1;
			int y = rand() % 400 + 1;
			g.drawImage(x, y, QImage("Dante.jpg"));
		}
	}
public:
	CosReadOnlyGUI(Service& s, Cos& c) : service{ s }, cos { c }
	{
		c.addObserver(this);
		update();
	}
	void update() override {
		this->repaint();
	}
};

