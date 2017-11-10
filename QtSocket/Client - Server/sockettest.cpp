#include "sockettest.h"
#include <QFile>

SocketTest::SocketTest(QObject *parent) :
	QObject(parent)
{
}

void SocketTest::Connect()
{
	socket = new QTcpSocket(this);
	socket->connectToHost("127.0.0.1", 1234);

	if (socket->waitForConnected(3000))
	{
		qDebug() << "Connected!";


		QFile file("1.jpg");

		file.open(QIODevice::ReadOnly);
		QByteArray buf = file.readAll();
		file.close();

		QFile file1("answer.bmp");
		file1.open(QIODevice::WriteOnly);

		socket->write(buf.toBase64());
		qDebug() << buf.size();
		socket->waitForBytesWritten(-1);

		while (socket->waitForReadyRead(-1)) {
			qDebug() << "Reading: " << socket->bytesAvailable();
			QByteArray str = QByteArray::fromBase64(socket->readAll());
			file1.write(str);
		}

		file1.close();
		socket->close();

	}
	else
	{
		qDebug() << "Not connected!";
	}
}