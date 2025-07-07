#include "customtextedit.h"
#include <QPainter>
#include <QTextDocument>
#include <QTextFrame>
#include <QScrollBar>
#include <QApplication>
#include <QMimeData>
#include <QDebug>
#include <QUrl>
#include <QAbstractTextDocumentLayout>
#include <iostream>
CustomTextEdit::CustomTextEdit(QWidget *parent) : QTextEdit(parent), m_offsetX(0), m_offsetY(0)
{
    setMouseTracking(true);
    
    // 创建右键菜单
    m_imageContextMenu = new QMenu(this);
    m_resetSizeAction = new QAction("重置图片大小", this);
    m_deleteImageAction = new QAction("删除图片", this);
    m_calibrateAction = new QAction("校准控制点位置", this);
    
    m_imageContextMenu->addAction(m_resetSizeAction);
    m_imageContextMenu->addAction(m_deleteImageAction);
    m_imageContextMenu->addSeparator();
    m_imageContextMenu->addAction(m_calibrateAction);
    
    connect(m_resetSizeAction, &QAction::triggered, [this]() {
        if (m_hasSelectedImage) {
            resizeImage(m_selectedImage, m_selectedImage.originalWidth, m_selectedImage.originalHeight);
        }
    });
    
    connect(m_deleteImageAction, &QAction::triggered, [this]() {
        if (m_hasSelectedImage) {
            m_selectedImage.cursor.removeSelectedText();
            m_hasSelectedImage = false;
            viewport()->update();
        }
    });
    
    connect(m_calibrateAction, &QAction::triggered, [this]() {
        QMessageBox::information(this, "校准控制点", 
            "使用以下快捷键微调控制点位置：\n"
            "Ctrl+方向键：移动控制点\n"
            "Ctrl+R：重置偏移量");
    });
}

bool CustomTextEdit::isImageAt(const QPoint &pos, ImageInfo &info)
{
    // 获取点击位置的光标
    QTextCursor cursor = cursorForPosition(pos);
    
    // 检查当前光标位置是否是图片
    QTextCharFormat format = cursor.charFormat();
    if (format.isImageFormat()) {
        if (setupImageInfo(cursor, info, pos)) {
            // 使用更准确的方法获取图片矩形
            QRectF rect = getAccurateImageRect(cursor);
            info.rect = rect;
            
            // 扩展一点点检测范围，容错5像素
            QRectF expandedRect = rect.adjusted(-5, -5, 5, 5);
            if (expandedRect.contains(pos)) {
                return true;
            }
        }
    }
    
    // 如果精确位置不是图片，检查前后字符
    // 这样可以避免大范围搜索带来的误判
    QTextCursor testCursor = cursor;
    
    // 检查前一个字符
    testCursor.movePosition(QTextCursor::PreviousCharacter);
    format = testCursor.charFormat();
    if (format.isImageFormat()) {
        if (setupImageInfo(testCursor, info, pos)) {
            QRectF rect = getAccurateImageRect(testCursor);
            info.rect = rect;
            QRectF expandedRect = rect.adjusted(-5, -5, 5, 5);
            if (expandedRect.contains(pos)) {
                return true;
            }
        }
    }
    
    // 检查后一个字符
    testCursor = cursor;
    testCursor.movePosition(QTextCursor::NextCharacter);
    format = testCursor.charFormat();
    if (format.isImageFormat()) {
        if (setupImageInfo(testCursor, info, pos)) {
            QRectF rect = getAccurateImageRect(testCursor);
            info.rect = rect;
            QRectF expandedRect = rect.adjusted(-5, -5, 5, 5);
            if (expandedRect.contains(pos)) {
                return true;
            }
        }
    }
    
    return false;
}

bool CustomTextEdit::setupImageInfo(const QTextCursor &cursor, ImageInfo &info, const QPoint &clickPos)
{
    QTextCharFormat format = cursor.charFormat();
    if (!format.isImageFormat()) return false;
    
    QTextImageFormat imageFormat = format.toImageFormat();
    info.name = imageFormat.name();
    info.cursor = cursor;
    
    // 保存原始尺寸
    if (!m_hasSelectedImage || info.name != m_selectedImage.name) {
        QTextDocument *doc = document();
        QVariant resource = doc->resource(QTextDocument::ImageResource, QUrl(info.name));
        if (resource.isValid()) {
            QImage img;
            if (resource.typeId() == QMetaType::QPixmap) {
                img = resource.value<QPixmap>().toImage();
            } else if (resource.typeId() == QMetaType::QImage) {
                img = resource.value<QImage>();
            }
            if (!img.isNull()) {
                info.originalWidth = img.width();
                info.originalHeight = img.height();
            }
        }
    } else {
        info.originalWidth = m_selectedImage.originalWidth;
        info.originalHeight = m_selectedImage.originalHeight;
    }
    
    info.currentWidth = imageFormat.width();
    info.currentHeight = imageFormat.height();
    
    return true;
}

