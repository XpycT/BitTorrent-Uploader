#ifndef PREVIEWDIALOG_H
#define PREVIEWDIALOG_H

#include <QDialog>
class QWebView;
class QSettings;
class PreviewDialog : public QDialog
{
    Q_OBJECT
public:
    PreviewDialog(QWidget *parent=0,QString &name=""
                  ,QString &category="",QString &content=""
                  ,QString &poster="",QStringList &screens=QStringList());
private:
    QString parseTBDevYuna(QString &name
                  ,QString &category,QString &content
                  ,QString &poster,QStringList &screens) const;
    QString parseTBDevYunaContent(const QString &content) const;
    QWebView *view;
    QSettings *m_settings;
};

#endif // PREVIEWDIALOG_H
