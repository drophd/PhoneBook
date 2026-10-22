#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "phonebookmodel.h"
#include "addrecorddialog.h"
#include <QSortFilterProxyModel>
#include <QMessageBox>
#include <QItemSelectionModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_model(new PhoneBookModel(this))
    , m_proxyModel(new QSortFilterProxyModel(this))
{
    ui->setupUi(this);

    m_proxyModel->setSourceModel(m_model);
    m_proxyModel->setSortRole(Qt::UserRole);
    m_proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    m_proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    m_proxyModel->setFilterKeyColumn(-1);

    ui->tableView->setModel(m_proxyModel);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->sortByColumn(0, Qt::AscendingOrder);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->editRecordPushButton->setEnabled(false);
    ui->deleteRecordPushButton->setEnabled(false);
    connect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged, this, [this]() {
        const bool has = ui->tableView->selectionModel()->hasSelection();
        ui->editRecordPushButton->setEnabled(has);
        ui->deleteRecordPushButton->setEnabled(has);
    });

    connect(ui->searchLineEdit, &QLineEdit::textChanged,
            m_proxyModel, &QSortFilterProxyModel::setFilterFixedString);

    connect(ui->addRecordPushButton, &QPushButton::clicked,
            this, &MainWindow::onAddRecord);
    connect(ui->editRecordPushButton, &QPushButton::clicked,
            this, &MainWindow::onEditRecord);
    connect(ui->deleteRecordPushButton, &QPushButton::clicked,
            this, &MainWindow::onDeleteRecord);
    connect(ui->resetPushButton, &QPushButton::clicked,
            this, &MainWindow::onResetRecords);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAddRecord()
{
    AddRecordDialog dlg(this);
    if (dlg.exec() != QDialog::Accepted)
        return;

    record rec = dlg.result();
    rec.id = m_model->getRecordsCount() + 1;
    rec.dateOfEntry = QDate::currentDate();

    m_model->addRecord(rec);
}

void MainWindow::onResetRecords()
{
    if (QMessageBox::question(this, tr("Сброс"),
                              tr("Вернуть записную книжку к начальному состоянию?")) != QMessageBox::Yes)
        return;

    m_model->resetToInitial();
}

void MainWindow::onEditRecord()
{
    const QModelIndexList sel = ui->tableView->selectionModel()->selectedRows();
    if (sel.isEmpty())
        return;

    const int row = m_proxyModel->mapToSource(sel.first()).row();

    AddRecordDialog dlg(this);
    dlg.setRecord(m_model->recordAt(row));
    if (dlg.exec() != QDialog::Accepted)
        return;

    m_model->updateRecord(row, dlg.result());
}

void MainWindow::onDeleteRecord()
{
    const QModelIndexList selected = ui->tableView->selectionModel()->selectedRows();
    if (selected.isEmpty())
        return;

    if (QMessageBox::question(this, tr("Удаление"),
                              tr("Удалить выбранную запись?")) != QMessageBox::Yes)
        return;

    const int row = m_proxyModel->mapToSource(selected.first()).row();
    m_model->removeRow(row);
}