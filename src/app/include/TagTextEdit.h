/**
 * @file TagTextEdit.h
 * @brief Defines the TagTextEdit class for handling key press events.
 * @author Muddyblack
 * @date 20.02.2024
 */
#ifndef TAGTEXTEDIT_H
#define TAGTEXTEDIT_H

#include <QTextEdit>

/**
 * @class TagTextEdit
 * @brief A custom QTextEdit that emits signals when Tab or Shift+Tab are pressed.
 *
 * This class provides a QTextEdit that can signal when the user presses Tab or Shift+Tab.
 */
class TagTextEdit : public QTextEdit {
    Q_OBJECT

public:
    /**
     * @brief Construct a new TagTextEdit object.
     *
     * @param Parent The parent widget.
     */
    TagTextEdit(QWidget *Parent = nullptr);

signals:
    /// @brief Signal that is emitted when the Tab key is pressed.
    void TabPressed();
    /// @brief Signal that is emitted when Shift+Tab is pressed.
    void CtrlTabPressed();

protected:
    /**
     * @brief Override the default behavior when the focus is moved to the next or previous child widget.
     *
     * @param next If true, move focus to the next child; if false, do nothing.
     * @return true if the focus was moved; false otherwise.
     */
    bool focusNextPrevChild(bool next) override;

        /**
     * @brief Override the default key press event to emit signals when Tab or Shift+Tab are pressed.
     *
     * @param Event The key event.
     */
    void keyPressEvent(QKeyEvent *Event) override;

    /**
     * @brief Override the default focus in event to select all text when the widget gains focus.
     *
     * @param Event The focus event.
     */
    void focusInEvent(QFocusEvent *Event) override;
};

#endif // TAGTEXTEDIT_H