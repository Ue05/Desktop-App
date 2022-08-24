#include "persistentstate.h"

#include <QRect>
#include <QSettings>
#include "utils/logger.h"
#include "utils/simplecrypt.h"
#include "types/global_consts.h"
#include "legacy_protobuf_support/legacy_protobuf.h"

void PersistentState::load()
{
    QSettings settings;
    bool bLoaded = false;
    if (settings.contains("guiPersistentState"))
    {
        SimpleCrypt simpleCrypt(SIMPLE_CRYPT_KEY);
        QString str = settings.value("guiPersistentState", "").toString();
        QByteArray arr = simpleCrypt.decryptToByteArray(str);

        QDataStream ds(&arr, QIODevice::ReadOnly);

        quint32 magic, version;
        ds >> magic;
        if (magic == magic_)
        {
            ds >> version;
            if (version <= versionForSerialization_)
            {
                ds >> state_;
                if (ds.status() == QDataStream::Ok)
                {
                    bLoaded = true;
                }
            }
        }
    }
    // try load from legacy protobuf
    // todo remove this code at some point later
    if (!bLoaded && settings.contains("persistentGuiSettings"))
    {
        QByteArray arr = settings.value("persistentGuiSettings").toByteArray();
        bLoaded = LegacyProtobufSupport::loadGuiPersistentState(arr, state_);
    }
    if (!bLoaded)
    {
        state_ = types::GuiPersistentState(); // reset to defaults
    }
    // remove the legacy key of settings
    settings.remove("persistentGuiSettings");
}

void PersistentState::save()
{
    QByteArray arr;
    {
        QDataStream ds(&arr, QIODevice::WriteOnly);
        ds << magic_;
        ds << versionForSerialization_;
        ds << state_;
    }

    SimpleCrypt simpleCrypt(SIMPLE_CRYPT_KEY);
    QSettings settings;
    settings.setValue("guiPersistentState", simpleCrypt.encryptToString(arr));
}

void PersistentState::setFirewallState(bool bFirewallOn)
{
    state_.isFirewallOn = bFirewallOn;
    save();
}

bool PersistentState::isFirewallOn() const
{
    return state_.isFirewallOn;
}

void PersistentState::setCountVisibleLocations(int cnt)
{
    state_.countVisibleLocations = cnt;
    save();
}

int PersistentState::countVisibleLocations() const
{
    return state_.countVisibleLocations;
}

void PersistentState::setFirstLogin(bool bFirstRun)
{
    state_.isFirstLogin = bFirstRun;
    save();
}

bool PersistentState::isFirstLogin()
{
    return state_.isFirstLogin;
}

void PersistentState::setIgnoreCpuUsageWarnings(bool isIgnore)
{
    state_.isIgnoreCpuUsageWarnings = isIgnore;
    save();
}

bool PersistentState::isIgnoreCpuUsageWarnings()
{
    return state_.isIgnoreCpuUsageWarnings;
}

void PersistentState::setLastLocation(const LocationID &lid)
{
    state_.lastLocation = lid;
    save();
}

LocationID PersistentState::lastLocation() const
{
    return state_.lastLocation;
}

void PersistentState::setLastExternalIp(const QString &ip)
{
    state_.lastExternalIp = ip;
    save();
}

QString PersistentState::lastExternalIp() const
{
    return state_.lastExternalIp;
}

void PersistentState::setNetworkWhitelist(const QVector<types::NetworkInterface> &list)
{
    state_.networkWhiteList = list;
    save();
}

QVector<types::NetworkInterface> PersistentState::networkWhitelist() const
{
    return state_.networkWhiteList;
}

PersistentState::PersistentState()
{
    load();
}

bool PersistentState::haveAppGeometry() const
{
    return !state_.appGeometry.isEmpty();
}

void PersistentState::setAppGeometry(const QByteArray &geometry)
{
    state_.appGeometry = geometry;
    save();
}

const QByteArray& PersistentState::appGeometry() const
{
    return state_.appGeometry;
}
