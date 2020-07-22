#ifndef LOGINYESNOBUTTON_H
#define LOGINYESNOBUTTON_H

#include <QFont>
#include <QColor>
#include <QGraphicsObject>
#include <QGraphicsPixmapItem>
#include <QVariantAnimation>
#include "CommonGraphics/clickablegraphicsobject.h"

namespace LoginWindow {

class LoginYesNoButton : public ClickableGraphicsObject
{
    Q_OBJECT
public:

    explicit LoginYesNoButton(QString text, ScalableGraphicsObject * parent = nullptr);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

    void setText(QString text);

    bool isHighlighted();

    void animateButtonHighlight();
    void animateButtonUnhighlight();

    void setOpacityByFactor(double newOpacityFactor);

signals:
    void activated();
    void deactivated();

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private slots:
    void onTextHoverOpacityChanged(const QVariant &value);
    void onIconHoverOpacityChanged(const QVariant &value);
    void onTextHoverOffsetChanged(const QVariant &value);

private:
    int width_;
    int height_;

    QString text_;
    bool highlight_;

    double curTextOpacity_;
    QVariantAnimation textOpacityAnimation_;

    double curIconOpacity_;
    QVariantAnimation iconOpacityAnimation_;

    int curTextPosX_;
    QVariantAnimation textPosXAnimation_;

    const int MARGIN_UNHOVER_TEXT_PX = 16;
    const int MARGIN_HOVER_TEXT_PX   = 24;
};

} // namespace LoginWindow

#endif // LOGINYESNOBUTTON_H
