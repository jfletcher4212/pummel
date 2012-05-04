/* Saveprompt.cpp
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
#include "saveprompt.h"
#include "global.h"
#include <QBoxLayout>
#include <iostream>
#include <QPainter>

savePrompt::savePrompt()
{
        QPainter painter;
        QLabel *test = new QLabel("Warning, any unsaved changes will be lost!\n Would you like to save?\n", this);
        g_savepromptval = 0;

        m_savequitButton = new QPushButton(tr("Save and Quit"));
        m_quitButton = new QPushButton(tr("Quit without saving"));
        m_cancelButton = new QPushButton(tr("Cancel"));
        test->show();
        QFormLayout *layout = new QFormLayout();
        QBoxLayout *buttonLayout = new QBoxLayout(QBoxLayout::LeftToRight, 0);
        QBoxLayout *labelLayout = new QBoxLayout(QBoxLayout::LeftToRight, 0);

        labelLayout->addWidget(test);
        buttonLayout->addWidget(m_savequitButton);
        buttonLayout->addWidget(m_quitButton);
        buttonLayout->addWidget(m_cancelButton);

        init();



        layout->addRow(labelLayout);
        layout->addRow(buttonLayout);

        this->setLayout(layout);

        this->setWindowModality(Qt::WindowModal);

}

void savePrompt::init()
{

    connect(m_savequitButton, SIGNAL(clicked()), this, SLOT(saveQuit()));
    connect(m_quitButton, SIGNAL(clicked()), this, SLOT(quit()));
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));

}

void savePrompt::saveQuit()
{
     g_savepromptval = 1;
    this->close();
}

void savePrompt::quit()
{
     g_savepromptval = -1;
    this->close();
}

void savePrompt::cancel()
{
     g_savepromptval = 0;
    this->close();
}

savePrompt::~savePrompt()
{
    delete this;
}
