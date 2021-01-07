#include "locationstab.h"

#include <QMessageBox>
#include <QPainter>
#include "graphicresources/imageresourcessvg.h"
#include "commongraphics/commongraphics.h"
#include "graphicresources/fontmanager.h"
#include "dpiscalemanager.h"
#include "tooltips/tooltiptypes.h"
#include "utils/writeaccessrightschecker.h"

extern QWidget *g_mainWindow;

namespace GuiLocations {


LocationsTab::LocationsTab(QWidget *parent, LocationsModel *locationsModel) : QWidget(parent),
    curTab_(CUR_TAB_ALL_LOCATIONS),
    tabPress_(CUR_TAB_NONE),
    curTabMouseOver_(CUR_TAB_NONE),
    checkCustomConfigPathAccessRights_(false),
    countOfVisibleItemSlots_(7),
    currentLocationListHeight_(0),
    isRibbonVisible_(false),
    showAllTabs_(true),
    backgroundColor_(14, 25, 38)
{
    setMouseTracking(true);
    curCursorShape_ = Qt::ArrowCursor;

    updateIconRectsAndLine();
    curWhiteLinePos_ = (rcAllLocationsIcon_.center().x() + 1) * G_SCALE;
    connect(&whiteLineAnimation_, SIGNAL(valueChanged(QVariant)), SLOT(onWhiteLinePosChanged(QVariant)));

    widgetAllLocations_ = new GuiLocations::WidgetLocations(this);

    widgetConfiguredLocations_ = new GuiLocations::WidgetCities(this, 6);
    widgetConfiguredLocations_->setEmptyListDisplayIcon("locations/FOLDER_ICON_BIG");
    connect(widgetConfiguredLocations_, SIGNAL(emptyListButtonClicked()),
                                        SLOT(onAddCustomConfigClicked()));
    widgetConfiguredLocations_->hide();

    widgetStaticIpsLocations_ = new GuiLocations::WidgetCities(this, 6);
    widgetStaticIpsLocations_->setEmptyListDisplayIcon("locations/STATIC_IP_ICON_BIG");
    widgetStaticIpsLocations_->setEmptyListDisplayText(tr("You don't have any Static IPs"), 120);
    widgetStaticIpsLocations_->setEmptyListButtonText(tr("Buy"));
    connect(widgetStaticIpsLocations_, SIGNAL(emptyListButtonClicked()),
                                       SIGNAL(addStaticIpClicked()));
    widgetStaticIpsLocations_->hide();

    widgetFavoriteLocations_ = new GuiLocations::WidgetCities(this);
    widgetFavoriteLocations_->setEmptyListDisplayIcon("locations/BROKEN_HEART_ICON");
    widgetFavoriteLocations_->setEmptyListDisplayText(tr("Nothing to see here..."), 120);
    widgetFavoriteLocations_->hide();

    staticIPDeviceInfo_ = new StaticIPDeviceInfo(this);
    connect(staticIPDeviceInfo_, SIGNAL(addStaticIpClicked()), SIGNAL(addStaticIpClicked()));
    staticIPDeviceInfo_->hide();

    configFooterInfo_ = new ConfigFooterInfo(this);
    configFooterInfo_->hide();
    connect(configFooterInfo_, SIGNAL(clearCustomConfigClicked()),
            SIGNAL(clearCustomConfigClicked()));
    connect(configFooterInfo_, SIGNAL(addCustomConfigClicked()), SLOT(onAddCustomConfigClicked()));
    int newHeight = 50 * countOfVisibleItemSlots_ - 1;
    updateLocationWidgetsGeometry(newHeight);

    connect(widgetAllLocations_, SIGNAL(selected(LocationID)), SIGNAL(selected(LocationID)));
    connect(widgetAllLocations_, SIGNAL(clickedOnPremiumStarCity()), SIGNAL(clickedOnPremiumStarCity()));
    connect(widgetConfiguredLocations_, SIGNAL(selected(LocationID)), SIGNAL(selected(LocationID)));
    connect(widgetStaticIpsLocations_, SIGNAL(selected(LocationID)), SIGNAL(selected(LocationID)));
    connect(widgetFavoriteLocations_, SIGNAL(selected(LocationID)), SIGNAL(selected(LocationID)));

    connect(widgetAllLocations_, SIGNAL(switchFavorite(LocationID,bool)), SIGNAL(switchFavorite(LocationID,bool)));
    connect(widgetConfiguredLocations_, SIGNAL(switchFavorite(LocationID,bool)), SIGNAL(switchFavorite(LocationID,bool)));
    connect(widgetStaticIpsLocations_, SIGNAL(switchFavorite(LocationID,bool)), SIGNAL(switchFavorite(LocationID,bool)));
    connect(widgetFavoriteLocations_, SIGNAL(switchFavorite(LocationID,bool)), SIGNAL(switchFavorite(LocationID,bool)));

    connect(widgetAllLocations_,        SIGNAL(showTooltip(TooltipInfo)), SIGNAL(showTooltip(TooltipInfo)));
    connect(widgetConfiguredLocations_, SIGNAL(showTooltip(TooltipInfo)), SIGNAL(showTooltip(TooltipInfo)));
    connect(widgetStaticIpsLocations_,  SIGNAL(showTooltip(TooltipInfo)), SIGNAL(showTooltip(TooltipInfo)));
    connect(widgetFavoriteLocations_,   SIGNAL(showTooltip(TooltipInfo)), SIGNAL(showTooltip(TooltipInfo)));
    connect(configFooterInfo_,          SIGNAL(showTooltip(TooltipInfo)), SIGNAL(showTooltip(TooltipInfo)));
    connect(widgetAllLocations_,        SIGNAL(hideTooltip(TooltipId)), SIGNAL(hideTooltip(TooltipId)));
    connect(widgetConfiguredLocations_, SIGNAL(hideTooltip(TooltipId)), SIGNAL(hideTooltip(TooltipId)));
    connect(widgetStaticIpsLocations_,  SIGNAL(hideTooltip(TooltipId)), SIGNAL(hideTooltip(TooltipId)));
    connect(widgetFavoriteLocations_,   SIGNAL(hideTooltip(TooltipId)), SIGNAL(hideTooltip(TooltipId)));
    connect(configFooterInfo_,          SIGNAL(hideTooltip(TooltipId)), SIGNAL(hideTooltip(TooltipId)));

    widgetAllLocations_->setModel(locationsModel->getAllLocationsModel());
    widgetConfiguredLocations_->setModel(locationsModel->getConfiguredLocationsModel());
    widgetStaticIpsLocations_->setModel(locationsModel->getStaticIpsLocationsModel());
    widgetFavoriteLocations_->setModel(locationsModel->getFavoriteLocationsModel());

    connect(widgetAllLocations_, SIGNAL(heightChanged(int,int)), SLOT(onAllLocationsHeightChanged(int,int)));

    connect(locationsModel, SIGNAL(deviceNameChanged(QString)), SLOT(onDeviceNameChanged(QString)));

    updateCustomConfigsEmptyListVisibility();
}

int LocationsTab::setCountVisibleItemSlots(int cnt)
{
    if (cnt != countOfVisibleItemSlots_)
    {
        countOfVisibleItemSlots_ = cnt;
        widgetAllLocations_->setCountAvailableItemSlots(countOfVisibleItemSlots_);
        widgetConfiguredLocations_->setCountAvailableItemSlots(countOfVisibleItemSlots_-1);
        widgetStaticIpsLocations_->setCountAvailableItemSlots(countOfVisibleItemSlots_-1);
        widgetFavoriteLocations_->setCountAvailableItemSlots(countOfVisibleItemSlots_);
        updateRibbonVisibility();

        const int newHeight = 50 * countOfVisibleItemSlots_ - 1;
        updateLocationWidgetsGeometry(newHeight);
        return newHeight ;
    }
    else
    {
        return (50 * countOfVisibleItemSlots_ - 1);
    }
}

int LocationsTab::getCountVisibleItems()
{
    return countOfVisibleItemSlots_;
}

void LocationsTab::setOnlyConfigTabVisible(bool onlyConfig)
{
    if (onlyConfig)
    {
        showAllTabs_ = false;
        changeTab(CUR_TAB_CONFIGURED_LOCATIONS);
    }
    else
    {
        showAllTabs_ = true;
        changeTab(CUR_TAB_ALL_LOCATIONS);
    }
}

void LocationsTab::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    if (isWhiteAnimationActive())
    {
        update();
    }

