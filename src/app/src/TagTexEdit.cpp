#include <TagTextEdit.h>
#include <QKeyEvent>

TagTextEdit::TagTextEdit(QWidget *Parent) : QTextEdit(Parent) {}

void TagTextEdit::keyPressEvent(QKeyEvent *Event) {
    if (Event->key() == Qt::Key_Tab && !Event->modifiers()) {
        emit TabPressed();
    } else {
        QTextEdit::keyPressEvent(Event);
    }
}

void TagTextEdit::focusInEvent(QFocusEvent *Event) {
    QTextEdit::focusInEvent(Event);
    selectAll();
}