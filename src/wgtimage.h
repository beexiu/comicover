#ifndef WGTIMAGE_H
#define WGTIMAGE_H

#include <QLabel>
#include <QPainter>
#include <QPixmap>

namespace Ui {
class wgtImage;
}

class MainWindow;

class wgtImage : public QLabel
{
    Q_OBJECT

public:
    explicit wgtImage(QWidget *parent = nullptr);
    ~wgtImage();

    void setMainWindow(MainWindow* wnd);

    void setImage(QImage &image);

    void setStep(int stp);

    QImage getClipImage();

protected:
    void resizeEvent(QResizeEvent *event);

private:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    Ui::wgtImage *ui;

    MainWindow *mMainWnd;
    QPoint mStartPoint, mEndPoint;
    QPainter mPainter;

    QImage   mSrcImage;
    QPixmap  mScaledPixmap;

    int      mStep;
};

#endif // WGTIMAGE_H
