#include "GUI.h"
#include <QtWidgets\QHBoxLayout>
#include <QtWidgets\QVBoxLayout>
#include <QtWidgets\qgroupbox.h>
#include "QMListWidgetItem.h"
#include <QtWidgets\qlistwidget.h>
#include <functional>
#include <qmessagebox.h>
#include <qtablewidget.h>
#include <qdebug.h>

GUI::GUI(Service& service, QWidget *parent) : QWidget(parent), service(service)
{
	setWindowTitle("INCHIRIERI DE FILME");
	service.suntCurios(this);
	auto mainLayout = new QHBoxLayout();
	mainLayout->addLayout(this->getCosLayout());
	mainLayout->addSpacing(15);
	mainLayout->addLayout(this->getLeftLayout());
	mainLayout->addSpacing(15);
	mainLayout->addLayout(this->getRightLayout());
	mainLayout->addSpacing(15);
	//mainLayout->addLayout(this->getHistogram());

	this->setLayout(mainLayout);

	connectSignalsSlots();
	connectSignalsSlotsCos();
}
QVBoxLayout* GUI::getRightLayout()
{
	auto rightContainer = new QVBoxLayout();
	this->movieForm = new MovieForm();
	rightContainer->addLayout(movieForm->getForm());

	auto filterContainer = new QHBoxLayout();
	this->filterButton = new QPushButton("Filtreaza");
	filterContainer->addWidget(this->filterButton);
	this->filterEdit = new QLineEdit();
	filterContainer->addWidget(this->filterEdit);

	auto filterBox = new QGroupBox("Filtru");
	this->filterByTitleRadioButton = new QRadioButton("Dupa titlu");
	this->filterByYearRadioButton = new QRadioButton("Dupa an");

	auto filterRatioButtonsLayout = new QHBoxLayout();
	filterRatioButtonsLayout->addWidget(this->filterByTitleRadioButton);
	filterRatioButtonsLayout->addWidget(this->filterByYearRadioButton);
	filterBox->setLayout(filterRatioButtonsLayout);

	//this->clearFilterButton = new QPushButton("Curata filtrare");
	//this->clearFilterButton->setEnabled(false);

	rightContainer->addSpacing(20);
	rightContainer->addWidget(filterBox);
	//rightContainer->addWidget(this->clearFilterButton);
	rightContainer->addLayout(filterContainer);
	rightContainer->addSpacing(20);

	auto movieOperationsLayout = new QHBoxLayout();
	this->addButton = new QPushButton("Adauga");
	rightContainer->addWidget(this->addButton);

	this->deleteButton = new QPushButton("Sterge");
	this->deleteButton->setEnabled(false);
	rightContainer->addWidget(this->deleteButton);

	this->updateButton = new QPushButton("Modifica");
	this->updateButton->setEnabled(false);
	rightContainer->addWidget(this->updateButton);

	return rightContainer;
}
QVBoxLayout* GUI::getLeftLayout()
{
	auto leftContainer = new QVBoxLayout();
	this->lista = new QListWidget();
	incarcaDate(this->service.getAll());
	leftContainer->addWidget(this->lista);

	auto sortContainer = new QHBoxLayout();
	this->sortTitle = new QPushButton("Sorteaza dupa titlu");
	this->sortActor = new QPushButton("Sorteaza dupa actor");
	sortContainer->addWidget(this->sortTitle);
	sortContainer->addWidget(this->sortActor);

	auto undoContainer = new QHBoxLayout();
	this->undoButton = new QPushButton("Undo");
	this->undoButton->setDisabled(false);
	undoContainer->addWidget(this->undoButton);

	leftContainer->addSpacing(15);
	leftContainer->addLayout(sortContainer);
	leftContainer->addSpacing(10);
	leftContainer->addLayout(undoContainer);
	return leftContainer;

}

