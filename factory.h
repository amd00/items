#ifndef FACTORY_H
#define FACTORY_H

#include <QObject>
#include <QMap>
#include <QUuid>

class Item;
class Constructor;

class Factory : public QObject
{
    Q_OBJECT

private:
	QMap< QString, QMap<QUuid, Item*> > m_pool;
	QMap< QString, QMap<QUuid, qint32> > m_ref_counter;

protected:
	static Factory *m_self;
	QMap<QString, Constructor*> m_constructors;

protected:
	explicit Factory(QObject *_parent = 0) : QObject(_parent) {}

public:
	virtual ~Factory() {}
	virtual Item *getItem(const QString &_type, const QUuid &_id);
	virtual QMap<QUuid, Item*> getItems(const QString &_type);
	virtual Item *createItem(const QString &_type);
	virtual void dropItem(Item **_item);
};

#endif // FACTORY_H
