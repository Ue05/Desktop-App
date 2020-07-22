#ifndef SHARINGFEATURESWINDOWITEM_H
#define SHARINGFEATURESWINDOWITEM_H

#include <QGraphicsObject>
#include <QVariantAnimation>
#include <QFont>
#include "sharingfeature.h"
#include "../Backend/Preferences/preferences.h"
#include "PreferencesWindow/dividerline.h"
#include "IPC/generated_proto/types.pb.h"

namespace SharingFeatures {

class SharingFeaturesWindowItem : public ScalableGraphicsObject
{
    Q_OBJECT
public:
    explicit SharingFeaturesWindowItem(ScalableGraphicsObject * parent = nullptr);

    virtual QGraphicsObject *getGraphicsObject() { return this; }
    virtual QRectF boundingRect() const;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

    void setSecureHotspotFeatures(bool isEnabled, const QString &ssid);
    void setSecureHotspotUsersCount(int usersCount);
    void setProxyGatewayFeatures(bool isEnabled, ProtoTypes::ProxySharingMode mode);
    void setProxyGatewayUsersCount(int usersCount);

    virtual void animateHornDisplay(bool show);

    void setHorns(bool show);

    virtual int currentHeight() const;

    QPixmap getCurrentPixmapShape();

    QPolygonF leftHornPolygon(int originX, int originY, int width, int height);
    QPolygonF rightHornPolygon(int originX, int originY, int width, int height);

    void updateShareFeatureRoundedness();

    void setClickable(bool enabled);

    void updateModedFeatures(SHARE_MODE mode);

    virtual void updateScaling();

signals:
    void clickedProxy();
    void clickedHotSpot();

private slots:
    void onHornPosChanged(const QVariant &value);
    void onHornOpacityChanged(const QVariant &value);

private:
    void setHotspotSSID(QString ssid);
    void setProxyType(ProtoTypes::ProxySharingMode mode);

    void setMode(SHARE_MODE mode);

    bool isSecureHotspotEnabled_;
    QString secureHotspotSsid_;

    bool isProxyGatewayEnabled_;
    ProtoTypes::ProxySharingMode proxyGatewayMode_;
    //ProtoTypes::WifiSharingInfo hotspot_;
    //ProtoTypes::ProxySharingInfo gateway_;

    PreferencesWindow::DividerLine *dividerLine_;
    PreferencesWindow::DividerLine *dividerLine2_;

    QString headerText_;
    SHARE_MODE mode_;

    double curOpacity_;

    const int WIDTH = 332;
    int height_;

    const QString TEXT_SHARING_FEATURES = QT_TR_NOOP("Sharing Features");

    void recalcHeight();

    SharingFeature *hotspotFeature_;
    SharingFeature *proxyFeature_;

    bool showingHorns_;

    double curHornOpacity_;
    int curHornPosY_;
    QVariantAnimation hornPosYAnimation_;
    QVariantAnimation hornOpacityAnimation_;

    const int HEADER_HEIGHT = 48;

    int HORN_POS_Y_HIDDEN;
    int HORN_POS_Y_SHOWING;

    const int LEFT_HORN_ORIGIN_X = 0;
    const int HORN_WIDTH = 30;
    const int HORN_HEIGHT = 30;

    void updatePositions();

};

}
#endif // SHARINGFEATURESWINDOWITEM_H
