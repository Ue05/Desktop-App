#ifndef NEWSFEEDWINDOWITEM_H
#define NEWSFEEDWINDOWITEM_H

#include <QTextBrowser>
#include "CommonGraphics/scalablegraphicsobject.h"
#include "NewsFeedWindow/inewsfeedwindow.h"
#include "CommonGraphics/iconbutton.h"
#include "PreferencesWindow/escapebutton.h"
#include "NewsFeedWindow/scrollablemessage.h"


namespace NewsFeedWindow {

class NewsFeedWindowItem : public ScalableGraphicsObject, public INewsFeedWindow
{
    Q_OBJECT
    Q_INTERFACES(INewsFeedWindow)
public:
    explicit NewsFeedWindowItem(QGraphicsObject *parent = nullptr);

    QGraphicsObject *getGraphicsObject() { return this; }
    virtual QRectF boundingRect() const;
    virtual void setClickable(bool isClickable);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    void updateScaling();

public slots:
    virtual void setMessages(const ProtoTypes::ArrayApiNotification &arr);

signals:
    void messageReaded(qint64 messageId);
    void escClick();
    void closeClick();
    void minimizeClick();

protected:
    bool eventFilter(QObject *watching, QEvent *event);
    void keyPressEvent(QKeyEvent *event);

private slots:
    void onBackArrowButtonClicked();
    void onLeftClick();
    void onRightClick();

private:
    void updateCurrentMessage();
    void updateLeftRightArrowClickability();

    void updatePositions();

    ScrollableMessage * messageItem_;

    const int MARGIN = 16;

    QString windowTitle_;
    QString messageTitle_;

    ProtoTypes::ArrayApiNotification messages_;

    int curMessageInd_;
    qint64 curMessageId_;
    bool messageIdIsInitialized_;

    QString mainBackground_;
    QString headerBackground_;

    double curBackgroundOpacity_;
    double curHeaderBackgroundOpacity_;

    double curMessageOpacity_;
    double curMessageTitleOpacity_;
    double curDefaultOpacity_;

    IconButton *backArrowButton_;
    IconButton *leftArrowButton_;
    IconButton *rightArrowButton_;

    IconButton *minimizeButton_;
    IconButton *closeButton_;

    QString locationButtonBG_;
};

}

#endif // NEWSFEEDWINDOWITEM_H
