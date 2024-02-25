#ifndef IMAGE_EDITOR_GUI_H
#define IMAGE_EDITOR_GUI_H

#include <QLabel>
#include <QMediaPlayer>
#include <QPushButton>
#include <QScrollArea>
#include <QString>
#include <QVBoxLayout>
#include <QVideoWidget>
#include <QWidget>

#include <MetaDataHandler.h>
#include <TagTextEdit.h>


#include <QTemporaryFile>

/**
 * @class ImageEditorGUI
 * @brief This class provides a GUI for editing files.
 * 
 * The GUI includes a QLabel for the image, QPushButton for various actions, 
 * QScrollArea for scrolling, QVideoWidget for displaying videos, and QVBoxLayout for layout.
 * It also includes methods for initializing the UI, updating the window title, 
 * extracting thumbnails, and removing tag widgets.
 */
class ImageEditorGUI : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for ImageEditorGUI.
     * 
     * Sets the window icon and initializes the UI.
     */
    ImageEditorGUI();

protected:
    /**
     * @brief Handles resize events.
     * 
     * Resizes the image if the size of the window has changed significantly.
     * @param event The resize event.
     */
    void resizeEvent(QResizeEvent *event);

private:
    QString *FileLabel;
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

    /**
     * @brief Initializes the UI.
     * 
     * Creates the QLabel for the image, QPushButton for various actions, 
     * QScrollArea for scrolling, QVideoWidget for displaying videos, and QVBoxLayout for the layout.
     */
    void InitUi();

    /**
     * @brief Updates the window title.
     * 
     * If a file is loaded, the title is "APPLICATIONANME (filename)". 
     * The title keeps the applicationname.
     */
    void UpdateWindowTitle();

    /**
     * @brief Removes a tag widget from the GUI.
     * 
     * Removes the sender of the signal from the list of tag widgets.
     */
    void removeTagWidget();    

private slots:
    /**
     * @brief Switches the mode of the GUI.
     * 
     * If the current mode is dark, it switches to light mode and vice versa.
     */
    void SwitchMode();

    /**
     * @brief Adds a tag widget to the GUI.
     * 
     * Creates a new TagWidget, adds it to the list of tag widgets, 
     * and inserts it into the ScrollLayout.
     */
    void addTag();

    /**
     * @brief Adds standard tags to the GUI.
     * 
     * Creates three new TagWidgets with standard values and inserts them into the ScrollLayout.
     * The standard tags are currently "START", "END", and "DisplayTime".
     */
    void addStandardTag();

    /**
     * @brief Loads a file into the GUI.
     * 
     * Opens a file-explorer-dialog for the user to select a file.
     * Then loads the selected file into the GUI.
     */
    void LoadFile();

    /**
     * @brief Saves the current file.
     * 
     * Opens a file-explorer-dialog for the user to select a location and new filename.
     * Then saves the current file to the selected location.
     */
    void saveFile();

    /**
     * @brief Gets the last directory used.
     * 
     * Returns the lasttime used directory in filexplorer from QSettings.
     * So the application can open the fileexplorer in the last used directory.
     * @return The last directory used.
     */
    QString GetLastDir();

    /**
     * @brief Sets the last opened directory.
     * 
     * Sets the last directory opened in fileexplorer to QSettings.
     * So next time the application is opened it can open in the last directory.
     * @param path The path to set as the last directory.
     */
    void SetLastDir(const QString& path);

    /**
     * @brief Displays a file in the GUI.
     * 
     * If the file is a video or audio file, it is displayed using QMediaPlayer and QVideoWidget. 
     * Otherwise, it is displayed as an image using QLabel if it is a supported fileformat.
     * @param FilePath The path of the file to display.
     */
    void DisplayFile(const QString &FilePath);

};



#endif // IMAGE_EDITOR_GUI_H