INCLUDEPATH += $$PWD

win32 {

SOURCES += $$PWD/multipleaccountdetection/multipleaccountdetection_win.cpp \
           $$PWD/multipleaccountdetection/secretvalue_win.cpp \
           $$PWD/utils/authchecker_win.cpp \
           $$PWD/utils/scaleutils_win.cpp \
           $$PWD/launchonstartup/launchonstartup_win.cpp \
           $$PWD/utils/interfaceutils_win.cpp

HEADERS += $$PWD/multipleaccountdetection/multipleaccountdetection_win.h \
           $$PWD/multipleaccountdetection/secretvalue_win.h \
           $$PWD/utils/authchecker_win.h \
           $$PWD/utils/scaleutils_win.h \
           $$PWD/launchonstartup/launchonstartup_win.h

} # win32


macx {

SOURCES += $$PWD/multipleaccountdetection/multipleaccountdetection_mac.cpp

OBJECTIVE_SOURCES += \
                $$PWD/application/checkrunningapp/checkrunningapp_mac.mm \
                $$PWD/launchonstartup/launchonstartup_mac.mm \
                $$PWD/utils/interfaceutils_mac.mm \
                $$PWD/utils/authchecker_mac.mm

HEADERS += \
           $$PWD/multipleaccountdetection/multipleaccountdetection_mac.h \
           $$PWD/application/checkrunningapp/checkrunningapp_mac.h \
           $$PWD/launchonstartup/launchonstartup_mac.h \
           $$PWD/utils/authchecker_mac.h \

RESOURCES += \
    $$PWD/windscribe_mac.qrc

} # macx

linux {

SOURCES += \
    $$PWD/multipleaccountdetection/multipleaccountdetection_linux.cpp \
    $$PWD/launchonstartup/launchonstartup_linux.cpp \
    $$PWD/utils/interfaceutils_linux.cpp \
    $$PWD/utils/authchecker_linux.cpp

HEADERS += \
    $$PWD/multipleaccountdetection/multipleaccountdetection_linux.h \
    $$PWD/launchonstartup/launchonstartup_linux.h \
    $$PWD/utils/authchecker_linux.h

} # linux


