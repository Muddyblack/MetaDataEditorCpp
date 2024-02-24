/**
 * @file main.cpp
 * @brief Entry point for the MetaData Editor application.
 */
#include <ImageEditorGUI.h>
#include <Styles.h>
#include <QApplication>
#include <QIcon>
#include <QRect>
#include <filesystem>
#include <AppConstants.h>
#include <iostream>
#include <string>
#include <Logger.h>

int main(int argc, char *argv[])
{
    logInfo() << "MetaData Editor starting...";
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(AppConstants::ICON_PATH));

    loadStyles(app, AppConstants::DARKMODE_STYLE_PATH);

    ImageEditorGUI editor;
    editor.setWindowTitle("MetaData Editor");
    editor.setGeometry(QRect(100, 100, 800, 600));
    editor.show();

    return app.exec();
}