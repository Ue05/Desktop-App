#ifndef DEBUGWINDOWITEM_H
#define DEBUGWINDOWITEM_H

#include <QTimer>
#include "../basepage.h"
#include "../ConnectionWindow/subpageitem.h"
#include "viewlogitem.h"
#include "serverratingsitem.h"
#include "../comboboxitem.h"
#include "../checkboxitem.h"
#include "../Backend/Preferences/preferences.h"
#include "../Backend/Preferences/preferenceshelper.h"
#include "apiresolutionitem.h"
#include "Tooltips/tooltiptypes.h"


enum DEBUG_SCREEN { DEBUG_SCREEN_HOME, DEBUG_SCREEN_ADVANCED_PARAMETERS };

namespace PreferencesWindow {

class DebugWindowItem : public BasePage
{
    Q_OBJECT
public:
    explicit DebugWindowItem(ScalableGraphicsObject *parent, Preferences *preferences, PreferencesHelper *preferencesHelper);

    QString caption();

    DEBUG_SCREEN getScreen();
    void setScreen(DEBUG_SCREEN screen);
    void setDebugLogResult(bool success);

    virtual void updateScaling();

signals:
    void viewLogClick();
    void sendLogClick();
    void clearServerRatingsClick();
    void advParametersClick();
    void showTooltip(TooltipInfo info);
    void hideTooltip(TooltipId id);
#ifdef Q_OS_WIN
    void setIpv6StateInOS(bool bEnabled, bool bRestartNow);
#endif
private slots:
    void onApiResolutionChanged(const ProtoTypes::ApiResolution &ar);
    void onIgnoreSslErrorsStateChanged(bool isChecked);
    void onKeepAliveStateChanged(bool isChecked);
    void onAppInternalDnsItemChanged(QVariant dns);

    void onViewLogItemSendLogClicked();
    void onViewButtonHoverEnter();
    void onSendButtonHoverEnter();
    void onViewOrSendButtonHoverLeave();
    void onClearButtonHoverEnter();
    void onClearButtonHoverLeave();
    void onClearServerRatingsButtonClick();

    void onIgnoreSslErrorsPreferencesChanged(bool b);
    void onKeepAlivePreferencesChanged(bool b);
    void onDnsPolicyPreferencesChanged(ProtoTypes::DnsPolicy d);
    void onApiResolutionPreferencesChanged(const ProtoTypes::ApiResolution &ar);

    void onLanguageChanged();

#ifdef Q_OS_WIN
    void onIPv6StateChanged(bool isChecked);
    void onPreferencesIpv6InOSStateChanged(bool bEnabled);
    void onTapAdapterChanged(QVariant v);
    void onTapAdapterPreferencesChanged(ProtoTypes::TapAdapterType tapAdapter);
#endif

protected:
    void hideOpenPopups();

private:
    SubPageItem *advParamtersItem_;
    ViewLogItem *viewLogItem_;
    ServerRatingsItem *serverRatingsItem_;

    ApiResolutionItem *apiResolutionItem_;
    CheckBoxItem *cbIgnoreSslErrors_;
    CheckBoxItem *cbKeepAlive_;
    ComboBoxItem *comboBoxAppInternalDns_;

    Preferences *preferences_;
    PreferencesHelper *preferencesHelper_;

    DEBUG_SCREEN currentScreen_;

    bool pendingDebugSendResposeFromEngine_;

#ifdef Q_OS_WIN
    CheckBoxItem *checkBoxIPv6_;
    ComboBoxItem *comboBoxTapAdapter_;
    void updateTapAdaptersList();
#endif

    void showSendButtonToolTip(const QString &text);

};

} // namespace PreferencesWindow

#endif // DEBUGWINDOWITEM_H
