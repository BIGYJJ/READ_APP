#include "notepad.h"

NotePad::NotePad(QWidget *parent)
    : QMainWindow(parent), isUntitled(true)
{
     setupUI();
     setupCustomTitleBar(); 
    setupMenuBar();
    setupToolBar();
    setupStatusBar();
    createConnections();
    createFileToolBarContent();
    setCurrentFile("");
    setWindowIcon(QIcon(":/icons/notepad.png")); // 可选图标
}

void NotePad::setupUI()
{
    // 创建中央文本编辑器
    textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);
    
    // 设置文本编辑器属性
    textEdit->setFont(QFont("Consolas", 12));
    textEdit->setLineWrapMode(QTextEdit::WidgetWidth);
    
    // 设置窗口属性
    setMinimumSize(800, 600);
    resize(1000, 700);

    // 应用现代化样式表
    applyModernStyle();
    
}

NotePad::~NotePad()
{
}

void NotePad::setupMenuBar()
{
    // 文件菜单
    fileMenu = QMainWindow::menuBar()->addMenu("文件(&F)");
    
    newAction = new QAction("新建(&N)", this);
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip("创建新文档");
    
    openAction = new QAction("打开(&O)", this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip("打开现有文档");
    
    saveAction = new QAction("保存(&S)", this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip("保存当前文档");
    
    saveAsAction = new QAction("另存为(&A)", this);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    saveAsAction->setStatusTip("将文档另存为新文件");
    
    exitAction = new QAction("退出(&X)", this);
    exitAction->setShortcut(QKeySequence::Quit);
    exitAction->setStatusTip("退出应用程序");
    
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
    
    // 编辑菜单
    editMenu = QMainWindow::menuBar()->addMenu("编辑(&E)");
    
    undoAction = new QAction("撤销(&U)", this);
    undoAction->setShortcut(QKeySequence::Undo);
    undoAction->setStatusTip("撤销上一步操作");
    
    redoAction = new QAction("重做(&R)", this);
    redoAction->setShortcut(QKeySequence::Redo);
    redoAction->setStatusTip("重做上一步操作");
    
    cutAction = new QAction("剪切(&T)", this);
    cutAction->setShortcut(QKeySequence::Cut);
    cutAction->setStatusTip("剪切选定内容");
    
    copyAction = new QAction("复制(&C)", this);
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setStatusTip("复制选定内容");
    
    pasteAction = new QAction("粘贴(&P)", this);
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setStatusTip("粘贴剪贴板内容");
    
    selectAllAction = new QAction("全选(&A)", this);
    selectAllAction->setShortcut(QKeySequence::SelectAll);
    selectAllAction->setStatusTip("选择全部内容");
    
    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);
    editMenu->addSeparator();
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addSeparator();
    editMenu->addAction(selectAllAction);
    
    // 格式菜单
    formatMenu = QMainWindow::menuBar()->addMenu("格式(&O)");
    
    fontAction = new QAction("字体(&F)", this);
    fontAction->setStatusTip("设置文本字体");
    
    colorAction = new QAction("颜色(&C)", this);
    colorAction->setStatusTip("设置文本颜色");
    
    formatMenu->addAction(fontAction);
    formatMenu->addAction(colorAction);
    // 帮助菜单
    helpMenu = QMainWindow::menuBar()->addMenu("帮助(&H)");
    aboutAction = new QAction("关于(&A)", this);
    aboutAction->setStatusTip("关于此应用程序");
    helpMenu->addAction(aboutAction);

    //插入菜单
    insertMenu = menuBar()->addMenu("插入(&I)");
    insertImageAction = new QAction("", this);  // 空文本
    insertImageAction->setIcon(QIcon("D:/read_app/icons/insert_image.png"));
    insertImageAction->setToolTip("插入图片");  // 悬浮提示
    insertImageAction->setStatusTip("在光标位置插入图片");  // 状态栏提示
    insertMenu->addAction(insertImageAction);
   
    
}

void NotePad::setupToolBar()
{
     // 创建主工具栏
    mainToolBar = addToolBar("主工具栏");
    mainToolBar->setMovable(false);  // 防止工具栏被移动
    mainToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);  // 显示文字和图标

      // 格式工具栏控件初始化
    fontComboBox = new QFontComboBox();
    fontComboBox->setToolTip("选择字体");
    
    fontSizeComboBox = new QComboBox();
    fontSizeComboBox->setEditable(true);
    fontSizeComboBox->setToolTip("选择字号");
    QStringList sizes = {"8", "9", "10", "11", "12", "14", "16", "18", "20", "22", "24", "26", "28", "36", "48", "72"};
    fontSizeComboBox->addItems(sizes);
    fontSizeComboBox->setCurrentText("12");

      // 格式按钮
    boldAction = new QAction("B", this);
    boldAction->setCheckable(true);
    boldAction->setToolTip("加粗");
    boldAction->setFont(QFont("Arial", 10, QFont::Bold));
    
    italicAction = new QAction("I", this);
    italicAction->setCheckable(true);
    italicAction->setToolTip("斜体");
    QFont italicFont("Arial", 10);
    italicFont.setItalic(true);
    italicAction->setFont(italicFont);
    
    underlineAction = new QAction("U", this);
    underlineAction->setCheckable(true);
    underlineAction->setToolTip("下划线");
    QFont underlineFont("Arial", 10);
    underlineFont.setUnderline(true);
    underlineAction->setFont(underlineFont);
    
    textColorAction = new QAction("A", this);
    textColorAction->setToolTip("字体颜色");
    
    // 默认显示文件工具栏
    currentToolBarState = FILE_TOOLBAR;
    //createFileToolBarContent();
}