SOURCES += $$PWD/backend/backend.cpp \
    $$PWD/backend/connectstatehelper.cpp \
    $$PWD/backend/firewallstatehelper.cpp \
    $$PWD/backend/notificationscontroller.cpp \
    $$PWD/backend/locationsmodel/alllocationsmodel.cpp \
    $$PWD/backend/locationsmodel/basiccitiesmodel.cpp \
    $$PWD/backend/locationsmodel/basiclocationsmodel.cpp \
    $$PWD/backend/locationsmodel/configuredcitiesmodel.cpp \
    $$PWD/backend/locationsmodel/favoritecitiesmodel.cpp \
    $$PWD/backend/locationsmodel/favoritelocationsstorage.cpp \
    $$PWD/backend/locationsmodel/locationsmodel.cpp \
    $$PWD/backend/locationsmodel/sortlocationsalgorithms.cpp \
    $$PWD/backend/locationsmodel/staticipscitiesmodel.cpp \
    $$PWD/backend/preferences/accountinfo.cpp \
    $$PWD/backend/preferences/detectlanrange.cpp \
    $$PWD/backend/preferences/guisettingsfromver1.cpp \
    $$PWD/backend/preferences/preferences.cpp \
    $$PWD/backend/preferences/preferenceshelper.cpp \
    $$PWD/backend/types/upgrademodetype.cpp \
    $$PWD/backend/types/dnswhileconnectedinfo.cpp \
    $$PWD/backend/persistentstate.cpp \
    $$PWD/application/windowsnativeeventfilter.cpp \
    $$PWD/application/windscribeapplication.cpp \
    $$PWD/commongraphics/imageitem.cpp \
    $$PWD/commongraphics/scalablegraphicsobject.cpp \
    $$PWD/commonwidgets/combomenuwidget.cpp \
    $$PWD/commonwidgets/combomenuwidgetbutton.cpp \
    $$PWD/commonwidgets/iconwidget.cpp \
    $$PWD/commonwidgets/lightwidget.cpp \
    $$PWD/connectwindow/backgroundimage/backgroundimage.cpp \
    $$PWD/connectwindow/backgroundimage/imagechanger.cpp \
    $$PWD/connectwindow/backgroundimage/simpleimagechanger.cpp \
    $$PWD/connectwindow/connectstateprotocolport/badgepixmap.cpp \
    $$PWD/connectwindow/connectstateprotocolport/connectionbadgedots.cpp \
    $$PWD/connectwindow/connectstateprotocolport/connectstateprotocolport.cpp \
    $$PWD/connectwindow/ipaddressitem/ipaddressitem.cpp \
    $$PWD/connectwindow/ipaddressitem/numberitem.cpp \
    $$PWD/connectwindow/ipaddressitem/numberspixmap.cpp \
    $$PWD/connectwindow/ipaddressitem/octetitem.cpp \
    $$PWD/connectwindow/middleitem.cpp \
    $$PWD/connectwindow/serverratingindicator.cpp \
    $$PWD/dialogs/advancedparametersdialog.cpp \
    $$PWD/dialogs/dialoggetusernamepassword.cpp \
    $$PWD/dialogs/dialogmessagecpuusage.cpp \
    $$PWD/graphicresources/fontdescr.cpp \
    $$PWD/graphicresources/iconmanager.cpp \
    $$PWD/graphicresources/independentpixmap.cpp \
    $$PWD/launchonstartup/launchonstartup.cpp \
    $$PWD/locationswindow/widgetlocations/footertopstrip.cpp \
    $$PWD/locationswindow/widgetlocations/itemwidgetcity.cpp \
    $$PWD/locationswindow/widgetlocations/itemwidgetheader.cpp \
    $$PWD/locationswindow/widgetlocations/itemwidgetregion.cpp \
    $$PWD/locationswindow/widgetlocations/scrollbar.cpp \
    $$PWD/locationswindow/widgetlocations/widgetcitieslist.cpp \
    $$PWD/locationswindow/widgetlocations/widgetlocations.cpp \
    $$PWD/locationswindow/widgetlocations/widgetlocationslist.cpp \
    $$PWD/mainwindowstate.cpp \
    $$PWD/preferenceswindow/connectionwindow/packetsizeeditboxitem.cpp \
    $$PWD/overlaysconnectwindow//upgradewindowitem.cpp \
    $$PWD/overlaysconnectwindow/updatewindowitem.cpp \
    $$PWD/overlaysconnectwindow/generalmessagetwobuttonwindowitem.cpp \
    $$PWD/overlaysconnectwindow/generalmessagewindowitem.cpp \
    $$PWD/overlaysconnectwindow/updateappitem.cpp \
    $$PWD/preferenceswindow/debugwindow/apiresolutionitem.cpp \
    $$PWD/preferenceswindow/generalwindow/backgroundsettingsitem.cpp \
    $$PWD/preferenceswindow/generalwindow/selectimageitem.cpp \
    $$PWD/preferenceswindow/generalwindow/versioninfoitem.cpp \
    $$PWD/preferenceswindow/networkwhitelistwindow/currentnetworkitem.cpp \
    $$PWD/preferenceswindow/networkwhitelistwindow/networklistitem.cpp \
    $$PWD/preferenceswindow/networkwhitelistwindow/networkwhitelistshared.cpp \
    $$PWD/preferenceswindow/splittunnelingwindow/appincludeditem.cpp \
    $$PWD/preferenceswindow/splittunnelingwindow/appsearchitem.cpp \
    $$PWD/preferenceswindow/splittunnelingwindow/iporhostnameitem.cpp \
    $$PWD/preferenceswindow/splittunnelingwindow/newiporhostnameitem.cpp \
    $$PWD/preferenceswindow/splittunnelingwindow/searchlineedititem.cpp \
    $$PWD/preferenceswindow/splittunnelingwindow/splittunnelingappsitem.cpp \
    $$PWD/preferenceswindow/splittunnelingwindow/splittunnelingappssearchitem.cpp \
    $$PWD/preferenceswindow/splittunnelingwindow/splittunnelingappssearchwindowitem.cpp \
    $$PWD/preferenceswindow/splittunnelingwindow/splittunnelingappswindowitem.cpp \
    $$PWD/preferenceswindow/splittunnelingwindow/splittunnelingiphostnamewindowitem.cpp \
    $$PWD/preferenceswindow/splittunnelingwindow/splittunnelingipsandhostnamesitem.cpp \
    $$PWD/preferenceswindow/splittunnelingwindow/splittunnelingitem.cpp \
    $$PWD/preferenceswindow/splittunnelingwindow/splittunnelingswitchitem.cpp \
    $$PWD/showingdialogstate.cpp \
    $$PWD/tooltips/itooltip.cpp \
    $$PWD/tooltips/serverratingstooltip.cpp \
    $$PWD/tooltips/tooltipbasic.cpp \
    $$PWD/tooltips/tooltipcontroller.cpp \
    $$PWD/tooltips/tooltipdescriptive.cpp \
    $$PWD/tooltips/tooltiputil.cpp \
    $$PWD/utils/imagewithshadow.cpp \
    $$PWD/utils/protoenumtostring.cpp \
    $$PWD/commonwidgets/custommenuwidget.cpp \
    $$PWD/commonwidgets/customtexteditwidget.cpp \
    $$PWD/commonwidgets/scrollareawidget.cpp \
    $$PWD/commonwidgets/verticalscrollbarwidget.cpp \
    $$PWD/loginwindow/initwindowitem.cpp \
    $$PWD/log/logviewerwindow.cpp \
    $$PWD/preferenceswindow/debugwindow/advancedparameterswindowitem.cpp \
    $$PWD/utils/textshadow.cpp \
    $$PWD/utils/writeaccessrightschecker.cpp \
    $$PWD/blockconnect.cpp \
    $$PWD/dpiscaleawarewidget.cpp \
    $$PWD/dpiscalemanager.cpp \
    $$PWD/freetrafficnotificationcontroller.cpp \
    $$PWD/guitest.cpp \
    $$PWD/systemtray/locationstraymenubutton.cpp \
    $$PWD/systemtray/locationstraymenuitemdelegate.cpp \
    $$PWD/systemtray/locationstraymenuwidget.cpp \
    $$PWD/systemtray/locationstraymenunative.cpp \
    $$PWD/systemtray/locationstraymenuscalemanager.cpp \
    $$PWD/loginattemptscontroller.cpp \
    $$PWD/mainwindow.cpp \
    $$PWD/loginwindow/loginwindowitem.cpp \
    $$PWD/loginwindow/welcomewindowitem.cpp \
    $$PWD/loginwindow/credentialswindowitem.cpp \
    $$PWD/loginwindow/logginginwindowitem.cpp \
    $$PWD/loginwindow/loginyesnobutton.cpp \
    $$PWD/loginwindow/usernamepasswordentry.cpp \
    $$PWD/loginwindow/loginbutton.cpp \
    $$PWD/loginwindow/iconhoverengagebutton.cpp \
    $$PWD/loginwindow/firewallturnoffbutton.cpp \
    $$PWD/graphicresources/fontmanager.cpp \
    $$PWD/graphicresources/imageresourcessvg.cpp \
    $$PWD/graphicresources/imageresourcesjpg.cpp \
    $$PWD/emergencyconnectwindow/emergencyconnectwindowitem.cpp \
    $$PWD/emergencyconnectwindow/textlinkbutton.cpp \
    $$PWD/commongraphics/commongraphics.cpp \
    $$PWD/connectwindow/connectwindowitem.cpp \
    $$PWD/locationswindow/locationswindow.cpp \
    $$PWD/locationswindow/widgetlocations/backgroundpixmapanimation.cpp \
    $$PWD/locationswindow/widgetlocations/cursorupdatehelper.cpp \
    $$PWD/locationswindow/widgetlocations/itemtimems.cpp \
    $$PWD/locationswindow/widgetlocations/locationstab.cpp \
    $$PWD/locationswindow/widgetlocations/widgetcities.cpp \
    $$PWD/locationswindow/widgetlocations/widgetlocationssizes.cpp \
    $$PWD/connectwindow/background.cpp \
    $$PWD/connectwindow/connectbutton.cpp \
    $$PWD/connectwindow/locationsbutton.cpp \
    $$PWD/connectwindow/wifiname.cpp \
    $$PWD/connectwindow/firewallbutton.cpp \
    $$PWD/utils/makecustomshadow.cpp \
    $$PWD/utils/shadowmanager.cpp \
    $$PWD/preferenceswindow/preferenceswindowitem.cpp \
    $$PWD/preferenceswindow/bottomresizeitem.cpp \
    $$PWD/preferenceswindow/generalwindow/generalwindowitem.cpp \
    $$PWD/preferenceswindow/scrollareaitem.cpp \
    $$PWD/preferenceswindow/accountwindow/accountwindowitem.cpp \
    $$PWD/preferenceswindow/connectionwindow/connectionwindowitem.cpp \
    $$PWD/preferenceswindow/debugwindow//debugwindowitem.cpp \
    $$PWD/preferenceswindow/sharewindow/sharewindowitem.cpp \
    $$PWD/preferenceswindow/preferencestab/preferencestabcontrolitem.cpp \
    $$PWD/commongraphics/checkboxbutton.cpp \
    $$PWD/preferenceswindow/checkboxitem.cpp \
    $$PWD/preferenceswindow/dividerline.cpp \
    $$PWD/preferenceswindow/escapebutton.cpp \
    $$PWD/preferenceswindow/comboboxitem.cpp \
    $$PWD/newsfeedwindow/newsfeedwindowitem.cpp \
    $$PWD/preferenceswindow/accountwindow/usernameitem.cpp \
    $$PWD/preferenceswindow/accountwindow/emailitem.cpp \
    $$PWD/preferenceswindow/accountwindow/planitem.cpp \
    $$PWD/preferenceswindow/accountwindow/expiredateitem.cpp \
    $$PWD/preferenceswindow/connectionwindow/subpageitem.cpp \
    $$PWD/preferenceswindow/basepage.cpp \
    $$PWD/preferenceswindow/baseitem.cpp \
    $$PWD/preferenceswindow/sharewindow/securehotspotitem.cpp \
    $$PWD/preferenceswindow/sharewindow/proxygatewayitem.cpp \
    $$PWD/preferenceswindow/editboxitem.cpp \
    $$PWD/preferenceswindow/sharewindow/proxyipaddressitem.cpp \
    $$PWD/preferenceswindow/debugwindow/viewlogitem.cpp \
    $$PWD/preferenceswindow/debugwindow/advancedparametersitem.cpp \
    $$PWD/preferenceswindow/connectionwindow/firewallmodeitem.cpp \
    $$PWD/preferenceswindow/connectionwindow/automanualswitchitem.cpp \
    $$PWD/preferenceswindow/connectionwindow/connectionmodeitem.cpp \
    $$PWD/preferenceswindow/connectionwindow/packetsizeitem.cpp \
    $$PWD/preferenceswindow/connectionwindow/macspoofingitem.cpp \
    $$PWD/preferenceswindow/connectionwindow/macaddressitem.cpp \
    $$PWD/preferenceswindow/connectionwindow/autorotatemacitem.cpp \
    $$PWD/commongraphics/verticalscrollbar.cpp \
    $$PWD/preferenceswindow/networkwhitelistwindow/networkwhitelistwindowitem.cpp \
    $$PWD/preferenceswindow/splittunnelingwindow/splittunnelingwindowitem.cpp \
    $$PWD/preferenceswindow/proxysettingswindow/proxysettingswindowitem.cpp \
    $$PWD/commongraphics/clickablegraphicsobject.cpp \
    $$PWD/commongraphics/textbutton.cpp \
    $$PWD/commongraphics/bubblebuttonbright.cpp \
    $$PWD/externalconfig/externalconfigwindowitem.cpp \
    $$PWD/twofactorauth/twofactorauthwindowitem.cpp \
    $$PWD/twofactorauth/twofactorauthokbutton.cpp \
    $$PWD/bottominfowidget/sharingfeatures/sharingfeatureswindowitem.cpp \
    $$PWD/bottominfowidget/sharingfeatures/sharingfeature.cpp \
    $$PWD/bottominfowidget/upgradewidget/upgradewidgetitem.cpp \
    $$PWD/bottominfowidget/bottominfoitem.cpp \
    $$PWD/commongraphics/bubblebuttondark.cpp \
    $$PWD/loginwindow/blockableqlineedit.cpp \
    $$PWD/commongraphics/texticonbutton.cpp \
    $$PWD/commongraphics/verticaldividerline.cpp \
    $$PWD/commonwidgets/custommenulineedit.cpp \
    $$PWD/commonwidgets/iconbuttonwidget.cpp \
    $$PWD/commonwidgets/textbuttonwidget.cpp \
    $$PWD/preferenceswindow/proxysettingswindow/proxysettingsitem.cpp \
    $$PWD/newsfeedwindow/scrollablemessage.cpp \
    $$PWD/commongraphics/iconbutton.cpp \
    $$PWD/preferenceswindow/textitem.cpp \
    $$PWD/connectwindow/logonotificationsbutton.cpp \
    $$PWD/preferenceswindow/connectionwindow/dnswhileconnecteditem.cpp \
    $$PWD/languagecontroller.cpp \
    $$PWD/locationswindow/widgetlocations/staticipdeviceinfo.cpp \
    $$PWD/locationswindow/widgetlocations/configfooterinfo.cpp \
    $$PWD/mainwindowcontroller.cpp \
    $$PWD/multipleaccountdetection/multipleaccountdetectionfactory.cpp \
    $$PWD/preferenceswindow/openurlitem.cpp \
    $$PWD/application/singleappinstance.cpp \
    $$PWD/localipcserver/localipcserver.cpp