QVBoxLayout* GUI::getCosLayout()
{
	auto cosContainer = new QVBoxLayout();
	this->cosLista = new QListWidget();
	cosContainer->addWidget(this->cosLista);

	this->addToCosButton = new QPushButton("Adauga in cos");
	this->clearCosButton = new QPushButton("Curata cosul");
	this->generateCosButton = new QPushButton("Genereaza cos");
	this->exportCSVButton = new QPushButton("Export CVS");
	this->exportHTMLButton = new QPushButton("Export HTML");
	this->addCosGui = new QPushButton("Add Cos Window");
	this->addCosReadOnly = new QPushButton("Add Read Only Window");


	cosContainer->addWidget(this->addToCosButton);
	this->addToCosButton->setEnabled(false);
	cosContainer->addWidget(this->clearCosButton);
	cosContainer->addWidget(this->generateCosButton);
	auto fileForm = new QFormLayout();
	this->fileEdit = new QLineEdit();
	this->fileEdit->setEnabled(1);
	fileForm->addRow(" Fisier de export  ", this->fileEdit);
	cosContainer->addLayout(fileForm);
	auto exportLayout = new QHBoxLayout();
	exportLayout->addWidget(this->exportCSVButton);
	exportLayout->addWidget(this->exportHTMLButton);
	cosContainer->addLayout(exportLayout);
	cosContainer->addWidget(this->addCosGui);
	cosContainer->addWidget(this->addCosReadOnly);
	//cosContainer->addWidget(this->exportCSVButton);
	//cosContainer->addWidget(this->exportHTMLButton);
	return cosContainer;
}
void GUI::incarcaDate(vector<std::pair<int, Film>> filme)
{
	this->lista->clear();
	for (const auto& f : filme)
	{
		auto qListWidgetItem = new QMListWidgetItem(f);
		qListWidgetItem->setText((f.second.getTitlu().c_str()));
		//qListWidgetItem->setBackgroundColor("Red");

		this->lista->addItem(qListWidgetItem);
	}
}
void GUI::incarcaDateInCos(vector<Film> filme)
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
void GUI::connectSignalsSlots()
{
	QObject::connect(this->lista, &QListWidget::itemSelectionChanged, [&]()
	{
		if (this->lista->selectedItems().isEmpty())
		{
			this->movieForm->clearData();
			this->deleteButton->setEnabled(false);
			this->updateButton->setEnabled(false);
		}
		else
		{
			QMListWidgetItem* itemSelected = (QMListWidgetItem*)this->lista->selectedItems().at(0);
			this->movieForm->setData(itemSelected->getFilm());
			//this->lista->selectedItems().at(0)->setBackgroundColor("yellow");
			this->deleteButton->setEnabled(true);
			this->updateButton->setEnabled(true);
		}
	});

	QObject::connect(this->addButton, &QPushButton::clicked, [&]()
	{
		qDebug() << "Apasat!";
		//std::string() defines the c_str() member which returns a pointer to the string, followed by a null byte.
		auto addWindow = new QDialog();
		auto addLayoutX = new QVBoxLayout();
		this->movieForm2 = new MovieForm();
		addLayoutX->addLayout(movieForm2->getForm());
		this->addSecondButton = new QPushButton("Adauga");
		QObject::connect(this->addSecondButton, &QPushButton::clicked, [&]()
		{
			qDebug() << "Apasat!";
			auto book = this->movieForm2->getFilm();
			try
			{
				this->service.adauga(book.getTitlu(), book.getGen(), book.getAn(), book.getActor());

			}
			catch (ValidateException& ex)
			{
				QMessageBox messBox;
				messBox.setText(ex.getMessage().c_str());
				messBox.exec();
				return false;
			}
			catch (RepositoryException& ex)
			{
				QMessageBox messBox;
				messBox.setText(ex.msg.c_str());
				messBox.exec();
				return false;
			}
			catch (exception& ex)
			{
				QMessageBox messBox;
				messBox.setText(ex.what());
				messBox.exec();
			}
			this->incarcaDate(this->service.getAll());
			this->undoButton->setDisabled(false);
			return true;
		});
		addLayoutX->addWidget(this->addSecondButton);
		addWindow->setLayout(addLayoutX);
		addWindow->exec();
		/*
		auto book = this->movieForm->getFilm();
		try
		{
		this->service.adauga(book.getTitlu(), book.getGen(), book.getAn(), book.getActor());

		}
		catch (ValidateException& ex)
		{
		QMessageBox messBox;
		for (const auto&msg: ex.msgs)
		{
		messBox.setText(msg.c_str());
		}
		messBox.exec();
		return false;
		}
		catch (RepositoryException& ex)
		{
		QMessageBox messBox;
		messBox.setText(ex.msg.c_str());
		messBox.exec();
		return false;
		}
		catch (exception& ex)
		{
		QMessageBox messBox;
		messBox.setText(ex.what());
		messBox.exec();
		}
		this->incarcaDate(this->service.getAll());
		this->undoButton->setDisabled(false);
		return true;
		*/
	});

	QObject::connect(this->deleteButton, &QPushButton::clicked, [&]()
	{
		QMListWidgetItem* itemSelected = (QMListWidgetItem*)this->lista->selectedItems().at(0);
		auto id = itemSelected->getFilm().first;
		try
		{
			this->service.sterge(id);
		}
		catch (RepositoryException&ex)
		{
			QMessageBox messBox;
			messBox.setText(ex.msg.c_str());
			messBox.exec();
			return false;
		}

		this->undoButton->setDisabled(false);
		this->incarcaDate(this->service.getAll());
	});
	QObject::connect(this->updateButton, &QPushButton::clicked, [&]()
	{
		QMListWidgetItem* itemSelected = (QMListWidgetItem*)this->lista->selectedItems().at(0);
		auto id = itemSelected->getFilm().first;
		Film film = this->movieForm->getFilm();
		try
		{
			this->service.modifica(id, film.getTitlu(), film.getGen(), film.getAn(), film.getActor());
		}
		catch (RepositoryException&ex)
		{
			QMessageBox messBox;
			messBox.setText(ex.msg.c_str());
			messBox.exec();
			return false;
		}
		catch (ValidateException&ex)
		{
			QMessageBox messBox;
			messBox.setText(ex.getMessage().c_str());
			messBox.exec();
			return false;
		}
		this->undoButton->setDisabled(false);
		this->incarcaDate(this->service.getAll());
	});
	QObject::connect(this->undoButton, &QPushButton::clicked, [&]()
	{
		if (this->service.getAll().size() == 0)
			this->undoButton->setDisabled(true);
		else
		{
			this->service.undo();
			this->incarcaDate(this->service.getAll());
		}
	});
	QObject::connect(this->sortTitle, &QPushButton::clicked, [&]()
	{
		this->incarcaDate(this->service.sorteazaDupaTitlu());
	});
	QObject::connect(this->sortActor, &QPushButton::clicked, [&]()
	{
		this->incarcaDate(this->service.sorteazaDupaActor());
	});
	QObject::connect(this->filterButton, &QPushButton::clicked, [&]()
	{
		if (this->filterByTitleRadioButton->isChecked())
		{
			std::string title = this->filterEdit->text().toStdString();
			if (title == "")
			{
				QMessageBox messBox;
				messBox.setText("Completati casuta!    ");
				messBox.exec();
			}
			else
			{
				auto list = this->service.filtruDupaTitlu(title);
				int val = list.size();
				QTableWidget* table = new QTableWidget{ val,4 };
				int i = 0;
				for (const auto&el : list)
				{
					//tr - to qstring - c_str -> to char*
					QTableWidgetItem* el1 = new QTableWidgetItem(tr(el.second.getTitlu().c_str()));
					el1->setTextAlignment(Qt::AlignCenter);
					table->setItem(i, 0, el1);
					QTableWidgetItem* el2 = new QTableWidgetItem(tr(el.second.getGen().c_str()));
					el2->setTextAlignment(Qt::AlignCenter);
					table->setItem(i, 1, el2);
					string st = to_string(el.second.getAn());
					QTableWidgetItem* el3 = new QTableWidgetItem(tr(st.c_str()));
					el3->setTextAlignment(Qt::AlignCenter);
					table->setItem(i, 2, el3);
					QTableWidgetItem* el4 = new QTableWidgetItem(tr(el.second.getActor().c_str()));
					el4->setTextAlignment(Qt::AlignCenter);
					table->setItem(i, 3, el4);
					i++;
				}
				table->setFixedWidth(420);
				auto filterL = new QDialog();
				auto layout = new QVBoxLayout();
				layout->addWidget(table);
				filterL->setLayout(layout);
				filterL->exec();
			}
		}
		if (this->filterByYearRadioButton->isChecked())
		{
			std::string year = this->filterEdit->text().toStdString();
			if (year == "")
			{
				QMessageBox messBox;
				messBox.setText("Completati casuta!    ");
				messBox.exec();
			}
			else
			{
				int yearInt = stoi(year);
				auto list = this->service.filtruDupaAn(yearInt);
				int val = list.size();
				QTableWidget* table = new QTableWidget{ val,4 };
				int i = 0;
				for (const auto&el : list)
				{
					//tr - to qstring - c_str -> to char*
					QTableWidgetItem* el1 = new QTableWidgetItem(tr(el.second.getTitlu().c_str()));
					el1->setTextAlignment(Qt::AlignCenter);
					table->setItem(i, 0, el1);
					QTableWidgetItem* el2 = new QTableWidgetItem(tr(el.second.getGen().c_str()));
					el2->setTextAlignment(Qt::AlignCenter);
					table->setItem(i, 1, el2);
					string st = to_string(el.second.getAn());
					QTableWidgetItem* el3 = new QTableWidgetItem(tr(st.c_str()));
					el3->setTextAlignment(Qt::AlignCenter);
					table->setItem(i, 2, el3);
					QTableWidgetItem* el4 = new QTableWidgetItem(tr(el.second.getActor().c_str()));
					el4->setTextAlignment(Qt::AlignCenter);
					table->setItem(i, 3, el4);
					i++;
				}
				table->setFixedWidth(420);
				auto filterL = new QDialog();
				auto layout = new QVBoxLayout();
				layout->addWidget(table);
				filterL->setLayout(layout);
				filterL->exec();
			}
		}

	});
}
void GUI::connectSignalsSlotsCos()
{

	QObject::connect(this->lista, &QListWidget::itemSelectionChanged, [&]()
	{
		if (this->lista->selectedItems().isEmpty())
		{
			this->addToCosButton->setEnabled(false);
		}
		else
		{
			this->addToCosButton->setEnabled(true);
		}
	});
	QObject::connect(this->addToCosButton, &QPushButton::clicked, [&]()
	{
		QMListWidgetItem* itemSelected = (QMListWidgetItem*)this->lista->selectedItems().at(0);
		this->service.addToCos(itemSelected->getFilm().second.getTitlu());
		this->incarcaDateInCos(service.getCos());
	});
	QObject::connect(this->clearCosButton, &QPushButton::clicked, [&]()
	{
		auto cos = this->service.golesteCos();
		this->incarcaDateInCos(cos);
	});
	QObject::connect(this->generateCosButton, &QPushButton::clicked, [&]()
	{
		service.suntCurios(this);
		auto cos = this->service.addRandom();
		this->incarcaDateInCos(cos);
	});
	QObject::connect(this->exportCSVButton, &QPushButton::clicked, [&]()
	{
		auto fisier = this->fileEdit->text();
		this->service.exportaCosCVS(fisier.toStdString());
		QMessageBox messBox;
		messBox.setText("Export reusit!    ");
		messBox.exec();
	});
	QObject::connect(this->exportHTMLButton, &QPushButton::clicked, [&]()
	{
		auto fisier = this->fileEdit->text();
		this->service.exportaCosHTML(fisier.toStdString());
		QMessageBox messBox;
		messBox.setText("Export reusit!    ");
		messBox.exec();
	});
	QObject::connect(this->addCosGui, &QPushButton::clicked, [&]()
	{
		auto cosgui = new COSGUI{ service };
		cosgui->show();
	});
	QObject::connect(this->addCosReadOnly, &QPushButton::clicked, [&]()
	{
		auto cosReadOnly = new COSReadOnlyGUI{ service };
		cosReadOnly->show();
	});
}