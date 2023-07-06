#include <QPushButton> 
#include <QComboBox>
#include <QLabel>
#include <QColorDialog>
#include <QGridLayout>
#include <QCheckBox>
#include <QDebug>
#include <QButtonGroup>
#include <QGroupBox>
#include "paint.h"
#include "canvas.h"

/** c'tor */
Paint::Paint(QWidget *parent)
    : QWidget(parent)
{
    // instantiate Canvas and button
    viewport = new Canvas();
    checkBoxGroup = new QGroupBox("Selection Tools");
    checkBoxes = new QButtonGroup(checkBoxGroup);
    cbCreate = new QCheckBox("Create objects");
    cbDelete = new QCheckBox("Delete selected");
    cbChangeColor = new QCheckBox("Change color");
    cbMove = new QCheckBox("Move objects");

    checkBoxes->addButton(cbCreate);
    checkBoxes->addButton(cbDelete);
    checkBoxes->addButton(cbChangeColor);
    checkBoxes->addButton(cbMove);



    btnClearCanvas = new QPushButton("&Clear Canvas");
    //cbShowBBox = new QCheckBox("Show all BBox");

    cobPrimModes = new QComboBox();
    cobPrimModes->addItem(tr("None"), Canvas::NONE);
    cobPrimModes->addItem(tr("Line"), Canvas::LINE);
    cobPrimModes->addItem(tr("Freehand"), Canvas::FREE_HAND);
    cobPrimModes->addItem(tr("Circle"), Canvas::CIRCLE);
    cobPrimModes->addItem(tr("Rectangle"), Canvas::RECTANGLE);
    //cobPrimModes->addItem(tr("Triangle"), Canvas::TRIANGLE);
    cobPrimModes->addItem(tr("Polygon"), Canvas::POLYGON);

    lblPrimModes = new QLabel("Primitive Mode");
    lblPrimModes->setBuddy(cobPrimModes);


    btnChangeCol = new QPushButton("&Set Color");

    cbOutline = new QCheckBox("Show Only &Outline", this);

    cbBBox = new QCheckBox("Show all BBox", this);

    // create layout and add gui elements to it
    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->addWidget(viewport,      0, 0, 1, 4);
    mainLayout->addWidget(checkBoxGroup, 1, 0, 5, 2);
    mainLayout->addWidget(cbCreate,      2, 0);
    mainLayout->addWidget(cbDelete,      3, 0);
    mainLayout->addWidget(cbChangeColor, 4, 0);
    mainLayout->addWidget(cbMove,        5, 0);
    mainLayout->addWidget(lblPrimModes,   1, 2, Qt::AlignRight);
    mainLayout->addWidget(cbOutline,      3, 2, Qt::AlignRight);
    mainLayout->addWidget(cbBBox,         5, 2, Qt::AlignRight);
    mainLayout->addWidget(cobPrimModes,   1, 3);
    mainLayout->addWidget(btnChangeCol,   3, 3);
    mainLayout->addWidget(btnClearCanvas, 5, 3);

    // add layout to this widget instance
    setLayout(mainLayout);

    // connect button click event to clear canvas handler
    connect(btnClearCanvas, SIGNAL(clicked()),
            this, SLOT(clearBtnPressed()));
    // connect button click event to delete selected object handler
    connect(btnDeleteObj, SIGNAL(clicked()),
            this, SLOT(deleteBtnPressed()));
    // connect button click event to color chooser handler
    connect(btnChangeCol, SIGNAL(clicked()),
            this, SLOT(colorBtnPressed()));
    // connect list view to primitive changed event handler
    connect(cobPrimModes, SIGNAL(activated(int)),
            this, SLOT(primModeChanged()));
    // connect checkbox to toggle outline event handler
    connect(cbOutline, SIGNAL(toggled(bool)),
            this, SLOT(showOutlineOnly(bool)));
    connect(cbBBox, SIGNAL(toggled(bool)),
            this, SLOT(cbShowBBoxPressed(bool)));
    connect(cbCreate, SIGNAL(clicked()),
            this, SLOT(cbCreatePressed()));
    connect(cbDelete, SIGNAL(clicked()),
            this, SLOT(cbDeletePressed()));
    connect(cbChangeColor, SIGNAL(clicked()),
            this, SLOT(cbChangeColorPressed()));
    connect(cbMove, SIGNAL(clicked()),
            this, SLOT(cbMovePressed()));
}

/** d'tor */
Paint::~Paint()
{
}

/** method for handling button clicked event */
void Paint::clearBtnPressed()
{
    viewport->clearCanvas();

    // force redraw
    update();
    qDebug() << "Clear image called";
}

void Paint::deleteBtnPressed()
{
    // Implementation requires inside test for all objects for selection
    qDebug() << "Next action: delete selected item (NYI)";
}

void Paint::colorBtnPressed()
{
    QColor color = QColorDialog::getColor(Qt::yellow, this );
    if (color.isValid()) {
        qDebug() << "Color Choosen : " << color.name();
        viewport->setCurrColor(color);
    }
}

void Paint::cbShowBBoxPressed(bool show)
{
    viewport->setShowBBox(show);
}

void Paint::showOutlineOnly(bool outline)
{
    qDebug() << "Only show outline: " << outline;
    viewport->setFillMode(outline);
}

void Paint::primModeChanged()
{
    int mode = cobPrimModes->itemData(
                               cobPrimModes->currentIndex(), Qt::UserRole).toInt();
    viewport->setPrimitiveMode(mode);
    qDebug() << "Primitive Mode changed to " << mode;
}

void Paint::cbCreatePressed()
{
    viewport->setInteractionMode(0);
    qDebug() << "Interaction Mode changed to create";
}

void Paint::cbDeletePressed()
{
    viewport->setInteractionMode(1);
    qDebug() << "Interaction Mode changed to delete";
}

void Paint::cbChangeColorPressed()
{
    viewport->setInteractionMode(2);
    qDebug() << "Interaction Mode changed to change color";
}

void Paint::cbMovePressed()
{
    viewport->setInteractionMode(3);
    qDebug() << "Interaction Mode changed to Move";
}
