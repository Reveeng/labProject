#ifndef SERIALPORTSINFOMODEL_H
#define SERIALPORTSINFOMODEL_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QVector>
#include <QAbstractListModel>

class SerialPortInfoModel : public QAbstractListModel
{
Q_OBJECT
public:
    SerialPortInfoModel(QObject *parent = nullptr);
    ~SerialPortInfoModel();

    enum Roles{
        PortRole = Qt::DisplayRole+1,
        DescriptrionRole,
        Enabled
    };

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index,int role) const;
    virtual bool setData(const QModelIndex &index,const QVariant &data, int role);
    virtual QHash<int, QByteArray> roleNames() const;

    void updateInfo();

signals:
    void availablePortsChanged(QStringList &p);

private:
    void changePortBusyMode(int index, bool b);
    QList<QSerialPortInfo> m_availablePorts;
    QList<QSerialPortInfo> m_busyPorts;
};

bool operator==(const QSerialPortInfo& f, const QSerialPortInfo& s);

#endif // SERIALPORTSINFOMODEL_H
