#pragma once
#include "ui_GUI.h"
#include "Service.h"
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/QListWidget>
#include <Observer.h>
class COSGUI : public QWidget, public Observer
{
	Q_OBJECT
public:
	COSGUI(Service& service, QWidget *parent = Q_NULLPTR);

	void update()
	{
		incarcaDateInCos(service.getCos());
	}
private:
	Ui::GUIClass ui;
	Service& service;

	QListWidget* cosLista;

	QPushButton* clearCosButton;
	QPushButton* generateCosButton;
	void incarcaDateInCos(vector<Film>);
	void connectSignalsSlotsCos();
};