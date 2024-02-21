#ifndef TAGTEXTEDIT_H
#define TAGTEXTEDIT_H

#include <QTextEdit>

class TagTextEdit : public QTextEdit {
    Q_OBJECT

public:
    TagTextEdit(QWidget *Parent = nullptr);

protected:
signals:
    void TabPressed();
    void ShiftTabPressed();

protected:
    bool focusNextPrevChild(bool next) override;

    void keyPressEvent(QKeyEvent *Event) override;
    void focusInEvent(QFocusEvent *Event) override;
};

#endif // TAGTEXTEDIT_H