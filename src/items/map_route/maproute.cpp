#include "maproute.h"
#include <QQmlEngine>

/*!
 * \brief MapRoute::MapRoute - constructor
 * \param parent
 */
MapRoute::MapRoute(QQuickItem *parent) :
    QQuickItem(parent),
    m_coords()
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

/*!
 * \brief MapRoute::coords - get list of coords
 * \return
 */
QList<QGeoCoordinate> MapRoute::coords() const
{
    return m_coords;
}

void MapRoute::setCoords(QList<QGeoCoordinate> coords)
{
    if (m_coords == coords)
        return;

    m_coords = coords;
    emit coordsChanged(m_coords);
}

/*!
 * \brief MapRoute::appendPoint - append point to list
 * \param latitude
 * \param longtitude
 */
void MapRoute::appendPoint(double latitude, double longtitude)
{
    auto newPoint = QGeoCoordinate(latitude, longtitude);
    m_coords.append(newPoint);

    emit newPointAdded(newPoint);
}
