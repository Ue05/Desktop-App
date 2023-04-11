#include "dnsdomainsgroup.h"

#include <QPainter>
#include "commongraphics/commongraphics.h"
#include "graphicresources/fontmanager.h"
#include "preferenceswindow/preferencegroup.h"
#include "utils/ipvalidation.h"
#include "utils/logger.h"
#include "utils/utils.h"
#include "dpiscalemanager.h"

namespace PreferencesWindow {

DnsDomainsGroup::DnsDomainsGroup(ScalableGraphicsObject *parent, const QString &desc, const QString &descUrl)
  : PreferenceGroup(parent, desc, descUrl)
{
    setFlags(flags() | QGraphicsItem::ItemIsFocusable);

    newAddressItem_ = new NewAddressItem(this);
    connect(newAddressItem_, &NewAddressItem::addNewAddressClicked, this, &DnsDomainsGroup::onAddClicked);
    connect(newAddressItem_, &NewAddressItem::keyPressed, this, &DnsDomainsGroup::clearError);
    connect(newAddressItem_, &NewAddressItem::escape, this, &DnsDomainsGroup::escape);
    addItem(newAddressItem_);
}

void DnsDomainsGroup::setAddresses(const QStringList &addresses)
{
    QSet<QString> curList;
    QSet<QString> newList;
    for (const QString &item: addresses_.values())
        curList << item;
    for (const QString &item: addresses)
        newList << item;

    if (newList != curList) {
        clearItems(true);
        for (auto &addr : addresses)
            addAddressInternal(addr);
        emit addressesUpdated(addresses_.values());
    }
}

void DnsDomainsGroup::addAddress(const QString &address)
{
    addAddressInternal(address);
    emit addressesUpdated(addresses_.values());
}

void DnsDomainsGroup::addAddressInternal(const QString &address)
{
    DnsDomainAddressItem *item = new DnsDomainAddressItem(address, this);
    connect(item, &DnsDomainAddressItem::deleteClicked, this, &DnsDomainsGroup::onDeleteClicked);
    addresses_[item] = address;
    addItem(item);
    hideItems(indexOf(item), -1, DISPLAY_FLAGS::FLAG_NO_ANIMATION);
    showItems(indexOf(item));
}

void DnsDomainsGroup::setFocusOnTextEntry()
{
    newAddressItem_->setSelected(true);
}

void DnsDomainsGroup::onAddClicked(const QString &address)
{
    ValidationCode code = validate(address);
    SPLIT_TUNNELING_NETWORK_ROUTE_TYPE type;
    types::SplitTunnelingNetworkRoute route;

    switch(code)
    {
        case OK:
            addAddress(address);
            break;
        case ERROR_EXISTS:
            emit setError(tr("IP or hostname already exists"),
                          tr("Please enter a new IP or hostname."));
            break;
    }
}

void DnsDomainsGroup::onDeleteClicked()
{
    DnsDomainAddressItem *item = static_cast<DnsDomainAddressItem *>(sender());
    addresses_.remove(item);
    hideItems(indexOf(item), -1, DISPLAY_FLAGS::FLAG_DELETE_AFTER);
    emit addressesUpdated(addresses_.values());
}

DnsDomainsGroup::ValidationCode DnsDomainsGroup::validate(const QString &address)
{
    if (itemByName(address) != nullptr)
    {
        return ValidationCode::ERROR_EXISTS;
    }

    return ValidationCode::OK;
}

DnsDomainAddressItem *DnsDomainsGroup::itemByName(const QString &address)
{
    for (DnsDomainAddressItem *item: addresses_.keys())
    {
        if (item->getAddressText() == address)
        {
            return item;
        }
    }
    return nullptr;
}

void DnsDomainsGroup::setLoggedIn(bool loggedIn)
{
    newAddressItem_->setClickable(loggedIn);
    for (DnsDomainAddressItem *item: addresses_.keys())
        item->setClickable(loggedIn);
}

}
