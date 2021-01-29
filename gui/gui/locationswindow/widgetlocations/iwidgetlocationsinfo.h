#ifndef IWIDGETLOCATIONSINFO_H
#define IWIDGETLOCATIONSINFO_H

#include <QKeyEvent>
#include "types/locationid.h"

class IWidgetLocationsInfo
{
public:
    virtual ~IWidgetLocationsInfo() {}

    virtual void updateScaling() = 0;

    virtual bool hasSelection() = 0;
    virtual LocationID selectedItemLocationId() = 0;
    virtual void setFirstSelected() = 0;

    virtual bool cursorInViewport() = 0;
    virtual void centerCursorOnSelectedItem() = 0;
    virtual void centerCursorOnItem(LocationID locId) = 0;

    virtual int countViewportItems() = 0;
    virtual void setCountViewportItems(int count) = 0;

    // state
    virtual bool isShowLatencyInMs() = 0;
    virtual void setShowLatencyInMs(bool showLatencyInMs) = 0;
    virtual bool isFreeSessionStatus() = 0;
//    virtual int getWidth() = 0;
//    virtual int getScrollBarWidth() = 0;

    // other
    virtual void startAnimationWithPixmap(const QPixmap &pixmap) = 0;
    virtual void handleKeyEvent(QKeyEvent *event) = 0;


};

#endif // IWIDGETLOCATIONSINFO_H
