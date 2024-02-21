#ifndef TAGWIDGET_H
#define TAGWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <TagTextEdit.h>

class TagWidget : public QWidget {
    Q_OBJECT

public:
    TagWidget(QString TagName = "", QString TagValue = "", int TextFieldHeight = 50, QWidget *Parent = nullptr);
    std::pair<QString, QString> getValues() const;
    
public slots:
    void RemoveSelf();

private:
    TagTextEdit *TagNameEdit;
    TagTextEdit *TagValueEdit;
    QPushButton *RemoveButton;
    int TextFieldHeight;
};

#endif // TAGWIDGET_H