QRectF CustomTextEdit::getImageRect(const QTextCursor &cursor)
{
    return getAccurateImageRect(cursor);
}

// 新增：更准确的图片矩形获取方法
QRectF CustomTextEdit::getAccurateImageRect(const QTextCursor &cursor)
{
    // 检查是否是图片格式
    QTextCharFormat format = cursor.charFormat();
    if (!format.isImageFormat()) return QRectF();
    
    QTextImageFormat imageFormat = format.toImageFormat();
    
    // 获取图片的尺寸
    qreal width = imageFormat.width();
    qreal height = imageFormat.height();
    
    // 如果没有设置高度，根据原始比例计算
    if (height <= 0) {
        QTextDocument *doc = document();
        QVariant resource = doc->resource(QTextDocument::ImageResource, QUrl(imageFormat.name()));
        if (resource.isValid()) {
            QImage img;
            if (resource.typeId() == QMetaType::QPixmap) {
                img = resource.value<QPixmap>().toImage();
            } else if (resource.typeId() == QMetaType::QImage) {
                img = resource.value<QImage>();
            }
            if (!img.isNull() && img.width() > 0) {
                qreal ratio = static_cast<qreal>(img.height()) / img.width();
                height = width * ratio;
            }
        }
        
        if (height <= 0) {
            height = width;
        }
    }
    
    // 使用文档布局获取图片的准确位置
    QAbstractTextDocumentLayout *layout = document()->documentLayout();
    QTextBlock block = cursor.block();
    
    // 获取图片在文档中的位置
    int imagePos = cursor.position();
    QTextCursor imageCursor = cursor;
    imageCursor.setPosition(imagePos);
    
    // 获取图片字符的边界矩形
    QRectF boundingRect = layout->blockBoundingRect(block);
    
    // 获取图片在块中的相对位置
    QTextLayout *textLayout = block.layout();
    if (textLayout) {
        int relativePos = imagePos - block.position();
        QTextLine line = textLayout->lineForTextPosition(relativePos);
        
        if (line.isValid()) {
            qreal x = line.cursorToX(relativePos);
            qreal y = boundingRect.top() + line.y();
            
            // 应用偏移量
            x += m_offsetX;
            y += m_offsetY;
            
            // 考虑滚动条的偏移
            QScrollBar *vBar = verticalScrollBar();
            QScrollBar *hBar = horizontalScrollBar();
            if (vBar) y -= vBar->value();
            if (hBar) x -= hBar->value();
            
            return QRectF(x, y, width, height);
        }
    }
    
    // 如果上述方法失败，使用备用方法
    QRect cursorRect = this->cursorRect(imageCursor);
    qreal imageX = cursorRect.x() + m_offsetX;
    qreal imageY = cursorRect.y() + m_offsetY;
    
    return QRectF(imageX, imageY, width, height);
}

void CustomTextEdit::keyPressEvent(QKeyEvent *event)
{
    // 处理控制点位置微调快捷键
    if (m_hasSelectedImage && event->modifiers() & Qt::ControlModifier) {
        const int ADJUST_STEP = 1;  // 每次调整的像素数
        
        switch (event->key()) {
            case Qt::Key_Left:
                m_offsetX -= ADJUST_STEP;
                m_selectedImage.rect = getImageRect(m_selectedImage.cursor);
                viewport()->update();
                event->accept();
                return;
                
            case Qt::Key_Right:
                m_offsetX += ADJUST_STEP;
                m_selectedImage.rect = getImageRect(m_selectedImage.cursor);
                viewport()->update();
                event->accept();
                return;
                
            case Qt::Key_Up:
                m_offsetY -= ADJUST_STEP;
                m_selectedImage.rect = getImageRect(m_selectedImage.cursor);
                viewport()->update();
                event->accept();
                return;
                
            case Qt::Key_Down:
                m_offsetY += ADJUST_STEP;
                m_selectedImage.rect = getImageRect(m_selectedImage.cursor);
                viewport()->update();
                event->accept();
                return;
                
            case Qt::Key_R:
                // 重置偏移量
                m_offsetX = 0;
                m_offsetY = 0;
                m_selectedImage.rect = getImageRect(m_selectedImage.cursor);
                viewport()->update();
                event->accept();
                return;
        }
    }
    
    QTextEdit::keyPressEvent(event);
}

