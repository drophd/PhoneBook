#ifndef ADDRECORDDIALOG_H
#define ADDRECORDDIALOG_H

#include <QDialog>
#include "phonebookmodel.h"

class QLineEdit;
class QDateEdit;
class QDialogButtonBox;

class AddRecordDialog : public QDialog
{
    Q_OBJECT
public:
    void setRecord(const ::record &r);
    explicit AddRecordDialog(QWidget *parent = nullptr);
    ~AddRecordDialog();

    record result() const { return m_record; }

private:
    record m_record;

    QLineEdit *fullnameEdit;
    QDateEdit *birthdayEdit;
    QLineEdit *emailEdit;
    QDialogButtonBox *m_buttonBox;
    void accept();
};

#endif // ADDRECORDDIALOG_H