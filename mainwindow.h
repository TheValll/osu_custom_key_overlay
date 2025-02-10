#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QPropertyAnimation>
#include <QTimer>
#include <QSettings>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    bool keyPressedKey1 = false;
    bool keyPressedKey2 = false;
    int keyPressTimesKey1 = 0;
    int keyPressTimesKey2 = 0;
    QList<QLabel *> labelsKey1;
    QList<QLabel *> labelsKey2;
    QList<QPropertyAnimation *> animationsKey1;
    QList<QPropertyAnimation *> animationsKey2;

    void checkStatusKey1(QPushButton *name, int keycode, const QString &imagePath, const QString &keyColor, const QString &keyBorderColor, const QString &keyColorOnPressing, const QString &keyBorderColorOnPressing, const QString &sliderColor, const QString &sliderBorderColor, const QString &sliderImg);
    void checkStatusKey2(QPushButton *name, int keycode, const QString &imagePath, const QString &keyColor, const QString &keyBorderColor, const QString &keyColorOnPressing, const QString &keyBorderColorOnPressing, const QString &sliderColor, const QString &sliderBorderColor, const QString &sliderImg);
    void createLabelKey1(const QString &sliderColor, const QString &sliderBorderColor, const QString &sliderImg);
    void createLabelKey2(const QString &sliderColor, const QString &sliderBorderColor, const QString &sliderImg);
    void updateLabelSizeKey1(int width);
    void updateLabelSizeKey2(int width);
    void startLabelAnimationKey1();
    void startLabelAnimationKey2();
    void removeLabelKey1();
    void removeLabelKey2();
    void fadeInLabel(QLabel *label);
};
#endif // MAINWINDOW_H