void CustomTextEdit::resizeImage(ImageInfo &imageInfo, qreal newWidth, qreal newHeight)
{
    // 限制尺寸
    newWidth = qBound(MIN_IMAGE_SIZE, newWidth, MAX_IMAGE_SIZE);
    newHeight = qBound(MIN_IMAGE_SIZE, newHeight, MAX_IMAGE_SIZE);
    
    // 保存当前光标位置
    int cursorPos = imageInfo.cursor.position();
    
    // 选中图片
    imageInfo.cursor.select(QTextCursor::WordUnderCursor);
    
    // 创建新的图片格式
    QTextImageFormat newFormat;
    newFormat.setName(imageInfo.name);
    newFormat.setWidth(newWidth);
    newFormat.setHeight(newHeight);
    
    // 应用新格式
    imageInfo.cursor.setCharFormat(newFormat);
    
    // 更新当前尺寸
    imageInfo.currentWidth = newWidth;
    imageInfo.currentHeight = newHeight;
    
    // 强制重新布局
    document()->markContentsDirty(cursorPos, 1);
    
    // 立即更新viewport以确保布局生效
    viewport()->update();
    
    // 重新创建光标，确保位置正确
    QTextCursor newCursor = textCursor();
    newCursor.setPosition(cursorPos);
    imageInfo.cursor = newCursor;
    
    // 立即重新计算图片区域
    QTimer::singleShot(1, [this, &imageInfo]() {
        imageInfo.rect = getImageRect(imageInfo.cursor);
        viewport()->update();
    });
}

bool CustomTextEdit::isOnResizeHandle(const QPoint &pos)
{
    if (!m_hasSelectedImage) return false;
    
    QRectF rect = m_selectedImage.rect;
    QPointF topLeft = rect.topLeft();
    QPointF topRight = rect.topRight();
    QPointF bottomLeft = rect.bottomLeft();
    QPointF bottomRight = rect.bottomRight();
    
    // 检查8个控制点
    QRectF tlHandle(topLeft.x() - HANDLE_SIZE/2, topLeft.y() - HANDLE_SIZE/2, HANDLE_SIZE, HANDLE_SIZE);
    QRectF trHandle(topRight.x() - HANDLE_SIZE/2, topRight.y() - HANDLE_SIZE/2, HANDLE_SIZE, HANDLE_SIZE);
    QRectF blHandle(bottomLeft.x() - HANDLE_SIZE/2, bottomLeft.y() - HANDLE_SIZE/2, HANDLE_SIZE, HANDLE_SIZE);
    QRectF brHandle(bottomRight.x() - HANDLE_SIZE/2, bottomRight.y() - HANDLE_SIZE/2, HANDLE_SIZE, HANDLE_SIZE);
    
    // 边中点
    QRectF leftHandle(topLeft.x() - HANDLE_SIZE/2, (topLeft.y() + bottomLeft.y())/2 - HANDLE_SIZE/2, HANDLE_SIZE, HANDLE_SIZE);
    QRectF rightHandle(topRight.x() - HANDLE_SIZE/2, (topRight.y() + bottomRight.y())/2 - HANDLE_SIZE/2, HANDLE_SIZE, HANDLE_SIZE);
    QRectF topHandle((topLeft.x() + topRight.x())/2 - HANDLE_SIZE/2, topLeft.y() - HANDLE_SIZE/2, HANDLE_SIZE, HANDLE_SIZE);
    QRectF bottomHandle((bottomLeft.x() + bottomRight.x())/2 - HANDLE_SIZE/2, bottomLeft.y() - HANDLE_SIZE/2, HANDLE_SIZE, HANDLE_SIZE);
    
    if (tlHandle.contains(pos)) { m_currentHandle = TopLeft; return true; }
    if (trHandle.contains(pos)) { m_currentHandle = TopRight; return true; }
    if (blHandle.contains(pos)) { m_currentHandle = BottomLeft; return true; }
    if (brHandle.contains(pos)) { m_currentHandle = BottomRight; return true; }
    if (leftHandle.contains(pos)) { m_currentHandle = Left; return true; }
    if (rightHandle.contains(pos)) { m_currentHandle = Right; return true; }
    if (topHandle.contains(pos)) { m_currentHandle = Top; return true; }
    if (bottomHandle.contains(pos)) { m_currentHandle = Bottom; return true; }
    
    m_currentHandle = NoHandle;
    return false;
}

