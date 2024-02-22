#include <TagTextEdit.h>
#include <QKeyEvent>
#include <QDebug>

TagTextEdit::TagTextEdit(QWidget *Parent) : QTextEdit(Parent) {}

void TagTextEdit::keyPressEvent(QKeyEvent *Event) {
    if (Event->key() == Qt::Key_Tab) {
        if (Event->modifiers() & Qt::ControlModifier) {
            emit CtrlTabPressed();
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