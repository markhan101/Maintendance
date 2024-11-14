#ifndef ANIMATIONLABEL_H
#define ANIMATIONLABEL_H

#include <QWidget>

namespace Ui {
class AnimationLabel;
}

class AnimationLabel : public QWidget
{
    Q_OBJECT

public:
    explicit AnimationLabel(QWidget *parent = nullptr);
    ~AnimationLabel();

private:
    Ui::AnimationLabel *ui;
};

#endif // ANIMATIONLABEL_H
