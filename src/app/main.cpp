#include <ImageEditorGUI.h>
#include <Styles.h>
#include <QApplication>
#include <QIcon>
#include <QRect>


#include <iostream>

QString ICON_PATH = ":/app.ico";
QString DARKMODE_STYLE_PATH = ":/styles/darkmode_style.qss";
QString LIGHTMODE_STYLE_PATH = ":/styles/lightmode_style.qss";

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(ICON_PATH));

    loadStyles(app, DARKMODE_STYLE_PATH);

    ImageEditorGUI editor;
    editor.setWindowTitle("MetaData Editor");
    editor.setGeometry(QRect(100, 100, 800, 600));
    editor.show();

    return app.exec();
}