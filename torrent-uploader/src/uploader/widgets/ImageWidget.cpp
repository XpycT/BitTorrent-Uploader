#include "ImageWidget.h"

ImageWidget::ImageWidget(QWidget *parent): i_manager(0)
{    
    setButton(None);
    setMouseTracking(true);
    setAttribute(Qt::WA_StaticContents);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setAcceptDrops(true);
    setAttribute(Qt::WA_StaticContents, true);
    setAttribute(Qt::WA_OpaquePaintEvent, true);
    setAttribute(Qt::WA_NoSystemBackground, true);

    pic_add =QImage(":/images/image_add.png");
    pic_del =QImage(":/images/image_delete.png");

    connect(&i_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(handleNetworkData(QNetworkReply*)));
    connect(&http, SIGNAL(done(bool)), this, SLOT(httpDone(bool)));

}
/*virtual*/ QSize ImageWidget::sizeHint() const
{
return QSize(180, 180);
}
void ImageWidget::resizeEvent(QResizeEvent *event)
{
    if(!i_imageOriginal.isNull()){
        i_image = i_imageOriginal.scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        qDebug() << QString("[Zoom %1%] ").arg(i_image.width() * 100 / i_imageOriginal.width());
   }
    update();
}
void ImageWidget::setButton(Mode mode)
{
   currentMode=mode;
}
void ImageWidget::handleNetworkData(QNetworkReply *networkReply)
{
    QImage image;

    qDebug() << "Received" << networkReply->size() << "bytes";
    QUrl url = networkReply->url();    
    if (networkReply->error()) {
        i_fileName = QString();
        qDebug() << "Can't download" << url.toString()
                 << ":" << networkReply->errorString();
    } else {
        i_fileName = url.toString();
        if (url.scheme() == "http") {
            getFile(QUrl(i_fileName));
    }
        if (url.scheme() == "file"){
            QString tmpUrl = url.toLocalFile().toLower();
            if(tmpUrl.endsWith(".jpg")  ||  tmpUrl.endsWith(".png")  ||
               tmpUrl.endsWith(".gif")  ||  tmpUrl.endsWith(".bmp") ){
                i_fileName = QFileInfo(tmpUrl).absoluteFilePath();
            }else{
                i_fileName ="";
            }
        }         
       image.load(networkReply, 0);
    }

    networkReply->deleteLater();
    loadImage(image);
}
bool ImageWidget::getFile(const QUrl &url)
{
    if (!url.isValid()) {
        qDebug() << "Error: Invalid URL";
        return false;
    }

    if (url.scheme() != "http") {
        qDebug() << "Error: URL must start with 'http:'";
        return false;
    }

    if (url.path().isEmpty()) {
        qDebug() << "Error: URL has no path";
        return false;
    }

    QString localFileName = QFileInfo(url.path()).fileName();
    if (localFileName.isEmpty())
        localFileName = "httpget.out";

    file.setFileName(QDir::tempPath()+"/"+localFileName);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Error: Cannot open " << qPrintable(file.fileName())
             << " for writing: " << qPrintable(file.errorString());
        return false;
    }        
    http.setHost(url.host(), url.port(80));
    http.get(url.path(), &file);
    http.close();
    return true;
}
void ImageWidget::httpDone(bool error)
{
    if (error) {
        qDebug() << "Error: " << qPrintable(http.errorString());
    } else {
        qDebug() << "File downloaded as " << qPrintable(file.fileName());
        i_fileName=file.fileName();
    }
    file.close();
    emit done();
}
void ImageWidget::loadImage(const QImage &image)
{

    i_image = image;
    i_imageOriginal =image;
    if (i_image.isNull()) {
        qDebug() << QString("Can not load %1").arg(i_fileName);
    } else {
            qDebug() << "Rescaling image....";
            int w = i_imageOriginal.width();
            i_image = i_image.scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
           qDebug() << QString("[Zoom %1%] ").arg(i_image.width() * 100 / w);
    }
    update();
}

