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


#include "qpixmapwidget.h"

QPixmapWidget::QPixmapWidget(const QPixmap &pixmap, QWidget *parent)
    :QWidget(parent),
      m_pixmap(new QPixmap(pixmap)),
      m_backgroundBrush(Qt::NoBrush),
      m_aspectRatioMode(Qt::KeepAspectRatio),
      m_transformationMode(Qt::FastTransformation),
      m_alignment(Qt::AlignCenter)
{
    setAcceptDrops(true);
}

QPixmapWidget::QPixmapWidget(QWidget *parent)
    :QWidget(parent),
      m_pixmap(new QPixmap()),
      m_backgroundBrush(Qt::NoBrush),
      m_aspectRatioMode(Qt::KeepAspectRatio),
      m_transformationMode(Qt::FastTransformation),
      m_alignment(Qt::AlignCenter)
{
    setAcceptDrops(true);
}

QPixmapWidget::QPixmapWidget(const QPixmap &pixmap, Qt::AspectRatioMode aspectRatioMode,
                             Qt::TransformationMode transformationMode,
                             Qt::Alignment alignment, QWidget *parent)
    :QWidget(parent),
      m_pixmap(new QPixmap(pixmap)),
      m_backgroundBrush(Qt::NoBrush),
      m_aspectRatioMode(aspectRatioMode),
      m_transformationMode(transformationMode),
      m_alignment(alignment)
{
    setAcceptDrops(true);
}

QPixmapWidget::~QPixmapWidget()
{
}

void QPixmapWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(rect(), m_backgroundBrush);
    if (!m_pixmap->isNull()) {
        QPixmap scaled;

        /*if the height/width of the widget is below the pixmap's height/width,
         *the pixmap will be scaled
         */
        if (width() < m_pixmap->width() || height() < m_pixmap->height())
            scaled = m_pixmap->scaled(size(), m_aspectRatioMode, m_transformationMode);
        else scaled = *m_pixmap;
        QPoint topLeft;
        if (m_alignment & Qt::AlignHCenter || m_alignment & Qt::AlignCenter)
            topLeft.setX((width()-scaled.width())/2);
        if (m_alignment & Qt::AlignVCenter || m_alignment & Qt::AlignCenter)
            topLeft.setY((height()-scaled.height())/2);
        if (m_alignment & Qt::AlignLeft || m_alignment == Qt::AlignLeading)
            topLeft.setX(0);
        if (m_alignment & Qt::AlignTop || m_alignment == Qt::AlignTrailing)
            topLeft.setY(0);
        if (m_alignment & Qt::AlignRight)
            topLeft.setX(width()-scaled.width());
        if (m_alignment & Qt::AlignBottom)
            topLeft.setY(height()-scaled.height());
        painter.drawPixmap(topLeft, scaled);
    }
}

/*section for drag and drop*/
void QPixmapWidget::dropEvent(QDropEvent *ev)
{
    QImage *image;
    if (ev->mimeData()->hasImage())
        image = new QImage(qvariant_cast<QImage>(ev->mimeData()->imageData()));
    else {
        QList<QUrl> urls = ev->mimeData()->urls();
        foreach(QUrl url, urls) {
            QString fileName = url.toString(/*QUrl::RemoveScheme*/);
            fileName.remove("file:///");
            QImage *image2 = new QImage(fileName);
            if (!image2->isNull())
                image = image2;
        }
    }
    if (!image->isNull()) {
        m_pixmap = new QPixmap(QPixmap::fromImage(*image));
    }
    update();
}

void QPixmapWidget::dragEnterEvent(QDragEnterEvent *ev)
{
    ev->accept();
}
