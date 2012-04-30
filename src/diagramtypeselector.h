#ifndef DIAGRAMTYPESELECTOR_H
#define DIAGRAMTYPESELECTOR_H


#include <QWidget>
#include <QtGui>
#include "drawarea.h"

class DiagramTypeSelector : public QDialog
{
    Q_OBJECT
public:
    DiagramTypeSelector();
    ~DiagramTypeSelector();
    DiagramType getType() { return type;
                          }

signals:

public slots:

private:
    void init();

    QPushButton *m_okButton, *m_cancelButton;
    QComboBox *m_typeCombo;
    DiagramType type;

private slots:
    void acknowledge();
    void quit();

};

#endif // DIAGRAMTYPESELECTOR_H
