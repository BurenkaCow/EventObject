#include "eventObject.h"
#include "objects/linkValue.h"


void EventObject::AddLink(const QString& name, const LinkValue* link)
{
	links.insert(name, link);
	if (pollLinks)
	{
		QObject::connect(link, &LinkValue::Change, this, &EventObject::AnalizFormula);
	}
}


void EventObject::PollLinks(bool _pollLinks)
{
	pollLinks = _pollLinks;
	if (pollLinks)
	{
		for(auto& link : links)
		{
			QObject::connect(link, &LinkValue::Change, this, &EventObject::AnalizFormula);
		}
	}
}


void EventObject::AnalizFormula(void)
{
	if (formula)
	{
		auto value = formula(links);
		if (value != oldValue)
		{
			oldValue = value;
			emit Change(value);
		}
	}
}


