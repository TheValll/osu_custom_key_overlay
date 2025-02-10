#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Windows.h>
#include <QTimer>
#include <QObject>
#include <QPushButton>
#include <QTime>
#include <QLabel>
#include <QFile>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QGraphicsOpacityEffect>
#include <QEasingCurve>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("OsuKeyOverlay");

    QSettings settings("config.ini", QSettings::Format::IniFormat);
    // settings.setValue("/icon/path", ":img/img/icon.ico");
    QString icon = settings.value("/icon/path").toString();
    this->setWindowIcon(QIcon(icon));

    // Keycode
    // settings.setValue("Key_1", 0x53);
    // settings.setValue("Key_2", 0x44);
    const int key_1 = settings.value("Key_1").toInt();
    const int key_2 = settings.value("Key_2").toInt();

    // Images
    // settings.setValue("/images/key_1", "path_of_your_img");
    // settings.setValue("/images/key_2", "path_of_your_img");
    QString imageKey1 = settings.value("/images/key_1").toString();
    QString imageKey2 = settings.value("/images/key_2").toString();

    // Color
    // settings.setValue("/colors/background_key_1", "rgb(255,255,255)");
    // settings.setValue("/colors/background_key_2", "rgb(255,255,255)");
    // settings.setValue("/colors/border_key_1", "rgb(255, 152, 210)");
    // settings.setValue("/colors/border_key_2", "rgb(255, 152, 210)");
    // settings.setValue("/colors/slider_1", "rgb(255, 152, 210)");
    // settings.setValue("/colors/slider_2", "rgb(255, 152, 210)");
    // settings.setValue("/colors/slider_border_1", "rgb(255,255,255)");
    // settings.setValue("/colors/slider_border_2", "rgb(255,255,255)");
    QString background_key_1 = settings.value("/colors/background_key_1").toString();
    QString background_key_2 = settings.value("/colors/background_key_2").toString();
    QString border_key_1 = settings.value("/colors/border_key_1").toString();
    QString border_key_2 = settings.value("/colors/border_key_2").toString();
    QString slider_1 = settings.value("/colors/slider_1").toString();
    QString slider_2 = settings.value("/colors/slider_2").toString();
    QString slider_border_1 = settings.value("/colors/slider_border_1").toString();
    QString slider_border_2 = settings.value("/colors/slider_border_2").toString();

    // Color on pressing
    // settings.setValue("/colors_on_pressing/background_key_1", "rgb(255, 152, 210)");
    // settings.setValue("/colors_on_pressing/background_key_2", "rgb(255, 152, 210)");
    // settings.setValue("/colors_on_pressing/border_key_1", "rgb(255,255,255)");
    // settings.setValue("/colors_on_pressing/border_key_2", "rgb(255,255,255)");
    QString on_pressing_background_key_1 = settings.value("/colors_on_pressing/background_key_1").toString();
    QString on_pressing_background_key_2 = settings.value("/colors_on_pressing/background_key_2").toString();
    QString on_pressing_border_key_1 = settings.value("/colors_on_pressing/border_key_1").toString();
    QString on_pressing_border_key_2 = settings.value("/colors_on_pressing/border_key_2").toString();


    // Slider image
    // settings.setValue("/slider_images/key_1", "path_of_your_img");
    // settings.setValue("/slider_images/key_2", "path_of_your_img");
    QString slider_image_key_1 = settings.value("/slider_images/key_1").toString();
    QString slider_image_key_2 = settings.value("/slider_images/key_2").toString();


    QTimer *timerKey1 = new QTimer(this);
    connect(timerKey1, &QTimer::timeout, this, [this, key_1, imageKey1, background_key_1, border_key_1, on_pressing_background_key_1, on_pressing_border_key_1, slider_1, slider_border_1, slider_image_key_1]() {
        checkStatusKey1(ui->ONE, key_1, imageKey1, background_key_1, border_key_1, on_pressing_background_key_1, on_pressing_border_key_1, slider_1, slider_border_1, slider_image_key_1);

    });
    timerKey1->start(15);

    QTimer *timerKey2 = new QTimer(this);
    connect(timerKey2, &QTimer::timeout, this, [this, key_2, imageKey2, background_key_2, border_key_2, on_pressing_background_key_2, on_pressing_border_key_2, slider_2, slider_border_2, slider_image_key_2]() {
        checkStatusKey2(ui->TWO, key_2, imageKey2, background_key_2, border_key_2, on_pressing_background_key_2, on_pressing_border_key_2, slider_2, slider_border_2, slider_image_key_2);
    });
    timerKey2->start(15);

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkStatusKey1(QPushButton *name, int keycode, const QString &imagePath, const QString &keyColor, const QString &keyBorderColor, const QString &keyColorOnPressing, const QString &keyBorderColorOnPressing, const QString &sliderColor, const QString &sliderBorderColor, const QString &sliderImg)
{
    SHORT KeyState = GetKeyState(keycode);
    QString style;

    if (KeyState & 0x8000) {
        if (!keyPressedKey1) {
            keyPressedKey1 = true;
            keyPressTimesKey1 = 0;
            createLabelKey1(sliderColor, sliderBorderColor, sliderImg);
        }

        keyPressTimesKey1 += 10;
        updateLabelSizeKey1(keyPressTimesKey1);

        style = QString("background-color: %1; border-color: %2; border-style: solid; border-width: 2px;")
                    .arg(keyColorOnPressing)
                    .arg(keyBorderColorOnPressing);
    }
    else {
        if (keyPressedKey1) {
            keyPressedKey1 = false;
            startLabelAnimationKey1();
        }

        style = QString("background-color: %1; border-color: %2; border-style: solid; border-width: 2px;")
                    .arg(keyColor)
                    .arg(keyBorderColor);
    }

    if (imagePath != "") {
        style.append(QString(" background-image: url(%1); background-position: center; background-repeat: no-repeat;").arg(imagePath));
    }

    name->setStyleSheet(style);
}


