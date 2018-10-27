#pragma once
#include "ui_GUI.h"
#include "Service.h"
#include "MovieForm.h"
#include "COSGUI.h"
#include "COSReadOnlyGUI.h"
#include <QtWidgets/QListWidget>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qradiobutton.h>


class GUI : public QWidget, public Observer
{
	Q_OBJECT

public:
	GUI(Service& service, QWidget *parent = Q_NULLPTR);

	void update()
	{
		incarcaDateInCos(service.getCos());
	}

private:
	Ui::GUIClass ui;
	Service& service;
	QListWidget* lista;
	QListWidget* cosLista;
	COSGUI cos{ service };
	QLineEdit* fileEdit;

	MovieForm* movieForm;
	MovieForm* movieForm2;

	QPushButton* addButton;
	QPushButton* addSecondButton;
	QPushButton* updateButton;
	QPushButton* deleteButton;

	QPushButton* filterButton;
	QLineEdit* filterEdit;
	QPushButton* clearFilterButton;
	QRadioButton* filterByYearRadioButton;
	QRadioButton* filterByTitleRadioButton;

	QPushButton* sortTitle;
	QPushButton* sortActor;

	QDialog* draw;

	QPushButton* addToCosButton;
	QPushButton* clearCosButton;
	QPushButton* generateCosButton;
	QPushButton* exportCSVButton;
	QPushButton* exportHTMLButton;
	QPushButton* addCosGui;
	QPushButton* addCosReadOnly;

	QPushButton* undoButton;

	void incarcaDate(vector<std::pair<int, Film>>);
	void incarcaDateInCos(vector<Film>);
	void connectSignalsSlots();
	void connectSignalsSlotsCos();

	QVBoxLayout* getRightLayout();
	QVBoxLayout* getLeftLayout();
	QVBoxLayout* getCosLayout();
	//QVBoxLayout* getHistogram();

};
