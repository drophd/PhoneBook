#include "addrecorddialog.h"
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QDateEdit>
#include <QMessageBox>

AddRecordDialog::AddRecordDialog(QWidget *parent)
    : QDialog{parent}
    , fullnameEdit(new QLineEdit(this))
    , birthdayEdit(new QDateEdit(this))
    , emailEdit(new QLineEdit(this))
    , m_buttonBox(new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this))
{
    setWindowTitle(tr("Добавить запись"));

    QFormLayout *form = new QFormLayout;
    form->addRow(tr("ФИО:"), fullnameEdit);
    form->addRow(tr("Почта:"), emailEdit);
    form->addRow(tr("День рождения:"), birthdayEdit);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addLayout(form);
    layout->addWidget(m_buttonBox);

    connect(m_buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(m_buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

AddRecordDialog::~AddRecordDialog() = default;

void AddRecordDialog::accept()
{
    const QString name = fullnameEdit->text().trimmed();
    if (name.isEmpty()) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Введите ФИО"));
        fullnameEdit->setFocus();
        return;
    }

    m_record.fullName = name;
    m_record.email = emailEdit->text().trimmed();
    m_record.birthday = birthdayEdit->date();
    QDialog::accept();
}

void AddRecordDialog::setRecord(const ::record &r)
{
    setWindowTitle(tr("Изменить запись"));

    fullnameEdit->setText(r.fullName);
    emailEdit->setText(r.email);
    birthdayEdit->setDate(r.birthday);
}
