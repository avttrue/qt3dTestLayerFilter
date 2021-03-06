#include "my3dwindow.h"

#include <QResizeEvent>
#include <Qt3DExtras/QFirstPersonCameraController>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QCameraSelector>
#include <Qt3DRender/QRenderSurfaceSelector>
#include <Qt3DRender/QClearBuffers>
#include <Qt3DRender/QViewport>
#include <Qt3DRender/QLayerFilter>


My3DWindow::My3DWindow(QScreen *screen):
    Qt3DExtras::Qt3DWindow(screen),
    m_Scene(nullptr),
    m_Camera(nullptr),
    m_TransparentLayer(nullptr),
    m_OpaqueLayer(nullptr)
{
    m_Scene = new Qt3DCore::QEntity;
    setRootEntity(m_Scene);

    auto renderSurfaceSelector = new Qt3DRender::QRenderSurfaceSelector;
    renderSurfaceSelector->setSurface(this);

    auto viewport = new Qt3DRender::QViewport(renderSurfaceSelector);
    auto cameraSelector = new Qt3DRender::QCameraSelector(viewport);

    auto clearBuffers = new Qt3DRender::QClearBuffers(cameraSelector);
    clearBuffers->setBuffers(Qt3DRender::QClearBuffers::AllBuffers);
    clearBuffers->setClearColor(Qt::gray);

    m_Camera = new Qt3DRender::QCamera(cameraSelector);
    m_Camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    m_Camera->setPosition(QVector3D(0.0f, 0.0f, 100.0f));
    m_Camera->setViewCenter(QVector3D(0.0f, 0.0f, 0.0f));
    cameraSelector->setCamera(m_Camera);

    auto cameraController = new Qt3DExtras::QFirstPersonCameraController(m_Scene);
    cameraController->setCamera(m_Camera);

    // именно в таком порядке: m_OpaqueLayer, m_TransparentLayer
    m_OpaqueLayer = new Qt3DRender::QLayer;
    auto opaqueFilter = new Qt3DRender::QLayerFilter(m_Camera);
    opaqueFilter->addLayer(m_OpaqueLayer);

    m_TransparentLayer = new Qt3DRender::QLayer;
    auto transparentFilter = new Qt3DRender::QLayerFilter(m_Camera);
    transparentFilter->addLayer(m_TransparentLayer);

    setActiveFrameGraph(renderSurfaceSelector);
}

void My3DWindow::resizeEvent(QResizeEvent *e)
{
    auto camera_aspect = static_cast<float>(e->size().width()) / e->size().height();
    m_Camera->lens()->setPerspectiveProjection(45.0f, camera_aspect, 0.1f, 1000.0f);
}

void My3DWindow::keyPressEvent(QKeyEvent *e) { Q_EMIT signalPressKey(e); }

Qt3DCore::QEntity *My3DWindow::Scene() const { return m_Scene; }
Qt3DRender::QLayer *My3DWindow::TransparentLayer() const { return m_TransparentLayer; }
Qt3DRender::QLayer *My3DWindow::OpaqueLayer() const { return m_OpaqueLayer; }

