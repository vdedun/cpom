#ifndef __MESH_H__
#define __MESH_H__

#include "Float3.h"

#include <vector>

namespace cpom
{

/// Type holding the vertex ids that form a mesh face.
struct Face
{
    /// Vector holding the indices in a list a vertex.
	std::vector<int> vertexIds;
};

/// Interface of Mesh required by cpom.
class Mesh
{
public:
    /// Return a vector with all vertices in the mesh.
    virtual std::vector<Point> getVertices() const = 0;

    /// Return a vector with all faces in the mesh.
    virtual std::vector<Face> getFaces() const = 0;
};

}

#endif // __MESH_H__