void NotePad::setupStatusBar()
{
    statusLabel = new QLabel("就绪");
    lineColLabel = new QLabel("行: 1, 列: 1");
    lengthLabel = new QLabel("长度: 0");
    
    QMainWindow::statusBar()->addWidget(statusLabel);
    QMainWindow::statusBar()->addPermanentWidget(lengthLabel);
    QMainWindow::statusBar()->addPermanentWidget(lineColLabel);
}

void NotePad::createConnections()
{
    // 文件操作连接
    connect(newAction, &QAction::triggered, this, &NotePad::newFile);
    connect(openAction, &QAction::triggered, this, &NotePad::openFile);
    connect(saveAction, &QAction::triggered, this, &NotePad::saveFile);
    connect(saveAsAction, &QAction::triggered, this, &NotePad::saveAsFile);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    
    // 编辑操作连接
    connect(undoAction, &QAction::triggered, this, &NotePad::undo);
    connect(redoAction, &QAction::triggered, this, &NotePad::redo);
    connect(cutAction, &QAction::triggered, this, &NotePad::cut);
    connect(copyAction, &QAction::triggered, this, &NotePad::copy);
    connect(pasteAction, &QAction::triggered, this, &NotePad::paste);
    connect(selectAllAction, &QAction::triggered, this, &NotePad::selectAll);
    
    // 格式操作连接
    connect(fontAction, &QAction::triggered, this, &NotePad::setFont);
    connect(colorAction, &QAction::triggered, this, &NotePad::setColor);
    
    // 帮助连接
    connect(aboutAction, &QAction::triggered, this, &NotePad::about);
    
    // 插入操作连接
    connect(insertImageAction, &QAction::triggered, this, &NotePad::insertImage);
    
    // 文本编辑器连接
    connect(textEdit, &QTextEdit::textChanged, this, &NotePad::documentModified);
    connect(textEdit, &QTextEdit::cursorPositionChanged, this, &NotePad::updateStatusBar);
    
    // 剪贴板连接
    connect(QApplication::clipboard(), &QClipboard::dataChanged, 
            this, [this]() {
        pasteAction->setEnabled(!QApplication::clipboard()->text().isEmpty());
    });

    // 格式工具栏连接
    connect(fontComboBox, &QFontComboBox::currentFontChanged, 
            this, &NotePad::fontFamilyChanged);
    connect(fontSizeComboBox, &QComboBox::currentTextChanged, 
            this, &NotePad::fontSizeChanged);
    connect(boldAction, &QAction::toggled, this, &NotePad::boldClicked);
    connect(italicAction, &QAction::toggled, this, &NotePad::italicClicked);
    connect(underlineAction, &QAction::toggled, this, &NotePad::underlineClicked);
    connect(textColorAction, &QAction::triggered, this, &NotePad::textColorClicked);
    
    // 当光标移动时更新格式按钮状态
    connect(textEdit, &QTextEdit::cursorPositionChanged, 
            this, &NotePad::updateFormatButtons);

    // 新增：菜单点击时切换工具栏
    connect(fileMenu, &QMenu::aboutToShow, this, &NotePad::showFileToolBar);
    connect(editMenu, &QMenu::aboutToShow, this, &NotePad::showEditToolBar);
    connect(formatMenu, &QMenu::aboutToShow, this, &NotePad::showFormatToolBar);
    connect(insertMenu, &QMenu::aboutToShow, this, &NotePad::showInsertToolBar);
    connect(helpMenu, &QMenu::aboutToShow, this, &NotePad::showHelpToolBar);
}

