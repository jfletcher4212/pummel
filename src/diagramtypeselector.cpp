#include "diagramtypeselector.h"

DiagramTypeSelector::DiagramTypeSelector()
{
    m_typeCombo = new QComboBox();
    m_okButton = new QPushButton(tr("OK"));
    m_cancelButton = new QPushButton(tr("Cancel"));

    QFormLayout *layout = new QFormLayout();
    QBoxLayout *buttonLayout = new QHBoxLayout();

    init();

    buttonLayout->addWidget(m_okButton);
    buttonLayout->addWidget(m_cancelButton);

    layout->addRow("Select Diagram Type:", m_typeCombo);
    layout->addRow(buttonLayout);

    this->setLayout(layout);

    this->setWindowModality(Qt::WindowModal);

}

DiagramTypeSelector::~DiagramTypeSelector()
{
    delete m_typeCombo;
}

//
void DiagramTypeSelector::init()
{
    m_typeCombo->addItem("Class");
    m_typeCombo->addItem("State Chart");
    m_typeCombo->addItem("Use Case");

    connect(m_okButton, SIGNAL(clicked()), this, SLOT(acknowledge()));
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}

void DiagramTypeSelector::acknowledge()
{
    //get type from typeCombo
    QString tmp = m_typeCombo->currentText();

    if (tmp.compare("Class") == 0)
        type = Class;
    else if(tmp.compare("State Chart") == 0)
        type = StateChart;
    else if(tmp.compare("Use Case") == 0)
        type = UseCase;
    else        //default
        type = Class;

    quit();
//    this->close();
}

void DiagramTypeSelector::quit()
{
    this->close();
}
