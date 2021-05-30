/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "chartview.h"
#include <QtGui/QMouseEvent>
#include "chart.h"
#include <QtCore/QtMath>
#include <QtCore/QRandomGenerator>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLegendMarker>
#include <qDebug>

ChartView::ChartView(QWidget *parent) :
    QChartView(nullptr, parent),
    m_isTouching(false)
{
    setRubberBand(QChartView::RectangleRubberBand);
}

ChartView::~ChartView()
{
	disconnectMarkers();
}

void ChartView::init()
{
	//![1]
	Chart *chart = new Chart();

	QValueAxis *xAxis = new QValueAxis();
	QValueAxis *yAxis = new QValueAxis();

	{
		xAxis->setRange(0, 28);
		yAxis->setRange(-0.2, 0.8);

		xAxis->setTickCount(15);
		yAxis->setTickCount(6);

		xAxis->setLabelFormat("%.02f");

		chart->addAxis(xAxis, Qt::AlignBottom);
		chart->addAxis(yAxis, Qt::AlignLeft);
	}

	for ( int j = 0; j < 7; j++ )
	{
		QLineSeries *series = new QLineSeries();
		for (int i = 0; i < 500; i++) {
			QPointF p( (i*1.0/5 + j*1.0/5), qSin(M_PI / 20 * i) / 3.14);
			p.ry() += QRandomGenerator::global()->bounded(0.05);
			p.ry() += 0.3;
			*series << p;
		}
		series->setName(QString(tr(u8"速度%1[t]")).arg(j));

		chart->addSeries(series);

		series->attachAxis(xAxis);
		series->attachAxis(yAxis);
	}

	chart->setAnimationOptions(QChart::NoAnimation);
	//chart->setTitle(tr(u8"时域信号"));
	chart->legend()->setAlignment(Qt::AlignBottom);

	setChart(chart);

	connectMarkers();
}

bool ChartView::viewportEvent(QEvent *event)
{
    if (event->type() == QEvent::TouchBegin) {
        // By default touch events are converted to mouse events. So
        // after this event we will get a mouse event also but we want
        // to handle touch events as gestures only. So we need this safeguard
        // to block mouse events that are actually generated from touch.
        m_isTouching = true;

        // Turn off animations when handling gestures they
        // will only slow us down.
        chart()->setAnimationOptions(QChart::NoAnimation);
    }
    return QChartView::viewportEvent(event);
}

void ChartView::mousePressEvent(QMouseEvent *event)
{
    if (m_isTouching)
        return;
    QChartView::mousePressEvent(event);
}

void ChartView::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isTouching)
        return;
    QChartView::mouseMoveEvent(event);
}

void ChartView::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_isTouching)
        m_isTouching = false;

    // Because we disabled animations when touch event was detected
    // we must put them back on.
    chart()->setAnimationOptions(QChart::SeriesAnimations);

    QChartView::mouseReleaseEvent(event);
}

void ChartView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        chart()->zoomIn();
        break;
    case Qt::Key_Minus:
        chart()->zoomOut();
        break;
    case Qt::Key_Left:
        chart()->scroll(-10, 0);
        break;
    case Qt::Key_Right:
        chart()->scroll(10, 0);
        break;
    case Qt::Key_Up:
        chart()->scroll(0, 10);
        break;
    case Qt::Key_Down:
        chart()->scroll(0, -10);
		break;
	case Qt::Key_R:
		chart()->axisX()->setRange(0, 28);
		chart()->axisY()->setRange(-0.2, 0.8);
		break;
    default:
        QGraphicsView::keyPressEvent(event);
        break;
    }
}

void ChartView::connectMarkers()
{
	auto chart = this->chart();
	const auto markers = chart->legend()->markers();
	for (QLegendMarker *marker : markers) {
		// Disconnect possible existing connection to avoid multiple connections
		QObject::disconnect(marker, &QLegendMarker::clicked, this, &ChartView::handleMarkerClicked);
		QObject::connect(marker, &QLegendMarker::clicked, this, &ChartView::handleMarkerClicked);
	}
}

void ChartView::disconnectMarkers()
{
	auto chart = this->chart();
	const auto markers = chart->legend()->markers();
	for (QLegendMarker *marker : markers) {
		QObject::disconnect(marker, &QLegendMarker::clicked, this, &ChartView::handleMarkerClicked);
	}
}

void ChartView::handleMarkerClicked()
{
	QLegendMarker* marker = qobject_cast<QLegendMarker*> (sender());
	Q_ASSERT(marker);

	switch (marker->type())
	{
	case QLegendMarker::LegendMarkerTypeXY:
	{
		// Toggle visibility of series
		marker->series()->setVisible(!marker->series()->isVisible());

		// Turn legend marker back to visible, since hiding series also hides the marker
		// and we don't want it to happen now.
		marker->setVisible(true);

		// Dim the marker, if series is not visible
		qreal alpha = 1.0;

		if (!marker->series()->isVisible())
			alpha = 0.5;

		QColor color;
		QBrush brush = marker->labelBrush();
		color = brush.color();
		color.setAlphaF(alpha);
		brush.setColor(color);
		marker->setLabelBrush(brush);

		brush = marker->brush();
		color = brush.color();
		color.setAlphaF(alpha);
		brush.setColor(color);
		marker->setBrush(brush);

		QPen pen = marker->pen();
		color = pen.color();
		color.setAlphaF(alpha);
		pen.setColor(color);
		marker->setPen(pen);

		break;
	}
	default:
	{
		qDebug() << "Unknown marker type";
		break;
	}
	}
}
