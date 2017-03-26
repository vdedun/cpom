#include "ClosestPointQuery.h"
#include "catch.hpp"

#include <limits>

using namespace cpom;

namespace {

/// \file
/// Unit test for cpom::ClosestPointOnQuery.

constexpr float infinity(std::numeric_limits<float>::infinity());

SCENARIO( "Invalid meshs", "[Mesh]" )
{
    GIVEN( "An empy mesh" )
    {
        class StubEmptyMesh : public Mesh
        {
            virtual void getVertices(std::vector<Point> &vertices) const
            { }

            virtual void getFaces(std::vector<Face> &faces) const
            { }
        };
        StubEmptyMesh stubEmptyMesh;

        WHEN( "Constructing a ClosestPointQuery with it" )
        {
            THEN( "An exception is thrown" )
            {
                REQUIRE_THROWS( new ClosestPointQuery(stubEmptyMesh) );
            }
        }
    }

    GIVEN( "A mesh with collinear vertices and a ClosestPointQuery on it" )
    {
        class StubSoloQuadMesh : public Mesh
        {
        public:
            virtual void getVertices(std::vector<Point> &vertices) const
            {
                static const std::vector<Point> s_vertices = { Point(1.0f),
                                                               Point(2.0f),
                                                               Point(3.0f),
                                                               Point(4.0f) };
                vertices.reserve(4);
                std::copy(s_vertices.begin(),
                          s_vertices.end(),
                          std::back_inserter(vertices));
            }

            virtual void getFaces(std::vector<Face> &faces) const
            {
                static const Face face = { { 0, 1, 2, 3}  };
                static const std::vector<Face> s_faces = { face };

                faces.reserve(1);
                std::copy(s_faces.begin(),
                          s_faces.end(),
                          std::back_inserter(faces));
            }
        };

        StubSoloQuadMesh stubSoloQuadMesh;
        ClosestPointQuery query(stubSoloQuadMesh);

        WHEN( "Evaluating the query" )
        {
            constexpr Point position(0.0f);

            THEN( "An exception is thrown" )
            {
                REQUIRE_THROWS( query(position, infinity) );
            }
        }
    }

    GIVEN( "A mesh with a pentagon and a ClosestPointQuery on it" )
    {
        class StubSoloPentagonMesh : public Mesh
        {
        public:
            virtual void getVertices(std::vector<Point> &vertices) const
            {
                static const std::vector<Point> s_vertices = { Point(0.0f, 0.0f, 0.0f),
                                                               Point(1.0f, 0.0f, 0.0f),
                                                               Point(1.0f, 1.0f, 0.0f),
                                                               Point(0.0f, 1.0f, 0.0f),
                                                               Point(0.0f, 0.5f, 0.0f) };
                vertices.reserve(5);
                std::copy(s_vertices.begin(),
                          s_vertices.end(),
                          std::back_inserter(vertices));
            }

            virtual void getFaces(std::vector<Face> &faces) const
            {
                static const Face face = { { 0, 1, 2, 3, 4}  };
                static const std::vector<Face> s_faces = { face };

                faces.reserve(1);
                std::copy(s_faces.begin(),
                          s_faces.end(),
                          std::back_inserter(faces));
            }
        };

        StubSoloPentagonMesh stubSoloPentagonMesh;
        ClosestPointQuery query(stubSoloPentagonMesh);

        WHEN( "Evaluating the query" )
        {
            constexpr Point position(0.0f);

            THEN( "An exception is thrown" )
            {
                REQUIRE_THROWS( query(position, infinity) );
            }
        }
    }
}

//! [Single Triangle Mesh]
SCENARIO( "Single Triangle Mesh", "[Mesh]" )
{
    class StubSoloTriangleMesh : public Mesh
    {
    public:
        virtual void getVertices(std::vector<Point> &vertices) const
        {
            static const std::vector<Point> s_vertices = { Point(0.0f, 0.0f, 0.0f),
                                                           Point(1.0f, 0.0f, 0.0f),
                                                           Point(0.0f, 1.0f, 0.0f) };

            vertices.reserve(3);
            std::copy(s_vertices.begin(),
                      s_vertices.end(),
                      std::back_inserter(vertices));
        }

        virtual void getFaces(std::vector<Face> &faces) const
        {
            static const Face face = { { 0, 1, 2 }  };
            static const std::vector<Face> s_faces = { face };

            faces.reserve(1);
            std::copy(s_faces.begin(),
                      s_faces.end(),
                      std::back_inserter(faces));
        }
    };

    GIVEN( "A mesh with a single triangle and a ClosestPointQuery on it" )
    {
        StubSoloTriangleMesh stubSoloTriangleMesh;
        const ClosestPointQuery query(stubSoloTriangleMesh);

        WHEN( "Evaluating the query with the first vertex as position" )
        {
            constexpr Point position(0.0f, 0.0f, 0.0f);
            const Point closestPoint = query(position, infinity);

            THEN( "The same position is returned" )
            {
                REQUIRE( position.equalsTo(closestPoint) );
            }
            AND_THEN( "The returned point has no NaN" )
            {
                REQUIRE( !closestPoint.hasNan() );
            }
        }

        WHEN( "Evaluating the query with a position outside the triangle" )
        {
            constexpr Point position(-1.0f);
            const Point closestPoint = query(position, infinity);

            THEN( "A different position is returned" )
            {
                REQUIRE( !position.equalsTo(closestPoint) );
            }

            AND_WHEN( "Evaluating the query for the returned position" )
            {
                const Point closestPoint2 = query(closestPoint, infinity);
                THEN( "The same position is returned" )
                {
                    REQUIRE( closestPoint.equalsTo(closestPoint2) );
                }
            }
        }

        WHEN( "Evaluating the query with a position in region 0" )
        {
            constexpr Point position(0.25f, 0.25f, 0.0f);
            const Point closestPoint = query(position, infinity);

            THEN( "The same position is returned" )
            {
                REQUIRE( position.equalsTo(closestPoint) );
            }
        }

        WHEN( "Evaluating the query with a position in region 1" )
        {
            constexpr Point position(1.0f, 1.0f, 0.0f);
            constexpr Point expectedResult(0.5f, 0.5f, 0.0f);
            const Point closestPoint = query(position, infinity);

            THEN( "The returned point is on the expected edge" )
            {
                REQUIRE( expectedResult.equalsTo(closestPoint) );
            }
        }

        WHEN( "Evaluating the query with a position in region 3" )
        {
            constexpr Point position(-1.0f, 0.5f, 0.0f);
            constexpr Point expectedResult(0.0f, 0.5f, 0.0f);
            const Point closestPoint = query(position, infinity);

            THEN( "The returned point is on the expected edge" )
            {
                REQUIRE( expectedResult.equalsTo(closestPoint) );
            }
        }

        WHEN( "Evaluating the query with a position in region 5" )
        {
            constexpr Point position(0.5f, -1.0f, 0.0f);
            constexpr Point expectedResult(0.5f, 0.0f, 0.0f);
            const Point closestPoint = query(position, infinity);

            THEN( "The returned point is on the expected edge" )
            {
                REQUIRE( expectedResult.equalsTo(closestPoint) );
            }
        }

        WHEN( "Evaluating the query with a position in region 2" )
        {
            constexpr Point position(-0.5f, 2.0f, 0.0f);
            constexpr Point expectedResult(0.0f, 1.0f, 0.0f);
            const Point closestPoint = query(position, infinity);

            THEN( "The returned point is on the expected vertex" )
            {
                REQUIRE( expectedResult.equalsTo(closestPoint) );
            }
        }

        WHEN( "Evaluating the query with a position in region 4" )
        {
            constexpr Point position(-0.5f, -0.5f, 0.0f);
            constexpr Point expectedResult(0.0f, 0.0f, 0.0f);
            const Point closestPoint = query(position, infinity);

            THEN( "The returned point is on the expected vertex" )
            {
                REQUIRE( expectedResult.equalsTo(closestPoint) );
            }
        }

        WHEN( "Evaluating the query with a position in region 6" )
        {
            constexpr Point position(2.0f, -0.5f, 0.0f);
            constexpr Point expectedResult(1.0f, 0.0f, 0.0f);
            const Point closestPoint = query(position, infinity);

            THEN( "The returned point is on the expected vertex" )
            {
                REQUIRE( expectedResult.equalsTo(closestPoint) );
            }
        }

        WHEN( "Evaluating the query with a position behind max distance from the triangle" )
        {
            constexpr Point position(-1000.0f);
            constexpr float maxDistance = 1.0f;
            const Point closestPoint = query(position, maxDistance);

            THEN( "The returned point has NaNs" )
            {
                CAPTURE( closestPoint );
                REQUIRE( closestPoint.hasNan() );
            }
        }

        WHEN( "Evaluating the query with the second vertex as position" )
        {
            constexpr Point position(1.0f, 0.0f, 0.0f);
            const Point closestPoint = query(position, infinity);

            THEN( "The same position is returned" )
            {
                REQUIRE( position.equalsTo(closestPoint) );
            }
        }

        WHEN( "Evaluating the query with a position on the first edge" )
        {
            constexpr Point position(0.5f, 0.0f, 0.0f);
            const Point closestPoint = query(position, infinity);

            THEN( "The same position is returned" )
            {
                REQUIRE( position.equalsTo(closestPoint) );
            }
        }

        WHEN( "Evaluating the query with a position at the centroid" )
        {
            constexpr Point position(1.0f/3.0f, 1.0f/3.0f, 0.0f);
            const Point closestPoint = query(position, infinity);

            THEN( "The same position is returned" )
            {
                REQUIRE( position.equalsTo(closestPoint) );
            }
        }
    }
}
//! [Single Triangle Mesh]

SCENARIO( "Single Quadrilateral Mesh", "[Mesh]" )
{
    GIVEN( "A mesh with a single quadrilateral and a ClosestPointQuery on it" )
    {
        class StubSoloQuadMesh : public Mesh
        {
        public:
            virtual void getVertices(std::vector<Point> &vertices) const
            {
                static const std::vector<Point> s_vertices = { Point(0.0f, 0.0f, 0.0f),
                                                               Point(1.0f, 0.0f, 0.0f),
                                                               Point(1.0f, 1.0f, 0.0f),
                                                               Point(0.0f, 1.0f, 0.0f) };

                vertices.reserve(4);
                std::copy(s_vertices.begin(),
                          s_vertices.end(),
                          std::back_inserter(vertices));
            }

            virtual void getFaces(std::vector<Face> &faces) const
            {
                static const Face face = { { 0, 1, 2, 3}  };
                static const std::vector<Face> s_faces = { face };

                faces.reserve(1);
                std::copy(s_faces.begin(),
                          s_faces.end(),
                          std::back_inserter(faces));
            }
        };

        StubSoloQuadMesh stubSoloQuadMesh;
        ClosestPointQuery query(stubSoloQuadMesh);

        WHEN( "Evaluating the query" )
        {
            constexpr Point position(0.0f);

            THEN( "No exception is thrown" )
            {
                REQUIRE_NOTHROW( query(position, infinity) );
            }
        }

        WHEN( "Evaluating the query with a position at the middle of the third edge" )
        {
            const Point position( Point(0.5f, 1.0f, 0.0f) );
            const Point closestPoint = query(position, infinity);

            THEN( "The same position is returned" )
            {
                REQUIRE( closestPoint.equalsTo(position) );
            }
        }
    }
}

SCENARIO( "Dual Adjacent Triangle Mesh", "[Mesh]")
{
    class StubDualTriangleMesh : public Mesh
    {
    public:
        virtual void getVertices(std::vector<Point> &vertices) const
        {
            static const std::vector<Point> s_vertices = { Point(0.0f, 0.0f, 0.0f),
                                                           Point(1.0f, 0.0f, 0.0f),
                                                           Point(0.0f, 1.0f, 0.0f),
                                                           Point(0.5f, 0.5f, 1.0f) };
            vertices.reserve(4);
            std::copy(s_vertices.begin(),
                      s_vertices.end(),
                      std::back_inserter(vertices));
        }

        virtual void getFaces(std::vector<Face> &faces) const
        {
            static const Face face1 = { { 0, 1, 2}  };
            static const Face face2 = { { 1, 3, 2}  };
            static const std::vector<Face> s_faces = { face1, face2 };

            faces.reserve(2);
            std::copy(s_faces.begin(),
                      s_faces.end(),
                      std::back_inserter(faces));
        }
    };

    GIVEN( "A mesh with two adjacent triangles and a ClosestPointQuery on it" )
    {
        StubDualTriangleMesh stubDualTriangleMesh;
        const ClosestPointQuery query(stubDualTriangleMesh);

        WHEN( "Evaluating the query with a position at the centroid of the second triangle" )
        {
            const Point position( ( Point(1.0f, 0.0f, 0.0f) +
                                    Point(0.0f, 1.0f, 0.0f) +
                                    Point(0.5f, 0.5f, 1.0f) ) / 3.0f );
            const Point closestPoint = query(position, infinity);

            THEN( "The same position is returned" )
            {
                REQUIRE( closestPoint.equalsTo(position) );
            }
        }

        WHEN( "Evaluating the query with a position which closest point is the middle of the adjacent edge" )
        {
            const Point position( Point(1.0f, 1.0f, 0.0f) );
            const Point closestPoint = query(position, infinity);

            THEN( "The middle of the adjacent edge is returned" )
            {
                const Point expectedClosestPoint =
                    ( Point(1.0f, 0.0f, 0.0f)+
                      Point(0.0f, 1.0f, 0.0f)) / 2.0f;
                CAPTURE( closestPoint );
                CAPTURE( expectedClosestPoint );                    
                REQUIRE( closestPoint.equalsTo(expectedClosestPoint) );
            }
        }
    }
}

SCENARIO( "Dual Apart Triangle Mesh", "[Mesh]")
{
    class StubDualTriangleMesh : public Mesh
    {
    public:
        virtual void getVertices(std::vector<Point> &vertices) const
        {
            static const std::vector<Point> s_vertices = { Point(0.0f, 0.0f, -1.0f),
                                                           Point(1.0f, 0.0f, -1.0f),
                                                           Point(0.0f, 1.0f, -1.0f),
                                                           Point(0.0f, 0.0f, +1.0f),
                                                           Point(1.0f, 0.0f, +1.0f),
                                                           Point(0.0f, 1.0f, +1.0f) };
            vertices.reserve(6);
            std::copy(s_vertices.begin(),
                      s_vertices.end(),
                      std::back_inserter(vertices));
        }

        virtual void getFaces(std::vector<Face> &faces) const
        {
            static const Face face1 = { { 0, 1, 2}  };
            static const Face face2 = { { 3, 4, 5}  };
            static const std::vector<Face> s_faces = { face1, face2 };

            faces.reserve(2);
            std::copy(s_faces.begin(),
                      s_faces.end(),
                      std::back_inserter(faces));
        }
    };

    GIVEN( "A mesh with apart triangles and a ClosestPointQuery on it" )
    {
        StubDualTriangleMesh stubDualTriangleMesh;
        const ClosestPointQuery query(stubDualTriangleMesh);

        WHEN( "Evaluating the query with a position which closest point is the first triangle" )
        {
            const Point position( Point(0.0f, 0.0f, -1.5f) );
            const Point closestPoint = query(position, infinity);

            THEN( "A point on the first triangle is returned" )
            {
                const Point expectedClosestPoint(0.0f, 0.0f, -1.0f);
                CAPTURE( closestPoint) ;
                CAPTURE( expectedClosestPoint );
                REQUIRE( closestPoint.equalsTo(expectedClosestPoint) );
            }
        }

        WHEN( "Evaluating the query with a position which closest point is the second triangle" )
        {
            const Point position( Point(1.0f, 1.0f, 1.5f) );
            const Point closestPoint = query(position, infinity);

            THEN( "A point on the second triangle is returned" )
            {
                const Point expectedClosestPoint(0.5f, 0.5f, 1.0f);
                CAPTURE( closestPoint) ;
                CAPTURE( expectedClosestPoint );
                REQUIRE( closestPoint.equalsTo(expectedClosestPoint) );
            }
        }        
    }
}

template<int R>
class StubDensePlaneMesh : public Mesh
{
public:
    