void ImageWidget::loadImage(const QString &fileName)
{
    i_fileName = fileName;
    loadImage(QImage(fileName));
    emit imageAdded();
}
void ImageWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/uri-list"))
            event->acceptProposedAction();
}
void ImageWidget::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.count()) {
        QUrl url = urls[0];
        if (event->mimeData()->hasImage()) {            
            QImage img = qvariant_cast<QImage>(event->mimeData()->imageData());
            i_fileName = url.toString();           
            loadImage(img);           
        }else {
            i_manager.get(QNetworkRequest(url));
            setWindowTitle(QString("Loading %1...").arg(url.toString()));
        }

        event->acceptProposedAction();
    }
}
void ImageWidget::paintEvent(QPaintEvent *event)
{       
    QRect panel(0,rect().height()-30,rect().width(),rect().height());

        QLinearGradient gradient(0, 0, 0, height());
        gradient.setSpread(QGradient::PadSpread);
        gradient.setColorAt(0, QColor(247, 247, 247, 255));
        gradient.setColorAt(1, QColor(187, 187, 187, 255));

    QPainter painter(this);
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    if (!i_image.isNull()){
        painter.fillRect(rect(),QBrush(gradient));
        painter.drawImage(0, 0, i_image);
    }
    else       
    {        

        painter.fillRect(rect(),QBrush(gradient));
        painter.setPen(QPen(Qt::gray,3,Qt::SolidLine));
        painter.setFont(QFont("Stencil Std",20,QFont::Bold));
        painter.drawText(rect(), Qt::AlignCenter, tr("No image"));
    }
        if(underMouse())
        {
        painter.setOpacity(0.4);
        painter.setPen(QPen(Qt::black,0,Qt::NoPen));
        painter.setBrush(Qt::black);
        painter.drawRect(panel);
        painter.setOpacity(1.0);
        painter.setClipRect(panel);
        painter.setPen(QPen(Qt::white,10,Qt::SolidLine));
        painter.setFont(QFont("Counter",10,QFont::Bold));

        painter.drawText(10,rect().height()-10,
                         (!i_image.isNull())?QString("%1x%2")
                         .arg(i_imageOriginal.width())
                         .arg(i_imageOriginal.height()):"");

        painter.setPen(QPen(Qt::black,1,Qt::SolidLine));
        switch(currentMode){
        case Open:
        if (!i_image.isNull()){
        painter.drawRoundRect(rect().width()-pic_add.width()-26,
                          rect().height()-23,18,
                          18,3,3);
        }else{
        painter.drawRoundRect(rect().width()-pic_add.width()-6,
                          rect().height()-23,18,
                          18,3,3);
        }
        break;
        case Clear:
        if (!i_image.isNull()){
        painter.drawRoundRect(rect().width()-pic_add.width()-6,
                          rect().height()-23,18,
                          18,3,3);
        }
        break;
        case None:
        break;
        }

        if (!i_image.isNull()){
            painter.drawImage(rect().width()-pic_add.width()-25,
                          rect().height()-22,pic_add);
            painter.drawImage(rect().width()-pic_add.width()-5,
                          rect().height()-22,pic_del);
        }else{
            painter.drawImage(rect().width()-pic_add.width()-5,
                          rect().height()-22,pic_add);
        }

        }
        painter.restore();
}


void ImageWidget::enterEvent(QEvent *event)
{
    update();
}
void ImageWidget::leaveEvent(QEvent *event)
{
    update();
}
void ImageWidget::mouseMoveEvent(QMouseEvent *event)
{
    mousePos = event->pos();
    if((mousePos.x() > (rect().width()-16-25)) &
       (mousePos.x() < (rect().width()-25))    &
       (mousePos.y() > (rect().height()-22))   &
       (mousePos.y() < (rect().height()-6)))
    {
        if (!i_image.isNull()){
            setCursor(Qt::PointingHandCursor);
            setButton(Open);
        }
    }else if((mousePos.x() > (rect().width()-16-5)) &
       (mousePos.x() < (rect().width()-5))    &
       (mousePos.y() > (rect().height()-22))   &
       (mousePos.y() < (rect().height()-6)))
    {
        setCursor(Qt::PointingHandCursor);
        if (!i_image.isNull()){
            setButton(Clear);
        }else{
            setButton(Open);
        }
    }else{        
        setCursor(Qt::ArrowCursor);
        setButton(None);
    }
    update();
}
void ImageWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){        
        switch(currentMode){
        case Open:
        {
          QString fileName = QFileDialog::getOpenFileName(this,tr("Select Image"),
                                       QApplication::applicationDirPath(),
                                       tr("Image Files (*.jpg *.jpeg *.png *.gif)"));

          if(fileName.isEmpty())
            return;
          else{
             loadImage(fileName);
         }
        }
        break;
        case Clear:
            i_fileName.clear();
            i_image = QImage("");
            i_imageOriginal= QImage("");
            break;
        case None:
        break;
    }
    update();
}else if(event->button() == Qt::RightButton)
    QMessageBox::information(this,"",i_fileName);

}
void ImageWidget::mouseReleaseEvent(QMouseEvent* event)
{
}
