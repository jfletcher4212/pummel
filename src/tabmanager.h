#ifndef TABMANAGER_H
#define TABMANAGER_H

#include <QTabWidget>

class TabManager : public QTabWidget
{
    Q_OBJECT
public:
    explicit TabManager(QWidget *parent = 0);

public slots:
   // void currentChangedSlot(int index);

};

#endif // TABMANAGER_H
