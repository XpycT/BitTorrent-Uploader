#include "bbcodewidget.h"
#include <qtcolorcombobox.h>
#include <QtGui>

BBCodeWidget::BBCodeWidget(QWidget *parent)
{
    toolbar1 = new QToolBar(this);
    toolbar1->setIconSize(QSize(16,16));
    toolbar2 = new QToolBar(this);
    toolbar2->setIconSize(QSize(16,16));

    createActions();

    this->setStyleSheet("QPlainTextEdit {font: 14px Courier New;}");
    setViewportMargins(0, toolbar1->sizeHint().height()*2+1, 0, 0);
    setContentsMargins(0, toolbar1->sizeHint().height()*2, 0, 0);
}

void BBCodeWidget::createActions(){
    b = new QAction(QPixmap(":/images/BBCode/text_bold.png"), tr("Bold"), this);
    i = new QAction(QPixmap(":/images/BBCode/text_italic.png"), tr("Italic"), this);
    u = new QAction(QPixmap(":/images/BBCode/text_underline.png"), tr("Underline"), this);
    s = new QAction(QPixmap(":/images/BBCode/text_strikethrough.png"), tr("Strike through"), this);

    al = new QAction(QPixmap(":/images/BBCode/text_align_left.png"), tr("Align left"), this);
    ar = new QAction(QPixmap(":/images/BBCode/text_align_right.png"), tr("Align right"), this);
    ac = new QAction(QPixmap(":/images/BBCode/text_align_center.png"), tr("Center"), this);
    aj = new QAction(QPixmap(":/images/BBCode/text_align_justify.png"), tr("Justify"), this);

    code    = new QAction(QPixmap(":/images/BBCode/page_white_code.png"), tr("Code"), this);
    php     = new QAction(QPixmap(":/images/BBCode/page_white_php.png"), tr("PHP-code"), this);
    spoiler = new QAction(QPixmap(":/images/BBCode/page_white_key.png"), tr("Hidden text (simple)"), this);
    spoiler_alt = new QAction(QPixmap(":/images/BBCode/page_white_key.png"), tr("Hidden text (alternative)"), this);
    quote = new QAction(QPixmap(":/images/BBCode/comment.png"), tr("Quote (simple)"), this);
    quote_alt = new QAction(QPixmap(":/images/BBCode/comment_add.png"), tr("Quote (alternative)"), this);

    link = new QAction(QPixmap(":/images/BBCode/link_add.png"), tr("Insert link"), this);
    mail = new QAction(QPixmap(":/images/BBCode/email_add.png"), tr("Insert email"), this);
    img = new QAction(QPixmap(":/images/BBCode/image_add.png"), tr("Insert image"), this);

    hr = new QAction(QPixmap(":/images/BBCode/text_horizontalrule.png"), tr("Insert horizontal rule"), this);
    li = new QAction(QPixmap(":/images/BBCode/text_list_bullets.png"), tr("Insert a list item"), this);

    QMenu *menuspoiler = new QMenu("spoiler");
    menuspoiler->addAction(spoiler_alt);
    spoiler->setMenu(menuspoiler);

    QMenu *menuquote = new QMenu("quote");
    menuquote->addAction(quote_alt);
    quote->setMenu(menuquote);

    fcb = new QFontComboBox(this);
    fcb->setEditable(false);
    connect(fcb, SIGNAL(activated(int)), this, SLOT(setFont()));
    toolbar2->addWidget(fcb);

    fsp = new QComboBox(this);
    toolbar2->addWidget(fsp);
    connect(fsp, SIGNAL(activated(const QString &)), this, SLOT(setFont_h()));
    foreach(int s, QFontDatabase::standardSizes())
    fsp->addItem(tr("Size %1").arg(QString::number(s)));

    combo = new QtColorComboBox;
    combo->setStandardColors();
    combo->setCurrentColor(Qt::black);
    combo->setColorDialogEnabled(true);
    connect(combo, SIGNAL(activated(const QColor &)), this, SLOT(setColor(const QColor &)));
    toolbar2->addWidget(combo);

    toolbar2->addSeparator();
    toolbar2->addAction(li);
    toolbar2->addAction(hr);


    QActionGroup *bbGroup = new QActionGroup(this);
    bbGroup->addAction(b);
    bbGroup->addAction(i);
    bbGroup->addAction(u);
    bbGroup->addAction(s);

    bbGroup->addAction(al);
    bbGroup->addAction(ar);
    bbGroup->addAction(ac);
    bbGroup->addAction(aj);

    bbGroup->addAction(code);
    bbGroup->addAction(php);
    bbGroup->addAction(spoiler);
    bbGroup->addAction(spoiler_alt);
    bbGroup->addAction(quote);
    bbGroup->addAction(quote_alt);

    bbGroup->addAction(link);
    bbGroup->addAction(mail);
    bbGroup->addAction(img);    

    bbGroup->addAction(hr);
    bbGroup->addAction(li);
    //////

    toolbar1->addAction(b);
    toolbar1->addAction(i);
    toolbar1->addAction(u);
    toolbar1->addAction(s);
    toolbar1->addSeparator();

    toolbar1->addAction(al);
    toolbar1->addAction(ac);
    toolbar1->addAction(ar);
    toolbar1->addAction(aj);
    toolbar1->addSeparator();

    toolbar1->addAction(code);
    toolbar1->addAction(php);
    toolbar1->addAction(spoiler);
    toolbar1->addAction(quote);
    toolbar1->addSeparator();

    toolbar1->addAction(link);
    toolbar1->addAction(mail);
    toolbar1->addAction(img);

    connect(bbGroup, SIGNAL(triggered(QAction *)), this, SLOT(addTag(QAction*)));

    setViewportMargins(0, toolbar1->sizeHint().height()+1, 0, 0);
    setContentsMargins(0, toolbar1->sizeHint().height(), 0, 0);
}

