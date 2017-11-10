#include "myserver.h"
#include <QFIle>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <fstream>

MyServer::MyServer(QObject *parent) :
	QObject(parent)
{
	server = new QTcpServer(this);

	connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

	if (!server->listen(QHostAddress::Any, 1234))
	{
		qDebug() << "Server could not start!";
	}
	else
	{
		qDebug() << "Server started!";
	}
}

void MyServer::newConnection()
{
	QTcpSocket *socket = server->nextPendingConnection();

	QFile file("tmp.jpg");
	file.open(QIODevice::WriteOnly);

	while (socket->waitForReadyRead(3000)) {
		qDebug() << "Reading: " << socket->bytesAvailable();
		QByteArray str = QByteArray::fromBase64(socket->readAll());
		file.write(str);
	}
	file.close();

	cv::Mat src = cv::imread("tmp.jpg", 1);

	cv::cvtColor(src, src, CV_BGR2GRAY);
	cv::GaussianBlur(src, src, cv::Size(7, 7), 1.5, 1.5);
	cv::Canny(src, src, 0, 30, 3);
	cv::imshow("ggg", src);

	cv::imwrite("tmp.jpg",src);
	
	QFile file1("tmp.jpg");

	file1.open(QIODevice::ReadOnly);
	QByteArray buf = file1.readAll();
	file1.close();

	socket->write(buf.toBase64());
	qDebug() << buf.size();
	socket->waitForBytesWritten(-1);

	socket->close();
}