void NotePad::newFile()
{
    if (maybeSave()) {
        textEdit->clear();
        setCurrentFile("");
    }
}

void NotePad::openFile()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this, 
            "打开文件", "", "文本文件 (*.txt);;所有文件 (*.*)");
        
        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                textEdit->setPlainText(in.readAll());
                setCurrentFile(fileName);
                statusLabel->setText("文件已打开");
            } else {
                QMessageBox::warning(this, "警告", 
                    "无法打开文件:\n" + file.errorString());
            }
        }
    }
}

void NotePad::saveFile()
{
    if (isUntitled) {
        saveAsFile();
    } else {
        QFile file(currentFile);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << textEdit->toPlainText();
            textEdit->document()->setModified(false);
            statusLabel->setText("文件已保存");
        } else {
            QMessageBox::warning(this, "警告", 
                "无法保存文件:\n" + file.errorString());
        }
    }
}

void NotePad::saveAsFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, 
        "保存文件", currentFile, "文本文件 (*.txt);;所有文件 (*.*)");
    
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << textEdit->toPlainText();
            setCurrentFile(fileName);
            statusLabel->setText("文件已保存");
        } else {
            QMessageBox::warning(this, "警告", 
                "无法保存文件:\n" + file.errorString());
        }
    }
}

void NotePad::undo()
{
    textEdit->undo();
}

void NotePad::redo()
{
    textEdit->redo();
}

void NotePad::cut()
{
    textEdit->cut();
}

void NotePad::copy()
{
    textEdit->copy();
}

void NotePad::paste()
{
    textEdit->paste();
}

void NotePad::selectAll()
{
    textEdit->selectAll();
}

void NotePad::setFont()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, textEdit->currentFont(), this);
    if (ok) {
        QTextCursor cursor = textEdit->textCursor();
        if (cursor.hasSelection()) {
            QTextCharFormat format;
            format.setFont(font);
            cursor.mergeCharFormat(format);
        } else {
            textEdit->setCurrentFont(font);
        }
    }
}

void NotePad::setColor()
{
    QColor color = QColorDialog::getColor(textEdit->textColor(), this);
    if (color.isValid()) {
        QTextCursor cursor = textEdit->textCursor();
        if (cursor.hasSelection()) {
            QTextCharFormat format;
            format.setForeground(color);
            cursor.mergeCharFormat(format);
        } else {
            textEdit->setTextColor(color);
        }
    }
}

void NotePad::about()
{
    QMessageBox::about(this, "关于简单笔记", 
        "简单笔记 v1.0\n\n"
        "一个基于Qt6.8.2的简单文本编辑器\n"
        "支持基本的文本编辑和格式化功能\n\n"
        "构建工具: CMake\n"
        "平台: Windows");
}

void NotePad::documentModified()
{
    setWindowModified(textEdit->document()->isModified());
    updateStatusBar();
}

void NotePad::updateStatusBar()
{
    // 更新文档长度
    int length = textEdit->toPlainText().length();
    lengthLabel->setText(QString("长度: %1").arg(length));
    
    // 更新光标位置
    QTextCursor cursor = textEdit->textCursor();
    int line = cursor.blockNumber() + 1;
    int col = cursor.columnNumber() + 1;
    lineColLabel->setText(QString("行: %1, 列: %2").arg(line).arg(col));
    
    // 更新操作按钮状态
    undoAction->setEnabled(textEdit->document()->isUndoAvailable());
    redoAction->setEnabled(textEdit->document()->isRedoAvailable());
    
    bool hasSelection = textEdit->textCursor().hasSelection();
    cutAction->setEnabled(hasSelection);
    copyAction->setEnabled(hasSelection);
}

void NotePad::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}

