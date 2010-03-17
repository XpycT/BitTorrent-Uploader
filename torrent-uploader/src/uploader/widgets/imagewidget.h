#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H
#include <QtGui>
#include <QtNetwork>

class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    ImageWidget(QWidget *parent=0);
    void loadImage(const QString &file);
    void loadImage(const QImage &image);
    enum Mode{Open,Clear,None};
    QString getFileName() const	{ return i_fileName; }
    bool getFile(const QUrl &url);
    QSize sizeHint() const;
signals:
    void done();
    void imageAdded();
public slots:
    void handleNetworkData(QNetworkReply *networkReply);
private slots:
    void httpDone(bool error);
protected:
    void dragEnterEvent(QDragEnterEvent*);
    void dropEvent(QDropEvent *event);
    void paintEvent(QPaintEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    void setButton(Mode mode);
    QString i_fileName;
    QImage i_image;
    QImage pic_add;
    QImage pic_del;
    QImage i_imageOriginal;
    QPoint mousePos;
    QNetworkAccessManager i_manager;
    QHttp http;
    QFile file;
    Mode currentMode;
};
#endif // IMAGEWIDGET_H
