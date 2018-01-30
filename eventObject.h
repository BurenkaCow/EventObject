#pragma once
#include <qObject>
#include <qVariant>
#include <functional>
#include "interfaces/iGetSetName.h"
class LinkValue;


//Анализ события по заданной формуле
class EventObject : public QObject, public IGetSetName
{
	Q_OBJECT
public:
	using LMap = QMap<QString, const LinkValue*>; //Карта связей
public:
	EventObject(QObject* parent = nullptr) : QObject(parent) {}
	EventObject(const QString& _name) : name(_name) {}
	inline void SetName(const QString& _name) override { name = _name; } //Задать имя события
	inline QString GetName(void) const override { return name; } //Взять имя события
	inline void SetFormula(const std::function<QVariant(const LMap&)>& _formula) { formula = _formula; } //Задать формулу
	void AddLink(const QString& name, const LinkValue* link); //Добавить связь
	void PollLinks(bool _poll = true); //Включить(отключить) опрос связей
	QVariant GetValue(void) const { return oldValue; } //Взять последнее(текущее) значение
	~EventObject(void) {}
signals:
	void Change(const QVariant& variant); //Событие измело свое значение
private:
	void AnalizFormula(void); //Анализ формулы на изменение значения события
private:
	QString name; //Имя события
	LMap links; //Связи
	std::function<QVariant(const LMap&)> formula; //Формула события
	bool pollLinks = false; //Производится ли опрос связей
	QVariant oldValue; //Старое(текущее) состояние значение
};