bool NotePad::maybeSave()
{
    if (textEdit->document()->isModified())
    {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, "简单笔记",
                                 "文档已被修改。\n"
                                 "是否要保存更改?",
                                 QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
        {
            saveFile();
            return true;
        }
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

void NotePad::setCurrentFile(const QString &fileName)
{
    currentFile = fileName;
    textEdit->document()->setModified(false);
    setWindowModified(false);
    
    QString shownName = currentFile;
    if (currentFile.isEmpty()) {
        shownName = "未命名.txt";
        isUntitled = true;
    } else {
        shownName = strippedName(currentFile);
        isUntitled = false;
    }
    
    setWindowTitle(QString("%1[*] - 简单笔记").arg(shownName));
}

QString NotePad::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}


void NotePad::fontFamilyChanged(const QFont &font)
{
    QTextCursor cursor = textEdit->textCursor();
    if (cursor.hasSelection()) {
        QTextCharFormat format;
        format.setFontFamily(font.family());
        cursor.mergeCharFormat(format);
    } else {
        textEdit->setCurrentFont(font);
    }
}

void NotePad::fontSizeChanged(const QString &size)
{
    bool ok;
    int pointSize = size.toInt(&ok);
    if (ok && pointSize > 0) {
        QTextCursor cursor = textEdit->textCursor();
        if (cursor.hasSelection()) {
            QTextCharFormat format;
            format.setFontPointSize(pointSize);
            cursor.mergeCharFormat(format);
        } else {
            QFont currentFont = textEdit->currentFont();
            currentFont.setPointSize(pointSize);
            textEdit->setCurrentFont(currentFont);
        }
    }
}

void NotePad::boldClicked(bool checked)
{
    QTextCursor cursor = textEdit->textCursor();
    QTextCharFormat format;
    format.setFontWeight(checked ? QFont::Bold : QFont::Normal);
    
    if (cursor.hasSelection()) {
        cursor.mergeCharFormat(format);
    } else {
        textEdit->mergeCurrentCharFormat(format);
    }
}

void NotePad::italicClicked(bool checked)
{
    QTextCursor cursor = textEdit->textCursor();
    QTextCharFormat format;
    format.setFontItalic(checked);
    
    if (cursor.hasSelection()) {
        cursor.mergeCharFormat(format);
    } else {
        textEdit->mergeCurrentCharFormat(format);
    }
}

void NotePad::underlineClicked(bool checked)
{
    QTextCursor cursor = textEdit->textCursor();
    QTextCharFormat format;
    format.setFontUnderline(checked);
    
    if (cursor.hasSelection()) {
        cursor.mergeCharFormat(format);
    } else {
        textEdit->mergeCurrentCharFormat(format);
    }
}

void NotePad::textColorClicked()
{
    QColor color = QColorDialog::getColor(textEdit->textColor(), this);
    if (color.isValid()) {
        QTextCursor cursor = textEdit->textCursor();
        QTextCharFormat format;
        format.setForeground(color);
        
        if (cursor.hasSelection()) {
            cursor.mergeCharFormat(format);
        } else {
            textEdit->mergeCurrentCharFormat(format);
        }
    }
}

void NotePad::updateFormatButtons()
{
      // 只在格式工具栏激活时更新按钮状态
    if (currentToolBarState != FORMAT_TOOLBAR) {
        return;
    }
    
    // 获取当前光标位置的格式
    QTextCharFormat format = textEdit->currentCharFormat();
    
    // 更新按钮状态以反映当前格式
    boldAction->setChecked(format.fontWeight() == QFont::Bold);
    italicAction->setChecked(format.fontItalic());
    underlineAction->setChecked(format.fontUnderline());
    
    // 更新字体和字号选择框
    fontComboBox->setCurrentFont(format.font());
    if (format.fontPointSize() > 0) {
        fontSizeComboBox->setCurrentText(QString::number(static_cast<int>(format.fontPointSize())));
    }
}

void NotePad::insertImage()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        "选择图片", "", "图片文件 (*.png *.jpg *.jpeg *.bmp *.gif)");
    
    if (!fileName.isEmpty()) {
        QTextCursor cursor = textEdit->textCursor();
        QTextImageFormat imageFormat;
        imageFormat.setName(fileName);
        imageFormat.setWidth(300);  // 设置默认宽度
        cursor.insertImage(imageFormat);
        statusLabel->setText("图片已插入");
    }
}

void NotePad::clearToolBar()
{
    mainToolBar->clear();
}

void NotePad::createFileToolBarContent()
{
    clearToolBar();
    currentToolBarState = FILE_TOOLBAR;
    
    mainToolBar->addAction(newAction);
    mainToolBar->addAction(openAction);
    mainToolBar->addSeparator();
    mainToolBar->addAction(saveAction);
    mainToolBar->addAction(saveAsAction);
    mainToolBar->addSeparator();
    mainToolBar->addAction(exitAction);
    
    statusLabel->setText("文件工具栏");
}

void NotePad::createEditToolBarContent()
{
    clearToolBar();
    currentToolBarState = EDIT_TOOLBAR;
    
    mainToolBar->addAction(undoAction);
    mainToolBar->addAction(redoAction);
    mainToolBar->addSeparator();
    mainToolBar->addAction(cutAction);
    mainToolBar->addAction(copyAction);
    mainToolBar->addAction(pasteAction);
    mainToolBar->addSeparator();
    mainToolBar->addAction(selectAllAction);
    
    statusLabel->setText("编辑工具栏");
}

