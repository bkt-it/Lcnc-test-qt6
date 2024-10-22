#include "WLED.h"
#include "WLEDPlugin.h"

#include <QtPlugin>

WLEDPlugin::
WLEDPlugin(QObject* parent) :
	QObject(parent),
	initialized(false)
{
}

QString WLEDPlugin::
name() const
{
    return "WLED";
}

QString WLEDPlugin::
group() const
{
	return tr("ICS Custom Widgets");
}

QString WLEDPlugin::
toolTip() const
{
    return tr("An WLED");
}

QString WLEDPlugin::
whatsThis() const
{
    return tr("An WLED");
}

QString WLEDPlugin::
includeFile() const
{
    return "WLED.h";
}

QIcon WLEDPlugin::
icon() const
{
	return QIcon();
}

bool WLEDPlugin::
isContainer() const
{
	return false;
}

QWidget * WLEDPlugin::
createWidget(QWidget *parent)
{
    return new WLED(parent);
}

#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
Q_EXPORT_PLUGIN2(wledplugin, WLEDPlugin)
#endif
