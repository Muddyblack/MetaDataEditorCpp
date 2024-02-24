#include <QAudioOutput>
#include <QDate>
#include <QDebug>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QIcon>
#include <QImage>
#include <QLoggingCategory>
#include <QMap>
#include <QMediaPlayer>
#include <QMessageBox>
#include <QMovie>
#include <QPixmap>
#include <QSettings>
#include <QStandardPaths>
#include <QStringList>
#include <QVideoWidget>

#include <AppConstants.h>
#include <ImageEditorGUI.h>
#include <MetaDataHandler.h>
#include <Styles.h>
#include <TagTextEdit.h>
#include <TagWidget.h>


QString IMAGE_FORMATS = "Images (*.png *.jpg *.jpeg )"; //*.bmp *.gif *.tif *.tiff *.blend
QString VIDEO_FORMATS = "Videos (*.mp4 )"; //*.avi *.mov *.wmv *.flv *.mkv *webm
QString AUDIO_FORMATS = "Audio (*.mp3)"; // *.wav *.flac *.ogg *.aac *.m4a
QString DOCUMENT_FORMATS = "Documents (*.doc *.docx *.odt *.txt *.rtf *.md)"; //*.pdf

QString ALL_FORMATS = QString("%1;;%2;;%3;;%4").arg(
    "All (*)",
    IMAGE_FORMATS,
    VIDEO_FORMATS,
    AUDIO_FORMATS
);

QString COMPANY = "Muddyblack";
QString APP_NAME = "MetaDataEditor";


ImageEditorGUI::ImageEditorGUI()
{
    setWindowIcon(QIcon(AppConstants::ICON_PATH));
    InitUi();
}

void ImageEditorGUI::InitUi() {
     // Create a label for the image
        ImageLabel = new QLabel(this);
        ImageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        ImageLabel->hide();

        videoWidget = new QVideoWidget(this);
        videoWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        videoWidget->hide();

        
        // Create Buttons
        ModeSwitch = new QPushButton("Switch to Light Mode", this);
        connect(ModeSwitch, &QPushButton::clicked, this, &ImageEditorGUI::SwitchMode);
        AddButton = new QPushButton("Add Tag", this);
        connect(AddButton, &QPushButton::clicked, this, &ImageEditorGUI::addTag);
        addStandardButton = new QPushButton("Add Standard", this);
        connect(addStandardButton, &QPushButton::clicked, this, &ImageEditorGUI::addStandardTag);
        LoadButton = new QPushButton("Load File", this);
        connect(LoadButton, &QPushButton::clicked, this, &ImageEditorGUI::LoadFile);
        SaveButton = new QPushButton("Save File", this);
        connect(SaveButton, &QPushButton::clicked, this, &ImageEditorGUI::saveFile);

        // Add Buttons to the bottom of the layout
        QHBoxLayout *ButtonLayout = new QHBoxLayout();
        ButtonLayout->addWidget(ModeSwitch);
        ButtonLayout->addWidget(AddButton);
        ButtonLayout->addWidget(addStandardButton);
        ButtonLayout->addWidget(LoadButton);
        ButtonLayout->addWidget(SaveButton);
        ButtonLayout->setSpacing(15);

        // Create a ScrollArea
        ScrollArea = new QScrollArea(this);
        ScrollArea->setWidgetResizable(true);
        ScrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        // Create a widget for the ScrollArea
        ScrollWidget = new QWidget();
        ScrollArea->setWidget(ScrollWidget);

        // Create a layout for the ScrollArea widget
        ScrollLayout = new QVBoxLayout(ScrollWidget);
        ScrollLayout->addWidget(videoWidget);
        ScrollLayout->addWidget(ImageLabel);

        // Add all to Mainlayout
        QVBoxLayout *layout = new QVBoxLayout();
        layout->addLayout(ButtonLayout);
        layout->addWidget(ScrollArea);

        // Start GUI
        setLayout(layout);
}


void ImageEditorGUI::SwitchMode() {
    if (ModeSwitch->text() == "Switch to Dark Mode") {
        loadStyles(*qApp, AppConstants::DARKMODE_STYLE_PATH);
        ModeSwitch->setText("Switch to Light Mode");
    } else {
        loadStyles(*qApp, AppConstants::LIGHTMODE_STYLE_PATH);
        ModeSwitch->setText("Switch to Dark Mode");
    }
}

void ImageEditorGUI::UpdateWindowTitle() {
    if (FileLabel != nullptr) {
        QFileInfo fileInfo(*FileLabel);
        QString filename = fileInfo.fileName();
        setWindowTitle(QString("MetaData Editor (%1)").arg(filename));
    } else {
        setWindowTitle("MetaData Editor");
    }
}

void ImageEditorGUI::addTag() {
    TagWidget *TagWidgetItem = new TagWidget();
    TagWidgets.append(TagWidgetItem);
    ScrollLayout->insertWidget(2, TagWidgetItem);
    connect(TagWidgetItem, &TagWidget::removeRequested, this, &ImageEditorGUI::removeTagWidget);
}