void NotePad::createFormatToolBarContent()
{
    clearToolBar();
    currentToolBarState = FORMAT_TOOLBAR;
    
    // 添加字体相关控件
    mainToolBar->addWidget(fontComboBox);
    mainToolBar->addWidget(fontSizeComboBox);
    mainToolBar->addSeparator();
    
    // 添加格式按钮
    mainToolBar->addAction(boldAction);
    mainToolBar->addAction(italicAction);
    mainToolBar->addAction(underlineAction);
    mainToolBar->addSeparator();
    
    // 添加颜色和字体对话框按钮
    mainToolBar->addAction(textColorAction);
    mainToolBar->addAction(fontAction);
    mainToolBar->addAction(colorAction);
    
    statusLabel->setText("格式工具栏");
}

void NotePad::createInsertToolBarContent()
{
    clearToolBar();
    currentToolBarState = INSERT_TOOLBAR;
    
    mainToolBar->addAction(insertImageAction);
    // 可以在这里添加更多插入相关的操作
    
    statusLabel->setText("插入工具栏");
}

void NotePad::createHelpToolBarContent()
{
    clearToolBar();
    currentToolBarState = HELP_TOOLBAR;
    
    mainToolBar->addAction(aboutAction);
    // 可以在这里添加更多帮助相关的操作
    
    statusLabel->setText("帮助工具栏");
}

void NotePad::showFileToolBar()
{
    if (currentToolBarState != FILE_TOOLBAR) {
        animateToolBarSwitch();
    }
}

void NotePad::showEditToolBar()
{
    if (currentToolBarState != EDIT_TOOLBAR) {
        createEditToolBarContent();
    }
}

void NotePad::showFormatToolBar()
{
    if (currentToolBarState != FORMAT_TOOLBAR) {
        createFormatToolBarContent();
    }
}

void NotePad::showInsertToolBar()
{
    if (currentToolBarState != INSERT_TOOLBAR) {
        createInsertToolBarContent();
    }
}

void NotePad::showHelpToolBar()
{
    if (currentToolBarState != HELP_TOOLBAR) {
        createHelpToolBarContent();
    }
}



