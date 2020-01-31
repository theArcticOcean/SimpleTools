#ifndef OPENFILEDIALOG_H
#define OPENFILEDIALOG_H

#include <QDialog>

namespace Ui {
class OpenFileDialog;
}

class OpenFileDialog : public QDialog
{
    Q_OBJECT

public:
    ~OpenFileDialog();
    static OpenFileDialog* getInstance();

private slots:
    void on_displayButton_clicked();
    void on_browseButton_clicked();

private:
    explicit OpenFileDialog(QWidget *parent = 0);
    int writePath();
    void readPath();

    static OpenFileDialog *instancePtr;
    Ui::OpenFileDialog *ui;
    QString recordFilePath;
};

#endif // OPENFILEDIALOG_H
