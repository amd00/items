
#include "constructor.h"
#include "item.h"

Item *Constructor::construct(const QUuid &_id)
{
	QUuid id = _id.isNull() ? QUuid::createUuid() : _id;
	Item *res = createItem(id);
	if(!res)
		return NULL;
	res -> setType(type());
	res -> setState(_id.isNull() ? Item::New : Item::Normal);
	connect(res, SIGNAL(saveSignal()), this, SLOT(saveSlot()));
	return res;
}
