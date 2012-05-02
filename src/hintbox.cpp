#include "hintbox.h"

HintBox::HintBox()
{
    this->setWindowTitle("Usage Tips");

    //set dialog box to be nonmodal
    this->setWindowModality(Qt::NonModal);

    initMembers();

    QFormLayout *layout = new QFormLayout();

    layout->addWidget(m_textBox);
    layout->addWidget(m_okButton);

    this->setLayout(layout);
}

HintBox::~HintBox()
{
    delete m_textBox;
    delete m_okButton;
}

void HintBox::initMembers()
{
    m_okButton = new QPushButton(tr("OK"));
    connect(m_okButton, SIGNAL(clicked()), this, SLOT(acknowledge()));

    m_textBox = new QTextEdit();
    m_textBox->setDisabled(true);

    QString hints = "";

    hints.append("1. To exit line insertion mode, click on an empty portion of the canvas.\n");
    hints.append("2. Exit using File->Exit\n");
    hints.append("3. Future hints go here!");

    m_textBox->setPlainText(hints);
}

void HintBox::acknowledge()
{
    this->close();
}
