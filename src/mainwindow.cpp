#include <QMouseEvent>
#include <QBuffer>
#include <QFileDialog>
#include <QMessageBox>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "./quazip/quazip/quazip.h"
#include "./quazip/quazip/quazipfile.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mPosLabel = new QLabel(this);
    ui->statusbar->addWidget(mPosLabel, 1);
    mZipLabel = new QLabel(this);
    ui->statusbar->addWidget(mZipLabel);

    ui->lblImage->setMainWindow(this);

    this->showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setLog(const QString& log)
{
    //ui->lblLog->setText(log);
}


void MainWindow::setPos(int x, int y)
{
    QString s = QString("(%1, %2)").arg(x).arg(y);
    mPosLabel->setText(s);
}

void MainWindow::loadZipFiles(QString sPath)
{
    mZipPath = sPath;

    mCurFile = QFileInfo(sPath).fileName();

    QuaZip zipR(mZipPath);             //设置读取的zip文件
    zipR.open(QuaZip::mdUnzip);             //以读取的方式打开zip文件
    QStringList files = zipR.getFileNameList();
    files.sort(Qt::CaseSensitive);

    ui->listFiles->clear();
    if(files.size() > 0)
    {
        ui->listFiles->addItems(files);

        loadImageFile(&zipR, files.at(0));

        mZipLabel->setText(mCurFile);
    }

    zipR.close();
}


void MainWindow::loadImageFile(QuaZip* quazip, QString sName)
{
    mImgName = sName;
    quazip->setCurrentFile(sName);        //设置要读取的zip内文件
    QuaZipFile fileR(quazip);
    fileR.open(QIODevice::ReadOnly);        //读取方式打开
    QByteArray imgData = fileR.readAll();
    fileR.close();                          //使用后需要关闭
    mImage.loadFromData(imgData);
    ui->lblImage->setImage(mImage);

    QFileInfo fileInfo(mImgName);
    QString fileName = QString("%1-1.%2").arg(fileInfo.completeBaseName()).arg(fileInfo.suffix());
    ui->edtImage->setText(fileName);
}


void MainWindow::on_btnStart_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
            this,
            tr("Choose a zip file."),
            "",
            tr("Compress(*.zip)"));

    if (fileName.isEmpty())
        return;

    loadZipFiles(fileName);

    QFileInfo fileInfo(fileName);
    QString dirPath = fileInfo.dir().absolutePath();
    QStringList sl;
    sl.append("*.zip");
    mZipFileList = fileInfo.dir().entryInfoList(sl, QDir::Files, QDir::SortFlag::Name);

    for(int i =  0; i < mZipFileList.size(); i++)
        printf("%s\n", mZipFileList.at(i).fileName().toLocal8Bit().data());
}

void MainWindow::updateCoverThumb()
{
    QImage img = ui->lblImage->getClipImage();
    img = img.scaled(ui->lblcover->width(), ui->lblcover->height(), Qt::KeepAspectRatio);
    ui->lblcover->setPixmap(QPixmap::fromImage(img));

}

void MainWindow::on_btnSave_clicked()
{
    QImage img = ui->lblImage->getClipImage();

    if(img.isNull())
    {
        QMessageBox::critical(this, "Error", "Image is too small.");
        return;
    }

    QBuffer buff;
    img.save(&buff, "jpg");
    QByteArray imgData = buff.buffer();


    QuaZip zipR(mZipPath);             //设置读取的zip文件
    zipR.open(QuaZip::mdUnzip);             //以读取的方式打开zip文件
    QStringList files = zipR.getFileNameList();
    zipR.close();

    QuaZip zipFile(mZipPath);
    zipFile.open(QuaZip::mdAdd);

    QFileInfo fileInfo(mImgName);

    QString fileName = QString("%1-1.%2").arg(fileInfo.completeBaseName()).arg(fileInfo.suffix());
    if(files.contains(fileName))
    {
        QMessageBox::critical(this, "Error", "File name duplicate.");
        zipFile.close();
    }
    QuaZipFile outFile(&zipFile);
    if(!outFile.open(QIODevice::WriteOnly, QuaZipNewInfo(fileName)))
    {
        if(outFile.getZipError() != UNZ_OK){
            qDebug() << "error ...4";
        }
    }
    outFile.write(imgData.data(), imgData.length());
    if(outFile.getZipError() != UNZ_OK){
        qDebug() << "error ...4";
    }
    outFile.close();

    zipFile.close();

    loadZipFiles(mZipPath);
}


void MainWindow::on_listFiles_currentTextChanged(const QString &currentText)
{
    QuaZip zipR(mZipPath);
    zipR.open(QuaZip::mdUnzip);
    loadImageFile(&zipR, currentText);
    zipR.close();
}


void MainWindow::on_btnNext_clicked()
{
    QList<QFileInfo>::Iterator it = mZipFileList.begin();
    QFileInfo fi;

    for(int i = 0; i < mZipFileList.size(); i++)
    {
        if(mZipFileList.at(i).fileName() == mCurFile)
        {
            printf( "%s\n", mZipFileList.at(i).fileName().toLocal8Bit().data() );

            if(i < mZipFileList.size() - 1)
            {
                loadZipFiles(mZipFileList.at(i+1).absoluteFilePath());
                break;
            }
        }
    }
}