    size_t vertexIndex(int x, int y) const
    {
        return x + y * (R+1);
    }

    virtual void getVertices(std::vector<Point> &vertices) const
    {
        vertices.resize( (R+1) * (R+1) );
        for (int y = 0; y <= R; ++y)
        {
            for (int x = 0; x <= R; ++x)
            {
                constexpr static float stepSize = 1.0f / (float) R;
                const Point vertex(Point(x, y, y) * stepSize);
                vertices[vertexIndex(x, y)] = vertex;
            }
        }
    }

    size_t faceIndex(int x, int y) const
    {
        return x + y*R;
    }

    virtual void getFaces(std::vector<Face> &faces) const
    {
        faces.resize( R * R );
        for (int y = 0; y < R; ++y)
        {
            for (int x = 0; x < R; ++x)
            {
                const int v0 = vertexIndex(x,   y);
                const int v1 = vertexIndex(x+1, y);
                const int v2 = vertexIndex(x+1, y+1);
                const int v3 = vertexIndex(x,   y+1);
                faces[faceIndex(x,y)] = {{ v0, v1, v2, v3}};
            }
        }
    }
};

SCENARIO( "Dense plane mesh", "[.Mesh]")
{
    GIVEN( "A plane mesh with 4 quad faces and a ClosestPointQuery on it" )
    {
        StubDensePlaneMesh<4> stubDensePlaneMesh;
        const ClosestPointQuery query(stubDensePlaneMesh);

        WHEN( "Evaluating one million times the query with a position far from the plane" )
        {
            const Point position( Point(0.75f, 1.0f, 0.0f) );
            const Point expectedClosestPoint( Point(0.75f, 0.5f, 0.5f) );

            Point closestPoint;
            for (int i = 0; i < 1e6; ++i)
                closestPoint = query(position, infinity);

            THEN( "The expected position is returned" )
            {
                CAPTURE( closestPoint );
                CAPTURE( position );
                REQUIRE( closestPoint.equalsTo(expectedClosestPoint) );
            }
        }
    }
    GIVEN( "A plane mesh with one million quad faces and a ClosestPointQuery on it" )
    {
        StubDensePlaneMesh<1000> stubDensePlaneMesh;
        const ClosestPointQuery query(stubDensePlaneMesh);

        WHEN( "Evaluating one million times the query with a position at the centroid of the plane" )
        {
            const Point position( Point(0.5f, 0.5f, 0.5f) );
            Point closestPoint;
            for (int i = 0; i < 1e6; ++i)
                closestPoint = query(position, infinity);

            THEN( "The same position is returned" )
            {
                CAPTURE( closestPoint );
                CAPTURE( position );
                REQUIRE( closestPoint.equalsTo(position) );
            }
        }

        WHEN( "Evaluating one thousand times the query with a position far from the plane" )
        {
            const Point position( Point(0.75f, 1.0f, 0.0f) );
            const Point expectedClosestPoint( Point(0.75f, 0.5f, 0.5f) );

            Point closestPoint;
            for (int i = 0; i < 1000; ++i)
                closestPoint = query(position, infinity);

            THEN( "The expected position is returned" )
            {
                CAPTURE( closestPoint );
                CAPTURE( position );
                REQUIRE( closestPoint.equalsTo(expectedClosestPoint) );
            }
        }
    }
}

} // anonymous namespace