    QPainter painter(this);
    drawTab(painter, QRect(0, 0, width(), TOP_TAB_HEIGHT * G_SCALE));

}

void LocationsTab::mouseMoveEvent(QMouseEvent *event)
{
    QPoint pt = QCursor::pos();

    pt = mapFromGlobal(pt);

    const int addMargin = 5*G_SCALE;

    if (showAllTabs_)
    {
        if (rcAllLocationsIcon_.adjusted(-addMargin, -addMargin, addMargin, addMargin).contains(pt))
        {
            curTabMouseOver_ = CUR_TAB_ALL_LOCATIONS;
            setPointingHandCursor();
            rectHoverEnter(rcAllLocationsIcon_, QT_TRANSLATE_NOOP("CommonWidgets::ToolTipWidget", "All"), 8 * G_SCALE, -5 * G_SCALE);
        }
        else if (rcConfiguredLocationsIcon_.adjusted(-addMargin, -addMargin, addMargin, addMargin).contains(pt))
        {
            curTabMouseOver_ = CUR_TAB_CONFIGURED_LOCATIONS;
            setPointingHandCursor();
            rectHoverEnter(rcConfiguredLocationsIcon_, QT_TRANSLATE_NOOP("CommonWidgets::ToolTipWidget", "Configured"), 9 * G_SCALE, -5 * G_SCALE);
        }
        else if (rcStaticIpsLocationsIcon_.adjusted(-addMargin, -addMargin, addMargin, addMargin).contains(pt))
        {
            curTabMouseOver_ = CUR_TAB_STATIC_IPS_LOCATIONS;
            setPointingHandCursor();
            rectHoverEnter(rcStaticIpsLocationsIcon_, QT_TRANSLATE_NOOP("CommonWidgets::ToolTipWidget", "Static IPs"), 8 * G_SCALE, -5 * G_SCALE);
        }
        else if (rcFavoriteLocationsIcon_.adjusted(-addMargin, -addMargin, addMargin, addMargin).contains(pt))
        {
            curTabMouseOver_ = CUR_TAB_FAVORITE_LOCATIONS;
            setPointingHandCursor();
            rectHoverEnter(rcFavoriteLocationsIcon_, QT_TRANSLATE_NOOP("CommonWidgets::ToolTipWidget", "Favourites"), 8 * G_SCALE, -5 * G_SCALE);
        }
        else
        {
            curTabMouseOver_ = CUR_TAB_NONE;
            setArrowCursor();

            emit hideTooltip(TOOLTIP_ID_LOCATIONS_TAB_INFO);
        }
    }

    QWidget::mouseMoveEvent(event);
}

