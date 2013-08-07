#include "factory.h"

#include "constructor.h"
#include "item.h"

Item *Factory::getItem(const QString &_type, const QUuid &_id)
{
	Item *res = m_pool[_type].value(_id, NULL);
	if(!res)
	{
		Constructor *constr = m_constructors.value(_type, NULL);

		if(!constr)
		{
			qWarning("Warning: No constructor for type \"%s\"", _type.toLocal8Bit().data());
			return NULL;
		}
		res = constr -> construct(_id);
		if(!res)
			return NULL;
		m_pool[_type][res -> id()] = res;
		m_ref_counter[_type][res -> id()] = 0;
	}
	m_ref_counter[_type][res -> id()]++;
	return res;
}

QMap<QUuid, Item*> Factory::getItems(const QString &_type)
{
	Constructor *constr = m_constructors.value(_type, NULL);
	if(!constr)
	{
		qWarning("Warning: No constructor for type \"%s\"", _type.toLocal8Bit().data());
		return QMap<QUuid, Item*>();
	}
	QMap<QUuid, Item*> res = constr -> constructList();
	QMapIterator<QUuid, Item*> it(res);
	while(it.hasNext())
	{
		it.next();
		QString id = it.key();
		Item *item = m_pool[_type].value(id, NULL);
		if(!item)
		{
			m_pool[_type][id] = it.value();
			m_ref_counter[_type][id] = 0;
		}
		else
		{
			Item *old_item = res[id];
			res[id] = item;
			old_item -> deleteLater();
		}

		m_ref_counter[_type][id]++;
	}
	return res;
}

Item *Factory::createItem(const QString &_type)
{
	Constructor *constr = m_constructors.value(_type, NULL);
	if(!constr)
		return NULL;
	Item *res = constr -> construct(QUuid());
	if(!res)
		return NULL;
	m_pool[_type][res -> id()] = res;
	m_ref_counter[_type][res -> id()] = 0;
	m_ref_counter[_type][res -> id()]++;
	return res;
}

void Factory::dropItem(Item **_item)
{
	if(!(*_item))
		return;
	QString type = (*_item) -> type();
	QUuid id = (*_item) -> id();
	m_ref_counter[type][id]--;
	if(!m_ref_counter[type][id])
	{
//		Item *item = m_pool[type][id];
//		m_pool[type].remove(id);
//		item -> deleteLater();
	}
}
