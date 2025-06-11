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
private:
    void setupUI();
    void setupMenuBar();
    void setupToolBar();
    void setupStatusBar();
    void createConnections();
    
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
    
    // 工具栏
    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    
    // 状态栏
    QLabel *statusLabel;
    QLabel *lineColLabel;
    QLabel *lengthLabel;
    
    // 文件相关
    QString currentFile;
    bool isUntitled;
};


#endif // MAINWINDOW_H