void LocationsTab::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (curTabMouseOver_ != CUR_TAB_NONE)
        {
            tabPress_ = curTabMouseOver_;
        }
    }
}

void LocationsTab::changeTab(CurTabEnum newTab)
{
    curTab_ = newTab;

    int endWhiteLinePos;
    if (curTab_ == CUR_TAB_CONFIGURED_LOCATIONS)
    {
        endWhiteLinePos = rcConfiguredLocationsIcon_.center().x();
        onClickConfiguredLocations();
    }
    else if (curTab_ == CUR_TAB_STATIC_IPS_LOCATIONS)
    {
        endWhiteLinePos = rcStaticIpsLocationsIcon_.center().x();
        onClickStaticIpsLocations();
    }
    else if (curTab_ == CUR_TAB_FAVORITE_LOCATIONS)
    {
        endWhiteLinePos = rcFavoriteLocationsIcon_.center().x();
        onClickFavoriteLocations();
    }
    else if (curTab_ == CUR_TAB_ALL_LOCATIONS)
    {
        endWhiteLinePos = rcAllLocationsIcon_.center().x();
        onClickAllLocations();
    }
    else
    {
        // bug if we here
        endWhiteLinePos = 0;
        Q_ASSERT(false);
    }

    whiteLineAnimation_.stop();
    whiteLineAnimation_.setStartValue(curWhiteLinePos_);
    whiteLineAnimation_.setEndValue(endWhiteLinePos + 2);
    whiteLineAnimation_.setDuration(ANIMATION_DURATION);
    whiteLineAnimation_.start();

    update();
}

