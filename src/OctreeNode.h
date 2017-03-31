#ifndef __OCTREENODE_H__
#define __OCTREENODE_H__

#include <Float3.h>

#include <algorithm>
#include <cassert>
#include <functional>
#include <memory>
#include <vector>

namespace cpom
{

////////////////////////////////////////////////////////////////////////////////
// DECLARATION SECTION
////////////////////////////////////////////////////////////////////////////////

/// Type defining an Axis Aligned Bounding Cube.
struct AABCube
{
    Point center;
    float halfWidth;
};

/// \brief Class defining an octree node that holds data of type T.
///
/// An octree is modeled by a tree of OctreeNode.
/// Leaves contain a number of elements of type T.
/// The octree can be traversed through visitor functions.
///
/// Example usage can be found in the unit test OctreeNode.ut.cpp.
template<class T>
class OctreeNode
{
public:
    /// Construct an OctreeNode with supplied Axis Aligned Bouding Cube.
    inline OctreeNode(const AABCube &bounds);

    using Intersect = std::function<bool(const AABCube &, T&)>;

    /// \brief Insert an element in the tree.
    ///
    /// \param[in] element Element to be inserted in the tree.
    /// \param[in] intersect Function to test intersection between an element
    /// and a node bounds.
    /// \param[in] maxDepth Maximal depth to grow the tree under this node.
    /// \param[in] maxFill The maximal number of elements in a node is
    /// maxFill * depth, unless maxDepth is reached.
    ///
    template<typename _T>
    void insert(_T &&element,
                Intersect intersect,
                int maxDepth=10,
                float maxFill=3.0);

    /// Accept and call a visitor function on all existing children nodes.
    inline void accept(std::function<void(const OctreeNode &)> visitChildren) const;

    /// Accept and call a visitor function on all elements of this node.
    inline void accept(std::function<void(const T &)> visitElement) const;

    /// Return a reference to the Axis Aligned Bounding Cube of the tree.
    inline const AABCube &getBounds() const;

    /// Return true if this node is a leaf.
    inline bool isLeaf() const;

private:
    inline AABCube getChildBounds(int) const;

    template<typename _T>
    void walkInsert(_T &&, Intersect, int, int, float);

	std::vector<T> m_elements;
    std::unique_ptr<OctreeNode> m_children[8];
    AABCube m_bounds;
    bool m_isLeaf;
};

////////////////////////////////////////////////////////////////////////////////
// DEFINITION SECTION
////////////////////////////////////////////////////////////////////////////////

template<class T>
OctreeNode<T>::OctreeNode(const AABCube &bounds)
: m_children{ nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr },
  m_bounds(bounds),
  m_isLeaf(true)
{ }

template<class T>
bool OctreeNode<T>::isLeaf() const
{
    return m_isLeaf;
}

template<class T>
const AABCube &OctreeNode<T>::getBounds() const
{
    return m_bounds;
}


template<class T>
void OctreeNode<T>::accept(std::function<void(const OctreeNode &)> visitChild) const
{
    for (auto &child: m_children)
    {
        if (child) visitChild(*child);
    }
}

template<class T>
void OctreeNode<T>::accept(std::function<void(const T &)> visitElement) const
{
    std::for_each(m_elements.begin(), m_elements.end(), visitElement);
}

template<class T>
template<class _T>
void OctreeNode<T>::insert(_T &&element,    
                           Intersect intersect,
                           int maxDepth,
                           float maxFill)
{
    return walkInsert(std::forward<_T>(element), intersect, 0, maxDepth, maxFill);
}

/// Returns the Axis Aligned Bounding Cube of a child node.
template<class T>
AABCube OctreeNode<T>::getChildBounds(int index) const
{
    assert(index >= 0 && index < 8);

    // If child exists, return its bounds.
    if (m_children[index])
    {
        return m_children[index]->m_bounds;
    }

    // Otherwise, compute them from the current parent node.
    AABCube childBounds;
    childBounds.halfWidth = m_bounds.halfWidth * 0.5f;
    childBounds.center = m_bounds.center;
    childBounds.center.x += ( (index & 1) ? 1.0f : -1.0f ) * childBounds.halfWidth;
    childBounds.center.y += ( (index & 2) ? 1.0f : -1.0f ) * childBounds.halfWidth;
    childBounds.center.z += ( (index & 4) ? 1.0f : -1.0f ) * childBounds.halfWidth;
    return childBounds;
}

/// Recursive walk through the tree for insertion purpose.
template<class T>
template<typename _T>
void OctreeNode<T>::walkInsert(_T &&element,
                               Intersect intersect,
                               int depth,
                               int maxDepth,
                               float maxFill)
{
    if (isLeaf())
    {
        // Should this leaf be subdivided?
        const float depthFillRatio = m_elements.size() / (float) (1+depth);
    	const bool shouldSubdivide = depthFillRatio > maxFill &&
                                     depth < maxDepth;
    	if (shouldSubdivide)
    	{
            // Yes, subdivide this leaf.. 
    		m_isLeaf = false;
            // .. and push elements to children.
            while (!m_elements.empty())
            {
                walkInsert(std::move(m_elements.back()), intersect, depth, maxDepth, maxFill);
                m_elements.pop_back();
            }
            walkInsert(std::forward<T>(element), intersect, depth, maxDepth, maxFill);
    	}
        else
        {
            // No, populate this leaf and return.
            m_elements.push_back(std::forward<T>(element));
        }
        return;
    }

    // Not a leaf: locate children overlapping the element to insert.
    int childIndex = 0;
    for (auto &child: m_children)
    {
        const auto childBounds(getChildBounds(childIndex));
        if (intersect(childBounds, element))
        {
            // Create child if needed.
            if (!child)
            {
                child = std::unique_ptr<OctreeNode>( new OctreeNode(childBounds) );
                assert(child);
            }
            // Walk down the tree under this child.
            child->walkInsert(std::forward<T>(element), intersect, depth+1, maxDepth, maxFill);
        }
        ++childIndex;
    }
}

} //namespace cpom

#endif // __OCTREENODE_H__