void NotePad::applyModernStyle()
{
    QString appStyle = R"(
        /* 主窗口背景 - 添加渐变效果 */
        QMainWindow {
            background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1,
                stop: 0 #f5f3ff, stop: 0.5 #f0f0f8, stop: 1 #e8e5ff);
        }
        
        /* 文本编辑器样式 - 添加渐变边框和更柔和的设计 */
        QTextEdit {
            background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,
                stop: 0 #ffffff, stop: 1 #fafbfc);
            border: 2px solid #667eea;
            border-radius: 12px;
            padding: 20px;
            color: #2d3748;
            selection-background-color: #667eea;
            selection-color: white;
            font-family: "Microsoft YaHei", "Consolas";
        }
        
        /* 菜单栏样式 - 渐变背景 */
        QMenuBar {
            background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,
                stop: 0 #ffffff, stop: 1 #f7f9fc);
            border-bottom: 2px solid #667eea;
            padding: 8px;
            min-height: 30px;
        }
        
        QMenuBar::item {
            background-color: transparent;
            padding: 6px 18px;
            margin: 3px 4px;
            border-radius: 8px;
            color: #4a5568;
            font-weight: 500;
        }
        
        QMenuBar::item:selected {
            background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1,
                stop: 0 #667eea, stop: 1 #764ba2);
            color: white;
        }
        
        QMenuBar::item:pressed {
            background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1,
                stop: 0 #5a67d8, stop: 1 #6b46a1);
        }
        
        /* 菜单样式 */
        QMenu {
            background: #ffffff;
            border: 1px solid #e1e4e8;
            border-radius: 12px;
            padding: 8px 0px;
        }
        
        QMenu::item {
            padding: 10px 30px;
            margin: 3px 8px;
            border-radius: 8px;
            color: #4a5568;
            min-width: 160px;
            font-weight: 400;
        }
        
        QMenu::item:selected {
            background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,
                stop: 0 #e6edff, stop: 1 #f0e6ff);
            color: #5a67d8;
        }
        
        QMenu::separator {
            height: 1px;
            background: #e1e4e8;
            margin: 8px 20px;
        }
        
        /* 工具栏样式 - 渐变背景 */
        QToolBar {
            background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,
                stop: 0 #fafbfc, stop: 1 #f0f2f5);
            border-bottom: 1px solid #e1e4e8;
            padding: 8px;
            spacing: 8px;
            min-height: 50px;
        }
        
        QToolButton {
            background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,
                stop: 0 #ffffff, stop: 1 #f7fafc);
            border: 1px solid #e1e4e8;
            border-radius: 10px;
            padding: 8px 16px;
            margin: 3px;
            color: #4a5568;
            font-size: 14px;
            font-weight: 500;
            min-width: 70px;
        }
        
        QToolButton:hover {
            background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,
                stop: 0 #f0f4ff, stop: 1 #e6edff);
            border: 1px solid #667eea;
        }
        
        QToolButton:pressed {
            background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,
                stop: 0 #e6edff, stop: 1 #dce6ff);
        }
        
        QToolButton:checked {
            background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1,
                stop: 0 #667eea, stop: 1 #764ba2);
            color: white;
            border: none;
        }
        
        /* 状态栏样式 - 渐变背景 */
        QStatusBar {
            background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,
                stop: 0 #f7f9fc, stop: 1 #eef2f7);
            border-top: 1px solid #e1e4e8;
            min-height: 30px;
        }
        
        QStatusBar::item {
            border: none;
        }
        
        QStatusBar QLabel {
            color: #5a67d8;
            padding: 5px 12px;
            font-size: 13px;
            font-weight: 500;
            background: rgba(255, 255, 255, 0.5);
            border-radius: 6px;
            margin: 2px;
        }
        
        /* 下拉框样式 - 渐变效果 */
        QComboBox {
            background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,
                stop: 0 #ffffff, stop: 1 #f7fafc);
            border: 1px solid #e1e4e8;
            border-radius: 8px;
            padding: 6px 12px;
            min-width: 120px;
            color: #4a5568;
            font-weight: 500;
        }
        
        QComboBox:hover {
            border: 1px solid #667eea;
            background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,
                stop: 0 #f0f4ff, stop: 1 #e6edff);
        }
        
        QComboBox:focus {
            border: 2px solid #667eea;
            outline: none;
        }
        
        QComboBox::drop-down {
            border: none;
            width: 25px;
            background: transparent;
        }
        
        QComboBox::down-arrow {
            image: none;
            width: 0;
            height: 0;
            border-left: 5px solid transparent;
            border-right: 5px solid transparent;
            border-top: 6px solid #667eea;
            margin-right: 8px;
        }
        
        QComboBox QAbstractItemView {
            background: #ffffff;
            border: 1px solid #e1e4e8;
            border-radius: 8px;
            selection-background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,
                stop: 0 #667eea, stop: 1 #764ba2);
            selection-color: white;
            padding: 4px;
        }
        
        /* 滚动条样式 - 渐变设计 */
        QTextEdit QScrollBar:vertical {
            background: #f0f2f5;
            width: 12px;
            border-radius: 6px;
            margin: 2px;
        }
        
        QTextEdit QScrollBar::handle:vertical {
            background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,
                stop: 0 #667eea, stop: 1 #764ba2);
            border-radius: 6px;
            min-height: 40px;
        }
        
        QTextEdit QScrollBar::handle:vertical:hover {
            background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,
                stop: 0 #5a67d8, stop: 1 #6b46a1);
        }
        
        QTextEdit QScrollBar::add-line:vertical,
        QTextEdit QScrollBar::sub-line:vertical {
            height: 0px;
        }
        
        QTextEdit QScrollBar:horizontal {
            background: #f0f2f5;
            height: 12px;
            border-radius: 6px;
            margin: 2px;
        }
        
        QTextEdit QScrollBar::handle:horizontal {
            background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,
                stop: 0 #667eea, stop: 1 #764ba2);
            border-radius: 6px;
            min-width: 40px;
        }
        
        QTextEdit QScrollBar::handle:horizontal:hover {
            background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,
                stop: 0 #5a67d8, stop: 1 #6b46a1);
        }
        
        QTextEdit QScrollBar::add-line:horizontal,
        QTextEdit QScrollBar::sub-line:horizontal {
            width: 0px;
        }
        
        /* 对话框样式 */
        QDialog {
            background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1,
                stop: 0 #f5f3ff, stop: 1 #e8e5ff);
        }
        
        /* 按钮样式 - 渐变效果 */
        QPushButton {
            background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1,
                stop: 0 #667eea, stop: 1 #764ba2);
            border: none;
            border-radius: 8px;
            padding: 8px 20px;
            color: white;
            font-weight: 600;
            min-width: 90px;
        }
        
        QPushButton:hover {
            background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1,
                stop: 0 #5a67d8, stop: 1 #6b46a1);
        }
        
        QPushButton:pressed {
            background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1,
                stop: 0 #4c55c0, stop: 1 #5d3a8a);
        }
        
        /* 消息框样式 */
        QMessageBox {
            background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1,
                stop: 0 #f5f3ff, stop: 1 #e8e5ff);
        }
        
        QMessageBox QLabel {
            color: #2d3748;
            min-width: 320px;
            font-size: 14px;
        }
    )";
    
    // 应用样式表
    this->setStyleSheet(appStyle);
    
    // 为文本编辑器添加更柔和的阴影效果
    QGraphicsDropShadowEffect* textShadow = new QGraphicsDropShadowEffect(this);
    textShadow->setBlurRadius(20);
    textShadow->setXOffset(0);
    textShadow->setYOffset(5);
    textShadow->setColor(QColor(102, 126, 234, 50));  // 紫色阴影
    textEdit->setGraphicsEffect(textShadow);
    
}

