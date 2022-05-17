#include <QMouseEvent>
#include <QPainter>
#include <QImage>
#include <QPixmap>
#include "mainwindow.h"
#include "wgtimage.h"
#include "ui_wgtimage.h"

wgtImage::wgtImage(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::wgtImage)
{
    ui->setupUi(this);

    this->setMouseTracking(true);
    this->setStyleSheet("background-color:black;");
}

wgtImage::~wgtImage()
{
    delete ui;
}

void wgtImage::setMainWindow(MainWindow* wnd)
{
    mMainWnd = wnd;
}


void wgtImage::setStep(int stp)
{
    mStep = stp;
}

void wgtImage::setImage(QImage &image)
{
    mStartPoint = mEndPoint = QPoint(0, 0);
    mSrcImage = image;
    QImage img = mSrcImage.scaled(width(), height(), Qt::KeepAspectRatio);
    mScaledPixmap = QPixmap::fromImage(img);
    update();

    mStep = 0;
}

void wgtImage::resizeEvent(QResizeEvent *event)
{
    QLabel::resizeEvent(event);

    if(mSrcImage.isNull())
        return;

    QImage img = mSrcImage.scaled(event->size().width(), event->size().height(), Qt::KeepAspectRatio);
    mScaledPixmap = QPixmap::fromImage(img);
}

void wgtImage::mousePressEvent(QMouseEvent *event)
{
    return QWidget::mousePressEvent(event);
}

void wgtImage::mouseMoveEvent(QMouseEvent* event)
{
    mMainWnd->setPos(event->pos().x(), event->pos().y());

    if(mStep == 1)
    {
        mEndPoint = event->pos();
        update();

        QString s = QString("%1 %2 %3 %4").arg(mStartPoint.x()).arg(mEndPoint.x());
        mMainWnd->setLog(s);
    }

    return QWidget::mouseMoveEvent(event);
}

void wgtImage::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if(mStep == 0)
        {
            mStartPoint = event->pos();
            if(mStartPoint.x() <= 10)
                mStartPoint.setX(0);
            mStep = 1;
        }
        else if(mStep == 1)
        {
            mEndPoint = event->pos();
            mStep = 0;

            mMainWnd->updateCoverThumb();
        }
    }

    return QWidget::mouseReleaseEvent(event);
}

void wgtImage::paintEvent(QPaintEvent *event)
{
    mPainter.begin(this);          //进行重绘;

    mPainter.drawPixmap(0, 0, mScaledPixmap);

    mPainter.setPen(QPen(Qt::yellow, 1, Qt::SolidLine, Qt::FlatCap));

    QRect selectedRect = QRect(mStartPoint.x(), 0, mEndPoint.x() - mStartPoint.x(), mScaledPixmap.height());
    mPainter.drawRect(selectedRect);

    mPainter.end();
}

QImage wgtImage::getClipImage()
{
    int left, right;
    left = mStartPoint.x() * mSrcImage.width() / mScaledPixmap.width();
    right = mEndPoint.x() * mSrcImage.width() / mScaledPixmap.width();

    if((right - left) < 50)
    {
        return QImage();
    }

    QImage img = mSrcImage.copy(left, 0, right - left, mSrcImage.height());
    return img;
}

void wgtImage::keyPressEvent(QKeyEvent *event)
{
    // Esc 键退出截图;
    if (event->key() == Qt::Key_Escape)
    {

    }
    // Eeter键完成截图;
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {

    }
}
