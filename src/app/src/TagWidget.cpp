#include <TagWidget.h>
#include <QPushButton>
#include <QHBoxLayout>

TagWidget::TagWidget(QString TagName, QString TagValue, int TextFieldHeight, QWidget *Parent)
    : QWidget(Parent), TextFieldHeight(TextFieldHeight) {
    TagNameEdit = new TagTextEdit(this);
    TagNameEdit->setFixedHeight(TextFieldHeight);
    if (!TagName.trimmed().isEmpty()) {
        TagNameEdit->setPlainText(TagName);
    }

    TagValueEdit = new TagTextEdit(this);
    TagValueEdit->setFixedHeight(TextFieldHeight);
    if (!TagValue.trimmed().isEmpty()) {
        TagValueEdit->setPlainText(TagValue);
    }

    RemoveButton = new QPushButton("Remove", this);

    QHBoxLayout *Layout = new QHBoxLayout;
    Layout->addWidget(TagNameEdit);
    Layout->addWidget(TagValueEdit);
    Layout->addWidget(RemoveButton);
    Layout->setSpacing(10);

    setLayout(Layout);

    connect(RemoveButton, &QPushButton::clicked, this, &TagWidget::RemoveSelf);
    setTabOrder(TagNameEdit, TagValueEdit);
}

std::pair<QString, QString> TagWidget::getValues() const {
    QString tagName = TagNameEdit->toPlainText();
    QString tagValue = TagValueEdit->toPlainText();
    return std::make_pair(tagName, tagValue);
}

void TagWidget::RemoveSelf() {
    qDebug() << "RemoveSelf called";
    delete this;
}