void MainWindow::createLabelKey1(const QString &sliderColor, const QString &sliderBorderColor, const QString &sliderImg)
{
    QLabel *newLabel = new QLabel(this->centralWidget());

    if (sliderImg.isEmpty() || sliderImg == "") {
        newLabel->setStyleSheet(QString(
                                    "background-color: %1; "
                                    "border-color: %2; "
                                    "border-style: solid; "
                                    "border-width: 2px;")
                                    .arg(sliderColor)
                                    .arg(sliderBorderColor));
    } else {
        newLabel->setStyleSheet(QString(
                                    "background-color: %1; "
                                    "border-color: %2; "
                                    "border-style: solid; "
                                    "border-width: 2px; "
                                    "background-image: url(%3); "
                                    "background-position: top left; "
                                    "background-repeat: repeat-x;")
                                    .arg(sliderColor)
                                    .arg(sliderBorderColor)
                                    .arg(sliderImg));
    }

    newLabel->setGeometry(750, 9, 10, 75);
    newLabel->show();
    newLabel->lower();

    fadeInLabel(newLabel);

    labelsKey1.append(newLabel);
}



void MainWindow::updateLabelSizeKey1(int width)
{
    if (!labelsKey1.isEmpty()) {
        QLabel *lastLabel = labelsKey1.last();
        int currentX = lastLabel->x();
        int newX = currentX - (width - lastLabel->width());
        lastLabel->setGeometry(newX, lastLabel->y(), width, 75);
    }
}

void MainWindow::startLabelAnimationKey1()
{
    if (labelsKey1.isEmpty()) return;

    QLabel *label = labelsKey1.last();
    QString bgImage = label->styleSheet();
    bool hasImage = bgImage.contains("background-image: url(") && !bgImage.contains("background-image: none");

    int currentWidth = label->width();
    int targetWidth = currentWidth;

    if (hasImage) {
        targetWidth = ((currentWidth + 74) / 75) * 75;
    }

    int newX = label->x() - (targetWidth - currentWidth);

    QParallelAnimationGroup *group = new QParallelAnimationGroup;

    if (hasImage) {
        QPropertyAnimation *sizeAnimation = new QPropertyAnimation(label, "geometry");
        sizeAnimation->setDuration(75);
        sizeAnimation->setStartValue(label->geometry());
        sizeAnimation->setEndValue(QRect(newX, label->y(), targetWidth, 75));
        sizeAnimation->setEasingCurve(QEasingCurve::OutCubic);
        group->addAnimation(sizeAnimation);
    }

    QPropertyAnimation *moveAnimation = new QPropertyAnimation(label, "pos");
    moveAnimation->setDuration(1500);
    moveAnimation->setStartValue(label->pos());
    moveAnimation->setEndValue(QPoint(newX - 1000, label->y()));
    moveAnimation->setEasingCurve(QEasingCurve::OutQuad);
    group->addAnimation(moveAnimation);

    connect(group, &QParallelAnimationGroup::finished, group, &QObject::deleteLater);
    connect(group, &QParallelAnimationGroup::finished, label, &QObject::deleteLater);

    group->start();
}


void MainWindow::removeLabelKey1()
{
    if (!labelsKey1.isEmpty()) {
        labelsKey1.takeFirst()->deleteLater();
    }
}

