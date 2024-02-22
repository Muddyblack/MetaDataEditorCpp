#ifndef STYLES_H
#define STYLES_H

#include <QApplication>
#include <QString>

/**
 * @brief Loads a stylesheet from a file and applies it to the application.
 * @param App The application to which the stylesheet will be applied.
 * @param StylePath The path to the .qss file containing the stylesheet.
 */
void loadStyles(QApplication &App, const QString &StylePath);

#endif // STYLES_H