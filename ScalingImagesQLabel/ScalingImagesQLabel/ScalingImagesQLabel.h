#pragma once

#include <qmainwindow.h>
#include "ui_ScalingImagesQLabel.h"

class ScalingImagesQLabel : public QMainWindow
{
  Q_OBJECT

public:
  explicit ScalingImagesQLabel(QWidget *parent = nullptr);

private:
  Ui::ScalingImagesQLabelClass ui;
};
