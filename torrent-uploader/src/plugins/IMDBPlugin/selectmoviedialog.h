#ifndef SELECTMOVIEDIALOG_H
#define SELECTMOVIEDIALOG_H

#include <QDialog>

class SelectMovieDialog : public QDialog
{
    Q_OBJECT
public:
    SelectMovieDialog(QWidget *parent=0,const QString & content="");
    QString movieID;
private slots:
    void selectMovie();
};

#endif // SELECTMOVIEDIALOG_H
