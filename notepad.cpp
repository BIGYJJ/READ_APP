#include "notepad.h"

NotePad::NotePad(QWidget *parent)
    : QMainWindow(parent), isUntitled(true)
{
    setupUI();
    setupMenuBar();
   setupToolBar();
    setupStatusBar();
    createConnections();
    
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


    
}

void NotePad::setupToolBar()
{
    // 现有的文件工具栏
    fileToolBar = addToolBar("文件");
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);
    
    // 现有的编辑工具栏
    editToolBar = addToolBar("编辑");
    editToolBar->addAction(undoAction);
    editToolBar->addAction(redoAction);
    editToolBar->addSeparator();
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);
    
    // 新增：格式工具栏
    formatToolBar = addToolBar("格式");
    
    // 字体选择框
    fontComboBox = new QFontComboBox();
    fontComboBox->setToolTip("选择字体");
    formatToolBar->addWidget(fontComboBox);
    
    // 字号选择框
    fontSizeComboBox = new QComboBox();
    fontSizeComboBox->setEditable(true);  // 允许手动输入
    fontSizeComboBox->setToolTip("选择字号");
    // 添加常用字号
    QStringList sizes = {"8", "9", "10", "11", "12", "14", "16", "18", "20", "22", "24", "26", "28", "36", "48", "72"};
    fontSizeComboBox->addItems(sizes);
    fontSizeComboBox->setCurrentText("12");  // 默认12号字
    formatToolBar->addWidget(fontSizeComboBox);
    
    formatToolBar->addSeparator();
    
    // 加粗按钮
    boldAction = new QAction("B", this);
    boldAction->setCheckable(true);  // 可以切换状态
    boldAction->setToolTip("加粗");
    boldAction->setFont(QFont("Arial", 10, QFont::Bold));
    formatToolBar->addAction(boldAction);
    
    // 斜体按钮
    italicAction = new QAction("I", this);
    italicAction->setCheckable(true);
    italicAction->setToolTip("斜体");
    QFont italicFont("Arial", 10);
    italicFont.setItalic(true);
    italicAction->setFont(italicFont);
    formatToolBar->addAction(italicAction);
    
    // 下划线按钮
    underlineAction = new QAction("U", this);
    underlineAction->setCheckable(true);
    underlineAction->setToolTip("下划线");
    QFont underlineFont("Arial", 10);
    underlineFont.setUnderline(true);
    underlineAction->setFont(underlineFont);
    formatToolBar->addAction(underlineAction);
    
    formatToolBar->addSeparator();
    
    // 字体颜色按钮
    textColorAction = new QAction("A", this);
    textColorAction->setToolTip("字体颜色");
    formatToolBar->addAction(textColorAction);
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
    
    // 文本编辑器连接
    connect(textEdit, &QTextEdit::textChanged, this, &NotePad::documentModified);
    connect(textEdit, &QTextEdit::cursorPositionChanged, this, &NotePad::updateStatusBar);
    
    // 剪贴板连接
    connect(QApplication::clipboard(), &QClipboard::dataChanged, 
            this, [this]() {
        pasteAction->setEnabled(!QApplication::clipboard()->text().isEmpty());
    });

      // 新增：格式工具栏连接
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
            return saveFile(), true;
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
    // 获取当前光标位置的格式
    QTextCharFormat format = textEdit->currentCharFormat();
    
    // 更新按钮状态以反映当前格式
    boldAction->setChecked(format.fontWeight() == QFont::Bold);
    italicAction->setChecked(format.fontItalic());
    underlineAction->setChecked(format.fontUnderline());
    
    // 更新字体和字号选择框
    fontComboBox->setCurrentFont(format.font());
    fontSizeComboBox->setCurrentText(QString::number(format.fontPointSize()));
}