// 添加自定义标题栏（可选，让窗口更现代）
void NotePad::setupCustomTitleBar()
{
    // 创建自定义标题栏
    QWidget* titleBar = new QWidget(this);
    titleBar->setFixedHeight(45);
    titleBar->setStyleSheet(R"(
        QWidget {
            background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,
                stop: 0 rgba(102, 126, 234, 0.1), 
                stop: 0.5 rgba(118, 75, 162, 0.1), 
                stop: 1 rgba(102, 126, 234, 0.1));
            border-bottom: 1px solid rgba(102, 126, 234, 0.2);
        }
    )");
    
    QHBoxLayout* titleLayout = new QHBoxLayout(titleBar);
    titleLayout->setContentsMargins(15, 0, 15, 0);
    
    // 添加应用图标和标题
    QLabel* iconLabel = new QLabel();
    iconLabel->setPixmap(QPixmap(":/icons/notepad.png").scaled(28, 28, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    
    QLabel* titleLabel = new QLabel("简单笔记");
    titleLabel->setStyleSheet(R"(
        color: #4a5568; 
        font-size: 16px; 
        font-weight: 600;
        letter-spacing: 0.5px;
    )");
    
    // 添加窗口控制按钮
    QPushButton* minimizeBtn = new QPushButton();
    QPushButton* maximizeBtn = new QPushButton();
    QPushButton* closeBtn = new QPushButton();
    
    // 设置按钮图标（使用Unicode字符）
    minimizeBtn->setText("－");
    maximizeBtn->setText("□");
    closeBtn->setText("✕");
    
    QString controlBtnStyle = R"(
        QPushButton {
            background: transparent;
            border: none;
            border-radius: 8px;
            width: 35px;
            height: 35px;
            font-size: 18px;
            color: #718096;
            font-weight: 400;
            margin: 0 2px;
        }
        QPushButton:hover {
            background: rgba(102, 126, 234, 0.1);
            color: #667eea;
        }
    )";
    
    QString closeBtnStyle = controlBtnStyle + R"(
        QPushButton:hover {
            background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1,
                stop: 0 #ff6b6b, stop: 1 #ee5a5a);
            color: white;
        }
    )";
    
    minimizeBtn->setStyleSheet(controlBtnStyle);
    maximizeBtn->setStyleSheet(controlBtnStyle);
    closeBtn->setStyleSheet(closeBtnStyle);
    
    // 添加分隔线
    QFrame* separator = new QFrame();
    separator->setFrameShape(QFrame::VLine);
    separator->setStyleSheet(R"(
        QFrame {
            background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,
                stop: 0 transparent,
                stop: 0.5 rgba(102, 126, 234, 0.3),
                stop: 1 transparent);
            max-width: 1px;
            margin: 8px 10px;
        }
    )");
    
    titleLayout->addWidget(iconLabel);
    titleLayout->addWidget(titleLabel);
    titleLayout->addStretch();
    titleLayout->addWidget(separator);
    titleLayout->addWidget(minimizeBtn);
    titleLayout->addWidget(maximizeBtn);
    titleLayout->addWidget(closeBtn);
    
    // 连接按钮信号
    connect(minimizeBtn, &QPushButton::clicked, this, &QWidget::showMinimized);
    connect(maximizeBtn, &QPushButton::clicked, [this]() {
        if (isMaximized()) {
            showNormal();
            // 更新按钮文本
            QPushButton* btn = qobject_cast<QPushButton*>(sender());
            if (btn) btn->setText("□");
        } else {
            showMaximized();
            // 更新按钮文本
            QPushButton* btn = qobject_cast<QPushButton*>(sender());
            if (btn) btn->setText("❐");
        }
    });
    connect(closeBtn, &QPushButton::clicked, this, &QWidget::close);
    
    // 添加悬浮动画效果
    auto addHoverAnimation = [](QPushButton* btn) {
        btn->installEventFilter(new QObject());
        QPropertyAnimation* scaleAnimation = new QPropertyAnimation(btn, "geometry");
        scaleAnimation->setDuration(150);
        
        btn->setProperty("hoverAnimation", QVariant::fromValue(scaleAnimation));
    };
    
    addHoverAnimation(minimizeBtn);
    addHoverAnimation(maximizeBtn);
    addHoverAnimation(closeBtn);
    
    // 设置拖动功能
    titleBar->installEventFilter(this);
    
    // 为标题栏添加轻微阴影
    QGraphicsDropShadowEffect* titleBarShadow = new QGraphicsDropShadowEffect(this);
    titleBarShadow->setBlurRadius(10);
    titleBarShadow->setXOffset(0);
    titleBarShadow->setYOffset(2);
    titleBarShadow->setColor(QColor(102, 126, 234, 20));
    titleBar->setGraphicsEffect(titleBarShadow);
}



