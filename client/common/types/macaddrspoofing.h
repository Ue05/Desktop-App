#pragma once

#include <QJsonArray>
#include <QString>
#include "networkinterface.h"
#include "utils/network_utils/network_utils.h"
#ifdef Q_OS_MACOS
#include "utils/macutils.h"
#elif defined(Q_OS_LINUX)
#include "utils/network_utils/network_utils_linux.h"
#endif

namespace types {

struct MacAddrSpoofing
{
    MacAddrSpoofing() :
        isEnabled(false),
        isAutoRotate(false)
    {}

    MacAddrSpoofing(const QJsonObject &json)
    {
        if (json.contains(kJsonIsEnabledProp) && json[kJsonIsEnabledProp].isBool()) {
            isEnabled = json[kJsonIsEnabledProp].toBool();
#ifdef Q_OS_MACOS
            // MacOS 14.4 does not support this feature
            if (MacUtils::isOsVersionAtLeast(14, 4)) {
                isEnabled = false;
            }
#endif
        }

        if (json.contains(kJsonMacAddressProp) && json[kJsonMacAddressProp].isString()) {
            QString str = json[kJsonMacAddressProp].toString();
            if (NetworkUtils::isValidMacAddress(str)) {
                macAddress = str;
            }
        }

        if (json.contains(kJsonIsAutoRotateProp) && json[kJsonIsAutoRotateProp].isBool()) {
            isAutoRotate = json[kJsonIsAutoRotateProp].toBool();
        }

        if (json.contains(kJsonSelectedNetworkInterfaceProp) && json[kJsonSelectedNetworkInterfaceProp].isObject()) {
            selectedNetworkInterface = NetworkInterface(json[kJsonSelectedNetworkInterfaceProp].toObject());
        }

        if (json.contains(kJsonNetworkInterfacesProp) && json[kJsonNetworkInterfacesProp].isArray()) {
            QJsonArray networkInterfacesArray = json[kJsonNetworkInterfacesProp].toArray();
            networkInterfaces.clear();
            for (const QJsonValue &ifaceValue : networkInterfacesArray) {
                if (ifaceValue.isObject()) {
                    NetworkInterface iface(ifaceValue.toObject());
                    networkInterfaces.append(iface);
                }
            }
        }
    }

    bool isEnabled;
    QString macAddress;
    bool isAutoRotate;
    NetworkInterface selectedNetworkInterface;
    QVector<NetworkInterface> networkInterfaces;

    bool operator==(const MacAddrSpoofing &other) const
    {
        return other.isEnabled == isEnabled &&
               other.macAddress == macAddress &&
               other.isAutoRotate == isAutoRotate &&
               other.selectedNetworkInterface == selectedNetworkInterface &&
               other.networkInterfaces == networkInterfaces;
    }

    bool operator!=(const MacAddrSpoofing &other) const
    {
        return !(*this == other);
    }

    QJsonObject toJson() const
    {
        QJsonObject json;

        json[kJsonIsEnabledProp] = isEnabled;
        json[kJsonMacAddressProp] = macAddress;
        json[kJsonIsAutoRotateProp] = isAutoRotate;
        json[kJsonSelectedNetworkInterfaceProp] = selectedNetworkInterface.toJson();

        if (!networkInterfaces.isEmpty()) {
            QJsonArray networkInterfacesArray;
            for (const NetworkInterface& iface : networkInterfaces) {
                networkInterfacesArray.append(iface.toJson());
            }
            json[kJsonNetworkInterfacesProp] = networkInterfacesArray;
        }

        return json;
    }

    friend QDataStream& operator <<(QDataStream &stream, const MacAddrSpoofing &o)
    {
        stream << versionForSerialization_;
        stream << o.isEnabled << o.macAddress << o.isAutoRotate << o.selectedNetworkInterface << o.networkInterfaces;
        return stream;
    }

    friend QDataStream& operator >>(QDataStream &stream, MacAddrSpoofing &o)
    {
        quint32 version;
        stream >> version;
        if (version > o.versionForSerialization_)
        {
            stream.setStatus(QDataStream::ReadCorruptData);
            return stream;
        }
        stream >> o.isEnabled >> o.macAddress >> o.isAutoRotate >> o.selectedNetworkInterface >> o.networkInterfaces;
        return stream;
    }

    void fromIni(const QSettings &settings)
    {
        isEnabled = settings.value(kIniIsEnabledProp, false).toBool();
        macAddress = settings.value(kIniMacAddressProp).toString();
        isAutoRotate = settings.value(kIniIsAutoRotateProp, false).toBool();

#ifdef Q_OS_LINUX
        QString name = settings.value(kIniInterfaceProp).toString();
        NetworkUtils_linux::networkInterfaceByName(name);
#endif
    }

    void toIni(QSettings &settings) const
    {
        settings.setValue(kIniIsEnabledProp, isEnabled);
        settings.setValue(kIniMacAddressProp, macAddress);
        settings.setValue(kIniIsAutoRotateProp, isAutoRotate);
        settings.setValue(kIniInterfaceProp, selectedNetworkInterface.interfaceName);
    }

    friend QDebug operator<<(QDebug dbg, const MacAddrSpoofing &m)
    {
        QDebugStateSaver saver(dbg);
        dbg.nospace();
        dbg << "{isEnabled:" << m.isEnabled << "; ";
        dbg << "macAddress:" << m.macAddress << "; ";
        dbg << "selectedNetworkInterface:" << m.selectedNetworkInterface << "; ";
        dbg << "networkInterfaces:{";
        for (const auto &i : m.networkInterfaces)
        {
            dbg << i;
        }

        dbg << "}";
        return dbg;
    }

private:
    const static inline QString kIniIsEnabledProp = "MACAddressSpoofingEnabled";
    const static inline QString kIniMacAddressProp = "MACAddressSpoofingAddress";
    const static inline QString kIniIsAutoRotateProp = "MACAddressSpoofingAutoRotate";
    const static inline QString kIniInterfaceProp = "MACAddressSpoofingInterface";

    const static inline QString kJsonIsEnabledProp = "isEnabled";
    const static inline QString kJsonMacAddressProp = "macAddress";
    const static inline QString kJsonIsAutoRotateProp = "isAutoRotate";
    const static inline QString kJsonSelectedNetworkInterfaceProp = "selectedNetworkInterface";
    const static inline QString kJsonNetworkInterfacesProp = "networkInterfaces";

    static constexpr quint32 versionForSerialization_ = 1;  // should increment the version if the data format is changed

};

} // types namespace
