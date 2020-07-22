#ifndef TEXTBUTTON_H
#define TEXTBUTTON_H

#include <QGraphicsObject>
#include <QVariantAnimation>
#include <QFont>
#include <QColor>
#include "clickablegraphicsobject.h"
#include "GraphicResources/fontdescr.h"

namespace CommonGraphics {

class TextButton : public ClickableGraphicsObject
{
    Q_OBJECT
public:
    explicit TextButton(QString text, const FontDescr &fd, QColor color, bool bSetClickable, ScalableGraphicsObject *parent = nullptr, int addWidth = 0);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

    double getOpacity();
    void quickSetOpacity(double opacity);

    void quickHide();
    void animateShow(int animationSpeed);
    void animateHide(int animationSpeed);

    int getWidth();
    void setText(QString text);
    QString text();

    void setCurrentOpacity(double opacity);
    void setUnhoverOpacity(double unhoverOpacity);

    void recalcBoundingRect();

    void setTextAlignment(int alignment);

protected:
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private slots:
    void onTextHoverOpacityChanged(const QVariant &value);

private:
    const int MARGIN_HEIGHT = 5;
    QString text_;
    QColor color_;
    FontDescr fontDescr_;

    int width_;
    int height_;
    int addWidth_;   // HACK - allows full displaying of text in Upgrade Widget

    double curTextOpacity_;
    QVariantAnimation textOpacityAnimation_;

    double unhoverOpacity_;

    int textAlignment_;
};

}
#endif // TEXTBUTTON_H
