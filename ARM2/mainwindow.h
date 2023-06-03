#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTime>
#include <QComboBox>
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QDate>

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
    QTcpSocket *socket;
    QByteArray Data;
    void SendToServer(QString str);
    quint16 nextBlockSize;
    QDate dt;

public slots:
    void slotReadyRead();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void on_lineEdit_returnPressed();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();
    void on_calendarWidget_activated(const QDate &date);
};
#endif // MAINWINDOW_H
