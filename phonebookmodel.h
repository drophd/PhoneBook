#ifndef PHONEBOOKMODEL_H
#define PHONEBOOKMODEL_H
#include <QDate>
#include <QString>
#include <QVector>

#include <QAbstractTableModel>

struct record{
    int id;
    QString fullName;
    QString email;
    QDate birthday;
    QDate dateOfEntry;

} ;

class PhoneBookModel : public QAbstractTableModel
{
private:
    static QVector<record> initialRecords();
    QVector<record> records;
public:
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    record recordAt(int row) const;
    bool updateRecord(int row, const record &rec);
    int getRecordsCount();
    explicit PhoneBookModel(QObject *parent = nullptr);
    void addRecord(record record);
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    void resetToInitial();



signals:
};

#endif // PHONEBOOKMODEL_H
