#ifndef TAGTEXTEDIT_H
#define TAGTEXTEDIT_H

#include <QTextEdit>

class TagTextEdit : public QTextEdit {
    Q_OBJECT

public:
    TagTextEdit(QWidget *Parent = nullptr);

signals:
    void TabPressed();

protected:
    void keyPressEvent(QKeyEvent *Event) override;
    void focusInEvent(QFocusEvent *Event) override;
};

#endif // TAGTEXTEDIT_H