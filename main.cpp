#include "my3dwindow.h"

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
    transform1->setTranslation(QVector3D(0.0f, 0.0f, -10.0f));

    auto transform2 = new Qt3DCore::QTransform;
    transform2->setTranslation(QVector3D(-10.0f, 0.0f, 0.0f));

    auto material1 = new Qt3DExtras::QPhongMaterial;
    material1->setAmbient(Qt::blue);

    auto material2 = new Qt3DExtras::QPhongAlphaMaterial;
    material2->setAmbient(Qt::red);

    auto spheremesh = new Qt3DExtras::QSphereMesh;
    spheremesh->setRadius(15.0);
    spheremesh->setSlices(32);
    spheremesh->setRings(32);

    sphere1->addComponent(transform1);
    sphere1->addComponent(material1);
    sphere1->addComponent(spheremesh);
    sphere1->addComponent(window->OpaqueLayer());

    sphere2->addComponent(transform2);
    sphere2->addComponent(material2);
    sphere2->addComponent(spheremesh);
    sphere2->addComponent(window->TransparentLayer());

    window->show();
    return application.exec();
}
