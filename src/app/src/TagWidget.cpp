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
    RemoveButton->setObjectName("removeButton");
    Layout->setSpacing(10);

    setLayout(Layout);

    connect(RemoveButton, &QPushButton::clicked, this, &TagWidget::RemoveSelf);
    setTabOrder(TagNameEdit, TagValueEdit);

    connect(TagNameEdit, &TagTextEdit::TabPressed, this, &TagWidget::FocusNext);
    connect(TagValueEdit, &TagTextEdit::TabPressed, this, &TagWidget::FocusNext);
    connect(TagNameEdit, &TagTextEdit::ShiftTabPressed, this, &TagWidget::FocusPrevious);
    connect(TagValueEdit, &TagTextEdit::ShiftTabPressed, this, &TagWidget::FocusPrevious);
}

std::pair<QString, QString> TagWidget::getValues() const {
    QString tagName = TagNameEdit->toPlainText();
    QString tagValue = TagValueEdit->toPlainText();
    return std::make_pair(tagName, tagValue);
}

void TagWidget::FocusNext() {
    // This slot will be called when the TabPressed signal is emitted
    // Here you can implement the logic to switch focus to the next widget
    QWidget::focusNextChild();
}

void TagWidget::FocusPrevious() {
    // This slot will be called when the ShiftTabPressed signal is emitted
    // Here you can implement the logic to switch focus to the previous widget
    QWidget::focusPreviousChild();
}

void TagWidget::RemoveSelf() {
    qDebug() << "RemoveSelf called";
    emit removeRequested();
    deleteLater();
}