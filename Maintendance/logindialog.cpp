#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent),
                                            ui(new Ui::LoginDialog),
                                            loginPass()
{
    ui->setupUi(this);
    setWindowTitle("Login");
    if (parent)
    {
        resize(parent->size());
    }

    setupTitleAnimation();
}

void LoginDialog::setupTitleAnimation() {
    // Create opacity effect for fade-in
    opacityEffect = new QGraphicsOpacityEffect(this);
    ui->label->setGraphicsEffect(opacityEffect);
    opacityEffect->setOpacity(0.0);

    // Store original position - Adjusted Y coordinate to bring title down
    QPoint originalPos = ui->label->pos();
    originalPos.setY(100);  // Adjust this value to move title down

    // Initial position - still offset by 50px from the new position
    ui->label->move(originalPos.x(), originalPos.y() - 50);

    // Create slide animation
    slideAnimation = new QPropertyAnimation(ui->label, "pos", this);
    slideAnimation->setDuration(1000);  // 1 second
    slideAnimation->setStartValue(ui->label->pos());
    slideAnimation->setEndValue(originalPos);
    slideAnimation->setEasingCurve(QEasingCurve::OutBack);  // Bouncy effect

    // Create fade animation
    fadeAnimation = new QPropertyAnimation(opacityEffect, "opacity", this);
    fadeAnimation->setDuration(1000);  // 1 second
    fadeAnimation->setStartValue(0.0);
    fadeAnimation->setEndValue(1.0);
    fadeAnimation->setEasingCurve(QEasingCurve::InOutQuad);

    // Create animation group to play both animations together
    QParallelAnimationGroup *animGroup = new QParallelAnimationGroup(this);
    animGroup->addAnimation(slideAnimation);
    animGroup->addAnimation(fadeAnimation);

    // Start the animation when the dialog is shown
    QTimer::singleShot(100, [animGroup]() {
        animGroup->start();
    });

    // Adjust layout spacing for username field
    if (QHBoxLayout* layout = qobject_cast<QHBoxLayout*>(ui->usernameLabel->layout())) {
        // Make left spacer smaller than right spacer (e.g., 1:2 ratio)
        layout->setStretch(0, 1);  // Left spacer
        layout->setStretch(2, 2);  // Right spacer
    }

}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    if (_validateCredentials(username, password))
    {
        accept();
    }
    else
    {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password!");
    }
}

bool LoginDialog::_validateCredentials(const QString &username, const QString &password)
{
    Position pos;
    if (loginPass.validateCredentials(username, password, pos))
    {
        userPosition = pos;
        userID = username;
        return true;
    }
    return false;
}
