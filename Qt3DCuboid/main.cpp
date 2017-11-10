#include <Qt3DCore/qentity.h>//класс для объединения всех объектов для визуализации
#include <Qt3DCore/qtransform.h>//класс для указания положения на сцене объектов

#include <QtWidgets/qapplication.h>//оболочка для графического приложения
#include <Qt3DExtras/qt3dwindow.h>//окна для отоб
#include <QtWidgets/qwidget.h>//объект который потом получит ссылку на 3Dwindow и отобразит его.

#include <Qt3DRender/qcamera.h>//класс камера дял просмотра сцены
#include <Qt3DExtras/qfirstpersoncameracontroller.h>//управление камерой стрелочками и мышью

#include <Qt3DExtras/qcuboidmesh.h>//набор вершин и многоугольников, определяющих форму трёхмерного объекта куба
#include <Qt3DExtras/qphongalphamaterial.h>//материал объекта от него зависит освещение и без него не собирается объект

/*$(QTDIR)\lib\qtmaind.lib
$(QTDIR)\lib\Qt53DExtrasd.lib
$(QTDIR)\lib\Qt53DRenderd.lib
$(QTDIR)\lib\Qt53DCored.lib
$(QTDIR)\lib\Qt5Widgetsd.lib
$(QTDIR)\lib\Qt5Guid.lib
$(QTDIR)\lib\Qt5Cored.lib*///библиотеки для подключения

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    QWidget *container = QWidget::createWindowContainer(view);

    // Root entity
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();

	// Set root object of the scene
	view->setRootEntity(rootEntity);

    // Camera
    Qt3DRender::QCamera *cameraEntity = view->camera();
    cameraEntity->setPosition(QVector3D(0, 0, 20.0f));

    // For camera controls
    Qt3DExtras::QFirstPersonCameraController *camController = new Qt3DExtras::QFirstPersonCameraController(rootEntity);
    camController->setCamera(cameraEntity);

	//object
	Qt3DExtras::QCuboidMesh *cuboid = new Qt3DExtras::QCuboidMesh();

	// CuboidMesh Transform
	Qt3DCore::QTransform *cuboidTransform = new Qt3DCore::QTransform();
	cuboidTransform->setScale(3.0f);
	cuboidTransform->setTranslation(QVector3D(0.0f, 0.0f, 0.0f));

	Qt3DExtras::QPhongAlphaMaterial *cuboidMaterial = new Qt3DExtras::QPhongAlphaMaterial();

	//Cuboid
	auto cuboidEntity = new Qt3DCore::QEntity(rootEntity);
	cuboidEntity->addComponent(cuboid);
	cuboidEntity->addComponent(cuboidMaterial);
	cuboidEntity->addComponent(cuboidTransform);

    // Show window
    container->show();
    container->resize(600, 400);

    return app.exec();
}