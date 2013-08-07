#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include <QUuid>

class Item : public QObject
{
	friend class Constructor;
    Q_OBJECT

public:
	enum State{Normal, New, Edited, Deleted};

private:
	QString m_type;
	QUuid m_id;

protected:
	State m_state;

protected:
	explicit Item(QObject *_parent = 0) : QObject(_parent), m_type(), m_id(), m_state(Normal) {}
	explicit Item(const QString &_type, const QUuid &_id, QObject *_parent = 0) :
		QObject(_parent), m_type(_type), m_id(_id) {}
	virtual ~Item() {}

	void setType(const QString &_type) { m_type = _type; }
	void setId(const QUuid &_id) { m_id = _id; }
	void setState(State _state) { m_state = _state; }

public:
	QString type() const { return m_type; }
	QUuid id() const { return m_id; }
	State state() const { return m_state; }
	bool save() { Q_EMIT saveSignal(); return true; }

Q_SIGNALS:
	void saveSignal();
};

#endif // ITEM_H
