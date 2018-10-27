#include <COSGUI.h>
#include <QtWidgets\QHBoxLayout>
#include <QtWidgets\QVBoxLayout>
#include <QtWidgets\qlistwidget.h>
#include "QMListWidgetItem.h"

COSGUI::COSGUI(Service& service, QWidget *parent) : QWidget(parent), service(service)
{
	setWindowTitle("COS FILME");
	service.suntCurios(this);
	auto mainLayout = new QHBoxLayout();
	auto cosContainer = new QVBoxLayout();
	this->cosLista = new QListWidget();
	cosContainer->addWidget(this->cosLista);

	this->clearCosButton = new QPushButton("Curata cosul");
	cosContainer->addWidget(this->clearCosButton);

	this->generateCosButton = new QPushButton("Genereaza cos");
	cosContainer->addWidget(this->generateCosButton);

	mainLayout->addLayout(cosContainer);
	this->setLayout(mainLayout);
	connectSignalsSlotsCos();
}

void COSGUI::incarcaDateInCos(vector<Film> filme)
{
	this->cosLista->clear();
	int i = 0;
	for (const auto& f : filme)
	{
		auto fl = std::make_pair(i, f);
		auto qListWidgetItem = new QMListWidgetItem(fl);
		qListWidgetItem->setText((f.getTitlu().c_str()));
		this->cosLista->addItem(qListWidgetItem);
	}
}
void COSGUI::connectSignalsSlotsCos()
{

	QObject::connect(this->clearCosButton, &QPushButton::clicked, [&]()
	{
		auto cos = this->service.golesteCos();
		this->incarcaDateInCos(cos);
	});
	QObject::connect(this->generateCosButton, &QPushButton::clicked, [&]()
	{
		auto cos = this->service.addRandom();
		this->incarcaDateInCos(cos);
	});

}