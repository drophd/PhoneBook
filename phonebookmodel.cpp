#include "phonebookmodel.h"
#include <QVector>

PhoneBookModel::PhoneBookModel(QObject *parent)
    : QAbstractTableModel(parent)
    , records(initialRecords())
{
}

QVector<record> PhoneBookModel::initialRecords()
{
    return {
             { 1,  QStringLiteral("Иван Петров"),       QStringLiteral("ivan.petrov@mail.ru"),     QDate(1990, 5, 12),  QDate(2024, 1, 10) },
             { 2,  QStringLiteral("Мария Сидорова"),    QStringLiteral("m.sidorova@gmail.com"),    QDate(1985, 11, 3),  QDate(2024, 2, 15) },
             { 3,  QStringLiteral("Алексей Кузнецов"),  QStringLiteral("alex.kuz@yandex.ru"),      QDate(1998, 7, 21),  QDate(2024, 3, 1)  },
             { 4,  QStringLiteral("Ольга Смирнова"),    QStringLiteral("olga.smirnova@mail.ru"),   QDate(1993, 2, 8),   QDate(2024, 3, 20) },
             { 5,  QStringLiteral("Дмитрий Волков"),    QStringLiteral("d.volkov@gmail.com"),      QDate(1988, 9, 30),  QDate(2024, 4, 5)  },
             { 6,  QStringLiteral("Анна Морозова"),     QStringLiteral("anna.morozova@yandex.ru"), QDate(1995, 3, 17),  QDate(2024, 4, 22) },
             { 7,  QStringLiteral("Сергей Новиков"),    QStringLiteral("s.novikov@mail.ru"),       QDate(1982, 12, 1),  QDate(2024, 5, 9)  },
             { 8,  QStringLiteral("Екатерина Лебедева"),QStringLiteral("e.lebedeva@gmail.com"),     QDate(1991, 6, 25),  QDate(2024, 5, 30) },
             { 9,  QStringLiteral("Павел Соколов"),     QStringLiteral("pavel.sokolov@mail.ru"),   QDate(1987, 1, 14),  QDate(2024, 6, 11) },
             { 10, QStringLiteral("Наталья Попова"),    QStringLiteral("n.popova@yandex.ru"),      QDate(1996, 8, 19),  QDate(2024, 6, 28) },
             };
}

void PhoneBookModel::resetToInitial()
{
    beginResetModel();
    records = initialRecords();
    endResetModel();
}

int PhoneBookModel::rowCount(const QModelIndex &parent) const
{
    if ( parent.isValid() )
        return 0;
    return records.size();

}
int PhoneBookModel::columnCount(const QModelIndex &parent) const
{
    if ( parent.isValid() )
        return 0;
    return 5;
}

record PhoneBookModel::recordAt(int row) const
{
    return records.value(row);
}

bool PhoneBookModel::updateRecord(int row, const record &rec)
{
    if (row < 0 || row >= records.size())
        return false;


    records[row].fullName = rec.fullName;
    records[row].email    = rec.email;
    records[row].birthday = rec.birthday;

    emit  dataChanged(index(row, 0), index(row, columnCount(QModelIndex()) - 1));
    return true;
}

QVariant PhoneBookModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= records.size())
        return {};

    const record &r = records.at(index.row());
    const int col = index.column();

    switch (role) {
    case Qt::DisplayRole:
        switch (col) {
        case 0: return r.id;
        case 1: return r.fullName;
        case 2: return r.email;
        case 3: return r.birthday.toString(QStringLiteral("dd.MM.yyyy"));
        case 4: return r.dateOfEntry.toString(QStringLiteral("dd.MM.yyyy"));
        }
        break;

    case Qt::UserRole:
        switch (col) {
        case 0: return r.id;
        case 1: return r.fullName;
        case 2: return r.email;
        case 3: return r.birthday;
        case 4: return r.dateOfEntry;
        }
        break;
    }

    return {};
}

QVariant PhoneBookModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return {};

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0: return QStringLiteral("ID");
        case 1: return QStringLiteral("ФИО");
        case 2: return QStringLiteral("Email");
        case 3: return QStringLiteral("Дата рождения");
        case 4: return QStringLiteral("Дата записи");
        default: return {};
        }
    }
    return QVariant();
}

void PhoneBookModel::addRecord(const record rec)
{
    beginInsertRows(QModelIndex(), records.size(), records.size());
    records.append(rec);
    endInsertRows();
}

bool PhoneBookModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (parent.isValid() || count <= 0 || row < 0 || row + count > records.size())
        return false;

    beginRemoveRows(parent, row, row + count - 1);
    records.remove(row, count);
    endRemoveRows();

    for (int i = row; i < records.size(); ++i)
        records[i].id = i + 1;

    if (row < records.size())
        emit dataChanged(index(row, 0), index(records.size() - 1, 0), {Qt::DisplayRole});

    return true;
}

int PhoneBookModel::getRecordsCount() {
    return records.size();
}


