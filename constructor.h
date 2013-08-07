#ifndef _CONSTRUCTOR_H_
#define _CONSTRUCTOR_H_

#include <QObject>
#include <QMap>
#include <QUuid>

class Item;

class Constructor : public QObject
{
    Q_OBJECT

private:
	QString m_type;

public:
	explicit Constructor(const QString &_type, QObject *_parent = 0) : QObject(_parent), m_type(_type) {}
	virtual ~Constructor() {}
	virtual Item *construct(const QUuid &_id);
	virtual QMap<QUuid, Item*> constructList() = 0;
	QString type() const { return m_type; }

protected:
	virtual Item *createItem(const QUuid &_id) = 0;

protected Q_SLOTS:
	virtual void saveSlot() = 0;
};

#endif // CONSTRUCTOR_H
