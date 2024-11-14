#include "animationlabel.h"
#include "ui_animationlabel.h"

AnimationLabel::AnimationLabel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AnimationLabel)
{
    ui->setupUi(this);
}

AnimationLabel::~AnimationLabel()
{
    delete ui;
}
