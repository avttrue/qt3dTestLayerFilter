#include "my3dwindow.h"

#include <QKeyEvent>
#include <QGuiApplication>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QPhongAlphaMaterial>

int main(int argc, char *argv[])
{
    QGuiApplication application(argc, argv);
    auto window = new My3DWindow;

    auto sphere1 = new Qt3DCore::QEntity(window->Scene());
    auto sphere2 = new Qt3DCore::QEntity(window->Scene());

    auto transform1 = new Qt3DCore::QTransform;
    transform1->setTranslation(QVector3D(5.0f, 0.0f, -10.0f));

    auto transform2 = new Qt3DCore::QTransform;
    transform2->setTranslation(QVector3D(-5.0f, 0.0f, -10.0f));

    auto material1 = new Qt3DExtras::QPhongMaterial;
    material1->setAmbient(Qt::blue);

    auto material2 = new Qt3DExtras::QPhongAlphaMaterial;
    material2->setAmbient(Qt::red);

    auto spheremesh1 = new Qt3DExtras::QSphereMesh;
    spheremesh1->setRadius(15.0);
    spheremesh1->setSlices(32);
    spheremesh1->setRings(32);

    auto spheremesh2 = new Qt3DExtras::QSphereMesh;
    spheremesh2->setRadius(15.0);
    spheremesh2->setSlices(32);
    spheremesh2->setRings(32);

    sphere1->addComponent(material1);
    sphere1->addComponent(spheremesh1);
    sphere1->addComponent(transform1);
    sphere1->addComponent(window->OpaqueLayer());

    sphere2->addComponent(material2);
    sphere2->addComponent(spheremesh2);
    sphere2->addComponent(transform2);
    sphere2->addComponent(window->TransparentLayer());

    auto func = [=](QKeyEvent *e)
    {
        if(e->key() == Qt::Key_S)
            transform2->setTranslation(transform2->translation() + QVector3D(0.0f, 0.0f, 1.0f));
        else if(e->key() == Qt::Key_W)
            transform2->setTranslation(transform2->translation() + QVector3D(0.0f, 0.0f, -1.0f));
        else if(e->key() == Qt::Key_A)
            transform2->setTranslation(transform2->translation() + QVector3D(-1.0f, 0.0f, 0.0f));
        else if(e->key() == Qt::Key_D)
            transform2->setTranslation(transform2->translation() + QVector3D(1.0f, 0.0f, 0.0f));

        qDebug() << transform2->translation();
    };
    QObject::connect(window, &My3DWindow::signalKey, func);

    window->show();
    return application.exec();
}
