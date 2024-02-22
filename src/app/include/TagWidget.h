#ifndef TAGWIDGET_H
#define TAGWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <TagTextEdit.h>

/**
 * @class TagWidget
 * @brief A widget for displaying and editing tags.
 *
 * This class provides a widget that allows users to edit tag names and their values.
 */
class TagWidget : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Construct a new Tag Widget object.
     *
     * @param TagName The initial tag name.
     * @param TagValue The initial tag value.
     * @param TextFieldHeight The height of the text field.
     * @param Parent The parent widget.
     */
    explicit TagWidget(QString TagName = "", QString TagValue = "", int TextFieldHeight = 50, QWidget *Parent = nullptr);
    /**
     * @brief Get the current tag name and value.
     *
     * @return A pair containing the tag name and value.
     */
    std::pair<QString, QString> getValues() const;
    
public slots:
    /// @brief Remove this widget.
    void RemoveSelf();
    /// @brief Focus the next widget using tab.
    void FocusNext();
    /// @brief Focus the previous widget using shift+tab.
    void FocusPrevious(); 

private:
    TagTextEdit *TagNameEdit; ///< Textfield for the tag name.
    TagTextEdit *TagValueEdit; ///< Textfield for the tag value.
    QPushButton *RemoveButton; ///< The button for removing this widget.
    int TextFieldHeight; ///< The height of the text fields.
    
    
signals:
    /// @brief Signal that is emitted when the widget is requested to be removed.
    void removeRequested();
};

#endif // TAGWIDGET_H