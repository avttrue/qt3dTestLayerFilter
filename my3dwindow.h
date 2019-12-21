#ifndef MY3DWINDOW_H
#define MY3DWINDOW_H

#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DRender/QLayer>

class My3DWindow : public Qt3DExtras::Qt3DWindow
{
public:
    My3DWindow(QScreen *screen = nullptr);

    Qt3DRender::QLayer *TransparentLayer() const;
    Qt3DRender::QLayer *OpaqueLayer() const;
    Qt3DCore::QEntity *Scene() const;

protected:
    void resizeEvent(QResizeEvent *e);

private:
    Qt3DRender::QLayer *m_TransparentLayer;
    Qt3DRender::QLayer *m_OpaqueLayer;
    Qt3DCore::QEntity *m_Scene;
    Qt3DRender::QCamera *m_Camera;
};

#endif // MY3DWINDOW_H