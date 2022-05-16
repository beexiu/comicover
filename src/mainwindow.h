#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QuaZip;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setLog(const QString& log);

    void setPos(int x, int y);

    void updateCoverThumb();

private slots:
    void on_btnStart_clicked();

    void on_btnSave_clicked();

    void on_listFiles_currentTextChanged(const QString &currentText);

private:
    void loadZipFiles(QString sPath);

    void loadImageFile(QuaZip* quazip, QString sName);

private:
    Ui::MainWindow *ui;

    QString   mZipPath;
    QLabel    *mPosLabel;

    QString    mImgName;
    QImage     mImage;
};
#endif // MAINWINDOW_H
