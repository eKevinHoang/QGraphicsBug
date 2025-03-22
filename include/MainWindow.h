#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ImageViewer.h"
#include <QMainWindow>
#include <QLineEdit>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

private:
  ImageViewer* imageViewer;
  void setupLayout();

protected:
    void closeEvent(QCloseEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // MAINWINDOW_H
