#ifndef PREVIEWDIALOG_H
#define PREVIEWDIALOG_H

#include <QDialog>
class QWebView;
class QSettings;
class PreviewDialog : public QDialog
{
    Q_OBJECT
public:
    PreviewDialog(QWidget *parent=0,const QString &name=QString()
                  ,const QString &category=QString(),const QString &content=QString()
                  ,const QString &poster=QString(),const QStringList &screens=QStringList());
private:
    QString parseTBDevYuna(const QString &name
                  ,const QString &category,const QString &content
                  ,const QString &poster,const QStringList &screens) const;
    QString parseTBDevYunaContent(const QString &content) const;
    QWebView *view;
    QSettings *m_settings;
};

#endif // PREVIEWDIALOG_H
