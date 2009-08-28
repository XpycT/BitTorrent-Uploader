#ifndef PREVIEWDIALOG_H
#define PREVIEWDIALOG_H

#include <QDialog>
class QWebView;

class PreviewDialog : public QDialog
{
    Q_OBJECT
public:
    PreviewDialog(QWidget *parent=0,QString &content="");
private:
    QWebView *view;
};

#endif // PREVIEWDIALOG_H
