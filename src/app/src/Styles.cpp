#include <Styles.h>
#include <QFile>
#include <QTextStream>
#include <QDebug>

void loadStyles(QApplication &App, const QString &StylePath) {
    QFile file(StylePath);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString styleSheet = stream.readAll();
        App.setStyleSheet(styleSheet);
        file.close();
    } else {
        qDebug() << "Failed to open .qss file";
    }
}