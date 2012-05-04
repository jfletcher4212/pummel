#ifndef HINTBOX_H
#define HINTBOX_H

#include <QWidget>
#include <QtGui>

class HintBox : public QWidget
{
    Q_OBJECT
public:
    HintBox();
    ~HintBox();

private:
    QTextEdit *m_textBox;
    QPushButton *m_okButton;
    void initMembers();

private slots:
    void acknowledge();

};

#endif // HINTBOX_H
