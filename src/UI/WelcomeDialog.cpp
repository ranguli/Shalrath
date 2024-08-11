// NOLINTBEGIN
#include <QMessageBox>
// NOLINTEND

#include "WelcomeDialog.h"

WelcomeDialog::WelcomeDialog(QWidget *parent) : QMessageBox(parent) {

    setIcon(QMessageBox::Information);
    setWindowTitle(tr("Welcome"));
    setText(tr("Welcome to Shalrath!"));

    addButton(QMessageBox::Ok);
    addButton(QMessageBox::Cancel);

    setDefaultButton(QMessageBox::Ok);
}