HEADERS += $$PWD/backend/backend.h \
    $$PWD/backend/connectstatehelper.h \
    $$PWD/backend/firewallstatehelper.h \
    $$PWD/backend/ibackend.h \
    $$PWD/backend/notificationscontroller.h \
    $$PWD/backend/locationsmodel/alllocationsmodel.h \
    $$PWD/backend/locationsmodel/basiccitiesmodel.h \
    $$PWD/backend/locationsmodel/basiclocationsmodel.h \
    $$PWD/backend/locationsmodel/configuredcitiesmodel.h \
    $$PWD/backend/locationsmodel/favoritecitiesmodel.h \
    $$PWD/backend/locationsmodel/favoritelocationsstorage.h \
    $$PWD/backend/locationsmodel/locationmodelitem.h \
    $$PWD/backend/locationsmodel/locationsmodel.h \
    $$PWD/backend/locationsmodel/sortlocationsalgorithms.h \
    $$PWD/backend/locationsmodel/staticipscitiesmodel.h \
    $$PWD/backend/preferences/accountinfo.h \
    $$PWD/backend/preferences/detectlanrange.h \
    $$PWD/backend/preferences/guisettingsfromver1.h \
    $$PWD/backend/preferences/preferences.h \
    $$PWD/backend/preferences/preferenceshelper.h \
    $$PWD/backend/types/upgrademodetype.h \
    $$PWD/backend/types/dnswhileconnectedinfo.h \
    $$PWD/backend/persistentstate.h \
    $$PWD/application/windowsnativeeventfilter.h \
    $$PWD/application/windscribeapplication.h \
    $$PWD/commongraphics/imageitem.h \
    $$PWD/commongraphics/scalablegraphicsobject.h \
    $$PWD/commonwidgets/combomenuwidget.h \
    $$PWD/commonwidgets/combomenuwidgetbutton.h \
    $$PWD/commonwidgets/iconwidget.h \
    $$PWD/commonwidgets/lightwidget.h \
    $$PWD/connectwindow/backgroundimage/backgroundimage.h \
    $$PWD/connectwindow/backgroundimage/imagechanger.h \
    $$PWD/connectwindow/backgroundimage/simpleimagechanger.h \
    $$PWD/connectwindow/connectstateprotocolport/badgepixmap.h \
    $$PWD/connectwindow/connectstateprotocolport/connectionbadgedots.h \
    $$PWD/connectwindow/connectstateprotocolport/connectstateprotocolport.h \
    $$PWD/connectwindow/ipaddressitem/ipaddressitem.h \
    $$PWD/connectwindow/ipaddressitem/numberitem.h \
    $$PWD/connectwindow/ipaddressitem/numberspixmap.h \
    $$PWD/connectwindow/ipaddressitem/octetitem.h \
    $$PWD/connectwindow/middleitem.h \
    $$PWD/connectwindow/serverratingindicator.h \
    $$PWD/dialogs/advancedparametersdialog.h \
    $$PWD/dialogs/dialoggetusernamepassword.h \
    $$PWD/dialogs/dialogmessagecpuusage.h \
    $$PWD/locationswindow/widgetlocations/footertopstrip.h \
    $$PWD/locationswindow/widgetlocations/iitemwidget.h \
    $$PWD/locationswindow/widgetlocations/itemwidgetcity.h \
    $$PWD/locationswindow/widgetlocations/itemwidgetheader.h \
    $$PWD/locationswindow/widgetlocations/itemwidgetregion.h \
    $$PWD/locationswindow/widgetlocations/scrollbar.h \
    $$PWD/locationswindow/widgetlocations/widgetcitieslist.h \
    $$PWD/locationswindow/widgetlocations/widgetlocations.h \
    $$PWD/locationswindow/widgetlocations/widgetlocationslist.h \
    $$PWD/mainwindowstate.h \
    $$PWD/overlaysconnectwindow/generalmessagetwobuttonwindowitem.h \
    $$PWD/overlaysconnectwindow/igeneralmessagetwobuttonwindow.h \
    $$PWD/overlaysconnectwindow/generalmessagewindowitem.h \
    $$PWD/overlaysconnectwindow/igeneralmessagewindow.h \
    $$PWD/overlaysconnectwindow/iupgradewindow.h \
    $$PWD/overlaysconnectwindow/upgradewindowitem.h \
    $$PWD/overlaysconnectwindow/iupdatewindow.h \
    $$PWD/overlaysconnectwindow/updatewindowitem.h \
    $$PWD/overlaysconnectwindow/iupdateappitem.h \
    $$PWD/overlaysconnectwindow/updateappitem.h \
    $$PWD/graphicresources/fontdescr.h \
    $$PWD/graphicresources/iconmanager.h \
    $$PWD/graphicresources/independentpixmap.h \
    $$PWD/launchonstartup/launchonstartup.h \
    $$PWD/loginwindow/iinitwindow.h \
    $$PWD/loginwindow/initwindowitem.h \
    $$PWD/preferenceswindow/connectionwindow/packetsizeeditboxitem.h \
    $$PWD/preferenceswindow/debugwindow/apiresolutionitem.h \
    $$PWD/preferenceswindow/generalwindow/backgroundsettingsitem.h \
    $$PWD/preferenceswindow/generalwindow/selectimageitem.h \
    $$PWD/preferenceswindow/generalwindow/versioninfoitem.h \
    $$PWD/preferenceswindow/networkwhitelistwindow/currentnetworkitem.h \
    $$PWD/preferenceswindow/networkwhitelistwindow/networklistitem.h \
    $$PWD/preferenceswindow/networkwhitelistwindow/networkwhitelistshared.h \
    $$PWD/preferenceswindow/splittunnelingwindow/appincludeditem.h \
    $$PWD/preferenceswindow/splittunnelingwindow/appsearchitem.h \
    $$PWD/preferenceswindow/splittunnelingwindow/iporhostnameitem.h \
    $$PWD/preferenceswindow/splittunnelingwindow/newiporhostnameitem.h \
    $$PWD/preferenceswindow/splittunnelingwindow/searchlineedititem.h \
    $$PWD/preferenceswindow/splittunnelingwindow/splittunnelingappsitem.h \
    $$PWD/preferenceswindow/splittunnelingwindow/splittunnelingappssearchitem.h \
    $$PWD/preferenceswindow/splittunnelingwindow/splittunnelingappssearchwindowitem.h \
    $$PWD/preferenceswindow/splittunnelingwindow/splittunnelingappswindowitem.h \
    $$PWD/preferenceswindow/splittunnelingwindow/splittunnelingiphostnamewindowitem.h \
    $$PWD/preferenceswindow/splittunnelingwindow/splittunnelingipsandhostnamesitem.h \
    $$PWD/preferenceswindow/splittunnelingwindow/splittunnelingitem.h \
    $$PWD/preferenceswindow/splittunnelingwindow/splittunnelingswitchitem.h \
    $$PWD/showingdialogstate.h \
    $$PWD/tooltips/itooltip.h \
    $$PWD/tooltips/serverratingstooltip.h \
    $$PWD/tooltips/tooltipbasic.h \
    $$PWD/tooltips/tooltipcontroller.h \
    $$PWD/tooltips/tooltipdescriptive.h \
    $$PWD/tooltips/tooltiptypes.h \
    $$PWD/tooltips/tooltiputil.h \
    $$PWD/utils/authcheckerfactory.h \
    $$PWD/utils/iauthchecker.h \
    $$PWD/utils/imagewithshadow.h \
    $$PWD/utils/protoenumtostring.h \
    $$PWD/commonwidgets/custommenuwidget.h \
    $$PWD/commonwidgets/customtexteditwidget.h \
    $$PWD/commonwidgets/scrollareawidget.h \
    $$PWD/commonwidgets/verticalscrollbarwidget.h \
    $$PWD/log/logviewerwindow.h \
    $$PWD/preferenceswindow/debugwindow/advancedparameterswindowitem.h \
    $$PWD/utils/textshadow.h \
    $$PWD/utils/writeaccessrightschecker.h \
    $$PWD/utils/interfaceutils.h \
    $$PWD/blockconnect.h \
    $$PWD/dpiscaleawarewidget.h \
    $$PWD/dpiscalemanager.h \
    $$PWD/freetrafficnotificationcontroller.h \
    $$PWD/guitest.h \
    $$PWD/systemtray/locationstraymenubutton.h \
    $$PWD/systemtray/locationstraymenuitemdelegate.h \
    $$PWD/systemtray/locationstraymenuwidget.h \
    $$PWD/systemtray/locationstraymenunative.h \
    $$PWD/systemtray/locationstraymenuscalemanager.h \
    $$PWD/loginattemptscontroller.h \
    $$PWD/mainwindow.h \
    $$PWD/graphicresources/fontmanager.h \
    $$PWD/graphicresources/imageresourcessvg.h \
    $$PWD/graphicresources/imageresourcesjpg.h \
    $$PWD/loginwindow/logginginwindowitem.h \
    $$PWD/connectwindow/connectwindowitem.h \
    $$PWD/locationswindow/locationswindow.h \
    $$PWD/locationswindow/widgetlocations/backgroundpixmapanimation.h \
    $$PWD/locationswindow/widgetlocations/cursorupdatehelper.h \
    $$PWD/locationswindow/widgetlocations/itemtimems.h \
    $$PWD/locationswindow/widgetlocations/iwidgetlocationsinfo.h \
    $$PWD/locationswindow/widgetlocations/locationstab.h \
    $$PWD/locationswindow/widgetlocations/widgetcities.h \
    $$PWD/locationswindow/widgetlocations/widgetlocationssizes.h \
    $$PWD/connectwindow/connectbutton.h \
    $$PWD/connectwindow/background.h \
    $$PWD/connectwindow/locationsbutton.h \
    $$PWD/connectwindow/wifiname.h \
    $$PWD/connectwindow/firewallbutton.h \
    $$PWD/loginwindow/loginwindowitem.h \
    $$PWD/loginwindow/welcomewindowitem.h \
    $$PWD/loginwindow/credentialswindowitem.h \
    $$PWD/loginwindow/ilogginginwindow.h \
    $$PWD/loginwindow/loginyesnobutton.h \
    $$PWD/loginwindow/usernamepasswordentry.h \
    $$PWD/loginwindow/loginbutton.h \
    $$PWD/loginwindow/iloginwindow.h \
    $$PWD/loginwindow/ilogginginwindow.h \
    $$PWD/loginwindow/iconhoverengagebutton.h \
    $$PWD/loginwindow/firewallturnoffbutton.h \
    $$PWD/emergencyconnectwindow/iemergencyconnectwindow.h \
    $$PWD/commongraphics/commongraphics.h \
    $$PWD/emergencyconnectwindow/emergencyconnectwindowitem.h \
    $$PWD/emergencyconnectwindow/textlinkbutton.h \
    $$PWD/utils/makecustomshadow.h \
    $$PWD/connectwindow/iconnectwindow.h \
    $$PWD/utils/shadowmanager.h \
    $$PWD/connectwindow/iconnectwindow.h \
    $$PWD/preferenceswindow/ipreferenceswindow.h \
    $$PWD/preferenceswindow/preferenceswindowitem.h \
    $$PWD/preferenceswindow/bottomresizeitem.h \
    $$PWD/preferenceswindow/generalwindow/generalwindowitem.h \
    $$PWD/preferenceswindow/scrollareaitem.h \
    $$PWD/preferenceswindow/accountwindow/accountwindowitem.h \
    $$PWD/preferenceswindow/connectionwindow/connectionwindowitem.h \
    $$PWD/preferenceswindow/debugwindow/debugwindowitem.h \
    $$PWD/preferenceswindow/sharewindow/sharewindowitem.h \
    $$PWD/preferenceswindow/preferencestab/ipreferencestabcontrol.h \
    $$PWD/preferenceswindow/preferencestab/preferencestabcontrolitem.h \
    $$PWD/commongraphics/checkboxbutton.h \
    $$PWD/preferenceswindow/checkboxitem.h \
    $$PWD/preferenceswindow/dividerline.h \
    $$PWD/preferenceswindow/escapebutton.h \
    $$PWD/preferenceswindow/comboboxitem.h \
    $$PWD/newsfeedwindow/inewsfeedwindow.h \
    $$PWD/newsfeedwindow/newsfeedwindowitem.h \
    $$PWD/preferenceswindow/accountwindow/usernameitem.h \
    $$PWD/preferenceswindow/accountwindow/emailitem.h \
    $$PWD/preferenceswindow/accountwindow/planitem.h \
    $$PWD/preferenceswindow/accountwindow/expiredateitem.h \
    $$PWD/preferenceswindow/connectionwindow/subpageitem.h \
    $$PWD/preferenceswindow/basepage.h \
    $$PWD/preferenceswindow/baseitem.h \
    $$PWD/preferenceswindow/sharewindow/securehotspotitem.h \
    $$PWD/preferenceswindow/sharewindow/proxygatewayitem.h \
    $$PWD/preferenceswindow/editboxitem.h \
    $$PWD/preferenceswindow/sharewindow/proxyipaddressitem.h \
    $$PWD/preferenceswindow/debugwindow/viewlogitem.h \
    $$PWD/preferenceswindow/debugwindow/advancedparametersitem.h \
    $$PWD/preferenceswindow/connectionwindow/firewallmodeitem.h \
    $$PWD/preferenceswindow/connectionwindow/automanualswitchitem.h \
    $$PWD/preferenceswindow/connectionwindow/connectionmodeitem.h \
    $$PWD/preferenceswindow/connectionwindow/packetsizeitem.h \
    $$PWD/preferenceswindow/connectionwindow/macspoofingitem.h \
    $$PWD/preferenceswindow/connectionwindow/macaddressitem.h \
    $$PWD/preferenceswindow/connectionwindow/autorotatemacitem.h \
    $$PWD/commongraphics/verticalscrollbar.h \
    $$PWD/preferenceswindow/networkwhitelistwindow/networkwhitelistwindowitem.h \
    $$PWD/preferenceswindow/splittunnelingwindow/splittunnelingwindowitem.h \
    $$PWD/preferenceswindow/proxysettingswindow/proxysettingswindowitem.h \
    $$PWD/commongraphics/clickablegraphicsobject.h \
    $$PWD/commongraphics/textbutton.h \
    $$PWD/commongraphics/bubblebuttonbright.h \
    $$PWD/externalconfig/iexternalconfigwindow.h \
    $$PWD/externalconfig/externalconfigwindowitem.h \
    $$PWD/twofactorauth/itwofactorauthwindow.h \
    $$PWD/twofactorauth/twofactorauthwindowitem.h \
    $$PWD/twofactorauth/twofactorauthokbutton.h \
    $$PWD/connectwindow/iconnectwindow.h \
    $$PWD/bottominfowidget/sharingfeatures/sharingfeatureswindowitem.h \
    $$PWD/bottominfowidget/sharingfeatures/sharingfeature.h \
    $$PWD/bottominfowidget/upgradewidget/upgradewidgetitem.h \
    $$PWD/bottominfowidget/ibottominfoitem.h \
    $$PWD/bottominfowidget/bottominfoitem.h \
    $$PWD/commongraphics/bubblebuttondark.h \
    $$PWD/loginwindow/blockableqlineedit.h \
    $$PWD/commongraphics/texticonbutton.h \
    $$PWD/commongraphics/verticaldividerline.h \
    $$PWD/commonwidgets/custommenulineedit.h \
    $$PWD/commonwidgets/iconbuttonwidget.h \
    $$PWD/commonwidgets/textbuttonwidget.h \
    $$PWD/preferenceswindow/proxysettingswindow/proxysettingsitem.h \
    $$PWD/newsfeedwindow/scrollablemessage.h \
    $$PWD/commongraphics/iconbutton.h \
    $$PWD/preferenceswindow/textitem.h \
    $$PWD/connectwindow/logonotificationsbutton.h \
    $$PWD/preferenceswindow/connectionwindow/dnswhileconnecteditem.h \
    $$PWD/languagecontroller.h \
    $$PWD/locationswindow/widgetlocations/staticipdeviceinfo.h \
    $$PWD/locationswindow/widgetlocations/configfooterinfo.h \
    $$PWD/mainwindowcontroller.h \
    $$PWD/multipleaccountdetection/imultipleaccountdetection.h \
    $$PWD/multipleaccountdetection/multipleaccountdetectionfactory.h \
    $$PWD/preferenceswindow/openurlitem.h \
    $$PWD/application/singleappinstance.h \
    $$PWD/application/singleappinstance_p.h \
    $$PWD/localipcserver/localipcserver.h