void LocationsTab::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (curTabMouseOver_ != CUR_TAB_NONE &&  curTabMouseOver_ != curTab_ && tabPress_ == curTabMouseOver_)
        {
            changeTab(curTabMouseOver_);
        }
    }
}

void LocationsTab::leaveEvent(QEvent *event)
{
    curTabMouseOver_ = CUR_TAB_NONE;
    setArrowCursor();
    emit hideTooltip(TOOLTIP_ID_LOCATIONS_TAB_INFO);
    QWidget::leaveEvent(event);
}

void LocationsTab::onClickAllLocations()
{
    widgetAllLocations_->startAnimationWithPixmap(this->grab(QRect(0, TOP_TAB_HEIGHT* G_SCALE, width(), height() - TOP_TAB_HEIGHT* G_SCALE)));
    widgetConfiguredLocations_->hide();
    widgetStaticIpsLocations_->hide();
    widgetFavoriteLocations_->hide();
    widgetAllLocations_->show();
    widgetAllLocations_->raise();
}

void LocationsTab::onClickConfiguredLocations()
{
    widgetConfiguredLocations_->startAnimationWithPixmap(this->grab(QRect(0, TOP_TAB_HEIGHT* G_SCALE, width(), height() - TOP_TAB_HEIGHT* G_SCALE)));
    widgetAllLocations_->hide();
    widgetStaticIpsLocations_->hide();
    widgetFavoriteLocations_->hide();
    widgetConfiguredLocations_->show();
    widgetConfiguredLocations_->raise();
    updateRibbonVisibility();
}

void LocationsTab::onClickStaticIpsLocations()
{
    widgetStaticIpsLocations_->startAnimationWithPixmap(this->grab(QRect(0, TOP_TAB_HEIGHT* G_SCALE, width(), height() - TOP_TAB_HEIGHT* G_SCALE)));
    widgetAllLocations_->hide();
    widgetConfiguredLocations_->hide();
    widgetFavoriteLocations_->hide();
    widgetStaticIpsLocations_->show();
    widgetStaticIpsLocations_->raise();
    updateRibbonVisibility();
}

void LocationsTab::onClickFavoriteLocations()
{
    widgetFavoriteLocations_->startAnimationWithPixmap(this->grab(QRect(0, TOP_TAB_HEIGHT* G_SCALE, width(), height() - TOP_TAB_HEIGHT* G_SCALE)));
    widgetAllLocations_->hide();
    widgetConfiguredLocations_->hide();
    widgetStaticIpsLocations_->hide();
    widgetFavoriteLocations_->show();
    widgetFavoriteLocations_->raise();
}

void LocationsTab::onWhiteLinePosChanged(const QVariant &value)
{
    curWhiteLinePos_ = value.toInt();
    update();
}

void LocationsTab::onAllLocationsHeightChanged(int oldHeight, int newHeight)
{
    Q_UNUSED(oldHeight);

    widgetAllLocations_->setGeometry(0, TOP_TAB_HEIGHT * G_SCALE, 334 * G_SCALE, newHeight * G_SCALE);
    widgetAllLocations_->setSize(334, newHeight);
}

void LocationsTab::onDeviceNameChanged(const QString &deviceName)
{
    staticIPDeviceInfo_->setDeviceName(deviceName);
}

void LocationsTab::onAddCustomConfigClicked()
{
    checkCustomConfigPathAccessRights_ = true;
    emit addCustomConfigClicked();
}

IWidgetLocationsInfo *LocationsTab::currentWidgetLocations()
{
    if (curTab_ == CUR_TAB_ALL_LOCATIONS)        return widgetAllLocations_;
    if (curTab_ == CUR_TAB_FAVORITE_LOCATIONS)   return widgetFavoriteLocations_;
    if (curTab_ == CUR_TAB_STATIC_IPS_LOCATIONS) return widgetStaticIpsLocations_;
    if (curTab_ == CUR_TAB_CONFIGURED_LOCATIONS) return widgetConfiguredLocations_;
    return nullptr;
}

