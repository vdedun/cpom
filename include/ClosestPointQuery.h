#ifndef __CLOSESTPOINTQUERY_H__
#define __CLOSESTPOINTQUERY_H__

#include <Mesh.h>

#include <memory>

namespace cpom
{

/// \brief Functor object that efficiently compute the points closest to the associated mesh.
///
/// An octree structure is used to partition space and accelerate the nearest face search.
class ClosestPointQuery
{
public:
    /// \brief Construct the functor for a given mesh.
    ///
    /// \pre The mesh is expected to contain only triangle and quadrilateral faces.
    /// \pre None of the faces should have 3 or more collinear vertices.
    /// \pre The mesh is expected to contain at least one face.
    ///
    /// \param[in] m Mesh where to find closest points.
    ///
    /// \post No reference to the Mesh m is maintened.
    ///
    ClosestPointQuery(const Mesh &m);

    //// Destructor
    ~ClosestPointQuery();

    /// \brief Return the closest point on the mesh within the specified maximum search distance.
    ///
    /// \param[in] queryPoint Coordinate from which we want to find the closest point.
    /// \param[in] maxDist Maximum search distance.
    ///
    /// \return Coordinate of the closest point on the mesh.
    ///
    /// \throw std::invalid_argument in the case a face has 3 or more collinear vertices.
    /// \throw std::invalid_argument in the case a face is not a triangle or quadrilateral.
    ///
    Point operator() (const Point &queryPoint, float maxDist) const;

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};

} // namespace cpom

#endif // __CLOSESTPOINTQUERY_H__
