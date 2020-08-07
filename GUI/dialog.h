#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <vector>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget*, std::vector<std::vector<double>>, int);
    ~Dialog();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
