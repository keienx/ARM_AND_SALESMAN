#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &MainWindow::deleteLater);

    nextBlockSize = 0;

    dt = QDate::currentDate();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete socket;
}

void MainWindow::SendToServer(QString str)
{

    //отправка сообщения клиенту

    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    out << quint16(0) << QTime::currentTime() << str;
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));
    socket->write(Data);
    ui->lineEdit->clear();
}

void MainWindow::slotReadyRead()
{

    //Чтение сообщений и вывод их на сервер

    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    if(in.status()==QDataStream::Ok){
        for (;;){
            if (nextBlockSize == 0){
                if (socket->bytesAvailable() < 2){
                    break;
                }
                in >> nextBlockSize;
            }
            if (socket->bytesAvailable() < nextBlockSize){
                break;
            }
            QString str;
            QTime time;
            in >> time >> str;
            nextBlockSize = 0;
            ui ->textBrowser->append(time.toString() + " " + str);
            break;
        }
    }
    else{
        ui->textBrowser->append("Ошибка чтения");
    }
}


void MainWindow::on_pushButton_clicked()
{

    //подключение к локальному хосту и порту

    socket->connectToHost("127.0.0.1", 2323);
}

void MainWindow::on_pushButton_2_clicked()
{
    SendToServer(ui->lineEdit->text());
}

void MainWindow::on_lineEdit_returnPressed()
{
    SendToServer(ui->lineEdit->text());
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->label->setText("Бригада 1\n1. Аюпов Олег Максимович\n(Старший сотрудник)\n2. Евдокимова Ольга Петровна\n(Модельер-конструктор)\n"
                       "3. Знойный Глеб Андреевич\n(Модельер-конструктор)\n4. Карпов Никита Сергеевич\n(Модельер-конструктор)");
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->label->setText("Бригада 2\n1. Мурина Светлана Алексеевна\n(Старший сотрудник)\n2. Петрова Анастасия Станиславовна\n(Оператор швейного оборудования)\n"
                       "3. Рудников Павел Федотович\n(Оператор швейного оборудования)\n4.Сырчикова Ева Ильинична\n(Оператор швейного оборудования)");
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->label->setText("Бригада 3\n1. Уварова Елена Михайловна\n(Старший сотрудник)\n2. Белякова Анна Артемовна\n(Дизайнер)\n"
                       "3. Суханова Симона Степановна\n(Дизайнер)\n4.Максимова Софья Аркадьевна\n(Дизайнер)");
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->label->setText("Бригада 4\n1. Степанова Северина Всеволодовна\n(Старший сотрудник)\n2. Белякова Анна Артемовна\n(Изготовитель лекал)\n"
                       "3. Горбачёва Инга Федоровна\n(Модистка головных уборов)\n4.Боброва Валентина Богдановна\n(Комплектовщик материалов, кроя и изделий)");
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->label->setText("Бригада 5\n1. Зимин Егор Матвеевич\n(Старший сотрудник)\n2. Николаев Корней Кириллович\n(Художник по костюму)\n"
                       "3. Анюков Антон Васильевич\n(Термоотделочник швейных изделий)\n4.Алексеев Никита Евгеньевич\n(Контролер материалов, лекал и изделий)");
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->label->setText("Бригада 6\n1. Дубина Оксана Павловна\n(Старший сотрудник)\n2. Степанов Пантелеймон Маркович\n(Комплектовщик материалов, кроя и изделий)\n"
                       "3. Васильев Илья Григорьевич\n(Отделочник материалов и готовых изделий)\n4.Зайцев Мирослав Константинович\n(Плиссировщик-гофрировщик)");
}


void MainWindow::on_pushButton_9_clicked()
{
    SendToServer((ui->comboBox->currentText()) + "\n" + (ui->comboBox_2->currentText()) + " в " + dt.toString());
}