RESOURCES += \
    $$PWD/svg.qrc \
    $$PWD/jpg.qrc \
    $$PWD/windscribe.qrc

TRANSLATIONS += \
    languages/ru.ts \
    languages/es.ts \
    languages/fr.ts \
    languages/ja.ts \
    languages/ar.ts \
    languages/hu.ts \
    languages/it.ts \
    languages/ko.ts \
    languages/nl.ts \
    languages/zh.ts \
    languages/de.ts \
    languages/pl.ts \
    languages/tr.ts \
    languages/cs.ts \
    languages/da.ts \
    languages/el.ts \
    languages/pt.ts \
    languages/sk.ts \
    languages/th.ts \
    languages/vi.ts \
    languages/en.ts \
    languages/en_nsfw.ts \
    languages/sv.ts \
    languages/id.ts \
    languages/hi.ts \
    languages/hr.ts

DISTFILES += \
    languages/ar.ts \
    languages/cs.ts \
    languages/da.ts \
    languages/de.ts \
    languages/el.ts \
    languages/en.ts \
    languages/en_nsfw.ts \
    languages/es.ts \
    languages/fr.ts \
    languages/hi.ts \
    languages/hr.ts \
    languages/hu.ts \
    languages/id.ts \
    languages/it.ts \
    languages/ja.ts \
    languages/ko.ts \
    languages/nl.ts \
    languages/pl.ts \
    languages/pt.ts \
    languages/ru.ts \
    languages/sk.ts \
    languages/sv.ts \
    languages/th.ts \
    languages/tr.ts \
    languages/vi.ts \
    languages/zh.ts 

FORMS += \
    $$PWD/dialogs/dialoggetusernamepassword.ui \
    $$PWD/dialogs/dialogmessagecpuusage.ui
