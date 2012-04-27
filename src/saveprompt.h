/* Saveprompt.h
 * This class has 4 main purposes
 * 1. Warns the user that he/she may lose
 *      unsaved progress on the current file, and gives
 *      the following three options:
 * 2. Save the file and exit (return value = 1)
 * 3. Exit without saving    (return value = -1)
 * 4. Cancel the exit command(return value = 0)
 * the return value should be passed back to the main window,
 * which will proceed based on the user's choice.
 */
#ifndef SAVEPROMPT_H
#define SAVEPROMPT_H

#include <QWidget>
#include <QtGui>
#include <QDialog>

class savePrompt : public QDialog
{
    Q_OBJECT
public:
    savePrompt();
    ~savePrompt();
private:
    QPushButton *m_savequitButton, *m_quitButton, *m_cancelButton;

private slots:
    void saveQuit();
    void quit();
    void cancel();
    void init();

};

#endif // SAVEPROMPT_H