void CustomTextEdit::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        ImageInfo imageInfo;
        m_dragStartPos = event->pos();
        m_lastMousePos = event->pos();
        
        // 先检查是否有选中的图片，如果有，检查是否点击在缩放手柄上
        if (m_hasSelectedImage && isOnResizeHandle(event->pos())) {
            m_isResizing = true;
            return;
        }
        
        // 检查是否点击在图片上
        if (isImageAt(event->pos(), imageInfo)) {
            m_selectedImage = imageInfo;
            m_hasSelectedImage = true;
            m_isDragging = true;
            setCursor(Qt::ClosedHandCursor);
            std::cout<<"选中了.\n"<<std::endl;
            viewport()->update();
            return;
        } else {
            // 如果没有点击在图片上，取消选中
            m_hasSelectedImage = false;
            viewport()->update();
        }
    }
    
    QTextEdit::mousePressEvent(event);
}

void CustomTextEdit::mouseMoveEvent(QMouseEvent *event)
{
    // 更新鼠标光标
    if (!m_isDragging && !m_isResizing) {
        if (isOnResizeHandle(event->pos())) {
            switch (m_currentHandle) {
                case TopLeft:
                case BottomRight:
                    setCursor(Qt::SizeFDiagCursor);
                    break;
                case TopRight:
                case BottomLeft:
                    setCursor(Qt::SizeBDiagCursor);
                    break;
                case Left:
                case Right:
                    setCursor(Qt::SizeHorCursor);
                    break;
                case Top:
                case Bottom:
                    setCursor(Qt::SizeVerCursor);
                    break;
                default:
                    break;
            }
        } else {
            ImageInfo imageInfo;
            if (isImageAt(event->pos(), imageInfo)) {
                setCursor(Qt::OpenHandCursor);
            } else {
                setCursor(Qt::IBeamCursor);
            }
        }
    }
    
    // 处理缩放
    if (m_isResizing && m_hasSelectedImage) {
        QPointF delta = event->pos() - m_lastMousePos;
        qreal newWidth = m_selectedImage.currentWidth;
        qreal newHeight = m_selectedImage.currentHeight;
        
        switch (m_currentHandle) {
            case TopLeft:
                newWidth -= delta.x();
                newHeight -= delta.y();
                break;
            case TopRight:
                newWidth += delta.x();
                newHeight -= delta.y();
                break;
            case BottomLeft:
                newWidth -= delta.x();
                newHeight += delta.y();
                break;
            case BottomRight:
                newWidth += delta.x();
                newHeight += delta.y();
                break;
            case Left:
                newWidth -= delta.x();
                break;
            case Right:
                newWidth += delta.x();
                break;
            case Top:
                newHeight -= delta.y();
                break;
            case Bottom:
                newHeight += delta.y();
                break;
        }
        
        // 保持纵横比
        if (event->modifiers() & Qt::ShiftModifier) {
            qreal aspectRatio = m_selectedImage.originalWidth / m_selectedImage.originalHeight;
            if (m_currentHandle == Left || m_currentHandle == Right) {
                newHeight = newWidth / aspectRatio;
            } else if (m_currentHandle == Top || m_currentHandle == Bottom) {
                newWidth = newHeight * aspectRatio;
            } else {
                // 对角缩放时，以宽度变化为准
                newHeight = newWidth / aspectRatio;
            }
        }
        
        resizeImage(m_selectedImage, newWidth, newHeight);
        
        // 立即更新控制点位置
        m_selectedImage.rect = getImageRect(m_selectedImage.cursor);
        
        m_lastMousePos = event->pos();
        viewport()->update();
        return;
    }
    
    m_lastMousePos = event->pos();
    QTextEdit::mouseMoveEvent(event);
}

