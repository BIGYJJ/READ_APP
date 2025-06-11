#include <QApplication>
#include <QStyleFactory>
#include <QDir>
#include "notepad.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // 设置应用程序信息
    app.setApplicationName("简单笔记");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("My Notes");
    
    // 设置样式
    app.setStyle(QStyleFactory::create("Fusion"));
    
    // 创建并显示主窗口
    NotePad notepad;
    notepad.show();
    
    return app.exec();
}