void LocationsTab::drawTab(QPainter &painter, const QRect &rc)
{
    painter.fillRect(rc, QBrush(backgroundColor_));

    drawBottomLine(painter, rc.left(), rc.right(), rc.bottom(), curWhiteLinePos_);

    // Draw Icons
    {
        IndependentPixmap *p = ImageResourcesSvg::instance().getIndependentPixmap("locations/CONFIG_ICON");
        painter.setOpacity(curTab_ == CUR_TAB_CONFIGURED_LOCATIONS ? 1.0 : 0.5);
        p->draw(rcConfiguredLocationsIcon_.left(), rcConfiguredLocationsIcon_.top(), &painter);
    }
    if (showAllTabs_)
    {
        {
            IndependentPixmap *p = ImageResourcesSvg::instance().getIndependentPixmap("locations/STATIC_IP_ICON");
            painter.setOpacity(curTab_ == CUR_TAB_STATIC_IPS_LOCATIONS ? 1.0 : 0.5);
            p->draw(rcStaticIpsLocationsIcon_.left(), rcStaticIpsLocationsIcon_.top(), &painter);
        }
        {
            IndependentPixmap *p = ImageResourcesSvg::instance().getIndependentPixmap("locations/FAV_ICON");
            painter.setOpacity(curTab_ == CUR_TAB_FAVORITE_LOCATIONS ? 1.0 : 0.5);
            p->draw(rcFavoriteLocationsIcon_.left(), rcFavoriteLocationsIcon_.top(), &painter);
        }
        {
            IndependentPixmap *p = ImageResourcesSvg::instance().getIndependentPixmap("locations/ALL_LOCATION_ICON");
            painter.setOpacity(curTab_ == CUR_TAB_ALL_LOCATIONS ? 1.0 : 0.5);
            p->draw(rcAllLocationsIcon_.left(), rcAllLocationsIcon_.top(), &painter);
        }
    }
}

void LocationsTab::drawBottomLine(QPainter &painter, int left, int right, int bottom, int whiteLinePos)
{
    painter.fillRect(QRect(left, bottom-G_SCALE*2 + 1, right-left, G_SCALE*2), QBrush(QColor(3, 9, 28)));
    // draw white line
    {
        painter.fillRect(QRect((whiteLinePos - WHITE_LINE_WIDTH / 2 *G_SCALE), bottom-G_SCALE*2 + 1, WHITE_LINE_WIDTH*G_SCALE, G_SCALE*2), QBrush(Qt::white));
    }
}

void LocationsTab::setArrowCursor()
{
    if (curCursorShape_ != Qt::ArrowCursor)
    {
        setCursor(Qt::ArrowCursor);
        curCursorShape_ = Qt::ArrowCursor;
    }
}

void LocationsTab::setPointingHandCursor()
{
    if (curCursorShape_ != Qt::PointingHandCursor)
    {
        setCursor(Qt::PointingHandCursor);
        curCursorShape_ = Qt::PointingHandCursor;
    }
}

bool LocationsTab::isWhiteAnimationActive()
{
    return whiteLineAnimation_.state() == QAbstractAnimation::Running;
}

void LocationsTab::handleKeyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Right)
    {
        int curTabInt = static_cast<int>(curTab_);
        if (curTabInt < CUR_TAB_CONFIGURED_LOCATIONS)
        {
            curTabInt++;
            changeTab(static_cast<CurTabEnum>(curTabInt));

            IWidgetLocationsInfo * curWidgetLoc = currentWidgetLocations();
            if (curWidgetLoc != nullptr)
            {
                if (curWidgetLoc->cursorInViewport())
                {
                    curWidgetLoc->centerCursorOnSelectedItem();
                }
            }
        }
    }
    else if (event->key() == Qt::Key_Left)
    {
        int curTabInt = static_cast<int>(curTab_);
        if (curTabInt > CUR_TAB_ALL_LOCATIONS)
        {
            curTabInt--;
            changeTab(static_cast<CurTabEnum>(curTabInt));

            IWidgetLocationsInfo * curWidgetLoc = currentWidgetLocations();
            if (curWidgetLoc != nullptr)
            {
                if (curWidgetLoc->cursorInViewport())
                {
                    curWidgetLoc->centerCursorOnSelectedItem();
                }
            }
        }
    }
    else
    {
        IWidgetLocationsInfo * curWidgetLoc = currentWidgetLocations();
        if (curWidgetLoc != nullptr)
        {
            if (curWidgetLoc->hasSelection())
            {
                curWidgetLoc->handleKeyEvent(event);
            }
            else
            {
                curWidgetLoc->setFirstSelected();
            }
        }
    }
}

