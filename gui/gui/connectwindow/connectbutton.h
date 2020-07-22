#ifndef CONNECTBUTTON_H
#define CONNECTBUTTON_H

#include <QGraphicsObject>
#include <QPropertyAnimation>
#include "../Backend/Types/types.h"
#include "CommonGraphics/clickablegraphicsobject.h"
#include "CommonGraphics/imageitem.h"

namespace ConnectWindow {

class ConnectButton : public ClickableGraphicsObject
{
    Q_OBJECT
public:
    explicit ConnectButton(ScalableGraphicsObject *parent = nullptr);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

    void onConnectStateChanged(ProtoTypes::ConnectStateType newConnectState, ProtoTypes::ConnectStateType prevConnectState);
    void setInternetConnectivity(bool online);
    void setSplitRouting(bool on);

    virtual void updateScaling();

private slots:
    void onConnectingRingOpacityAnimationFinished();
    void onNoInternetRingOpacityAnimationFinished();

private:
    ProtoTypes::ConnectStateType connectStateType_;

    ImageItem *svgItemButton_;
    ImageItem *svgItemConnectedRing_;
    ImageItem *svgItemConnectedSplitRoutingRing_;
    ImageItem *svgItemConnectingRing_;
    ImageItem *svgItemConnectingNoInternetRing_;
    bool online_;
    bool splitRouting_;

    QPropertyAnimation buttonRotationAnimation_;
    QPropertyAnimation connectingRingRotationAnimation_;
    QPropertyAnimation connectingRingOpacityAnimation_;
    QPropertyAnimation noInternetRingRotationAnimation_;
    QPropertyAnimation noInternetRingOpacityAnimation_;
    QPropertyAnimation connectedRingOpacityAnimation_;    
    QPropertyAnimation connectedSplitRoutingRingOpacityAnimation_;

    void fuzzyHideConnectedRing();
    void fuzzyHideConnectingRing();
    void fuzzyHideNoInternetRing();

    void updatePositions();
    void startConnectedRingAnimations(QPropertyAnimation::Direction dir);
    void startConnectingRingAnimations(QPropertyAnimation::Direction dir);
    void startNoInternetRingAnimations(QPropertyAnimation::Direction dir);
};

} //namespace ConnectWindow

#endif // CONNECTBUTTON_H
