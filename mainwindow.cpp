#include "mainwindow.h"
#include "qjsondocument.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <signup.h>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if(ui->pushButton->text() == "Logout"){
        //logout code
        return;
    }
    m_accessmanager = new QNetworkAccessManager();
    reply = m_accessmanager->get(QNetworkRequest(QUrl("https://qtfirebase-18b69-default-rtdb.firebaseio.com/users.json")));
    connect(reply, &QNetworkReply::readyRead, this, &MainWindow::replyReady);

}


void MainWindow::on_pushButton_2_clicked()
{
    signup *s = new signup();
    s->show();
    s->exec();
}

void MainWindow::replyReady(){
    QFile f("data.json");
    f.open(QIODevice::WriteOnly);
    QTextStream out(&f);
    out << reply->readAll();
    f.close();
    QString email = ui->lineEdit_2->text();
    QString pass = ui->lineEdit_3->text();

    QString name = checkCredentials(email, pass);
    if (!name.isEmpty()) {
        ui->textBrowser->setText("Welcome "+name+" You are successfully\n logged in as "+email);
        ui->lineEdit->setText("Logged in at "+QTime::currentTime().toString());
        ui->lineEdit_2->setVisible(false);
        ui->lineEdit_3->setVisible(false);
        ui->pushButton->setText("Logout");
    } else {
        QMessageBox::information(this, "Error", "Invalid email or password!", 0);
        return;
    }

}

QString MainWindow::checkCredentials(QString email, QString password) {
    // Read JSON file
    QFile file("data.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file.";
        return "";
    }
    QByteArray jsonData = file.readAll();
    file.close();
    QFile::remove("data.json");

    // Parse JSON
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (!doc.isObject()) {
        qDebug() << "Invalid JSON format.";
        return "";
    }
    QJsonObject obj = doc.object();

    // Search for matching email and password
    for (const auto& key : obj.keys()) {
        QJsonObject user = obj.value(key).toObject();
        if (user.value("email").toString() == email && user.value("password").toString() == password) {
            return user.value("name").toString();
        }
    }

    // No match found
    return "";
}

