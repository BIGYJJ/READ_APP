#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>
#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QFontDialog>
#include <QColorDialog>
#include <QTextStream>
#include <QFile>
#include <QCloseEvent>
#include <QDateTime>
#include <QTextCharFormat>
#include <QTextCursor>
#include <QApplication>
#include <QClipboard>
#include <QFontComboBox>    // 字体选择框
#include <QComboBox>        // 普通下拉框
#include <QFileInfo>
#include <QTextImageFormat>
#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QTimer>

class NotePad:public QMainWindow
{
    Q_OBJECT
    public:
    NotePad(QWidget*parent=nullptr);
    ~NotePad();
    protected:
   void closeEvent(QCloseEvent *event) override;
private slots:
    // 文件操作
    void newFile();
    void openFile();
    void saveFile();
    void saveAsFile();
 // 编辑操作
    void undo();
    void redo();
    void cut();
    void copy();
    void paste();
    void selectAll();
    
    // 格式操作
    void setFont();
    void setColor();
    
    // 帮助
    void about();
    
    // 其他
    void documentModified();
    void updateStatusBar();

    void fontFamilyChanged(const QFont &font);  // 字体改变
    void fontSizeChanged(const QString &size);  // 字号改变
    void boldClicked(bool checked);             // 加粗点击
    void italicClicked(bool checked);           // 斜体点击
    void underlineClicked(bool checked);        // 下划线点击
    void textColorClicked();                    // 字体颜色点击
    void updateFormatButtons();                 // 更新按钮状态
    void insertImage();                         // 插入图片

     //工具栏切换槽函数
    void showFileToolBar();
    void showEditToolBar();
    void showFormatToolBar();
    void showInsertToolBar();
    void showHelpToolBar();
private:
    void setupUI();
    void setupMenuBar();
    void setupToolBar();
    void setupStatusBar();
    void createConnections();
    
    //创建不同的工具栏内容
    void createFileToolBarContent();
    void createEditToolBarContent();
    void createFormatToolBarContent();
    void createInsertToolBarContent();
    void createHelpToolBarContent();
    
    //清空工具栏
    void clearToolBar();

     bool maybeSave();
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);
    
    // UI组件
    QTextEdit *textEdit;
    
    // 菜单
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *formatMenu;
    QMenu *helpMenu;
    QMenu *insertMenu; 
    
    // 文件菜单动作
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *exitAction;
    
    // 编辑菜单动作
    QAction *undoAction;
    QAction *redoAction;
    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *selectAllAction;
    
    // 格式菜单动作
    QAction *fontAction;
    QAction *colorAction;
    
    // 帮助菜单动作
    QAction *aboutAction;
    // 插入图片动作
    QAction *insertImageAction;      
    // 工具栏
    QToolBar *mainToolBar;
    
    // 状态栏
    QLabel *statusLabel;
    QLabel *lineColLabel;
    QLabel *lengthLabel;
    
    // 文件相关
    QString currentFile;
    bool isUntitled;

    // 格式工具栏控件
    QFontComboBox *fontComboBox;      // 字体选择框
    QComboBox *fontSizeComboBox;      // 字号选择框
    QAction *boldAction;              // 加粗按钮
    QAction *italicAction;            // 斜体按钮
    QAction *underlineAction;         // 下划线按钮
    QAction *textColorAction;         // 字体颜色按钮
    

 // 新增：当前工具栏状态
    enum ToolBarState {
        FILE_TOOLBAR,
        EDIT_TOOLBAR,
        FORMAT_TOOLBAR,
        INSERT_TOOLBAR,
        HELP_TOOLBAR
    };
    ToolBarState currentToolBarState;

    void applyModernStyle();
    void setupCustomTitleBar();
    bool eventFilter(QObject *obj, QEvent *event) override;
    QPoint dragPosition;  // 记录拖动位置
    bool isDragging = false;
    void animateToolBarSwitch();
    void updateToolBarContent();  // 实际更新工具栏内容的函数
};


#endif // MAINWINDOW_H