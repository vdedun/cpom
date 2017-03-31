#include <ClosestPointQuery.h>

#include <Float3.h>
#include <OctreeNode.h>

#include <cassert>
#include <limits>
#include <memory>
#include <numeric>
#include <queue>
#include <stdexcept>
#include <utility>

namespace cpom
{

namespace
{

constexpr float nan = std::numeric_limits<float>::quiet_NaN();
constexpr float infinity = std::numeric_limits<float>::infinity();

/// Type defining an Axis Aligned Bounding Box.
struct AABBox
{
    Point center;
    Float3 halfWidth;
};

// Type aliases
using Extent = std::pair<Point, Point>;
using ClosestPointSpec = std::pair<Point, float>;

using OctreeElement = std::pair<const Face *, const AABBox>;
using Node = OctreeNode<OctreeElement>;

// Function that tests if an Octree element intersects an AACube.
inline bool intersect(const AABCube &cube, const OctreeElement &element)
{
    const AABBox &box = element.second;
    const auto distances = (cube.center-box.center).abs();
    const auto halfWidthSum = Point(cube.halfWidth) + box.halfWidth;
    return (distances.x <= halfWidthSum.x &&
            distances.y <= halfWidthSum.y &&
            distances.z <= halfWidthSum.z);
}

/// \brief Compute the point on a triangle closest to a specified position.
///
/// This is implementing the method described in
/// "Distance Between Point and Triangle in 3D" by David Eberly.
///
/// \pre The vertices must not be collinear.
///
/// \param[in] vertex0 Coordinate of the first vertex.
/// \param[in] vertex1 Coordinate of the second vertex.
/// \param[in] vertex2 Coordinate of the third vertex.
/// \param[in] fromPoint Coordinate from which we want to find the closest point.
///
/// \return Pair (coordinate, squared distance) for the closest point.
///
/// \throw std::invalid_argument if all vertices are collinear.
///
ClosestPointSpec computeClosestPointOnTriangle(const Point &vertex0,
                                               const Point &vertex1,
                                               const Point &vertex2,
                                               const Point &fromPoint)
{
    const Float3 edge0 = vertex1 - vertex0;
    const Float3 edge1 = vertex2 - vertex0;
    const Float3 v0 = vertex0 - fromPoint;

    const float a = edge0.dot(edge0);
    const float b = edge0.dot(edge1);
    const float c = edge1.dot(edge1);
    const float d = edge0.dot(v0);
    const float e = edge1.dot(v0);

    const float det = a*c - b*b;
    const float s1 = b*e - c*d;
    const float t1 = b*d - a*e;

    if (det == 0.0f)
    {
        throw std::invalid_argument("Collinear triangle vertices");
    }

    float s2 = s1;
    float t2 = t1;
    if (s1 + t1 <= det)
    {
        if (s1 < 0.0f)
        {
            if (t1 < 0.0f)
            {
                // Region 4
                if (d < 0.0f)
                {
                    t2 = 0.0f;
                    if (-d >= a)
                        s2 = 1.0f;
                    else
                        s2 = -d/a;
                }
                else
                {
                    s2 = 0.0f;
                    if (e >= 0.0f)
                        t2 = 0.0f;
                    else if (-e >= c)
                        t2 = 1.0f;
                    else
                        t2 = -e/c;
                }
            }
            else
            {
                // Region 3
                s2 = 0.0f;
                if (e >= 0.0f)
                    t2 = 0.0f;
                else if (-e >= c)
                    t2 = 1.0f;
                else
                    t2 = -e/c;
            }
        }
        else if (t1 < 0.0f)
        {
            // Region 5
            t2 = 0.0f;
            if (d >= 0.0f)
                s2 = 0.0f;
            else if (-d >= a)
                s2 = 1.0f;
            else
                s2 = -d/a;
        }
        else
        {
            // Region 0
            const float invDet = 1.0f / det;
            s2 *= invDet;
            t2 *= invDet;
        }
    }
    else
    {
        if (s1 < 0.0f)
        {
            // Region 2
            const float tmp0 = b+d;
            const float tmp1 = c+e;
            if (tmp1 > tmp0)
            {
                const float num = tmp1 - tmp0;
                const float denom = a - 2.0f*b + c;
                if (num >= denom)
                    s2 = 1.0f;
                else
                    s2 = num/denom;
                t2 = 1.0f - s2;
            }
            else
            {
                s2 = 0.0f;
                if (tmp1 <= 0.0f)
                    t2 = 1.0f;
                else if (e >= 0.0f)
                    t2 = 0.0f;
                else
                    t2 = -e/c;
            }
        }
        else if (t1 < 0.0f)
        {
            // Region 6
            const float tmp0 = b + e;
            const float tmp1 = a + d;
            if (tmp1 > tmp0)
            {
                const float num = tmp1 - tmp0;
                const float denom = a - 2.0f * b + c;
                if (num >= denom)
                    t2 = 1.0f;
                else
                    t2 = num/denom;
                s2 = 1 - s2;
            }
            else
            {
                t2 = 0.0f;
                if (tmp1 <= 0.0f)
                    s2 = 1.0f;
                else if (d >= 0.0f)
                    s2 = 0.0f;
                else
                    s2 = -d/a;
            }
        }
        else
        {
            // Region 1
            const float num = c + e - b - d;
            if (num <= 0.0f)
                s2 = 0.0f;
            else
            {
                const float denom = a - 2.0f * b + c;
                if (num >= denom)
                    s2 = 1.0;
                else
                    s2 = num/denom;
            }
            t2 = 1.0f - s2;
        }
    }
    const Point closestPoint = vertex0 + edge0*s2 + edge1*t2;
    const float sqrDistance = (fromPoint - closestPoint).sqrLength();
    return ClosestPointSpec(closestPoint, sqrDistance);
}

/// \brief Return the closest point on the face.
///
/// \pre The face must have 3 or 4 vertices.
///
/// \param[in] face Face on which to find the closest point.
/// \param[in] vertices Sequence of vertices of the underlying mesh.
/// \param[in] queryPoint Coordinate from which we want to find the closest point.
///
/// \return Pair (coordinate, squared distance) for the closest point on the face.
///
/// \throw std::invalid_argument if the face has an unsupported number of vertices.
///
inline ClosestPointSpec computeClosestPointOnFace(const Face &face,
                                                  const std::vector<Point> &vertices,
                                                  const Point &queryPoint)
{
    if (face.vertexIds.size() < 3 || face.vertexIds.size() > 4)
        throw std::invalid_argument("Face has unsupported number of vertices");
    const Point &v0 = vertices[face.vertexIds[0]];
    const Point &v1 = vertices[face.vertexIds[1]];
    const Point &v2 = vertices[face.vertexIds[2]];
    const auto result1 = computeClosestPointOnTriangle(v0, v1, v2, queryPoint);
    if (face.vertexIds.size() == 3)
        return result1;
    const Point &v3 = vertices[face.vertexIds[3]];
    const auto result2 = computeClosestPointOnTriangle(v2, v3, v0, queryPoint);
    return result2.second < result1.second ? result2 : result1;
}

/// Grow a given extent to include a given point and returns the result.
inline Extent growExtent(const Extent &extent, const Point &point)
{
    const Point resultMin = Point( std::min(extent.first.x, point.x),
                                   std::min(extent.first.y, point.y),
                                   std::min(extent.first.z, point.z) );
    const Point resultMax = Point( std::max(extent.second.x, point.x),
                                   std::max(extent.second.y, point.y),
                                   std::max(extent.second.z, point.z) );
    return Extent(resultMin, resultMax);
}

/// Return the smallest bounding cube of an extent.
inline AABCube computeCubicBounds(const Extent &extent)
{
    const auto dimensions = extent.second - extent.first;
    AABCube bounds;
    bounds.center = (extent.first+extent.second) * 0.5f;
    bounds.halfWidth = 0.5f * std::max(dimensions.x, std::max(dimensions.y,
                                                              dimensions.z));
    return bounds;
}

/// Return the smallest bounding box of an extent.
inline AABBox computeBounds(const Extent &extent)
{
    const auto dimensions = extent.second - extent.first;
    AABBox bounds;
    bounds.center = (extent.first+extent.second) * 0.5f;
    bounds.halfWidth = dimensions * 0.5f;
    return bounds;
}

/// Return the squared distance to the closest point on a bounding cube.
inline float computeSqrDistanceToBounds(const Point &queryPoint,
                                        const AABCube &bounds)
{
    const auto d = (queryPoint-bounds.center).abs() - bounds.halfWidth;
    return Float3(std::max(d.x, 0.0f),
                  std::max(d.y, 0.0f),
                  std::max(d.z, 0.0f)).sqrLength();
}

} // anonymous namespace

struct ClosestPointQuery::Impl
{
    std::vector<Point> m_vertices;
    std::vector<Face> m_faces;
    std::unique_ptr<Node> m_partitionedSpace;