// 实现事件过滤器以支持窗口拖动
bool NotePad::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            isDragging = true;
            dragPosition = mouseEvent->globalPos() - frameGeometry().topLeft();
            return true;
        }
    }
    else if (event->type() == QEvent::MouseMove) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (isDragging && mouseEvent->buttons() & Qt::LeftButton) {
            move(mouseEvent->globalPos() - dragPosition);
            return true;
        }
    }
    else if (event->type() == QEvent::MouseButtonRelease) {
        isDragging = false;
        return true;
    }
    return QMainWindow::eventFilter(obj, event);
}


// 实现 updateToolBarContent 函数
void NotePad::updateToolBarContent()
{
    // 这个函数在动画中间被调用，用于实际切换工具栏内容
    // 根据菜单的触发来决定显示哪个工具栏
    
    QObject* sender = this->sender();
    
    if (sender == fileMenu || 
        (sender && sender->inherits("QPropertyAnimation") && currentToolBarState == FILE_TOOLBAR)) {
        createFileToolBarContent();
    }
    else if (sender == editMenu || 
             (sender && sender->inherits("QPropertyAnimation") && currentToolBarState == EDIT_TOOLBAR)) {
        createEditToolBarContent();
    }
    else if (sender == formatMenu || 
             (sender && sender->inherits("QPropertyAnimation") && currentToolBarState == FORMAT_TOOLBAR)) {
        createFormatToolBarContent();
    }
    else if (sender == insertMenu || 
             (sender && sender->inherits("QPropertyAnimation") && currentToolBarState == INSERT_TOOLBAR)) {
        createInsertToolBarContent();
    }
    else if (sender == helpMenu || 
             (sender && sender->inherits("QPropertyAnimation") && currentToolBarState == HELP_TOOLBAR)) {
        createHelpToolBarContent();
    }
}

// 修改后的 animateToolBarSwitch 实现
void NotePad::animateToolBarSwitch()
{
    // 保存即将切换到的状态
    ToolBarState targetState = currentToolBarState;
    
    // 根据触发源确定目标状态
    QObject* triggerSource = sender();
    if (triggerSource == fileMenu) targetState = FILE_TOOLBAR;
    else if (triggerSource == editMenu) targetState = EDIT_TOOLBAR;
    else if (triggerSource == formatMenu) targetState = FORMAT_TOOLBAR;
    else if (triggerSource == insertMenu) targetState = INSERT_TOOLBAR;
    else if (triggerSource == helpMenu) targetState = HELP_TOOLBAR;
    
    // 创建淡出动画
    QPropertyAnimation* fadeOut = new QPropertyAnimation(mainToolBar, "windowOpacity");
    fadeOut->setDuration(150);
    fadeOut->setStartValue(1.0);
    fadeOut->setEndValue(0.0);
    
    connect(fadeOut, &QPropertyAnimation::finished, [this, targetState]() {
        // 切换工具栏内容
        switch(targetState) {
            case FILE_TOOLBAR:
                createFileToolBarContent();
                break;
            case EDIT_TOOLBAR:
                createEditToolBarContent();
                break;
            case FORMAT_TOOLBAR:
                createFormatToolBarContent();
                break;
            case INSERT_TOOLBAR:
                createInsertToolBarContent();
                break;
            case HELP_TOOLBAR:
                createHelpToolBarContent();
                break;
        }
        
        // 创建淡入动画
        QPropertyAnimation* fadeIn = new QPropertyAnimation(mainToolBar, "windowOpacity");
        fadeIn->setDuration(150);
        fadeIn->setStartValue(0.0);
        fadeIn->setEndValue(1.0);
        fadeIn->start(QPropertyAnimation::DeleteWhenStopped);
    });
    
    fadeOut->start(QPropertyAnimation::DeleteWhenStopped);
}