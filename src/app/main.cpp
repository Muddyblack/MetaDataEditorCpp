#include <ImageEditorGUI.h>
#include <Styles.h>
#include <QApplication>
#include <QIcon>
#include <QRect>

#include <AppConstants.h>



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(AppConstants::ICON_PATH));

    loadStyles(app, AppConstants::DARKMODE_STYLE_PATH);

    ImageEditorGUI editor;
    editor.setWindowTitle("MetaData Editor");
    editor.setGeometry(QRect(100, 100, 800, 600));
    editor.show();

    return app.exec();
}