    Impl(const Mesh &m);
    void partitionSpace();
    Point processPartitionedSpace(const Point&, float) const;
    Point processMesh(const Point&, float) const;
};

ClosestPointQuery::ClosestPointQuery(const Mesh &m)
: m_impl(new ClosestPointQuery::Impl(m) )
{ }

ClosestPointQuery::~ClosestPointQuery() = default;

Point ClosestPointQuery::operator() (const Point& queryPoint, float maxDist) const
{
    if (m_impl->m_partitionedSpace)
        return m_impl->processPartitionedSpace(queryPoint, maxDist*maxDist);
    return m_impl->processMesh(queryPoint, maxDist*maxDist);
}

ClosestPointQuery::Impl::Impl(const Mesh &m)
{
    m.getVertices(m_vertices);
    m.getFaces(m_faces);
    if (m_vertices.empty())
    {
        throw std::invalid_argument("Empty mesh");
    }

    constexpr int minSpacePartitioningFaces = 32;
    if (m_faces.size() >= minSpacePartitioningFaces)
    {
        partitionSpace();
    }
}

/// Iterator through all faces and find closest point on face.
inline Point ClosestPointQuery::Impl::processMesh(const Point& queryPoint,
                                                  const float sqrMaxDist) const
{
    const auto &vertices = m_vertices;
    const auto reduceClosestPointOnFace = [&](const ClosestPointSpec &inputClosest,
                                              const Face &face)
    {
        // Compute the closest point on this face and return the closest of this
        // or the input, respecting sqrMaxDist.
        const auto faceClosest = computeClosestPointOnFace(face, vertices, queryPoint);
        return faceClosest.second < sqrMaxDist && faceClosest.second < inputClosest.second ?
            faceClosest : inputClosest;
    };
    return std::accumulate(m_faces.begin(),
                           m_faces.end(),
                           ClosestPointSpec(Point(nan), infinity),
                           reduceClosestPointOnFace).first;
}

/// Partition space and sort faces into partitions.
void ClosestPointQuery::Impl::partitionSpace()
{
    // Compute the extent of the space taken by all vertices.
    Extent meshExtent = std::accumulate(m_vertices.begin(),
                                        m_vertices.end(),
                                        Extent(Point(infinity), Point(-infinity)),
                                        growExtent);

    // Construct the root octree node bounding the mesh.
    m_partitionedSpace = std::unique_ptr<Node>(new Node( computeCubicBounds(meshExtent) ));
    auto& rootNode = *m_partitionedSpace;

    // Function that inserts a face into the octree.
    const auto &vertices = m_vertices;
    const auto insertFace = [&vertices, &rootNode](const Face &face)
    {
        const auto growFaceExtent = [&vertices](const Extent &extent,
                                                const int vertexId)
        {
            return growExtent(extent, vertices[vertexId]);
        };
        // Compute extent of face vertices.
        Extent faceExtent = std::accumulate(face.vertexIds.begin(),
                                            face.vertexIds.end(),
                                            Extent(Point(infinity), Point(-infinity)),
                                            growFaceExtent);
        // Insert this face into the octree.
        rootNode.insert(OctreeElement(&face, computeBounds(faceExtent)),
                        intersect);
    };
    // Insert all faces into the octree.
    std::for_each(m_faces.begin(), m_faces.end(), insertFace);
}

/// Walk partitioned space and return the closest point on face.
inline Point ClosestPointQuery::Impl::processPartitionedSpace(const Point& queryPoint,
                                                              const float sqrMaxDist) const
{
    // Initialize the result.
    auto result = ClosestPointSpec(Point(nan), infinity);

    // Initialize a heap whose top is the node closest to queryPoint.
    using HeapEntry = std::pair<std::reference_wrapper<const Node>, float>;
    const auto heapCompare = [&queryPoint](const HeapEntry &a, const HeapEntry &b)
    {
        return (a.second > b.second);
    };
    using HeapContainer = std::vector<HeapEntry>;
    using HeapCompareType = decltype(heapCompare);
    using Heap = std::priority_queue< HeapEntry,
                                      HeapContainer,
                                      HeapCompareType >;
    Heap heap(heapCompare);

    // Prepare octree visitor functions.
    const auto &vertices = m_vertices;
    // When visiting an element (face)..
    const auto visitElement = [&](const OctreeElement &element)
    {
        // .. compute the closest point to it and update the global result,
        // respecting sqrMaxDist.
        assert(element.first);
        const auto &face = *(element.first);
        const auto faceClosest = computeClosestPointOnFace(face, vertices, queryPoint);
        if (faceClosest.second < sqrMaxDist && faceClosest.second < result.second)
            result = faceClosest;
    };

    // When visiting an octree child..
    const auto visitChild = [&queryPoint, &heap, &result](Node const &child)
    {
        // ..if the child is closer than the closest point currently found..
        const float nodeSqrDist = computeSqrDistanceToBounds( queryPoint,
                                                              child.getBounds() );
        if (nodeSqrDist < result.second)
        {
            //.. then add it to the heap.
            heap.push( HeapEntry(child, nodeSqrDist) );
        }
    };

    // Initialize the heap with the octree root.
    const auto &rootNode = *m_partitionedSpace;
    const float rootSqrDist = computeSqrDistanceToBounds( queryPoint,
                                                          rootNode.getBounds() );
    heap.push( HeapEntry(std::cref(rootNode), rootSqrDist) );

    // Do a Best First Search over the octree:
    // while the heap has nodes and the top one is closer than the current result,
    while (!heap.empty() && heap.top().second < result.second)
    {
        // Eat the top of the heap.
        const Node &node = heap.top().first.get();
        heap.pop();

        if (node.isLeaf())
        {
            // If it's a leaf, visit the elements (faces).
            node.accept(visitElement);
        }
        else
        {
            // Otherwise, visit the children nodes.
            node.accept(visitChild);
        }
    }

    return result.first;
}

} // namespace cpom
