#include "AdPushButton.h"

AdPushButton::AdPushButton(Ad* ad, QWidget* parent)
: QPushButton(QString::fromStdString(ad->name), parent), _ad(ad)
{
	connect(this, SIGNAL(clicked()), this, SLOT(triggerPush()));
}

void AdPushButton::triggerPush()
{
	emit ClickedWithArgument(_ad);
}

AdPushButton::~AdPushButton()
{
	disconnect(this, SIGNAL(clicked()), this, SLOT(triggerPush()));
}

