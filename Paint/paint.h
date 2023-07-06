#ifndef PAINT_H
#define PAINT_H

#include <QWidget>

class QPushButton;
class QComboBox;
class QLabel;
class QCheckBox;
class Canvas;
class QGroupBox;
class QButtonGroup;

class Paint : public QWidget
{
	Q_OBJECT

public:
	Paint(QWidget *parent = 0);
	~Paint();

private slots:
	void clearBtnPressed();
    void deleteBtnPressed();
    void colorBtnPressed();
	void primModeChanged();
    void showOutlineOnly(bool);
    void cbShowBBoxPressed(bool);
    void cbCreatePressed();
    void cbDeletePressed();
    void cbChangeColorPressed();
    void cbMovePressed();

private:
	Canvas *viewport;

    QGroupBox *checkBoxGroup;
    QButtonGroup *checkBoxes;
	QPushButton *btnClearCanvas;
	QComboBox *cobPrimModes;
	QLabel *lblPrimModes;
    QLabel *lblSelection;
    QPushButton *btnDeleteObj;
    QPushButton *btnChangeCol;
    QCheckBox *cbOutline;
    QCheckBox *cbBBox;
    QCheckBox *cbCreate;
    QCheckBox *cbDelete;
    QCheckBox *cbChangeColor;
    QCheckBox *cbMove;
};

#endif // PAINT_H
