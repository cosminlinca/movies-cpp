#include "MovieForm.h"
#include <string>
#include <qintvalidator>

MovieForm::MovieForm()
{
	auto movieForm = new QFormLayout();

	this->idEdit = new QLineEdit();
	this->idEdit->setEnabled(1);
	movieForm->addRow("ID: ", this->idEdit);

	this->titluEdit = new QLineEdit();
	this->titluEdit->setEnabled(1);
	movieForm->addRow("Titlu:", this->titluEdit);

	this->genEdit = new QLineEdit();
	this->genEdit->setEnabled(1);
	movieForm->addRow("Gen:", this->genEdit);


	this->anEdit = new QLineEdit();
	this->anEdit->setEnabled(1);
	movieForm->addRow("An:", this->anEdit);
	QValidator *validator = new QIntValidator(1000, 9999, this->anEdit);
	anEdit->setValidator(validator);

	this->actorEdit = new QLineEdit();
	this->actorEdit->setEnabled(1);
	movieForm->addRow("Actor:", this->actorEdit);

	this->formlayout = movieForm;
}
Film MovieForm::getFilm()
{
	//toUtf8() - Returns a UTF-8 representation of the string as a QByteArray.
	//constData() - Returns a pointer to the data stored in the byte array
	std::string titlu = this->titluEdit->text().toStdString();
	std::string gen = this->genEdit->text().toStdString();
	std::string an = this->anEdit->text().toStdString();
	std::string actor = this->actorEdit->text().toStdString();
	return Film{ titlu, gen, std::stoi(an), actor };
}
QFormLayout* MovieForm::getForm()
{
	return this->formlayout;
}
void MovieForm::clearData()
{
	this->idEdit->setText("");
	this->titluEdit->setText("");
	this->genEdit->setText("");
	this->anEdit->setText("");
	this->actorEdit->setText("");
}
void MovieForm::setData(const std::pair<int, Film>& film)
{
	this->idEdit->setText(std::to_string(film.first).c_str());
	this->titluEdit->setText(film.second.getTitlu().c_str());
	this->genEdit->setText(film.second.getGen().c_str());
	this->anEdit->setText(std::to_string(film.second.getAn()).c_str());
	this->actorEdit->setText(film.second.getActor().c_str());
}