void LocationsTab::updateIconRectsAndLine()
{
    const int posY = 15;
    rcAllLocationsIcon_.       setRect(106 * G_SCALE, posY * G_SCALE, 16 * G_SCALE, 16 * G_SCALE);
    rcFavoriteLocationsIcon_.  setRect(166 * G_SCALE, posY * G_SCALE, 16 * G_SCALE, 14 * G_SCALE);
    rcStaticIpsLocationsIcon_. setRect(226 * G_SCALE, posY * G_SCALE, 16 * G_SCALE, 16 * G_SCALE);
    rcConfiguredLocationsIcon_.setRect(286 * G_SCALE, posY * G_SCALE, 18 * G_SCALE, 16 * G_SCALE);


    if      (currentWidgetLocations() == widgetAllLocations_)        curWhiteLinePos_ = (rcAllLocationsIcon_.center().x() + 1*G_SCALE)        ;
    else if (currentWidgetLocations() == widgetConfiguredLocations_) curWhiteLinePos_ = (rcConfiguredLocationsIcon_.center().x() + 1*G_SCALE) ;
    else if (currentWidgetLocations() == widgetStaticIpsLocations_)  curWhiteLinePos_ = (rcStaticIpsLocationsIcon_.center().x() + 1*G_SCALE)  ;
    else if (currentWidgetLocations() == widgetFavoriteLocations_)   curWhiteLinePos_ = (rcFavoriteLocationsIcon_.center().x() + 1*G_SCALE)   ;
    update();
}

void LocationsTab::updateLocationWidgetsGeometry(int newHeight)
{
    const int kRibbonHeight = isRibbonVisible_ ? 48 : 0;

    currentLocationListHeight_ = newHeight;

    widgetAllLocations_->setGeometry(
        0, TOP_TAB_HEIGHT * G_SCALE, WINDOW_WIDTH * G_SCALE, newHeight * G_SCALE);
    widgetFavoriteLocations_->setGeometry(
        0, TOP_TAB_HEIGHT * G_SCALE, WINDOW_WIDTH * G_SCALE, newHeight * G_SCALE);
    widgetStaticIpsLocations_->setGeometry(
        0, TOP_TAB_HEIGHT * G_SCALE, WINDOW_WIDTH * G_SCALE, (newHeight - kRibbonHeight) * G_SCALE);
    widgetConfiguredLocations_->setGeometry(
        0, TOP_TAB_HEIGHT * G_SCALE, WINDOW_WIDTH * G_SCALE, (newHeight - kRibbonHeight)* G_SCALE);

    widgetAllLocations_->setSize(WINDOW_WIDTH, newHeight);
    widgetFavoriteLocations_->setSize(WINDOW_WIDTH, newHeight);
    widgetStaticIpsLocations_->setSize(WINDOW_WIDTH, newHeight - kRibbonHeight );
    widgetConfiguredLocations_->setSize(WINDOW_WIDTH, newHeight - kRibbonHeight);

    staticIPDeviceInfo_->setGeometry(
        0, (newHeight - 2) * G_SCALE, WINDOW_WIDTH * G_SCALE, kRibbonHeight * G_SCALE);
    configFooterInfo_->setGeometry(
        0, (newHeight - 2) * G_SCALE, WINDOW_WIDTH * G_SCALE, kRibbonHeight * G_SCALE);

    updateScaling();
}

void LocationsTab::updateScaling()
{
    widgetAllLocations_->       updateScaling();
    widgetFavoriteLocations_->  updateScaling();
    widgetStaticIpsLocations_-> updateScaling();
    widgetConfiguredLocations_->updateScaling();
    configFooterInfo_->         updateScaling();
}

