#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class PhoneBookModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void onDeleteRecord();
    void onEditRecord();
    void onAddRecord();
    void onResetRecords();


private:
    Ui::MainWindow *ui;
    PhoneBookModel *m_model;
    QSortFilterProxyModel *m_proxyModel;
};

#endif // MAINWINDOW_H