#ifndef PREVIEWDIALOG_H
#define PREVIEWDIALOG_H

#include <QDialog>
class QWebView;

class PreviewDialog : public QDialog
{
    Q_OBJECT
public:
    PreviewDialog(QWidget *parent=0,QString &name=""
                  ,QString &category="",QString &content=""
                  ,QString &poster="",QStringList &screens=QStringList());
private:
    QWebView *view;
};

#endif // PREVIEWDIALOG_H
