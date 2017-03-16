#include "../src/OctreeNode.h"
#include "catch.hpp"

#include <limits>

using namespace cpom;

namespace {

/// \file
/// Unit test for cpom::OctreeNode.

/// Return true if a point is inside an Axis-Aligned Bounding Cube.
bool intersect(const AABCube &cube, const Point &point)
{
    const auto distances( (cube.center-point).abs() );
    return (distances.x <= cube.halfWidth &&
            distances.y <= cube.halfWidth &&
            distances.z <= cube.halfWidth);
}

SCENARIO( "Basic octree", "[Octree]" )
{
    GIVEN( "Some bounds" )
    {
        const AABCube bounds{ Point(0.0f), 0.5f };
        WHEN( "Constructing an OctreeNode" )
        {
            THEN( "No exception is thrown" )
            {
                REQUIRE_NOTHROW( new OctreeNode<int>(bounds) );
            }
        }
    }

    GIVEN( "A root node and a point" )
    {
        using Node = OctreeNode<Point>;
        const AABCube bounds{ Point(0.0f), 0.5f };
        Node rootNode(bounds);

        Point point(0.0f);

        WHEN ("The point is inserted 1 time")
        {
            rootNode.insert( point, intersect );
            THEN ("The root node is a leaf")
            {
                REQUIRE(rootNode.isLeaf());
            }
            AND_WHEN ( "Visiting the children of the root node" )
            {
                bool visitedNode = false;
                rootNode.accept([&](Node &node) { visitedNode = true; } );
                THEN( "No node is visited" )
                {
                    REQUIRE(!visitedNode);
                }
            }
            AND_WHEN( "Visiting the elements of the root node" )
            {
                bool visitedPoint = false;
                std::function<void(Point &)> visitElement = [&](Point &nodePoint)
                {
                    if (point.equalsTo(nodePoint))
                    {
                        visitedPoint = true;
                    }
                };
                rootNode.accept(visitElement);
                THEN( "The point is visited" )
                {
                    REQUIRE(visitedPoint);
                }
            }
        }
        WHEN ("The point is inserted 10 times with maxDepth=0 and maxFill=0")
        {
            constexpr int maxDepth = 0;
            constexpr float maxFill = 0.0;
            for (int i = 0; i < 10; ++i)
            {
                rootNode.insert(point, intersect, maxDepth,  maxFill);
            }
            THEN ("The root node is a leaf")
            {
                REQUIRE(rootNode.isLeaf());
            }
        }
        WHEN ("The point is inserted 20 times with maxDepth=100 and maxFill=3")
        {
            constexpr int maxDepth = 100;
            constexpr float maxFill = 3.0;
            for (int i = 0; i < 20; ++i)
            {
                rootNode.insert( point, intersect, maxDepth,  maxFill);
            }
            THEN ("The root node is not a leaf")
            {
                REQUIRE(!rootNode.isLeaf());
            }
            AND_WHEN( "Traversing the tree" )
            {
                bool visitedPoint = false;
                int maxVisitedDepth = 0;
                int maxVisitedFill = 0;

                std::function<void(Node &, int)> visitNode =
                    [&](Node &node, int depth)
                    {
                        if (node.isLeaf())
                        {
                            int nodeFill = 0;
                            node.accept([&](Point &nodePoint)
                                {
                                    nodeFill++;
                                    if (point.equalsTo(nodePoint))
                                    {
                                        visitedPoint = true;
                                    }
                                });
                            maxVisitedDepth = std::max(maxVisitedDepth, depth);
                            maxVisitedFill = std::max(maxVisitedFill, nodeFill);
                        }
                        else
                        {
                            node.accept([&visitNode, depth](Node &node)
                                {
                                    visitNode(node, depth+1);
                                });
                        }
                    };

                visitNode(rootNode, 0);

                THEN( "The point is visited" )
                {
                    REQUIRE( visitedPoint );
                }
                THEN( "The deepest leaf node has depth 6" )
                {
                    REQUIRE( maxVisitedDepth == 6 );
                }
                THEN( "The fullest node has 20 elements" )
                {
                    REQUIRE( maxVisitedFill == 20);
                }
            }
        }
    }

    GIVEN( "A root node" )
    {
        using Node = OctreeNode<Point>;
        const AABCube bounds{ Point(0.0f), 2.0f };
        Node rootNode(bounds);

        WHEN ("A point is inserted in each corner with maxFill=1")
        {
            constexpr int maxDepth = 10;
            constexpr float maxFill = 1.0;
            Point points[8] = { {-1, -1, -1},
                                {+1, -1, -1},
                                {-1, +1, -1},
                                {+1, +1, -1},
                                {-1, -1, +1},
                                {+1, -1, +1},
                                {-1, +1, +1},
                                {+1, +1, +1} };
            for (auto &point: points)
            {
                rootNode.insert(point, intersect, maxDepth,  maxFill);
            }
            THEN ("The root node is not a leaf")
            {
                REQUIRE(!rootNode.isLeaf());
            }
            AND_WHEN ("Visiting the children of the root nodes")
            {
                int visitedChildren = 0;
                int visitedLeaves = 0;
                rootNode.accept([&](Node& child)
                    {
                        ++visitedChildren;
                        if (child.isLeaf())
                        {
                            ++visitedLeaves;
                        }
                    });
                THEN ("8 children are visited")
                {
                    REQUIRE(visitedChildren == 8);
                }
                THEN ("All children are leaves")
                {
                    REQUIRE(visitedChildren == visitedLeaves);
                }
            }
        }
    }
}

} // anonymous namespace
