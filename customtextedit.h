#ifndef CUSTOMTEXTEDIT_H
#define CUSTOMTEXTEDIT_H

#include <QTextEdit>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QTextCursor>
#include <QTextImageFormat>
#include <QTextBlock>
#include <QTextFragment>
#include <QTextDocument>
#include <QTextCharFormat>
#include <QRubberBand>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <QMetaType>
#include <QAbstractTextDocumentLayout>
#include <QTextLayout>
#include <QTimer>
#include <QDebug>
#include <QMessageBox>

class CustomTextEdit : public QTextEdit
{
    Q_OBJECT

public:
    explicit CustomTextEdit(QWidget *parent = nullptr);

signals:
    void imageInserted(const QString &imagePath);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    struct ImageInfo {
        QString name;
        QTextCursor cursor;
        QRectF rect;
        qreal originalWidth;
        qreal originalHeight;
        qreal currentWidth;
        qreal currentHeight;
    };

    bool isImageAt(const QPoint &pos, ImageInfo &info);
    bool setupImageInfo(const QTextCursor &cursor, ImageInfo &info, const QPoint &clickPos);
    void resizeImage(ImageInfo &imageInfo, qreal newWidth, qreal newHeight);
    QRectF getImageRect(const QTextCursor &cursor);
    QRectF getAccurateImageRect(const QTextCursor &cursor);  // 新增：更准确的图片矩形获取方法
    void updateImageHandles();
    bool isOnResizeHandle(const QPoint &pos);
    void drawResizeHandles(QPainter *painter);

    // 拖拽相关
    bool m_isDragging = false;
    bool m_isResizing = false;
    QPoint m_dragStartPos;
    QPoint m_lastMousePos;
    ImageInfo m_selectedImage;
    bool m_hasSelectedImage = false;
    
    // 缩放相关
    enum ResizeHandle {
        NoHandle,
        TopLeft, TopRight,
        BottomLeft, BottomRight,
        Left, Right,
        Top, Bottom
    };
    ResizeHandle m_currentHandle = NoHandle;
    
    // 右键菜单
    QMenu *m_imageContextMenu = nullptr;
    QAction *m_resetSizeAction = nullptr;
    QAction *m_deleteImageAction = nullptr;
    QAction *m_calibrateAction = nullptr;
    
    // 位置偏移量（用于微调控制点位置）
    int m_offsetX = 0;
    int m_offsetY = 0;
    
    // 缩放限制
    const qreal MIN_IMAGE_SIZE = 50.0;
    const qreal MAX_IMAGE_SIZE = 2000.0;
    const int HANDLE_SIZE = 8;
};

#endif // CUSTOMTEXTEDIT_H