void ImageEditorGUI::addStandardTag() {
    // Get the current date
    QDate currentDate = QDate::currentDate();

    // Create TagWidgets with standard values
    TagWidget *tagWidget1 = new TagWidget("START", currentDate.toString("yyyy-MM-dd"));
    QDate endDate = currentDate.addDays(7);
    TagWidget *tagWidget2 = new TagWidget("ENDDATE", endDate.toString("yyyy-MM-dd"));
    TagWidget *tagWidget3 = new TagWidget("DisplayTime", "10");

    connect(tagWidget1, &TagWidget::removeRequested, this, &ImageEditorGUI::removeTagWidget);
    connect(tagWidget2, &TagWidget::removeRequested, this, &ImageEditorGUI::removeTagWidget);
    connect(tagWidget3, &TagWidget::removeRequested, this, &ImageEditorGUI::removeTagWidget);


    // Append the new TagWidgets to the list
    TagWidgets.append(tagWidget1);
    TagWidgets.append(tagWidget2);
    TagWidgets.append(tagWidget3);

    // Insert the new TagWidgets at the beginning of the ScrollLayout
    ScrollLayout->insertWidget(2, tagWidget1);
    ScrollLayout->insertWidget(3, tagWidget2);
    ScrollLayout->insertWidget(4, tagWidget3);
}


void ImageEditorGUI::removeTagWidget() {
    TagWidget *tagWidget = qobject_cast<TagWidget*>(sender());
    if (tagWidget) {
        TagWidgets.removeOne(tagWidget);
    }
}

QString ImageEditorGUI::GetLastDir() {
    // Get the last used directory from QSettings
    QSettings settings("Company", "AppName");
    return settings.value("LastDir", "").toString();
}

void ImageEditorGUI::SetLastDir(const QString &path) {
    // Set the last used directory in QSettings
    qDebug() << "Setting last dir: " << path;
    QSettings settings("Company", "AppName");
    settings.setValue("LastDir", QFileInfo(path).path());
    qDebug() << "Succeded setting last dir: " << path;
}

void ImageEditorGUI::LoadFile() {
    try {
        QFileDialog fileDialog(this);
        fileDialog.setFileMode(QFileDialog::ExistingFile);
        fileDialog.setNameFilter(ALL_FORMATS);

        // Load the last directory from QSettings
        QString lastDir = GetLastDir();
        fileDialog.setDirectory(lastDir);

        if (fileDialog.exec()) {
            QStringList selectedFiles = fileDialog.selectedFiles();
            qDebug() << "Selected files: " << selectedFiles;
            if (!selectedFiles.isEmpty()) {
                QString ImagePath = selectedFiles[0];
                ImageLabel->clear();
      
                DisplayFile(ImagePath);
                qDebug() << "SHowing now temp file";


                // Save the directory to QSettings
                qDebug() << "Setting last dir";
                try {
                    SetLastDir(ImagePath);
                } catch (const std::exception &e) {
                    qWarning() << "Exception in SetLastDir: " << e.what();
                }
                qDebug() << "WHAT THA HELLLLL";

                if (FileLabel == nullptr) {
                    qDebug() << "FileLabel is nullptr";
                    FileLabel = new QString();
                }
                qDebug() << "WHAT THA HELLLLL";
                try {
                    *FileLabel = ImagePath;
                } catch (const std::exception &e) {
                    qWarning() << "Exception when assigning ImagePath to FileLabel: " << e.what();
                }
                //qDebug() << "FileLabel: " << *FileLabel;

                for (auto &tagWidget : TagWidgets) {
                    ScrollLayout->removeWidget(tagWidget);
                    delete tagWidget;
                }
                TagWidgets.clear();

                qDebug() << "Updating window title";

                UpdateWindowTitle();
                qDebug() << "Updated window title";
                
                // adding tags
                MetaDataHandler metadataHandler;
                QMap<QString, QString> metaDatas = metadataHandler.readMetadata(ImagePath);
                for (auto it = metaDatas.begin(); it != metaDatas.end(); ++it) {
                    TagWidget *tagWidget = new TagWidget(it.key(), it.value());
                    connect(tagWidget, &TagWidget::removeRequested, this, &ImageEditorGUI::removeTagWidget);
                    TagWidgets.append(tagWidget);

                    ScrollLayout->addWidget(tagWidget);
                }
            }
        }
    } catch (const std::exception &error) {
        qWarning() << error.what();
    }
}