void LocationsTab::updateLanguage()
{
    widgetFavoriteLocations_->setEmptyListDisplayText(tr("Nothing to see here"));
}

void LocationsTab::setLatencyDisplay(ProtoTypes::LatencyDisplayType l)
{
    bool isShowLatencyInMs = (l == ProtoTypes::LATENCY_DISPLAY_MS);
    if (isShowLatencyInMs != widgetAllLocations_->isShowLatencyInMs())
    {
        widgetAllLocations_       ->setShowLatencyInMs(isShowLatencyInMs);
        widgetConfiguredLocations_->setShowLatencyInMs(isShowLatencyInMs);
        widgetStaticIpsLocations_ ->setShowLatencyInMs(isShowLatencyInMs);
        widgetFavoriteLocations_  ->setShowLatencyInMs(isShowLatencyInMs);
    }
}

void LocationsTab::setCustomConfigsPath(QString path)
{
    configFooterInfo_->setText(path);
    updateCustomConfigsEmptyListVisibility();
    updateRibbonVisibility();

    if (checkCustomConfigPathAccessRights_) {
        WriteAccessRightsChecker checker(path);
        if (checker.isWriteable()) {
            const QString desc = tr(
                "The selected directory is writeable for non-privileged users.\n"
                "Custom configs in this directory may pose a potential security risk.\n"
                "Directory: \"%1\"")
                .arg(path);
            QMessageBox::warning(g_mainWindow, tr("Windscribe"), desc);
        }
        checkCustomConfigPathAccessRights_ = false;
    }
}

void LocationsTab::rectHoverEnter(QRect buttonRect, QString text, int offsetX, int offsetY)
{
    QPoint buttonGlobalPoint = mapToGlobal(buttonRect.topLeft());
    int posX = buttonGlobalPoint.x() + offsetX;
    int posY = buttonGlobalPoint.y() + offsetY;

    TooltipInfo ti(TOOLTIP_TYPE_BASIC, TOOLTIP_ID_LOCATIONS_TAB_INFO);
    ti.x = posX;
    ti.y = posY;
    ti.title = text;
    ti.tailtype = TOOLTIP_TAIL_BOTTOM;
    ti.tailPosPercent = 0.5;
    emit showTooltip(ti);
}

void LocationsTab::updateCustomConfigsEmptyListVisibility()
{
    Q_ASSERT(configFooterInfo_ != nullptr);
    if (configFooterInfo_->text().isEmpty()) {
        widgetConfiguredLocations_->setEmptyListDisplayText(
            tr("Choose the directory that contains custom configs you wish to display here"), 160);
        widgetConfiguredLocations_->setEmptyListButtonText(tr("Choose"));
    } else {
        widgetConfiguredLocations_->setEmptyListDisplayText(
            tr("The selected directory contains no custom configs"), 160);
        widgetConfiguredLocations_->setEmptyListButtonText(QString());
    }
}

void LocationsTab::updateRibbonVisibility()
{
    auto *current_widget_locations = currentWidgetLocations();
    const bool is_location_list_empty = current_widget_locations->countVisibleItems() <= 1;

    isRibbonVisible_ = false;

    if (current_widget_locations == widgetStaticIpsLocations_)
    {
        configFooterInfo_->hide();
        if (is_location_list_empty) {
            staticIPDeviceInfo_->hide();
        } else {
            staticIPDeviceInfo_->show();
            staticIPDeviceInfo_->raise();
            isRibbonVisible_ = true;
        }
    }
    else if (current_widget_locations == widgetConfiguredLocations_)
    {
        staticIPDeviceInfo_->hide();
        const bool is_custom_configs_dir_set = !configFooterInfo_->text().isEmpty();
        if (!is_custom_configs_dir_set) {
            configFooterInfo_->hide();
        } else {
            configFooterInfo_->show();
            configFooterInfo_->raise();
            isRibbonVisible_ = true;
        }
    }
    else
    {
        configFooterInfo_->hide();
        staticIPDeviceInfo_->hide();
    }

    if (currentLocationListHeight_ != 0)
        updateLocationWidgetsGeometry(currentLocationListHeight_);
}

} // namespace GuiLocations