void BBCodeWidget::addTag(QAction* a){

    if(a == b){
            insertDoubleTag("b");
    }else if(a == i){
            insertDoubleTag("i");
    }else if(a == u){
            insertDoubleTag("u");
    }else if(a == s){
            insertDoubleTag("s");
    }else if(a == al){
            insertDoubleTag("left");
    }else if(a == ar){
            insertDoubleTag("right");
    }else if(a == ac){
            insertDoubleTag("center");
    }else if(a == aj){
            insertDoubleTag("justify");
    }else if(a == code){
            insertDoubleTag("code");
    }else if(a == php){
            insertDoubleTag("php");
    }else if(a == spoiler){
            insertDoubleTag("spoiler");
    }else if(a == spoiler_alt){
            QString name=QInputDialog::getText(0,tr("Enter title"),
                                               tr("Enter spoiler title:"));
            if(!name.isEmpty())
                insertDoubleTag("spoiler",name);
    }else if(a == quote){
            insertDoubleTag("quote");
    }else if(a == quote_alt){
            QString name=QInputDialog::getText(0,tr("Enter name"),
                                               tr("Enter user name:"));
            if(!name.isEmpty())
                insertDoubleTag("quote",name);
    }else if(a == link){
            QString name=QInputDialog::getText(0,tr("Enter link"),
                                               tr("Enter link:"), QLineEdit::Normal,
                                               "http://");
            if(!name.isEmpty())
                insertDoubleTag("url",name);
    }else if(a == mail){
            insertDoubleTag("mail");
    }else if(a == img){
            insertDoubleTag("img");
    }else if(a == hr){
            insertSingleTag("hr");
    }else if(a == li){
            insertSingleTag("li");
    }
}
void BBCodeWidget::insertDoubleTag(const QString &tag,QString opt){
    QTextCursor cursor(this->textCursor());
    QString s=cursor.selectedText();
    cursor.beginEditBlock();
    if(opt.isEmpty())
        cursor.insertText("["+tag+"]");
    else
        cursor.insertText("["+tag+"="+opt+"]");
    cursor.insertText(s);
    cursor.insertText("[/"+tag+"]");
    cursor.endEditBlock();
}
void BBCodeWidget::insertSingleTag(const QString &tag,QString opt){
    QTextCursor cursor(this->textCursor());
    QString s=cursor.selectedText();
    cursor.beginEditBlock();
    if(opt.isEmpty())
        cursor.insertText("["+tag+"]");
    else
        cursor.insertText("["+tag+"="+opt+"]");
    cursor.insertText(s);
    cursor.endEditBlock();
}
void BBCodeWidget::setFont(){
    QString f = fcb->currentText();
    insertDoubleTag("family",f);
    setFocus();
}
void BBCodeWidget::setFont_h(){
    QString f = fsp->currentText();
    QRegExp rx("(\\d+)");
    rx.indexIn(f);
    insertDoubleTag("size",rx.cap(1));
    setFocus();
}
void BBCodeWidget::setColor(const QColor &color){
    insertDoubleTag("color",color.name());
    setFocus();
}
void BBCodeWidget::resizeEvent(QResizeEvent *re){
    toolbar1->setGeometry(1,1,width()-1,
                          toolbar1->sizeHint().height());
    toolbar2->setGeometry(1,toolbar1->sizeHint().height()+1,width()-1,
                          toolbar1->sizeHint().height());
    QPlainTextEdit::resizeEvent(re);
    QRect geo = verticalScrollBar()->geometry();
    geo.setTop(toolbar1->geometry().bottom()*2+2);
    verticalScrollBar()->setGeometry(geo);
}