void ImageEditorGUI::saveFile() {
    while (true) {
        try {
            if (FileLabel == nullptr || FileLabel->isEmpty()) {
                break;
            }

            QString fileExtension = QFileInfo(*FileLabel).suffix().toLower();

            QFileDialog fileDialog(this);
            fileDialog.setAcceptMode(QFileDialog::AcceptSave);
            fileDialog.setNameFilter(ALL_FORMATS);
            fileDialog.setDefaultSuffix(fileExtension);
            fileDialog.setDirectory(*FileLabel);

            if (!fileDialog.exec()) {
                break;
            }

            QString savePath = fileDialog.selectedFiles()[0];

            // Check if the filename has an extension
            QFileInfo fileInfo(savePath);
            if (fileInfo.suffix().isEmpty()) {
                // If not, add the default extension
                savePath += "." + fileExtension;
            }

            QMap<QString, QString> metadata;
            for (auto &widget : TagWidgets) {
                qDebug() << "widget: " << widget;
                TagWidget *tagWidget = qobject_cast<TagWidget*>(widget);
                if (tagWidget) {
                    QString tagName, tagValue;
                    std::tie(tagName, tagValue) = tagWidget->getValues();
                    metadata[tagName] = tagValue;
                }
            }
            QImage originalImage(*FileLabel);
            MetaDataHandler metadataHandler;
            qDebug() << "Writing metadata currently in new dev status " << savePath;
            metadataHandler.writeMetadata(savePath, metadata, originalImage);
            break;
            
        } catch (const std::exception &error) {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setText("Error");
            QString errorMessage = QString("An error occurred: %1. Do you want to retry?").arg(error.what());
            msgBox.setInformativeText(errorMessage);
            msgBox.setWindowTitle("Error");
            msgBox.setStandardButtons(QMessageBox::Retry | QMessageBox::Cancel);
            int ret = msgBox.exec();

            // Output the error message to the console
            qDebug() << errorMessage;
            if (ret == QMessageBox::Cancel) {
                break;
            }
        }
    }
}

void ImageEditorGUI::DisplayFile(const QString &FilePath) {
    QFileInfo fileInfo(FilePath);
    QString fileExtension = fileInfo.suffix().toLower();
    ImageLabel->clear();
    videoWidget->hide();
    try
    {

        if (VIDEO_FORMATS.contains(fileExtension) || AUDIO_FORMATS.contains(fileExtension)) {
            // If the file is a video, use QMediaPlayer and QVideoWidget to display it
            QMediaPlayer* player = new QMediaPlayer;
            QAudioOutput *audioOutput = new QAudioOutput;
            
            ImageLabel->hide();
            videoWidget->show();

            player->setVideoOutput(videoWidget);
            player->setAudioOutput(audioOutput);
            player->setSource(QUrl(FilePath));

            audioOutput->setVolume(50);
            player->play();
        }

            
        else {
            ImageLabel->show();
            QPixmap pixmap(FilePath);
            if (!pixmap.isNull()) {
                pixmap = pixmap.scaled(ScrollArea->size(), Qt::KeepAspectRatio);
                ImageLabel->setPixmap(pixmap);
            } else {
                QString resourceImagePath = ":/resources/" + fileExtension + ".png";
                if (QFile::exists(resourceImagePath)) {
                    QPixmap pixmap(resourceImagePath);
                    pixmap = pixmap.scaled(ScrollArea->size(), Qt::KeepAspectRatio);
                    ImageLabel->setPixmap(pixmap);
                } else {
                    qDebug() << "Resource Image Path: " << resourceImagePath;
                    if (QFile::exists(resourceImagePath)) {
                        QPixmap resourcePixmap(resourceImagePath);
                        resourcePixmap = resourcePixmap.scaled(ScrollArea->size(), Qt::KeepAspectRatio);
                        ImageLabel->setPixmap(resourcePixmap);
                    } else {
                        // If no image is found in the resource folder, display "Cant Display anything for this file type."
                        ImageLabel->setStyleSheet("QLabel { color : red; }");
                        ImageLabel->setText("This file type is currently not supported.");
                    }
                }
            }
        }
    }
    catch(const std::exception& e)
    {
        qCritical() << "error: " << e.what();
    }
}

void ImageEditorGUI::resizeEvent(QResizeEvent *event) {
    static QSize lastSize;  // Stores the size of the window the last time the image was resized

    // Only resize the image if the size of the window has changed significantly
    if (abs(lastSize.width() - width()) > 10 || abs(lastSize.height() - height()) > 10) {
        lastSize = size();

        if (FileLabel != nullptr && !FileLabel->isEmpty()) {
            QImageReader reader(*FileLabel);
            if (reader.canRead()) {
                if (FileLabel->toLower().endsWith(".gif")) {
                    Movie->setScaledSize(ScrollArea->size());
                } else {
                    QPixmap pixmap(*FileLabel);
                    if (!pixmap.isNull()) {
                        pixmap = pixmap.scaled(ScrollArea->size(), Qt::KeepAspectRatio);
                        ImageLabel->setPixmap(pixmap);
                    }
                }
            }
        }
    }

    QWidget::resizeEvent(event);
}