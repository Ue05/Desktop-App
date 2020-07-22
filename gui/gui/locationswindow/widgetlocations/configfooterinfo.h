#ifndef CONFIGLOCATIONFOOTER_H
#define CONFIGLOCATIONFOOTER_H

#include <QAbstractButton>
#include <QVariantAnimation>
#include "CommonWidgets/iconbuttonwidget.h"

class ConfigFooterInfo : public QAbstractButton
{
    Q_OBJECT
public:
    explicit ConfigFooterInfo(QWidget *parent = nullptr);

    QSize sizeHint() const override;

signals:
    void addCustomConfigClicked();

protected:
    void paintEvent(QPaintEvent *event) override;

    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void onTextOpacityChanged(const QVariant &value);
    void onIconOpacityChanged(const QVariant &value);

private:
    bool pressed_;
    QString text_;

    const int HEIGHT_ = 48;
    QFont font_;

    double curTextOpacity_;
    QVariantAnimation textOpacityAnimation_;

    double curIconOpacity_;
    QVariantAnimation iconOpacityAnimation_;


};

#endif // CONFIGLOCATIONFOOTER_H
