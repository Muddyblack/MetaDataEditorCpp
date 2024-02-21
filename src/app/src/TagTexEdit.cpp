#include <TagTextEdit.h>
#include <QKeyEvent>

TagTextEdit::TagTextEdit(QWidget *Parent) : QTextEdit(Parent) {}

void TagTextEdit::keyPressEvent(QKeyEvent *Event) {
    if (Event->key() == Qt::Key_Tab) {
        if (Event->modifiers() & Qt::ShiftModifier) {
            emit ShiftTabPressed();
            Event->ignore();  // Ignore the event so QTextEdit doesn't process it
        } else {
            emit TabPressed();
        }
    } else {
        QTextEdit::keyPressEvent(Event);
    }
}
void TagTextEdit::focusInEvent(QFocusEvent *Event) {
    QTextEdit::focusInEvent(Event);
    selectAll();
}

bool TagTextEdit::focusNextPrevChild(bool next) {
    if (next) {
        return QTextEdit::focusNextPrevChild(next);
    } else {
        return false;
    }
}