#ifndef MAPROUTE_H
#define MAPROUTE_H

#include <QQuickItem>
#include <QGeoCoordinate>

/*!
 * \brief The MapRoute class - provides list of coordinates
 */
class MapRoute : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QList<QGeoCoordinate> coords READ coords WRITE setCoords NOTIFY coordsChanged)
public:
    explicit MapRoute(QQuickItem *parent = nullptr);

    QList<QGeoCoordinate> coords() const;

public slots:
    void setCoords(QList<QGeoCoordinate> coords);
    void appendPoint(double latitude, double longtitude);

signals:
    void coordsChanged(QList<QGeoCoordinate> coords);
    void newPointAdded(QGeoCoordinate newPoint);

private:
    QList<QGeoCoordinate> m_coords; /// coords
};

#endif // MAPROUTE_H