void CustomTextEdit::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_isDragging = false;
        m_isResizing = false;
        setCursor(Qt::IBeamCursor);
        
        // 更新选中的图片信息
        if (m_hasSelectedImage) {
            m_selectedImage.rect = getImageRect(m_selectedImage.cursor);
            viewport()->update();
        }
    }
    
    QTextEdit::mouseReleaseEvent(event);
}

void CustomTextEdit::wheelEvent(QWheelEvent *event)
{
    // Ctrl+滚轮缩放图片
    if (event->modifiers() & Qt::ControlModifier && m_hasSelectedImage) {
        ImageInfo imageInfo;
        if (isImageAt(event->position().toPoint(), imageInfo)) {
            qreal scaleFactor = 1.0;
            if (event->angleDelta().y() > 0) {
                scaleFactor = 1.1;  // 放大10%
            } else {
                scaleFactor = 0.9;  // 缩小10%
            }
            
            qreal newWidth = imageInfo.currentWidth * scaleFactor;
            qreal newHeight = imageInfo.currentHeight * scaleFactor;
            
            // 保持纵横比
            qreal aspectRatio = imageInfo.originalWidth / imageInfo.originalHeight;
            newHeight = newWidth / aspectRatio;
            
            resizeImage(imageInfo, newWidth, newHeight);
            m_selectedImage = imageInfo;
            m_hasSelectedImage = true;
            
            event->accept();
            return;
        }
    }
    
    QTextEdit::wheelEvent(event);
}

void CustomTextEdit::contextMenuEvent(QContextMenuEvent *event)
{
    ImageInfo imageInfo;
    if (isImageAt(event->pos(), imageInfo)) {
        m_selectedImage = imageInfo;
        m_hasSelectedImage = true;
        
        // 立即更新图片位置信息
        m_selectedImage.rect = getImageRect(m_selectedImage.cursor);
        viewport()->update();
        
        m_imageContextMenu->exec(event->globalPos());
        return;
    }
    
    QTextEdit::contextMenuEvent(event);
}

void CustomTextEdit::paintEvent(QPaintEvent *event)
{
    QTextEdit::paintEvent(event);
    
    // 绘制选中图片的边框和控制手柄
    if (m_hasSelectedImage) {
        QPainter painter(viewport());
        painter.setRenderHint(QPainter::Antialiasing);
        
        // 重新计算图片位置，确保位置准确
        m_selectedImage.rect = getImageRect(m_selectedImage.cursor);
        
        // 验证图片是否仍然有效
        QTextCharFormat format = m_selectedImage.cursor.charFormat();
        if (!format.isImageFormat()) {
            // 如果光标位置不再是图片，取消选中
            m_hasSelectedImage = false;
            return;
        }
        
        // 确保矩形在视口内且有效
        QRect viewportRect = viewport()->rect();
        QRectF imageRect = m_selectedImage.rect;
        
        // 验证计算出的矩形是否合理
        if (imageRect.width() > 0 && imageRect.height() > 0 && 
            imageRect.intersects(viewportRect)) {
            
            // 绘制选择框
            QPen pen(QColor(0, 120, 215), 2, Qt::DashLine);
            painter.setPen(pen);
            painter.setBrush(Qt::NoBrush);
            painter.drawRect(imageRect);
            
            // 绘制缩放手柄
            drawResizeHandles(&painter);
        }
    }
}

void CustomTextEdit::drawResizeHandles(QPainter *painter)
{
    if (!m_hasSelectedImage) return;
    
    painter->setPen(QPen(QColor(0, 120, 215), 1));
    painter->setBrush(QBrush(Qt::white));
    
    QRectF rect = m_selectedImage.rect;
    
    // 确保矩形有效
    if (rect.width() <= 0 || rect.height() <= 0) return;
    
    // 8个控制点的位置
    QPointF points[8] = {
        rect.topLeft(),
        rect.topRight(),
        rect.bottomLeft(),
        rect.bottomRight(),
        QPointF(rect.left(), rect.center().y()),
        QPointF(rect.right(), rect.center().y()),
        QPointF(rect.center().x(), rect.top()),
        QPointF(rect.center().x(), rect.bottom())
    };
    
    // 绘制控制点
    for (int i = 0; i < 8; ++i) {
        QRectF handleRect(points[i].x() - HANDLE_SIZE/2, 
                         points[i].y() - HANDLE_SIZE/2, 
                         HANDLE_SIZE, HANDLE_SIZE);
        
        painter->drawRect(handleRect);
    }
}