void MainWindow::checkStatusKey2(QPushButton *name, int keycode, const QString &imagePath, const QString &keyColor, const QString &keyBorderColor, const QString &keyColorOnPressing, const QString &keyBorderColorOnPressing, const QString &sliderColor, const QString &sliderBorderColor, const QString &sliderImg)
{
    SHORT KeyState = GetKeyState(keycode);
    QString style;

    if (KeyState & 0x8000) {
        if (!keyPressedKey2) {
            keyPressedKey2 = true;
            keyPressTimesKey2 = 0;
            createLabelKey2(sliderColor, sliderBorderColor, sliderImg);
        }

        keyPressTimesKey2 += 10;
        updateLabelSizeKey2(keyPressTimesKey2);

        style = QString("background-color: %1; border-color: %2; border-style: solid; border-width: 2px;")
                    .arg(keyColorOnPressing)
                    .arg(keyBorderColorOnPressing);
    }
    else {
        if (keyPressedKey2) {
            keyPressedKey2 = false;
            startLabelAnimationKey2();
        }

        style = QString("background-color: %1; border-color: %2; border-style: solid; border-width: 2px;")
                    .arg(keyColor)
                    .arg(keyBorderColor);
    }

    if (imagePath != "") {
        style.append(QString(" background-image: url(%1); background-position: center; background-repeat: no-repeat;").arg(imagePath));
    }

    name->setStyleSheet(style);
}


void MainWindow::createLabelKey2(const QString &sliderColor, const QString &sliderBorderColor, const QString &sliderImg)
{
    QLabel *newLabel = new QLabel(this->centralWidget());

    if (sliderImg.isEmpty() || sliderImg == "") {
        newLabel->setStyleSheet(QString(
                                    "background-color: %1; "
                                    "border-color: %2; "
                                    "border-style: solid; "
                                    "border-width: 2px;")
                                    .arg(sliderColor)
                                    .arg(sliderBorderColor));
    } else {
        newLabel->setStyleSheet(QString(
                                    "background-color: %1; "
                                    "border-color: %2; "
                                    "border-style: solid; "
                                    "border-width: 2px; "
                                    "background-image: url(%3); "
                                    "background-position: top left; "
                                    "background-repeat: repeat-x;")
                                    .arg(sliderColor)
                                    .arg(sliderBorderColor)
                                    .arg(sliderImg));
    }

    newLabel->setGeometry(750, 89, 10, 75);
    newLabel->show();
    newLabel->lower();

    fadeInLabel(newLabel);

    labelsKey2.append(newLabel);
}

void MainWindow::updateLabelSizeKey2(int width)
{
    if (!labelsKey2.isEmpty()) {
        QLabel *lastLabel = labelsKey2.last();
        int currentX = lastLabel->x();
        int newX = currentX - (width - lastLabel->width());
        lastLabel->setGeometry(newX, lastLabel->y(), width, 75);
    }
}

void MainWindow::startLabelAnimationKey2()
{
    if (labelsKey2.isEmpty()) return;

    QLabel *label = labelsKey2.last();
    QString bgImage = label->styleSheet();
    bool hasImage = bgImage.contains("background-image: url(") && !bgImage.contains("background-image: none");

    int currentWidth = label->width();
    int targetWidth = currentWidth;

    if (hasImage) {
        targetWidth = ((currentWidth + 74) / 75) * 75;
    }

    int newX = label->x() - (targetWidth - currentWidth);

    QParallelAnimationGroup *group = new QParallelAnimationGroup;

    if (hasImage) {
        QPropertyAnimation *sizeAnimation = new QPropertyAnimation(label, "geometry");
        sizeAnimation->setDuration(75);
        sizeAnimation->setStartValue(label->geometry());
        sizeAnimation->setEndValue(QRect(newX, label->y(), targetWidth, 75));
        sizeAnimation->setEasingCurve(QEasingCurve::OutCubic);
        group->addAnimation(sizeAnimation);
    }

    QPropertyAnimation *moveAnimation = new QPropertyAnimation(label, "pos");
    moveAnimation->setDuration(1500);
    moveAnimation->setStartValue(label->pos());
    moveAnimation->setEndValue(QPoint(newX - 1000, label->y()));
    moveAnimation->setEasingCurve(QEasingCurve::OutQuad);
    group->addAnimation(moveAnimation);

    connect(group, &QParallelAnimationGroup::finished, group, &QObject::deleteLater);
    connect(group, &QParallelAnimationGroup::finished, label, &QObject::deleteLater);

    group->start();
}

void MainWindow::removeLabelKey2()
{
    if (!labelsKey2.isEmpty()) {
        labelsKey2.takeFirst()->deleteLater();
    }
}


void MainWindow::fadeInLabel(QLabel *label)
{
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(label);
    label->setGraphicsEffect(opacityEffect);

    QPropertyAnimation *fadeIn = new QPropertyAnimation(opacityEffect, "opacity");
    fadeIn->setDuration(250);
    fadeIn->setStartValue(0.0);
    fadeIn->setEndValue(1.0);
    fadeIn->setEasingCurve(QEasingCurve::OutQuad);

    fadeIn->start(QAbstractAnimation::DeleteWhenStopped);
}

