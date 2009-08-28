#ifndef BBCODEWIDGET_H
#define BBCODEWIDGET_H

#include <qtcolorcombobox.h>

#include <QPlainTextEdit>
#include <QToolBar>
#include <QFontComboBox>
#include <QComboBox>
#include <QAction>
class BBCodeWidget : public QPlainTextEdit
{
    Q_OBJECT
public:
    BBCodeWidget(QWidget *parent=0);
private slots:
    void addTag(QAction*);
    void setFont();
    void setFont_h();
    void setColor(const QColor &);
protected:
    void createActions();
    void insertDoubleTag(const QString &tag,QString opt="");
    void insertSingleTag(const QString &tag,QString opt="");
    void resizeEvent(QResizeEvent *re);
    QToolBar *toolbar1,*toolbar2;
    QFontComboBox *fcb;
    QComboBox *fsp;
    QtColorComboBox *combo;
    QAction *b, *i, *u, *s;
    QAction *ac, *al, *ar, *aj;
    QAction *code, *php, *spoiler, *spoiler_alt, *quote, *quote_alt;
    QAction *link, *mail, *img;
    QAction *hr, *li;

};

#endif // BBCODEWIDGET_H
