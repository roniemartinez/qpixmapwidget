/*
Copyright (c) 2013 Ronie Martinez (ronmarti18@gmail.com)
All rights reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the GNU Lesser General Public License for more
details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
02110-1301  USA
*/

/* Based on python implementation (qpixmapwidget.py) found at
 * http://pydoc.net/Python/taurus/2.1.0/taurus.qt.qtgui.display.qpixmapwidget/
 * http://www.tango-controls.org/static/taurus/v300/doc/html/devel/api/taurus/qt/qtgui/display/_QPixmapWidget.html
 */

#ifndef QPIXMAPWIDGET_H
#define QPIXMAPWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QUrl>
#include <QMimeData>

class QPixmapWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QPixmap pixmap READ pixmap WRITE setPixmap)
    Q_PROPERTY(Qt::AspectRatioMode aspectRatioMode READ aspectRatioMode WRITE setAspectRatioMode)
    Q_PROPERTY(Qt::TransformationMode transformationMode READ transformationMode WRITE setTransformationMode)
    Q_PROPERTY(Qt::Alignment alignment READ alignment WRITE setAlignment)
    Q_PROPERTY(QBrush backgroundBrush READ backgroundBrush WRITE setBackgroundBrush)

public:
    QPixmapWidget(QWidget *parent = 0);
    QPixmapWidget(const QPixmap& pixmap, QWidget *parent = 0);
    QPixmapWidget(const QPixmap& pixmap,
                  Qt::AspectRatioMode aspectRatioMode = Qt::KeepAspectRatio,
                  Qt::TransformationMode transformationMode = Qt::FastTransformation,
                  Qt::Alignment alignment = Qt::AlignCenter, QWidget *parent = 0);
    ~QPixmapWidget();

    QPixmap* pixmap() const
    {
        return m_pixmap;
    }

    Qt::AspectRatioMode aspectRatioMode() const
    {
        return m_aspectRatioMode;
    }

    Qt::TransformationMode transformationMode() const
    {
        return m_transformationMode;
    }

    Qt::Alignment alignment() const {
        return m_alignment;
    }

    QBrush backgroundBrush() const
    {
        return m_backgroundBrush;
    }

public slots:
    void setPixmap(const QPixmap& arg)
    {
        m_pixmap = new QPixmap(arg);
        update();
    }

    void setAspectRatioMode(Qt::AspectRatioMode arg)
    {
        m_aspectRatioMode = arg;
        update();
    }

    void setTransformationMode(Qt::TransformationMode arg)
    {
        m_transformationMode = arg;
        update();
    }

    void setAlignment(Qt::Alignment arg)
    {
        /*Qt::AlignJustify is not valid*/
        if (arg & Qt::AlignJustify)
            return;
        /*Qt::AlignAbsolute is not valid because there is no layout direction*/
        if (arg & Qt::AlignAbsolute)
            return;
        m_alignment = arg;
        update();
    }

    void setBackgroundBrush(QBrush arg)
    {
        m_backgroundBrush = arg;
        update();
    }

protected:
    void paintEvent(QPaintEvent *);
    void dragEnterEvent(QDragEnterEvent *ev);
    void dropEvent(QDropEvent *ev);

private:
    QPixmap* m_pixmap;
    Qt::AspectRatioMode m_aspectRatioMode;
    Qt::TransformationMode m_transformationMode;
    Qt::Alignment m_alignment;
    QBrush m_backgroundBrush;
};

#endif // QPIXMAPWIDGET_H
