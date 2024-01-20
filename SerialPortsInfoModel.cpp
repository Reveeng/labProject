#include "SerialPortsInfoModel.h"
#include <QSerialPortInfo>
#include <QDebug>

SerialPortInfoModel::SerialPortInfoModel(QObject *parent):
    QAbstractListModel(parent),
    m_availablePorts(QSerialPortInfo::availablePorts())
{
    for (auto &p : m_availablePorts){
        qDebug() << p.portName();
    }
}

SerialPortInfoModel::~SerialPortInfoModel()
{

}

int SerialPortInfoModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_availablePorts.size();
}

QVariant SerialPortInfoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }
    if (index.row() >= m_availablePorts.size())
        return QVariant();

    switch (role) {
    case PortRole:
        return m_availablePorts[index.row()].portName();
    case DescriptrionRole:
        return m_availablePorts[index.row()].portName();
    case Enabled:
        return !m_busyPorts.contains(m_availablePorts[index.row()]);
    default:
        return QVariant();
    }
}

bool SerialPortInfoModel::setData(const QModelIndex &index, const QVariant &data, int role)
{
    if (!index.isValid()) {
        return false;
    }

    switch (role) {
    case PortRole:
        return false;
    case DescriptrionRole:
        return false;
    case Enabled:
        changePortBusyMode(index.row(), data.toBool());
        break;
    default:
        return false;
    }

    emit dataChanged(index, index, QVector<int>() << role);
    return true;
}

QHash<int, QByteArray> SerialPortInfoModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[PortRole] = "port";
    roles[DescriptrionRole] = "description";
    roles[Enabled] = "enabled";
    return roles;
}

void SerialPortInfoModel::updateInfo()
{
    beginResetModel();
    endResetModel();
}

void SerialPortInfoModel::changePortBusyMode(int index, bool b)
{
    QSerialPortInfo &p = m_availablePorts[index];
    if (!b){
        m_busyPorts.removeOne(p);
    }else{
        m_busyPorts.push_back(p);
    }
}

bool operator==(const QSerialPortInfo& f, const QSerialPortInfo& s){
    return f.portName() == s.portName();
}
