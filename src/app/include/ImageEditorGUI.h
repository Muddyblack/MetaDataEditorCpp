#ifndef IMAGE_EDITOR_GUI_H
#define IMAGE_EDITOR_GUI_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>

#include <QVideoWidget>
#include <QMediaPlayer>
#include <TagTextEdit.h>
#include <MetaDataHandler.h>


class ImageEditorGUI : public QWidget
{
    Q_OBJECT

public:
    ImageEditorGUI();


protected:

private:
    QString *imageLabel;
    QList<QWidget*> TagWidgets;
    QMovie *Movie;

    QLabel *ImageLabel;
    QPushButton *ModeSwitch;
    QPushButton *AddButton;
    QPushButton *addStandardButton;
    QPushButton *LoadButton;
    QPushButton *SaveButton;
    QScrollArea *ScrollArea;
    QVideoWidget *videoWidget;
    QWidget *ScrollWidget;
    QVBoxLayout *ScrollLayout;

    void InitUi();
    void UpdateWindowTitle();
    QString extractThumbnail(const QString &videoPath);
    void removeTagWidget();    

private slots:
    void SwitchMode();
    void addTag();
    void addStandardTag();
    void LoadFile();
    void saveFile();
    QString GetLastDir();
    void SetLastDir(const QString& path);
    void DisplayFile(const QString &FilePath);
};



#endif // IMAGE_EDITOR_GUI_H